UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
CXX := clang++
CXXFLAGS := -std=c++11 -Wall -O2
MAC_FRAMEWORKS := -framework OpenGL -framework GLUT -framework Cocoa -framework IOKit -framework CoreFoundation -framework ApplicationServices -framework CoreGraphics
ifneq ($(shell which sdl2-config 2>/dev/null),)
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LIBS := $(shell sdl2-config --libs)
else
SDL_CFLAGS := -I/usr/local/include/SDL2 -D_THREAD_SAFE
SDL_LIBS := -L/usr/local/lib -lSDL2
endif
else
CXX := g++
CXXFLAGS := -std=c++11 -Wall -O2
ifneq ($(shell which sdl2-config 2>/dev/null),)
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LIBS := $(shell sdl2-config --libs)
else
SDL_CFLAGS := -I/usr/local/include/SDL2 -D_THREAD_SAFE
SDL_LIBS := -L/usr/local/lib -lSDL2
endif
MAC_FRAMEWORKS :=
endif

INCLUDE_DIRS := -Isource -Isource/include -Isource/generic -Isource/GL
CXXFLAGS += $(SDL_CFLAGS) $(INCLUDE_DIRS)

SRCS := $(shell find source -name '*.cpp' | grep -v -E 'Win32|ThreadsWinAPI|/ms3d/')

# Default target: build executable
all: Kinetica

SDL_IMAGE_LIB := -lSDL2_image
SDL_MIXER_LIB := -lSDL2_mixer

LINK_EXTRA := $(SDL_IMAGE_LIB) $(SDL_MIXER_LIB) -framework OpenAL -lalut

Kinetica:
	$(CXX) $(CXXFLAGS) -o Kinetica $(SRCS) $(SDL_LIBS) $(LINK_EXTRA) $(MAC_FRAMEWORKS) -lGLEW -lGLU -lm

clean:
	rm -f Kinetica

.PHONY: all clean
