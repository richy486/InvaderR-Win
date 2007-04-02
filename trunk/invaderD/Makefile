
PCCC     = gcc
PCCFLAGS = -O2 -g -Wall -DDEBUG -DNOTPSP
PCLIBS   = -L/usr/lib
PCINCLUDE = -I/usr/include -I/usr/include/SDL
OBJS = Bomber.o End.o Invader.o InvaderSet.o main.o Player.o Shooter.o

TARGET = invaderD

CFLAGS = -O2 -g -Wall -DDEBUG
LIBS=
LIBDIR =
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP kxploit
EXTRA_CLEAN = pcclean

# --- PC SDL
PCCFLAGS += $(shell sdl-config --cflags)
PCLIBS += $(shell sdl-config --libs)
PCLIBS += -lm -lSDL -lSDLmain

PSP_EBOOT_TITLE = invaderD
PSP_DIR_NAME = invaderD

PSPSDK=$(shell psp-config --pspsdk-path)
PSPBIN = $(PSPSDK)/../bin
CFLAGS += $(shell $(PSPBIN)/sdl-config --cflags)
LIBS += $(shell $(PSPBIN)/sdl-config --libs)
LIBS += -lstdc++ -lm -lSDL -lSDLmain
include $(PSPSDK)/lib/build.mak 