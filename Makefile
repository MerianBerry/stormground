
#===================USER SETTINGS==================#

override MAKEFLAGS=$(MFLAGS) --

PLAT= guess

#===================BUILD SETTINGS=================#

SOURCES := $(wildcard src/*.c)
MKCLIFLAGS= "--no-print-directory"
PLATS := guess linux mingw
UNAME = uname
WHICH= which

#==================TARGET SETTINGS=================#

target: $(PLAT)

guess:
	@echo Guessing `$(UNAME)`
	$(MAKE) $(MKCLIFLAGS) `$(UNAME)`

Linux linux:
	$(MAKE) $(MKCLIFLAGS) all PLAT=linux

mingw:
	$(MAKE) $(MKCLIFLAGS) all PLAT=mingw WHICH=where

#=======================BUILD======================#

all: format
	mkdir -p build
	@echo #============LIB stage=============#

	$(MAKE) $(MKCLIFLAGS) -C lib PLAT="$(PLAT)"

	@echo #===========STORMGROUND============#
	
#	@$(MAKE) $(MKCLIFLAGS) -C src PLAT=$(PLAT) ALL=echo
	$(MAKE) $(MKCLIFLAGS) -C src PLAT=$(PLAT)

format: $(SOURCES)
	$(if $(shell $(WHICH) clang-format), $(shell clang-format -i -style=file $(SOURCES)))

clean:
	rm -rf build
	$(MAKE) -C lib clean
	$(MAKE) -C src clean

.PHONY: format
#end of file