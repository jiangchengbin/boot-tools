/*
 *   dbr_reader.c -  
 *   Copyright (C) 2011 Joe Jiang (Jiangchengbin2@tom.com)
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 * 	 the Free Software Foundation;
 *
 */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ourhead.h"

int Read_Next_PT_Ex(char *data)
{
	struct PCT pt;
	memcpy(&pt,data,sizeof(struct PCT));
	
	char *result=Read_DBR(pt);
	memcpy(data,result+DPT_OFFSET/*446*/,64);

#ifdef DEBUG	
	printf("Read S DPT data\n");
	print_date(data,64);
#endif
	return 0;
}

/*	find next PCT from a DPT data */
struct DPT *Read_Next_PT(char *data)
{
	struct DPT *result=malloc(sizeof(struct DPT));
	unsigned char tmp_data[64];
	memset(tmp_data,0,64);
	memcpy(tmp_data,data+16,48);
	memcpy(data,tmp_data,64);
	
	(*result).pt=Read_PT(data);
	(*result).next=NULL;
	
	// deal with result
	unsigned char t_type=(*result).pt.type;
	switch ( t_type )
	{
		case 0x07:
		case 0x0b:
		case 0x83:
		case 0x82:
		case 0x8e:
			(*result).next=Read_Next_PT(data);
			return result;
		case 0x05:
		case 0x0f:
			if (Read_Next_PT_Ex(data) == 0 )
			{
				struct DPT *now=malloc(sizeof(struct DPT));
				(*now).pt=Read_PT(data);
				(*now).next=Read_Next_PT(data);
				(*result).next=now;
				return result;
			}
			else
			{
				return result;
			}
	}
	return NULL;
}

struct DPT Read_DPT()
{
	struct DPT dpt;
	
	/* 准备阶段 */
	char *tmp_data_p=malloc(64);
	if ( tmp_data_p==NULL ){ printf("malloc memory fail when read DPT \n"); exit(1);}
	
	char *data_p=Read_MBR(); 		//读MBR
	if ( data_p ==NULL ){ printf("Read MBR fail when read DPT \n"); exit(1);}
	
	memcpy(tmp_data_p,data_p+DPT_OFFSET/*446*/,64);
	dpt.pt=Read_PT(tmp_data_p);
	dpt.next=Read_Next_PT(tmp_data_p);
	return dpt;
}
