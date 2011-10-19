/*
 *   comm_data.c - common data deal with
 *   Copyright (C) 2011 Joe Jiang (Jiangchengbin2@tom.com)
 * 
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 * 	 the Free Software Foundation;
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


#include "ourhead.h"

/* initialization value  */
long EXTEND_POSITION=0;
char Read_File[]="/dev/sda";
char Save_File[]="grub_mbr";

/* only used by me */
char tmp_data[50];
void Print_PCT( struct PCT (*data)[] );

/* the table of file systme type */
struct FILE_TYPE F_Tab[]={
    {0x05,"Extended"},
    {0x07,"HPFS/NTFS/exFAT"},
    {0x0F,"Extended"},
    {0x82,"Linux swap / Solaris"},
    {0x83,"Linux"},
    {0x0B,"FAT32"}
};

/*  open the device file for read date  */
long File_Len()
{
    long filesize=0;
    FILE *fp=fopen(Read_File ,"rb");
	if (fp == NULL)
	{
		fprintf(stderr,"open file %s error \n",Read_File);
		exit (OPEN_ERR);
	}
	fseek(fp,0,SEEK_END);
	filesize=ftell(fp);
	fclose(fp);
	return filesize;
}

/* open the device file for read date */
char *Read_Data(long position,long count)
{
	char *data_p=malloc(count);
	if ( data_p==NULL) 
	{
		fprintf(stderr,"can't malloc memory to readfile %s\n",Read_File);
		exit (OPEN_ERR);
	}
	
	FILE *fp=fopen(Read_File ,"rb");
	if (fp == NULL)
	{
		fprintf(stderr,"open file %s error \n",Read_File);
		exit (OPEN_ERR);
	}
	fseek(fp,position,SEEK_SET);
	fread(data_p,1,count,fp);
	fclose(fp);
	return data_p;
}

/* open the device file for save date */
void Save_Data(unsigned char (*data)[] ,long count)
{
	FILE *fp=fopen(Save_File ,"wb");
	if (fp == NULL)
	{
		fprintf(stderr,"create file %s error \n",Save_File);
		exit (OPEN_ERR);
	}
	fwrite(*data,1,count,fp);
	fclose(fp);
}


/* Read section data*/
char *Read_S(long position)
{
	return Read_Data(position*512,512);
}

/*  print the data  */ 
void print_date(unsigned char *data,int len)
{
	int i,j,l;
	l=len / 16;
	for (j=0;j<l;++j)
	{
		printf("%08X ",(unsigned char)j);
		for ( i=0;i<16;++i)
		{
			printf("%02X ",data[i+j*16]);
		}
		printf("\n");
	}
	if ( len > 16*l )
	{
		l=len-16*l;
		printf("%08X ",(unsigned char)j);
		for ( i=0;i<l;++i)
		{
			printf("%02X ",data[i+j*16]);
		}
		printf("\n");
	}
}

/* Read MBR data */
char *Read_MBR()
{
	return Read_S(0);
}

/*  Read DBR data by PCT*/
char *Read_DBR(struct PCT pt)
{
	char *result;
	long p=pt.before_s;
#ifdef DEBUG
	printf("===Will Read S %ld\n",p);
#endif
	if ( EXTEND_POSITION == 0 )
		EXTEND_POSITION=p;
	else
		p+=EXTEND_POSITION;
	result=Read_S(p);
#ifdef DEBUG
	print_date(result,512);
	printf("===Read S end\n",p);
#endif
	return result;
}

/* Read a PCT data from DPT*/
struct PCT Read_PT(char *data)
{
	struct PCT pt;
	memcpy(&pt,data,16);
	return pt;
} 

/* query the filesystem type */
char *query_type(unsigned char data)
{
	char *type="Unknown";
	int i,len;
	struct FILE_TYPE ft;
	len=sizeof(F_Tab) / sizeof(ft);
	for(i=0;i<len;i++)
	{
		ft=F_Tab[i];
		if (data==ft.id )
		{
			type=ft.name;
			break;
		}
	}
	return type;
}

/* print the PCT data from a PCT array */
void Print_PCT( struct PCT (*data)[] )
{
	int i=0,j=0;
	struct PCT pt=(*data)[i];
	printf("   Deivce   Boot     Start         End      Blocks           Id   System \n" );
	while ( pt.type != 0)
	{
		printf("%s%d  ",Read_File,++j);
		if ( pt.type == 0x0f || pt.type == 0x05 && i < 3) j=4;
		if (pt.boot == 0x80) printf("  *");
		printf("\t%10d  ",pt.before_s);
		printf("%10d\t",pt.before_s+pt.user_s-1);
		float f=pt.user_s/2/1024;f=f/1024;
		printf("%10d(%5.1fGB)  ",pt.user_s/2,f);
		printf("%02X   ",pt.type);
		printf("%s ",query_type(pt.type));
		printf(" \n");
		pt=(*data)[++i];
	}
}

/* print DPT data from a DPT struct */
void Print_DPT(struct DPT dpt)
{
	struct DPT *now=&dpt;
	struct DPT *next;
	struct PCT pt;
	struct PCT DPT_Array[20];
	int i=0;
	
	memset(DPT_Array,0,sizeof(DPT_Array));
	bool extend_state=false;
	unsigned int extend_s = 0;
	do
	{
		next=(*now).next;
		pt=(*now).pt;
		now=next;
		if ( pt.type == 0x05 || pt.type == 0x0f ) 
		{
			extend_s+=pt.before_s;
			if ( extend_state==true) continue ;
			extend_state=true;
		}
		if ( extend_state==true && pt.type != 0x05 && pt.type != 0x0f ) { pt.before_s+=extend_s;}
		DPT_Array[i++]=pt;
	}while ( now != NULL);
	Print_PCT(&DPT_Array);
}


void time_l_to_s(char *s ,long data)
{
	strftime(s,30,"%Y-%m-%d %H:%M:%S",localtime(&data));  
}

/* print a UUID data */
char *print_UUID(char *datap)
{
	unsigned char d[16];
	memcpy(&d,datap,16);
	memset(tmp_data,0,sizeof(tmp_data));
	int i=16;
	/* print UUID data */
	sprintf(tmp_data,"%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
			d[--i],d[--i],d[--i],d[--i],d[--i],d[--i],d[--i],d[--i],d[--i],d[--i],d[--i],d[--i],d[--i],d[--i],d[--i],d[--i]);
	return tmp_data;
}

/* only for debug */
#ifdef DEBUG
void debug_print(char *string)
{
	printf(string);
	fflush(stdout);
}
#endif
