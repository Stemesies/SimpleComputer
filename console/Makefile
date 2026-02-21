LIB = ../mySimpleComputer/libMySimpleComputer.a

COMPILE= gcc -g -c -I ../
LINK= gcc -g -Wall -L../mySimpleComputer -lMySimpleComputer -I ../ 

DEPENDENCIES= ${shell find ./ -name '*.c'}
OBJECTS= $(DEPENDENCIES:.c=.o)
BIN_NAME= console.bin

all: ${BIN_NAME}

${BIN_NAME}: ${OBJECTS} ${LIB}
	${LINK} $^ -o ${BIN_NAME}

%.o: %.c
	${COMPILE} $< -o $@

run:
	./${BIN_NAME}

clean:
	find -name '${BIN_NAME}' -delete
