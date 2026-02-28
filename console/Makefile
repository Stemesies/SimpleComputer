SOURCES= ${shell find ./ -name '*.c'}
OBJECTS= $(addprefix .build/, $(SOURCES:.c=.o))

BIN_NAME= .bin/console.bin

LIB = ../mySimpleComputer/.bin/libMySimpleComputer.a
LIB2 = ../myTerm/.bin/libMyTerm.a

COMPILE= gcc -g -c -Wall -Werror -Wextra -I ../
LINK= gcc -g -Wall -Werror -Wextra -I ../ 

all: ${BIN_NAME}

${BIN_NAME}: ${OBJECTS} ${LIB} ${LIB2}
	@mkdir -p $(@D)
	${LINK} $^ -o ${BIN_NAME}

.build/%.o: %.c
	@mkdir -p $(@D)
	${COMPILE} $< -o $@

run:
	./${BIN_NAME}

clean:
	-@rm -r .bin/
	-@rm -r .build/