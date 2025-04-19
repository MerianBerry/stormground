
#===================USER SETTINGS==================#

#override MAKEFLAGS=$(MAKEFLAGS) --

PLAT= guess

#===================BUILD SETTINGS=================#

PLATS := guess linux mingw
MKCLIFLAGS= "--no-print-directory"
UNAME= uname
CC:= gcc
CSTANDARD:= -std=c11
OFLAGS:= -O2
IDIRS:= 
CFLAGS:= $(CSTANDARD) $(OFLAGS) $(IDIRS)
LDFLAGS:= 
LDDIRS:= -L../lib
SG_EXE:= sg

#==================TARGET SETTINGS=================#

target: $(PLAT)

guess:
#	@echo Guessing `$(UNAME)`
	@$(MAKE) $(MKCLIFLAGS) `$(UNAME)` OFLAGS="$(OFLAGS)"

Linux linux:
	@$(MAKE) $(MKCLIFLAGS) all CSTANDARD="-std=gnu11" OFLAGS="$(OFLAGS)" LDFLAGS="$(LDDIRS) -lglfw3 -lGL -lpthread -lX11 -lXrandr -lXi -ldl -lm"

mingw:
	$(MAKE) $(MKCLIFLAGS) all PLAT=mingw OFLAGS="$(OFLAGS)" SG_EXE=sg.exe CC="x86_64-w64-mingw32-gcc" LDFLAGS="$(LDDIRS) -lglfw3mingw -lm -lopengl32 -lgdi32 -ldwmapi"

#=======================BUILD======================#

all: builddir
	@$(MAKE) $(MKCLIFLAGS) -Csrc PLAT=$(PLAT) CC=$(CC) SG_EXE="$(SG_EXE)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" 

debug:
	@$(MAKE) $(MKCLIFLAGS) OFLAGS="-g"

shaders:
	@$(MAKE) $(MKCLIFLAGS) -Csrc shaders

#========================MISC======================#

builddir:
	@mkdir -p build

clean:
	rm -rf build src/*.o
	@$(MAKE) $(MKCLIFLAGS) -C src clean

.PHONY: shaders
#end of file