#

ALL:= all

#==================BUILD SETTINGS==================#

MKCLIFLAGS= "--no-print-directory"
CC:=
CFLAGS:=
LDFLAGS:=
SG_EXE:= sg

W32_RES= resources/resource.res

SG_OBJECTS= scl.o sg.o sgapi.o sgcli.o sgimage.o sginput.o sgrender.o sgshader.o cJSON.o glad.o
SH_HEADERS= shaders/main_vert.h shaders/main_frag.h shaders/blit_vert.h shaders/blit_frag.h

ifeq ($(PLAT), mingw)
SG_OBJECTS:= $(SG_OBJECTS) $(W32_RES)
endif

#=====================TARGETS======================#

%.res: %.rc
	x86_64-w64-mingw32-windres -O coff -o $@ $<

all: $(SG_EXE)
	@mv $(SG_EXE) ../build/$(SG_EXE)

$(SG_EXE):
	@echo ===========STORMGROUND============
	@$(MAKE) $(MKCLIFLAGS) PLAT=$(PLAT) CC=$(CC) CFLAGS="$(CFLAGS)" $(SG_OBJECTS)
	@echo CC $(SG_OBJECTS)
	@$(CC) $(SG_OBJECTS) $(LDFLAGS) -o $@

shaders/%_vert.h: shaders/%.vert 
	@echo xxd $<
	@xxd -i $< $@
shaders/%_frag.h: shaders/%.frag 
	@echo xxd $<
	@xxd -i $< $@

shaders: $(SH_HEADERS)

minilua.o: minilua.c 
scl.o: scl.c 
sg.o: sg.c
sgapi.o: sgapi.c 
sgcli.o: sgcli.c 
sgimage.o: sgimage.c 
sginput.o: sginput.c 
sgrender.o: sgrender.c $(SH_HEADERS)
sgshader.o: sgshader.c 
cJSON.o: cJSON.c
glad.o: glad.c

%.o: %.c
	@echo CC $<
	@$(CC) $(CFLAGS) -c -o $@ $<

#========================MISC======================#
clean:
	rm -f *.o $(SH_HEADERS) $(W32_RES)
#end of file