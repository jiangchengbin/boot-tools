/*
 *   comm_data.h - common data deal with
 *   Copyright (C) 2011 Joe Jiang (Jiangchengbin2@tom.com)
 * 
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 * 	 the Free Software Foundation;
 *
 */
 
#ifndef __COMM_DATA_H__JOE
#define __COMM_DATA_H__JOE

extern long EXTEND_POSITION;
extern char Read_File[];
extern char Save_File[];


extern void print_date(unsigned char *data,int len);
extern char * Read_MBR();
extern char *Read_DBR(struct PCT pt);

extern struct PCT Read_PT(char *data);
extern void Print_DPT(struct DPT dpt);

extern char *Read_Data(long position,long count);
char *Read_S(long position);
extern void Save_Data(unsigned char (*data)[] ,long count);

extern long File_Len();
extern void time_l_to_s(char *s,long data);
extern char *print_UUID(char *datap);


/* only for debug */
#ifdef DEBUG
extern void debug_print(char *string);
#endif

#endif
