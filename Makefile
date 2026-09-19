# A good example of starting with Makefile
# https://github.com/edubart/sokol_gp/blob/d2af9f4ef58850b6599a9aea6edaa7bd79ce67b4/Makefile

CC=gcc
CFLAGS+=-std=gnu23
CFLAGS+=-Wall -Wextra -Wshadow -Wno-unused-function -Werror -Wno-missing-field-initializers
INCS+=-Ideps
DEFS+=-DSOKOL_GLCORE
LIBS+=-lX11 -lXi -lXcursor -lGL -ldl -lm
LSP+=$(DEFS) $(INCS)

all: gui

gui: src/main.c
	$(CC) $(CFLAGS) $(INCS) $(DEFS) $(LIBS) -o gui src/main.c

run: gui
	@./gui

# Clangd specific
compile_flags.txt: FORCE
	@echo 'Generating compile_flags.txt for clangd support'
	@echo $(LSP) | tr ' ' '\n' > $@

FORCE:

sokol_update:
	wget -O deps/sokol_gfx.h https://raw.githubusercontent.com/floooh/sokol/refs/heads/master/sokol_gfx.h
	wget -O deps/sokol_app.h https://raw.githubusercontent.com/floooh/sokol/refs/heads/master/sokol_app.h
	wget -O deps/sokol_glue.h https://raw.githubusercontent.com/floooh/sokol/refs/heads/master/sokol_glue.h
