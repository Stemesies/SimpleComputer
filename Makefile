SEQUENCE = mySimpleComputer console


all: format $(addsuffix -compile, ${SEQUENCE})

format:
	find . -type f -name *.[ch] | xargs clang-format --style GNU -i --verbose

clean: $(addsuffix -clean, ${SEQUENCE})
	find . -name '*.[ch].temp-stream-*' -type f -delete
	find . -name '*.o' -type f -delete



%-compile:
	@$(MAKE) -C $*
	@echo "\033[38;2;255;20;140mCompilation of $* complete.\033[0m"

%-clean:
	@$(MAKE) -C $* clean

run: all
	@$(MAKE) -C console run