VERSION    = 0.1.2
CC         = g++
cc         = gcc
CFLAGS     = -Wall -O2
DBGFLAGS   = -g
SYSTEM     = $(shell $(cc) -dumpmachine)

### objects ###
OBJECTS    += application.o
OBJECTS    += client.o
OBJECTS    += clientgame.o
OBJECTS    += console.o
OBJECTS    += distantnetplayer.o
OBJECTS    += game.o
OBJECTS    += localgame.o
OBJECTS    += localnetplayer.o
OBJECTS    += localplayer.o
OBJECTS    += main.o
OBJECTS    += menu.o
OBJECTS    += player.o
OBJECTS    += playfield.o
OBJECTS    += server.o
OBJECTS    += servergame.o
OBJECTS    += visualisation.o
###

OBJPATH    = objects/
SRCPATH    = src/
OBJ        = $(OBJECTS:%.o=$(OBJPATH)%.o)
DBGOBJ     = $(OBJ:%.o=%.o_d)
BINNAME    = matchgame
DBGBINNAME = $(BINNAME:%=%_d)
ifeq ($(findstring mingw32, $(SYSTEM)), mingw32)
LDFLAGS    = -lws2_32
RM         = del /Q /F
BIN        = $(BINNAME:%=%.exe)
DBGBIN     = $(DBGBINNAME:%=%.exe)
DELPATH    = objects\\
DELOBJ     = $(OBJECTS:%.o=$(DELPATH)%.o)
DELDBGOBJ  = $(DELOBJ:%.o=%.o_d)
else
LDFLAGS    =
RM         = rm -rf
BIN        = $(BINNAME)
DBGBIN     = $(DBGBINNAME)
DELOBJ     = $(OBJ)
DELDBGOBJ  = $(DBGOBJ)
endif

all: $(BIN)

debug: $(DBGBIN)

$(BIN):  $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ) $(LDFLAGS)

$(DBGBIN): $(DBGOBJ)
	$(CC) $(CFLAGS) $(DBGFLAGS) -o $(DBGBIN) $(DBGOBJ) $(LDFLAGS)

### general rules ###

$(OBJPATH)%.o: $(SRCPATH)%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)%.o_d: $(SRCPATH)%.cpp
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

### dependencies ###
### gcc -MM is used to generate these ###

### objects ###
$(OBJPATH)application.o: $(SRCPATH)application.cpp $(SRCPATH)application.h $(SRCPATH)game.h $(SRCPATH)menu.h
$(OBJPATH)client.o: $(SRCPATH)client.cpp $(SRCPATH)client.h $(SRCPATH)network.h $(SRCPATH)console.h
$(OBJPATH)clientgame.o: $(SRCPATH)clientgame.cpp $(SRCPATH)clientgame.h $(SRCPATH)game.h $(SRCPATH)network.h $(SRCPATH)playfield.h $(SRCPATH)player.h $(SRCPATH)console.h
$(OBJPATH)console.o: $(SRCPATH)console.cpp $(SRCPATH)console.h
$(OBJPATH)distantnetplayer.o: $(SRCPATH)distantnetplayer.cpp $(SRCPATH)distantnetplayer.h $(SRCPATH)player.h $(SRCPATH)game.h $(SRCPATH)network.h
$(OBJPATH)game.o: $(SRCPATH)game.cpp $(SRCPATH)game.h $(SRCPATH)player.h $(SRCPATH)playfield.h $(SRCPATH)console.h $(SRCPATH)visualisation.h
$(OBJPATH)localgame.o: $(SRCPATH)localgame.cpp $(SRCPATH)localgame.h $(SRCPATH)game.h
$(OBJPATH)localnetplayer.o: $(SRCPATH)localnetplayer.cpp $(SRCPATH)localnetplayer.h $(SRCPATH)player.h $(SRCPATH)game.h $(SRCPATH)network.h
$(OBJPATH)localplayer.o: $(SRCPATH)localplayer.cpp $(SRCPATH)localplayer.h $(SRCPATH)player.h $(SRCPATH)game.h
$(OBJPATH)main.o: $(SRCPATH)main.cpp $(SRCPATH)application.h $(SRCPATH)game.h
$(OBJPATH)menu.o: $(SRCPATH)menu.cpp $(SRCPATH)menu.h $(SRCPATH)console.h
$(OBJPATH)player.o: $(SRCPATH)player.cpp $(SRCPATH)player.h $(SRCPATH)game.h $(SRCPATH)console.h $(SRCPATH)playfield.h
$(OBJPATH)playfield.o: $(SRCPATH)playfield.cpp $(SRCPATH)playfield.h
$(OBJPATH)server.o: $(SRCPATH)server.cpp $(SRCPATH)server.h $(SRCPATH)network.h $(SRCPATH)console.h
$(OBJPATH)servergame.o: $(SRCPATH)servergame.cpp $(SRCPATH)servergame.h $(SRCPATH)game.h $(SRCPATH)network.h $(SRCPATH)playfield.h $(SRCPATH)player.h $(SRCPATH)console.h
$(OBJPATH)visualisation.o: $(SRCPATH)visualisation.cpp $(SRCPATH)visualisation.h $(SRCPATH)playfield.h $(SRCPATH)console.h

