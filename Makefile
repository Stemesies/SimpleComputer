SEQUENCE = mySimpleComputer console

all: $(addsuffix -compile, ${SEQUENCE})

.SILENT:
clean: $(addsuffix -clean, ${SEQUENCE})


%-compile:
	$(MAKE) -C $*
	echo "\033[38;2;255;20;140mCompilation of $* complete.\033[0m"

%-clean:
	$(MAKE) -C $* clean

run: all
	$(MAKE) -C console run