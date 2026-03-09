SOURCES= ${shell find ./ -name '*.c'}
OBJECTS= $(addprefix .build/, $(SOURCES:.c=.o))

LIB_NAME= .bin/libMyReadKey.a
# -Wall -Werror -Wextra
COMPILE= gcc  -I ../ -g -c
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
