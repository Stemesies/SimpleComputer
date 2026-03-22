ARGS=
SEQUENCE = mySimpleComputer myTerm myBigChars myReadKey console simpleassembler
BRUH = 

all: format
	@for dir in $(SEQUENCE); do \
		$(MAKE) -C $$dir; \
		echo -e "\033[38;2;255;20;140mCompilation of $$dir complete.\033[0m"; \
	done
	@echo -e "\033[38;2;255;20;140mDone. (ꈍ ꒳ ꈍ✿)\033[0m"

format:
	find . -type f -name *.[ch] | xargs clang-format --style GNU -i --verbose
	find . -name '*.[ch].temp-stream-*' -type f -delete

clean:
	for dir in $(SEQUENCE); do \
		$(MAKE) clean -C $$dir; \
	done

run: all
	./console/.bin/console.bin ${ARGS}

run-font: all
	./console/.bin/font.bin ${ARGS}

run-tests: all
	./console/.bin/tests.bin ${ARGS}

run-trans: all
	./simpleassembler/.bin/sat.bin ${ARGS}