### debug objects ###
$(OBJPATH)application.o_d: $(SRCPATH)application.cpp $(SRCPATH)application.h $(SRCPATH)game.h $(SRCPATH)menu.h
$(OBJPATH)client.o_d: $(SRCPATH)client.cpp $(SRCPATH)client.h $(SRCPATH)network.h $(SRCPATH)console.h
$(OBJPATH)clientgame.o_d: $(SRCPATH)clientgame.cpp $(SRCPATH)clientgame.h $(SRCPATH)game.h $(SRCPATH)network.h $(SRCPATH)playfield.h $(SRCPATH)player.h $(SRCPATH)console.h
$(OBJPATH)console.o_d: $(SRCPATH)console.cpp $(SRCPATH)console.h
$(OBJPATH)distantnetplayer.o_d: $(SRCPATH)distantnetplayer.cpp $(SRCPATH)distantnetplayer.h $(SRCPATH)player.h $(SRCPATH)game.h $(SRCPATH)network.h
$(OBJPATH)game.o_d: $(SRCPATH)game.cpp $(SRCPATH)game.h $(SRCPATH)player.h $(SRCPATH)playfield.h $(SRCPATH)console.h $(SRCPATH)visualisation.h
$(OBJPATH)localgame.o_d: $(SRCPATH)localgame.cpp $(SRCPATH)localgame.h $(SRCPATH)game.h
$(OBJPATH)localnetplayer.o_d: $(SRCPATH)localnetplayer.cpp $(SRCPATH)localnetplayer.h $(SRCPATH)player.h $(SRCPATH)game.h $(SRCPATH)network.h
$(OBJPATH)localplayer.o_d: $(SRCPATH)localplayer.cpp $(SRCPATH)localplayer.h $(SRCPATH)player.h $(SRCPATH)game.h
$(OBJPATH)main.o_d: $(SRCPATH)main.cpp $(SRCPATH)application.h $(SRCPATH)game.h
$(OBJPATH)menu.o_d: $(SRCPATH)menu.cpp $(SRCPATH)menu.h $(SRCPATH)console.h
$(OBJPATH)player.o_d: $(SRCPATH)player.cpp $(SRCPATH)player.h $(SRCPATH)game.h $(SRCPATH)console.h $(SRCPATH)playfield.h
$(OBJPATH)playfield.o_d: $(SRCPATH)playfield.cpp $(SRCPATH)playfield.h
$(OBJPATH)server.o_d: $(SRCPATH)server.cpp $(SRCPATH)server.h $(SRCPATH)network.h $(SRCPATH)console.h
$(OBJPATH)servergame.o_d: $(SRCPATH)servergame.cpp $(SRCPATH)servergame.h $(SRCPATH)game.h $(SRCPATH)network.h $(SRCPATH)playfield.h $(SRCPATH)player.h $(SRCPATH)console.h
$(OBJPATH)visualisation.o_d: $(SRCPATH)visualisation.cpp $(SRCPATH)visualisation.h $(SRCPATH)playfield.h $(SRCPATH)console.h

clean:
	$(RM) $(BIN) $(DBGBIN) $(DELOBJ) $(DELDBGOBJ)
