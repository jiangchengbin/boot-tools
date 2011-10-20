/*
 *   dbr_reader.h -  
 *   Copyright (C) 2011 Joe Jiang (Jiangchengbin2@tom.com)
 * 
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 * 	 the Free Software Foundation;
 *
 */
 
#ifndef __DBR_READER_H__JOE
#define __DBR_READER_H__JOE

extern struct DPT *Read_Next_PT(char *data);
extern int Read_Next_PCT_Ex(char *data);
extern struct DPT Read_DPT();

#endif
