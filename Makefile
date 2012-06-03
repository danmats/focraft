#
# @Makefile for focraft
#
# author: Dan Matsuoka
#

SDL_FLAGS = $(shell sdl-config --cflags --libs)
#LIBS = -lguichan_sdl -lguichan -lSDL_image
LIBS = -lSDL_image

TARGET = focraft
SRCS = focraft.cpp cexception.cpp isoeng.cpp asset.cpp assetanim.cpp tile.cpp unit.cpp
OBJS = $(SRCS: .cpp = .o)

.SUFFIXES: .o .cpp

%.o: %.cpp
	g++ -c $<

all:
	g++ -Wall -pedantic $(OBJS) -o $(TARGET) $(LIBS) $(SDL_FLAGS)

clean:
	rm -rf *.o
	rm -rf $(TARGET)
