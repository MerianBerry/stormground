

#==================BUILD SETTINGS==================#

PLAT= 
CC= gcc
CFLAGS= -O3 -std=c89
LDFLAGS= 
SG_E= 
LIBS= 

MKCLIFLAGS= "--no-print-directory"
PLATS := linux mingw
SG_N= stormground

ALL= all

SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))
SHADERS := $(wildcard shaders/*.vert) $(wildcard shaders/*.frag) $(wildcard shaders/*.comp)
SHADEROBJS := $(patsubst %, %.o, $(SHADERS))
EXTOBJECTS= ../lib/cJSON/cJSON.o ../lib/glad.o ../lib/hydrogen/hydrogen.o $(SHADEROBJS)

$(if $(shell which clang-format), $(eval CFMT=clang-format), $(info clang-format isnt present and will not format code))

#==================TARGET SETTINGS=================#

target: $(PLAT)

Linux linux:
	@echo Building $(SG_N) for linux
	$(MAKE) $(MKCLIFLAGS) $(ALL) PLAT=linux SG_E=$(SG_N) LIB_PREF=lib LIB_EXT=.a LIBS="-lglfw3 -lGL -lpthread -lX11 -lXrandr -lXi -ldl -lm" 

mingw:
	@echo Building $(SG_N).exe for Windows
	$(MAKE) $(MKCLIFLAGS) $(ALL) PLAT=mingw SG_E=$(SG_N).exe LIB_EXT=.lib CC="x86_64-w64-mingw32-gcc" CFLAGS="-O3 -std=c89 -Wno-overflow" LIBS="-lglfw3mingw -lm -lopengl32 -lgdi32"

#======================BUILD=======================#

echo:
	@echo PLAT=$(PLAT)
	@echo CC=$(CC)
	@echo CFLAGS=$(CFLAGS)
	@echo LDFLAGS=$(LDFLAGS)
	@echo SG_E=$(SG_E)
	@echo LIBS=$(LIBS)

all: $(OBJECTS) $(SHADEROBJS)
	$(CC) -L../lib $(OBJECTS) $(EXTOBJECTS) -o $(SG_E) $(LIBS)
	@mv $(SG_E) ../build/$(SG_E)

%.o: %.c 
	$(if $(value $(CFMT)),,$(shell $(CFMT) -i -style=file $<))
	$(CC) $(CFLAGS) -I../include -I../lib -c $< -o $@

shaders/%.o: shaders/%
	ld -r -b binary $< -o $@

clean:
	rm -f $(OBJECTS) $(SG_E) shaders/*.o

.PHONY: target
#end of file