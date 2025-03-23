CC	=	gcc
CFLAGS	=	-Wall	-Wextra

TARGET	=	program.exe

SRCS	=	main.c	proje.c
OBJS	=	main.o	proje.o

$(TARGET):	$(OBJS)
	$(CC)	$(OBJS)	-o	$(TARGET)

main.o:	main.c	proje.h
	$(CC)	$(CFLAGS)	-c	main.c

proje.o:	proje.c	proje.h
	$(CC)	$(CFLAGS)	-c	proje.c

clean:
	del	*.o	$(TARGET)

run:	$(TARGET)
	$(TARGET)

.PHONY:	clean	run	
