
CC=gcc
OBJ_FILE  =  cmdproc.o

all: demo lib

$(OBJ_FILE):%.o:%.c
	$(CC) -Wall $(EXTRA_CFLAGS)  -c $< -o $@ 


lib: $(OBJ_FILE)
	ar rsc  lib_cmd.a 	$(OBJ_FILE)

demo:  lib
	$(CC) -g -Wall -o uart_demo   uart_demo.c  lib_cmd.a  -lpthread -lrt

clean:
	rm -rf uart_demo *.a
