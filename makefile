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

OBJPATH    = objs/
SRCPATH    = src/
OBJ        = $(OBJECTS:%.o=$(OBJPATH)%.o)
DBGOBJ     = $(OBJ:%.o=%_d.o)
BINNAME    = matchgame
DBGBINNAME = $(BINNAME:%=%_d)
ifeq ($(findstring mingw32, $(SYSTEM)), mingw32)
LDFLAGS    = -lws2_32
RM         = del /Q /F
BIN        = $(BINNAME:%=%.exe)
DBGBIN     = $(DBGBINNAME:%=%.exe)
DELPATH    = objs\\
DELOBJ     = $(OBJECTS:%.o=$(DELPATH)%.o)
DELDBGOBJ  = $(DELOBJ:%.o=%_d.o)
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

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ) $(LDFLAGS)

$(DBGBIN): $(DBGOBJ)
	$(CC) $(CFLAGS) $(DBGFLAGS) -o $(DBGBIN) $(DBGOBJ) $(LDFLAGS)

### general rules ###

$(OBJPATH)%.o: $(SRCPATH)%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)%_d.o: $(SRCPATH)%.cpp
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
$(OBJPATH)application_d.o: $(SRCPATH)application.cpp $(SRCPATH)application.h $(SRCPATH)game.h $(SRCPATH)menu.h
$(OBJPATH)client_d.o: $(SRCPATH)client.cpp $(SRCPATH)client.h $(SRCPATH)network.h $(SRCPATH)console.h
$(OBJPATH)clientgame_d.o: $(SRCPATH)clientgame.cpp $(SRCPATH)clientgame.h $(SRCPATH)game.h $(SRCPATH)network.h $(SRCPATH)playfield.h $(SRCPATH)player.h $(SRCPATH)console.h
$(OBJPATH)console_d.o: $(SRCPATH)console.cpp $(SRCPATH)console.h
$(OBJPATH)distantnetplayer_d.o: $(SRCPATH)distantnetplayer.cpp $(SRCPATH)distantnetplayer.h $(SRCPATH)player.h $(SRCPATH)game.h $(SRCPATH)network.h
$(OBJPATH)game_d.o: $(SRCPATH)game.cpp $(SRCPATH)game.h $(SRCPATH)player.h $(SRCPATH)playfield.h $(SRCPATH)console.h $(SRCPATH)visualisation.h
$(OBJPATH)localgame_d.o: $(SRCPATH)localgame.cpp $(SRCPATH)localgame.h $(SRCPATH)game.h
$(OBJPATH)localnetplayer_d.o: $(SRCPATH)localnetplayer.cpp $(SRCPATH)localnetplayer.h $(SRCPATH)player.h $(SRCPATH)game.h $(SRCPATH)network.h
$(OBJPATH)localplayer_d.o: $(SRCPATH)localplayer.cpp $(SRCPATH)localplayer.h $(SRCPATH)player.h $(SRCPATH)game.h
$(OBJPATH)main_d.o: $(SRCPATH)main.cpp $(SRCPATH)application.h $(SRCPATH)game.h
$(OBJPATH)menu_d.o: $(SRCPATH)menu.cpp $(SRCPATH)menu.h $(SRCPATH)console.h
$(OBJPATH)player_d.o: $(SRCPATH)player.cpp $(SRCPATH)player.h $(SRCPATH)game.h $(SRCPATH)console.h $(SRCPATH)playfield.h
$(OBJPATH)playfield_d.o: $(SRCPATH)playfield.cpp $(SRCPATH)playfield.h
$(OBJPATH)server_d.o: $(SRCPATH)server.cpp $(SRCPATH)server.h $(SRCPATH)network.h $(SRCPATH)console.h
$(OBJPATH)servergame_d.o: $(SRCPATH)servergame.cpp $(SRCPATH)servergame.h $(SRCPATH)game.h $(SRCPATH)network.h $(SRCPATH)playfield.h $(SRCPATH)player.h $(SRCPATH)console.h
$(OBJPATH)visualisation_d.o: $(SRCPATH)visualisation.cpp $(SRCPATH)visualisation.h $(SRCPATH)playfield.h $(SRCPATH)console.h

clean:
	$(RM) $(BIN) $(DBGBIN) $(DELOBJ) $(DELDBGOBJ)
