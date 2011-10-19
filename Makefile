#################################################################
#                                                               #
# Author:           Joe Jiang                                   #
# Lable:            Makefile                                    #
# Information:      Some tools for boot use                     #
# Create Date:      2011-10-14                                  #
# Modify Date:      2011-10-14                                  #
# Version:          v1.0                                        #
#                                                               #
#################################################################
VERSION = 1.0
DESTDIR =
PREFIX =/usr
CC=cc
#CC=@cc

BINDIR = $(PREFIX)/bin
SBINDIR = $(PREFIX)/sbin
SRCDIR= $(PREFIX)/include/boot-tools
LIBDIR= lib/

PROGS=	setmbr \
		readhex \
		parse-fs

setmbr_SRCS=setmbr.c comm_data.c dbr_reader.c parse_command.c install_mbr.c 
readhex_SRCS=readhex.c comm_data.c
parse-fs_SRCS=parse-fs.c comm_data.c comm_ext.c

setmbr_OBJS=$(setmbr_SRCS:.c=.o)
readhex_OBJS=$(readhex_SRCS:.c=.o)
parse-fs_OBJS=$(parse-fs_SRCS:.c=.o)

all_OBJS=$(setmbr_OBJS) $(readhex_OBJS) $(parse-fs_OBJS)
mrproper=clean $(PROGS)

#===========================
#编译流程控制
#==========================
default:$(mrproper)

all:$(PROGS)

setmbr:$(setmbr_OBJS)

readhex:$(readhex_OBJS)

parse-fs:$(parse-fs_OBJS)

install:$(PROGS)
	mkdir -p $(DESTDIR)/$(BINDIR)
	install -m 0755 $(PROGS) $(DESTDIR)/$(BINDIR)

devel_install:$(PROGS)
	mkdir -p $(DESTDIR)/$(SRCDIR)
	mkdir -p $(DESTDIR)/$(LIBDIR)

clean:
	@$(RM) $(all_OBJS) $(PROGS)
