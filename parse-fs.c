/*
 *   parse-fs.c - parse the file system
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

/* include our define file */
#include "ourhead.h"

/* parse file system */
void parse_file_system(char *file)
{
	int ret;
	if (is_ext_fs(file)) {parse_ext_fs(file);}
	else  { fprintf(stderr,"unmae file system \n"); exit -1; }
}

/* the main */
int main(int argc ,char ** argv)
{
	switch ( argc )
	{
		case 2:
			parse_file_system(argv[1]);
			break;
		default:
			fprintf(stderr,"plese input parse-fs filename\n");
			return -1;
	}
	
#ifdef DEBUG
	printf("safe quit \n");
#endif
	return 0;
}
