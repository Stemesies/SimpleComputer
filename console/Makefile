LIB = ../mySimpleComputer/libMySimpleComputer.a
LIB2 = ../myTerm/libMyTerm.a

COMPILE= gcc -g -c -I ../
LINK= gcc -g -Wall -I ../ 

DEPENDENCIES= ${shell find ./ -name '*.c'}
OBJECTS= $(DEPENDENCIES:.c=.o)
BIN_NAME= console.bin

all: ${BIN_NAME}

${BIN_NAME}: ${OBJECTS} ${LIB} ${LIB2}
	${LINK} $^ -o ${BIN_NAME}

%.o: %.c
	${COMPILE} $< -o $@

run:
	./${BIN_NAME}

clean:
	find -name '${BIN_NAME}' -delete
