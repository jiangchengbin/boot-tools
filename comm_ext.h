/*
 *   comm_ext.h 
 *   Copyright (C) 2011 Joe Jiang (Jiangchengbin2@tom.com)
 * 
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 * 	 the Free Software Foundation;
 *
 */

#ifndef __COMM_EXT_H__JOE
#define __COMM_EXT_H__JOE

struct super_block{
	unsigned int total_Node;
	unsigned int total_Blocks;
	unsigned int retain_Blcoks;
	unsigned int free_Blocks;
	unsigned int free_Node;
	unsigned int No_0_Block;
	unsigned int block_Size;
	unsigned int part_Size;/*=block_Size */;
	unsigned int block_Group_Blocks;
	unsigned int block_Group_Parts;
	unsigned int block_Group_Nodes;
	unsigned int last_Mount_Time;
	unsigned int last_Write_Time;
	unsigned short current_Mounts;
	unsigned short max_Mounts;
	unsigned short signature_Logo; /*53EF*/
	unsigned short filesystem_State;
	unsigned short err_deal_with;
	unsigned short assist_Version;
	unsigned int last_Check_Time;
	unsigned int check_Interval_Time;
	unsigned int create_os;
	unsigned int main_Version;
	unsigned short UID_Block;
	unsigned short GID_Block;
	unsigned int No_1_Noretain_Node;
	unsigned short node_Size;
	unsigned short super_Block_Group;
	unsigned int signature_Compatible;
	unsigned int signature_Uncompatible;
	unsigned int signature_Readonly_Compatible;
	char filesytem_ID[16];
	char volume_Name[16];
	char last_Mount_Path[64];
	unsigned int bitmap_rules;
	unsigned char file_Redistribution_Blocks;
	unsigned char dir_Redistribution_Blocks;
	unsigned short no_Used1;
	char log_ID[16];
	unsigned int log_Node;
	unsigned int log_drive;
	unsigned int isolate_Node_Table_Head;
	char no_Used2[788];
};

struct group_block{
	unsigned int bitmap_Start_Block;
	unsigned int nodemap_Start_Block;
	unsigned int nodetable_Start_Blcoks;
	unsigned short free_Blocks;
	unsigned short free_Nodes;
	unsigned short free_Dir;
	char no_Used[14];
};

extern void print_super_block(struct super_block sb);
extern void print_group_block(struct group_block gb);
extern void print_extx_info();
extern void parse_ext_fs(char *File);
extern int is_ext_fs(char *File);

#endif
