/*
 *   parse_command.c - Parsing user input parameters
 *   Copyright (C) 2011 Joe Jiang (Jiangchengbin2@tom.com)
 * 
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 * 	 the Free Software Foundation;
 *
 */
 
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

/* include our head files */
#include "ourhead.h"

//Long option define
struct option opts[]={
		{"read",1,0,'r'},
		{"install",1,0,'i'},
		{"help",0,0,'h'},
		{NULL,0,0,0},
};

// Long option help infomation define
const char *opts_help[]={
		"Set the file name for read data",
		"Set the file name to install data",
		"Show the help infomation for setmbr",
};

/* Parsing user input parameters */
void handle_opt_command(int *argc,char ***argv)
{
	int i,parameters=0;
	// Parsing the user input command
	struct option *opt;
	const char **hlp;
	char *l_opt_arg;
	int max,size;
	
#ifdef DEBUG
	printf("===Entry parse command====================\n");
#endif
	
	for(;;){
		int c;
		c=getopt_long(*argc,*argv,"i:r:h",opts,NULL);
		if(c == -1) break;
		
#ifdef DEBUG
		printf("===Parse command -%c ...\n",c);
#endif

		switch(c){
		case 'i':
			l_opt_arg=optarg;
			char **m_opt1=*argv;
			strcpy(Save_File,m_opt1[optind-1]);
#ifdef DEBUG
			printf("===Set Save_File=%s\n",Save_File);
#endif
			parameters++;
			break;
		case 'r':
			l_opt_arg=optarg;
			char **m_opt=*argv;
			strcpy(Read_File,m_opt[optind-1]);
#ifdef DEBUG
			printf("===Set Read_File=%s\n",Read_File);
#endif
			parameters++;
			break ;
		case 'h':
		default:
			/* 打印命令使用说明 */
			fprintf(stderr,"Usage: setmbr [--install filename ] [ --read filename ] \n");
			max=0;
			for (opt = opts; opt->name; opt++){
				size = strlen(opt->name);
				if ( size > max){
					max =size;
				}
			}
			for (opt = opts,hlp = opts_help ; opt->name;opt++,hlp++){
				fprintf(stderr,"  -%c, --%s", opt->val, opt->name);
				size=strlen(opt->name);
				for (;size < max;size++)
					fprintf(stderr," ");
				fprintf(stderr,"  %s\n",*hlp);
			}
			exit(CMD_ERR);	
		}
	}
	if ( parameters == 0 ){ handle_no_opt_command(*argc,*argv); }
}

/* Parsing the no option command */
void handle_no_opt_command(int argc,char **argv)
{
#ifdef DEBUG
	debug_print("===Entry parse no opt command=============\n");
#endif
	switch(argc){
	case 1: break;
	case 2:
		strcpy(Read_File,argv[1]);
#ifdef DEBUG
		printf("===argv[1]=%s\n",argv[1]);
		printf("===Set Read_File=%s\n",Read_File);
#endif
		break;
	default:
		fprintf(stderr,"Input parameter is incorrect \nplease input parameter -h or --help see help infomation	\n");
		exit(CMD_ERR);
	}
} 
