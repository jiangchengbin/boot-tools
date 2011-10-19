/*
 *   install_mbr.c - 
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

/* include our define file */
#include "ourhead.h"

/*要写入MBR的数据*/
unsigned char binary_data[]={
		#include "grub4dos.dat"
};

/*读分区表数据*/
void Read_MBR_DPT()
{
	char *data_p=Read_MBR(); 		//读MBR
	if ( data_p ==NULL ){ printf("Read MBR fail when read DPT \n"); exit(1);}
	
	int i;
	for (i=0;i<0x40;i++)
	{
		binary_data[i+DPT_OFFSET]=data_p[i+DPT_OFFSET];
	}
}

/*安装MBR*/
void install_mbr()
{
    Read_MBR_DPT();
    Save_Data(&binary_data ,sizeof(binary_data));

#ifdef DEBUG
    printf("===Install MBR to file %s sucess !!\n",Save_File);
#endif
}
