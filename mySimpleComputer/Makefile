COMPILE= gcc -I ../include -g -c
LINK= ar rcs

DEPENDENCIES= ${shell find ./ -name '*.c'}
OBJECTS= $(DEPENDENCIES:.c=.o)
LIB_NAME= libMySimpleComputer.a

all: ${LIB_NAME}

${LIB_NAME}: ${OBJECTS}
	${LINK} ${LIB_NAME} $^

%.o: %.c
	${COMPILE} $< -o $@

clean:
	find -name '${LIB_NAME}' -delete