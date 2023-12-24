#==================BUILD SETTINGS==================#

override MAKEFLAGS=$(MFLAGS) --

PLAT= 
CC= 
EXCFLAGS= 
CFLAGS= -O3 -std=c99 $(EXCFLAGS)
LIB_PREF= 
LIB_EXT= 
EXE_EXT= 

MKCLIFLAGS= "--no-print-directory"
PLATS := linux mingw

LUALIB= liblua.a

#==================TARGET SETTINGS=================#

target: $(PLAT)

Linux linux:
	@echo Building $(SG_N) for linux
	$(MAKE) $(MKCLIFLAGS) all PLAT=linux CC=gcc CFLAGS="-O3 -std=c99 -I../include -I../lib" LIB_PREF="lib" LIB_EXT=".a"

mingw:
	@echo Building $(SG_N).exe for Windows
	$(MAKE) $(MKCLIFLAGS) all PLAT=mingw CC="x86_64-w64-mingw32-gcc" CFLAGS="-O3 -std=c99 -Wno-overflow -I../include -I../lib" LIB_EXT=".lib" EXE_EXT=".exe"

#======================BUILD=======================#

all: lua cJSON/cJSON.o glad.o hydrogen/hydrogen.o

lua:
#	$(MAKE) $(MKCLIFLAGS) -C lua-5.4.6 PLAT=$(PLAT) echo
	$(MAKE) $(MKCLIFLAGS) -C lua-5.4.6 PLAT=$(PLAT) "CC=$(CC) -std=gnu99"
	mv lua-5.4.6/src/$(LUALIB) ../build/$(LUALIB)
	mv lua-5.4.6/src/luac$(EXE_EXT) ../build/luac$(EXE_EXT)

clean: 
	$(MAKE) -C lua-5.4.6 clean
	rm -f cJSON/cJSON.o glad.o hydrogen/hydrogen.o
	rm -f lua-5.4.6/src/*.exe lua-5.4.6/src/*.dll

cJSON/cJSON.o: cJSON/cJSON.c cJSON/cJSON.h
glad.o: glad.c 
hydrogen/hydrogen.o: hydrogen/hydrogen.c hydrogen/hydrogen.h
#end of file