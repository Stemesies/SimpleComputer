all: format compile run

COMPILE= gcc -g -c
LINK= gcc -g -Wall

DEPENDENCIES= ${shell find ./ -name '*.c'}
OBJECTS= ${shell find ./ -name '*.o'}

%.o: %.c
	${COMPILE} $< -o $@

format:
	find . -type f -name *.[ch] | xargs clang-format --style GNU -i --verbose

compile: ${OBJECTS}
	${LINK} $^ -o bin

run:
	./bin
