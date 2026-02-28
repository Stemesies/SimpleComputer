SOURCES= ${shell find ./ -name '*.c'}
OBJECTS= $(addprefix .build/, $(SOURCES:.c=.o))

LIB_NAME= .bin/libMyTerm.a

COMPILE= gcc -Wall -Werror -Wextra -I ../ -g -c
LINK= ar rcs

all: ${LIB_NAME}

${LIB_NAME}: ${OBJECTS}
	@mkdir -p $(@D)
	${LINK} ${LIB_NAME} $^

.build/%.o: %.c
	@mkdir -p $(@D)
	${COMPILE} $< -o $@

clean:
	-@rm -r .bin/
	-@rm -r .build/