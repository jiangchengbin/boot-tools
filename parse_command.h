/*
 *   parse_command.h - 
 *   Copyright (C) 2011 Joe Jiang (Jiangchengbin2@tom.com)
 * 
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 * 	 the Free Software Foundation;
 *
 */
 
#ifndef __PARSE_COMMAND_H__JOE
#define __PARSE_COMMAND_H__JOE

extern void handle_opt_command(int *argc,char ***argv);
void handle_no_opt_command(int argc,char **argv);

#endif
