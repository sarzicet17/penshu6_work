##
## Internship client Makefile
##
CC		= gcc
CFLAGS		= `pkg-config --cflags gtk+-3.0`
LIBS		= `pkg-config --libs gtk+-3.0 gmodule-export-2.0`
SRCS		= intern_main.c cb_login_open.c cb_login.c cb_teacher_isentry.c cb_com_regis.c cb_com_regis_open.c cb_teacher_isentry_open.c
HDRS            = intern_client.h login.h com_isreg_func.h teacher_isentry_func.h
OBJS		= $(SRCS:.c=.o)
PROGRAM		= intern 

all:		$(PROGRAM)

$(PROGRAM):	$(OBJS) $(HDRS) 
		$(CC) $(OBJS) $(LIBS) -o $(PROGRAM)

clean:
		rm -f *.o *~ $(PROGRAM)

###
