/*
 *   setmbr.c - set the MBR and Partition table
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

int main(int argc ,char ** argv)
{

	/* parse command */
	handle_opt_command(&argc,&argv);	//解析用户输入的参数
	struct DPT dpt=Read_DPT(); 			//读分区表
	Print_DPT(dpt);						//打印分区表
	install_mbr();						//安装MBR
	
#ifdef DEBUG
	printf("safe quite \n");
#endif
	return 0;
}
