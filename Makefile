# A good example of starting with Makefile
# https://github.com/edubart/sokol_gp/blob/d2af9f4ef58850b6599a9aea6edaa7bd79ce67b4/Makefile

CC=gcc
CFLAGS+=-std=gnu23
CFLAGS+=-Wall -Wextra -Wshadow -Wno-unused-function -Werror -Wno-missing-field-initializers
INCS+=-Ideps -Ishaders
DEFS+=-DSOKOL_GLCORE
LIBS+=-lX11 -lXi -lXcursor -lGL -ldl -lm
LSP+=$(DEFS) $(INCS)
OUTDIR=build
OUTEXC=gui

SHDC=sokol-shdc
# SHDCFLAGS=--format sokol_impl --slang glsl410
SHDCFLAGS=--format sokol_impl --slang glsl430:hlsl5:metal_macos
SHADERS= \
	 shaders/shd.glsl.h

all: $(OUTEXC)

shaders: $(SHADERS)


$(OUTDIR)/deps.o: deps/deps.c
	@mkdir -p $(OUTDIR)
	$(CC) -c $(CFLAGS) $(DEFS) -o $@ deps/deps.c

$(OUTEXC): $(OUTDIR)/deps.o shaders/*.h src/main.c
	$(CC) $(CFLAGS) $(INCS) $(LIBS) $(OUTDIR)/deps.o -o $(OUTDIR)/$(OUTEXC) src/main.c

run: $(OUTEXC)
	@./$(OUTDIR)/$(OUTEXC)

clean:
	@rm -rf $(OUTDIR)

# Clangd specific
compile_flags.txt: FORCE
	@echo 'Generating compile_flags.txt for clangd support'
	@echo $(LSP) | tr ' ' '\n' > $@

FORCE:

shaders/%.glsl.h: shaders/%.glsl
	$(SHDC) $(SHDCFLAGS) -i $^ -o $@

clean-shaders:
	rm -f $(SHADERS)

update-thirdparty:
	wget -O deps/sokol_gfx.h https://raw.githubusercontent.com/floooh/sokol/refs/heads/master/sokol_gfx.h
	wget -O deps/sokol_app.h https://raw.githubusercontent.com/floooh/sokol/refs/heads/master/sokol_app.h
	wget -O deps/sokol_glue.h https://raw.githubusercontent.com/floooh/sokol/refs/heads/master/sokol_glue.h

.PHONY: all shaders clean clean-shaders update-thirdparty
