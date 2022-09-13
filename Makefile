VPATH = include

HEADS = fileop.h booklist.h bookop.h debug.h winpos.h
OBJECTS = fileop.o booknode.o bookinfo.o bookop.o main.o
LIB = -I include/
CC = gcc
DEBUG = gdb
FLAGS = -c -o
DEBUG_FLAG = #-g -Wall 
#!!!注意release版去掉把DEBUG_FLAG 定义为空,还有debug.h中的选项
all:main clean

debug:main clean
	$(DEBUG) main

.PHONY:clean
clean:
	del $(OBJECTS)

main:$(OBJECTS) $(HEADS)
	$(CC)	$(LIB) 	$(OBJECTS) 	$(DEBUG_FLAG) -o main
fileop.o:fileop.c fileop.h
	$(CC) 	$(LIB) 	fileop.c 	$(DEBUG_FLAG) $(FLAGS) fileop.o
main.o:main.c $(HEAD)
	$(CC) 	$(LIB) 	main.c 		$(DEBUG_FLAG) $(FLAGS)  main.o
booknode.o:booknode.c booklist.h
	$(CC) 	$(LIB) 	booknode.c 	$(DEBUG_FLAG) $(FLAGS) booknode.o
bookinfo.o:bookinfo.c booklist.h
	$(CC) 	$(LIB) 	bookinfo.c 	$(DEBUG_FLAG) $(FLAGS) bookinfo.o
bookop.o: bookop.c bookop.h
	$(CC) 	$(LIB) 	bookop.c 	$(DEBUG_FLAG) $(FLAGS) bookop.o