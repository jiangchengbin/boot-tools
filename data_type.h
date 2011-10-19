/*
 *   comm_data.h - common data deal with
 *   Copyright (C) 2011 Joe Jiang (Jiangchengbin2@tom.com)
 * 
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 * 	 the Free Software Foundation;
 *
 */

#ifndef __DATATYPE_H__JOE
#define __DATATYPE_H__JOE

/* define some error code */
#define OPEN_ERR 1
#define CMD_ERR 2
#define DPT_OFFSET 0x01BE /*446*/


struct PCT{
	unsigned char boot;			//1
	unsigned char starthard;		//2
	short  start_s:6;				//3
	short  start_c:10;			//3-2,4
	unsigned char type;			//5
	unsigned char endhard;		//6
	short end_s:6;					//7
	short end_c:10;				//7-2,8
	unsigned int before_s;		//9,12
	unsigned int user_s;			//13,16
}PT;

struct DPT{
	struct PCT pt;
	struct DPT *next;
};

enum DPT_type{
	Linux=0x83,
	Extended=0x05,
	FAT32=0x0B
};

struct FILE_TYPE{
	unsigned char id;
	char *name;
};
#endif
