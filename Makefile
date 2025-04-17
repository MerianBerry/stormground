
#===================USER SETTINGS==================#

#override MAKEFLAGS=$(MAKEFLAGS) --

PLAT= guess

#===================BUILD SETTINGS=================#

PLATS := guess linux mingw
MKCLIFLAGS= "--no-print-directory"
UNAME= uname
WHICH= which
CC:= gcc
LDFLAGS:= 
IDIRS:= 
CSTANDARD:= -std=c11
OFLAGS:= -O2
CFLAGS= $(CSTANDARD) $(OFLAGS) $(IDIRS)
SG_EXE:= build/sg

SG_OBJECTS:= src/scl.o src/sg.o src/sgapi.o src/sgcli.o src/sgimage.o src/sginput.o src/sgrender.o src/sgshader.o src/cJSON.o src/glad.o

#==================TARGET SETTINGS=================#

target: $(PLAT)

guess:
#	@echo Guessing `$(UNAME)`
	@$(MAKE) $(MKCLIFLAGS) `$(UNAME)` OFLAGS="$(OFLAGS)"

Linux linux:
	@$(MAKE) $(MKCLIFLAGS) all PLAT=linux CSTANDARD="-std=gnu11" OFLAGS="$(OFLAGS)" LDFLAGS="-Llib -lglfw3 -lGL -lpthread -lX11 -lXrandr -lXi -ldl -lm"

mingw:
	$(MAKE) $(MKCLIFLAGS) all PLAT=mingw WHICH=where OFLAGS="$(OFLAGS)" SG_EXE=build/sg.exe

#=======================BUILD======================#

all: builddir $(SG_EXE)
	
#	@$(MAKE) -C src PLAT=$(PLAT) ALL=echo
#	$(MAKE) -C src PLAT=$(PLAT)
builddir:
	@mkdir -p build


debug:
	@$(MAKE) $(MKCLIFLAGS) OFLAGS="-g"



$(SG_EXE): $(SG_OBJECTS)
	@echo ===========STORMGROUND============
	$(CC) $(SG_OBJECTS) $(LDFLAGS) -o $@


src/minilua.o: src/minilua.c 
src/scl.o: src/scl.c 
src/sg.o: src/sg.c
src/sgapi.o: src/sgapi.c 
src/sgcli.o: src/sgcli.c 
src/sgimage.o: src/sgimage.c 
src/sginput.o: src/sginput.c 
src/sgrender.o: src/sgrender.c build/main_vert.h build/main_frag.h
src/sgshader.o: src/sgshader.c 
src/cJSON.o: src/cJSON.c
src/glad.o: src/glad.c

build/main_%.h: src/shaders/main.%
	xxd -i $< $@

clean:
	rm -rf build src/*.o

.PHONY:
#end of file