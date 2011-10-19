/*
 *   readhex.c -
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

/* include our head files */
#include "ourhead.h"

/* print the Hex Data use specific format string */
void format_print_Hex_Data(char *format,char *format_split,unsigned char *data,long l)
{
	long i=0;
	unsigned char j;
	char s[40];
	do
	{
		j=data[i++];
		printf(format,j);
		if ( i == l) break;
		printf(format_split);
	}while ( 1 );
}

/* print Shell format Hex Data */
void print_Hex_Data_Shell(unsigned char *data,long l)
{
	format_print_Hex_Data("\\\\x%02X","",data,l);
}

/* print C format Hex Data */
void print_Hex_Data_C(unsigned char *data,long l)
{
	format_print_Hex_Data("0x%02X",",",data,l);
}

unsigned char t_data[]={0xEB,0x48,0x90};
		
/* tell use how to use me */		
void print_user_input_err()
{
	fprintf(stderr,"plese input readhex filename [[startposition] len ][type]\n");
	fprintf(stderr,"type can use c ,s(scripit) or h(hex)\n");
}
		
/* the main */
void main (int argc ,char **argv)
{
	long start=0,len=0;
	char c_type='c';
	
	memcpy(&c_type,argv[argc-1],1);
	if ( argc > 2)
	{
		if ( isdigit(c_type) ) { c_type='c';}
		else { argc--;}
	}
	else
	{
		c_type='c';
	}
		
#ifdef DEBUG
	printf("argc=%d\n",argc);
#endif
	switch ( argc )
	{
		case 4:
			start=atoi(argv[2]);
			len=atoi(argv[3]);
		case 3:if ( len == 0 ) len=atoi(argv[2]);
		case 2:break;
		default:
			print_user_input_err();
			exit(-1);
	}
	strcpy(Read_File,argv[1]);
	if (len == 0) len=File_Len();
	
	//read hex data from a file
#ifdef DEBUG
	printf("open filename=%s\n",Read_File);
#endif
	unsigned char *data_p=Read_Data(start,len);
	
	
	//switch hexdata the print type 
	switch (c_type)
	{
		case 'c':
			print_Hex_Data_C(data_p,len);
			break;
		case 's':
			print_Hex_Data_Shell(data_p,len);
			break;
		case 'h':
			print_date(data_p,len);
			break;
		default:
			print_user_input_err();
			exit(-1);
	}

	fflush(stdout);
	fprintf(stderr,"\n");
}
