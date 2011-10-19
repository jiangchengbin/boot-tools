/*
 *   comm_ext.c - extX common data deal with
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
#include <stdbool.h>

/* include our define file */
#include "ourhead.h"

/* print the data base */
void format_print_base(char *s,unsigned char s_offset,unsigned char e_offset,unsigned int data)
{	
	char t_s[30];
	sprintf(t_s,"%02X-%02X(%02d) 0x%%0%1dX",s_offset,e_offset,e_offset-s_offset+1,(e_offset-s_offset+1)*2);
	sprintf(s,t_s,data);	
}

void format_print_s(char *s,unsigned short s_offset,unsigned short e_offset,char *data)
{	
	if ( strlen( data) < 22 )
	{
		sprintf(s,"%02X-%02X(%02d) %s",s_offset,e_offset,e_offset-s_offset+1,data);
	}
	else
	{
		sprintf(s,"%02X-%02X(%02d) %s",s_offset,e_offset,e_offset-s_offset+1,"already print");
		printf("最后挂载路径:%s\n",data);	
	}
}


void format_print_Ex(char *s,unsigned char s_offset,unsigned char e_offset,unsigned int data1,unsigned int data2)
{	
	format_print_base(s,s_offset,e_offset,data1);
	sprintf(s,"%s(%01d)",s,data2);	
}

/* print the data by special format */
void format_print(char *s,unsigned char s_offset,unsigned char e_offset,unsigned int data)
{
	format_print_base(s,s_offset,e_offset,data);
	sprintf(s,"%s(%01d)",s,data);	
}

/* print the time information */
void format_print_Ex_t(char *s,unsigned char s_offset,unsigned char e_offset,unsigned int data)
{	
	format_print_base(s,s_offset,e_offset,data);
	char t_s[30];
	time_l_to_s(t_s,data);
	sprintf(s,"%s(%s)",s,t_s);	
}

/* print the extX file system support block information */
void print_super_block(struct super_block sb)
{
		const char *help[]={
		"文件系统总的i-节点数",
		"文件系统总块数",
		"文件系统预保留的快数",
		"空闲快数",
		"空闲i-节点数",
		"0号快组起始快号",
		"快大小（此值为1024左移动位数）",
		"片段大小（与快大小字段相同）",
		"每个快组所包含快数",
		"每个快组所包含片段数",
		"每个快组i-节点数",
		"最后挂载时间",
		"最后写入时间",
		"当前挂载数",
		"最大挂载数",
		"签名标志53EF",
		"文件系统状态(1-正常，3-有错误)",
		"错误处理方式",
		"辅版本级别",
		"最后进行一致性检查时间",
		"一致性检查间隔时间",
		"创建本文件系统的操作系统（0-linux)",
		"主版本级别(1-动态)",
		"默认UID保留块",
		"默认GID保留块",
		"第一个非保留i-节点",
		"每个i-节点结构大小",
		"本超级块所在的块组号",
		"兼容特征标志（0x10-自调节大小）",
		"非兼容特征标志",
		"只读兼容特征标志(1-稀疏超级快和组描述符表)",
		"文件系统ID",
		"卷名",
		"最后挂载路径",
		"位图使用运算法则",
		"文件再分配块数",
		"目录再分配块数",
		"未使用",
		"日志ID",
		"日志i-节点",
		"日志设备",
		"孤立i-节点表头",
		"未使用",
	};
	char data[50][50];
	memset(data,0,sizeof(data));
	int i=0;
	format_print(data[i++],0x00,0x03,sb.total_Node);
	format_print(data[i++],0x04,0x07,sb.total_Blocks);
	format_print(data[i++],0x08,0x0B,sb.retain_Blcoks);
	format_print(data[i++],0x0C,0x0F,sb.free_Blocks);
	format_print(data[i++],0x10,0x13,sb.free_Node);
	format_print(data[i++],0x14,0x17,sb.No_0_Block);
	format_print_Ex(data[i++],0x18,0x1B,sb.block_Size,1024 << sb.block_Size);
	format_print_Ex(data[i++],0x1C,0x1F,sb.part_Size,1024 << sb.part_Size);
	format_print(data[i++],0x20,0x23,sb.block_Group_Blocks);
	format_print(data[i++],0x24,0x27,sb.block_Group_Parts);
	format_print(data[i++],0x28,0x2B,sb.block_Group_Nodes);
	
	
	format_print_Ex_t(data[i++],0x2C,0x2F,sb.last_Mount_Time);
	format_print_Ex_t(data[i++],0x30,0x33,sb.last_Write_Time);
	
	
	format_print(data[i++],0x34,0x35,sb.current_Mounts);
	format_print(data[i++],0x36,0x37,sb.max_Mounts);
	format_print(data[i++],0x38,0x39,sb.signature_Logo);
	format_print(data[i++],0x3A,0x3B,sb.filesystem_State);
	format_print(data[i++],0x3C,0x3D,sb.err_deal_with);
	format_print(data[i++],0x3E,0X3F,sb.assist_Version);
	
	format_print_Ex_t(data[i++],0x40,0x43,sb.last_Check_Time);
	format_print(data[i++],0x44,0x47,sb.check_Interval_Time);
	
	format_print(data[i++],0x48,0x4B,sb.create_os);
	format_print(data[i++],0x4C,0x4F,sb.main_Version);
	format_print(data[i++],0x50,0x51,sb.UID_Block);
	format_print(data[i++],0x52,0x53,sb.GID_Block);
	format_print(data[i++],0x54,0x57,sb.No_1_Noretain_Node);
	format_print(data[i++],0x58,0x59,sb.node_Size);
	format_print(data[i++],0x5A,0x5B,sb.super_Block_Group);
	format_print(data[i++],0x5C,0x5F,sb.signature_Compatible);
	format_print(data[i++],0x60,0x63,sb.signature_Uncompatible);
	format_print(data[i++],0x64,0x67,sb.signature_Readonly_Compatible);

	//char data 
	format_print_s(data[i++],0x68,0x77,"no print now"/*sb.filesytem_ID*/);
	format_print_s(data[i++],0x78,0x87,sb.volume_Name);
	format_print_s(data[i++],0x88,0xC7,sb.last_Mount_Path);
	format_print(data[i++],0xC8,0xCB,sb.bitmap_rules);
	format_print(data[i++],0xCC,0xCC,sb.file_Redistribution_Blocks);
	format_print(data[i++],0xCD,0xCD,sb.dir_Redistribution_Blocks);
	format_print(data[i++],0xCE,0xCF,sb.no_Used1);
	//char data 
	format_print_s(data[i++],0xD0,0xDF,sb.log_ID);
	format_print(data[i++],0xE0,0xE3,sb.log_Node);
	format_print(data[i++],0xE4,0xE7,sb.log_drive);
	format_print(data[i++],0xE8,0xEB,sb.isolate_Node_Table_Head);
	format_print_s(data[i++],0xEC,0x3FF,"no print now"/*sb.no_Used2*/);
	

	int count=i,max=0,tmp;
	for ( i=0;i<count;i++){ tmp=strlen(data[i]); max=max < tmp? tmp:max;}
	
	printf("文件系统UUID: %s\n",print_UUID(sb.filesytem_ID));
	for ( i=0;i<count;i++)
	{
		printf("%s",data[i]);
		for (tmp=max-strlen(data[i])+3;tmp>0;tmp--) printf(" ");
		printf("%s\n",help[i]);
	}
}


