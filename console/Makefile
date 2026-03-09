ARGS=

SOURCES= ${shell find ./ -name '*.c' ! -name 'font.c'}
OBJECTS= $(addprefix .build/, $(SOURCES:.c=.o))

BIN_NAME= .bin/console.bin
BIN_NAME2= .bin/font.bin

LIB = ../mySimpleComputer/.bin/libMySimpleComputer.a
LIB2 = ../myBigChars/.bin/libMyBigChars.a
LIB3 = ../myTerm/.bin/libMyTerm.a


COMPILE= gcc -g -c -Wall -Werror -Wextra -I ../
LINK= gcc -g -Wall -Werror -Wextra -I ../ 

all: ${BIN_NAME} ${BIN_NAME2}

${BIN_NAME}: ${OBJECTS} ${LIB} ${LIB2} ${LIB3}
	@mkdir -p $(@D)
	${LINK} $^ -o ${BIN_NAME}

${BIN_NAME2}: font.c ${LIB2} ${LIB3}
	@mkdir -p $(@D)
	${LINK} $^ -o ${BIN_NAME2}

.build/%.o: %.c
	@mkdir -p $(@D)
	${COMPILE} $< -o $@

run:
	./${BIN_NAME} ${ARGS}

run-font:
	./${BIN_NAME2}

clean:
	-@rm -r .bin/
	-@rm -r .build/