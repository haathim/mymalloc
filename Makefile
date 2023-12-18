
SOURCE=myMalloc.c main.c
BIN=main
FLAGS= -Wall -Werror

all: ${BIN}


${BIN}: ${SOURCE}
	gcc -o $@ $^ ${FLAGS}

clean: 
	rm -rf ${BIN}