/* print the group block infomation */
void print_group_block(struct group_block gb)
{
	const char *help[]={
	"块位图起始地址(块号)",
	"i-节点位图起始地址(块号)",
	"i-节点表起始地址(块号)",
	"该块组中的空闲块数",
	"该块组中的空闲i-节点数",
	"该块组中的目录数",
	"未使用",
	};
		char data[50][50];
		memset(data,0,sizeof(data));
		int i=0;
		format_print(data[i++],0x00,0x03,gb.bitmap_Start_Block);
		format_print(data[i++],0x04,0x07,gb.nodemap_Start_Block);
		format_print(data[i++],0x08,0x0B,gb.nodetable_Start_Blcoks);
		format_print(data[i++],0x0C,0x0D,gb.free_Blocks);
		format_print(data[i++],0x0E,0x0F,gb.free_Nodes);
		format_print(data[i++],0x10,0x11,gb.free_Dir);
		//*format_print_s(data[i++],0x12,0x1F,"no print now"/*gb.no_Used*/);
		int count=i,max=0,tmp,spaceCount=4;
		for ( i=0;i<count;i++){ tmp=strlen(data[i]); max=max < tmp? tmp:max;}
		for ( i=0;i<count;i++)
		{
				printf("%s",data[i]);
				for (tmp=max-strlen(data[i])+spaceCount;tmp>0;tmp--) printf(" ");
				printf("%s\n",help[i]);
		}
}

struct group_block get_group_block(struct super_block sb,long index)
{
	struct group_block data;
	long blockSize=1024 << sb.block_Size;
	long startp=blockSize*(sb.No_0_Block+1);
	startp+=index*32;
	unsigned char *t_data;
	t_data=Read_Data(startp,32);
	memcpy(&data,t_data,sizeof(data));
	return data;
}

/* print the extX file system infomation */
void print_extx_info()
{
		struct super_block superblock;
		struct group_block groupblock;
		unsigned char *t_data;
		t_data=Read_Data(1024,1024);
		memcpy(&superblock,t_data,sizeof(superblock));
		print_super_block(superblock);
		
		int i,groupCount=superblock.total_Blocks / superblock.block_Group_Blocks+1;
		for (i=0;i<groupCount;i++)
		{
			printf("BlockGroup=%01d\n",i);
			groupblock=get_group_block(superblock,i);
			print_group_block(groupblock);
		}
}

/* parse the extX filesystem */
void parse_ext_fs(char *File)
{
	strcpy(Read_File,File);
    print_extx_info();
}

/* judge the extX filesystem */
int is_ext_fs(char *File)
{
	strcpy(Read_File,File);
	struct super_block superblock;
	unsigned char *t_data;
	t_data=Read_Data(1024,1024);
	memcpy(&superblock,t_data,sizeof(superblock));
	if ( superblock.signature_Logo == 0xEF53 )
	{
		return true;
	}
	else
	{
		return false;
	}
}
