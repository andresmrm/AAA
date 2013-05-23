SRCDIR=src/

BIN=aaa
CC=gcc
CXX=g++
CFLAGS=-g `sdl-config --cflags`
LDFLAGS=-lSDL_net -lSDL_image -lSDL_ttf -lSDL_mixer `sdl-config --libs` -lGL
RM=rm -f

OBJ=$(SRCDIR)Base.o\
    $(SRCDIR)Botoe.o\
    $(SRCDIR)Cidad.o\
    $(SRCDIR)Comba.o\
    $(SRCDIR)Globa.o\
    $(SRCDIR)Jogad.o\
    $(SRCDIR)Jogo.o\
    $(SRCDIR)Magia.o\
    $(SRCDIR)Menus.o\
    $(SRCDIR)Raca.o\
    $(SRCDIR)Rede.o\
    $(SRCDIR)Salva.o\
    $(SRCDIR)Sons.o\
    $(SRCDIR)Terre.o\
    $(SRCDIR)Tipos.o\
    $(SRCDIR)Unida.o\
    $(SRCDIR)main.o

all: $(BIN)

$(BIN): $(OBJ) 
	$(CXX) -o $(BIN) $(SRCDIR)*.o $(CFLAGS) $(LDFLAGS)

$(SRCDIR)%.o: $(SRCDIR)%.cpp AAA.h
	$(CXX) -o $@ $(CFLAGS) -c $(SRCDIR)$*.cpp

cleanall: clean cleanbak cleanbin

clean: cleanbak cleanobj

cleanbak:
	$(RM) *~
	$(RM) $(SRCDIR)*~

cleanbin:
	$(RM) $(BIN)

cleanobj:
	$(RM) $(SRCDIR)$(OBJ)
