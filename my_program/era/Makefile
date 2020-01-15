##
## Internship client Makefile
##
CC		= gcc
CFLAGS		= `pkg-config --cflags gtk+-3.0` -Wextra -g
LIBS		= `pkg-config --libs gtk+-3.0 gmodule-export-2.0`
SRCS		= intern_main.c cb_login_open.c cb_login.c cb_com_regis_open.c cb_com_regis.c cb_teacher_isentry_open.c cb_teacher_isentry.c setup_connect.c common_func.c 
HDRS            = intern_client.h login.h com_isreg_func.h teacher_isentry_func.h
OBJS		= $(SRCS:.c=.o)
PROGRAM		= intern 

all:		$(PROGRAM)

$(PROGRAM):	$(OBJS) $(HDRS) 
		$(CC) $(OBJS) $(LIBS) -o $(PROGRAM)

clean:
		rm -f *.o *~ $(PROGRAM)

###
