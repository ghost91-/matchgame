VERSION    = 0.1.2
CC         = g++
cc         = gcc
CFLAGS     = -Wall
DBGFLAGS   = -g
SYSTEM     = $(shell $(cc) -dumpmachine)
OBJECTS    = main.o application.o menu.o console.o game.o localgame.o servergame.o clientgame.o visualisation.o server.o client.o player.o playfield.o
OBJPATH    = objects/
SRCPATH    = src/
ENGINEPATH = engine/
GAMEPATH   = game/
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
DELDBGOBJ = $(DELOBJ:%.o=%.o_d)
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
	$(CC) $(CFLAGS) -o $(DBGBIN) $(DBGOBJ) $(LDFLAGS)

$(OBJPATH)main.o: $(SRCPATH)main.cpp $(SRCPATH)$(ENGINEPATH)application.h $(SRCPATH)$(GAMEPATH)game.h 
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)application.o: $(SRCPATH)$(ENGINEPATH)application.cpp $(SRCPATH)$(ENGINEPATH)application.h $(SRCPATH)$(GAMEPATH)game.h $(SRCPATH)$(GAMEPATH)menu.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)menu.o: $(SRCPATH)$(GAMEPATH)menu.cpp $(SRCPATH)$(GAMEPATH)menu.h $(SRCPATH)$(ENGINEPATH)console.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)console.o: $(SRCPATH)$(ENGINEPATH)console.cpp $(SRCPATH)$(ENGINEPATH)console.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)game.o: $(SRCPATH)$(GAMEPATH)game.cpp $(SRCPATH)$(GAMEPATH)game.h $(SRCPATH)$(GAMEPATH)player.h $(SRCPATH)$(GAMEPATH)visualisation.h $(SRCPATH)$(ENGINEPATH)console.h $(SRCPATH)$(GAMEPATH)playfield.h 
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)localgame.o: $(SRCPATH)$(GAMEPATH)localgame.cpp $(SRCPATH)$(GAMEPATH)localgame.h $(SRCPATH)$(GAMEPATH)game.h 
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)servergame.o: $(SRCPATH)$(GAMEPATH)servergame.cpp $(SRCPATH)$(GAMEPATH)servergame.h $(SRCPATH)$(GAMEPATH)game.h $(SRCPATH)$(ENGINEPATH)network.h $(SRCPATH)$(GAMEPATH)player.h $(SRCPATH)$(ENGINEPATH)console.h $(SRCPATH)$(GAMEPATH)playfield.h 
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)clientgame.o: $(SRCPATH)$(GAMEPATH)clientgame.cpp $(SRCPATH)$(GAMEPATH)clientgame.h $(SRCPATH)$(GAMEPATH)game.h $(SRCPATH)$(ENGINEPATH)network.h $(SRCPATH)$(GAMEPATH)player.h $(SRCPATH)$(ENGINEPATH)console.h $(SRCPATH)$(GAMEPATH)playfield.h 
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)visualisation.o: $(SRCPATH)$(GAMEPATH)visualisation.cpp $(SRCPATH)$(GAMEPATH)visualisation.h $(SRCPATH)$(GAMEPATH)playfield.h $(SRCPATH)$(ENGINEPATH)console.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)client.o: $(SRCPATH)$(ENGINEPATH)client.cpp $(SRCPATH)$(ENGINEPATH)client.h $(SRCPATH)$(ENGINEPATH)network.h $(SRCPATH)$(ENGINEPATH)console.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)server.o: $(SRCPATH)$(ENGINEPATH)server.cpp $(SRCPATH)$(ENGINEPATH)server.h $(SRCPATH)$(ENGINEPATH)network.h $(SRCPATH)$(ENGINEPATH)console.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)player.o: $(SRCPATH)$(GAMEPATH)player.cpp $(SRCPATH)$(GAMEPATH)player.h $(SRCPATH)$(ENGINEPATH)network.h $(SRCPATH)$(GAMEPATH)game.h $(SRCPATH)$(ENGINEPATH)console.h $(SRCPATH)$(GAMEPATH)playfield.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)playfield.o: $(SRCPATH)$(GAMEPATH)playfield.cpp $(SRCPATH)$(GAMEPATH)playfield.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)main.o_d: $(SRCPATH)main.cpp $(SRCPATH)$(ENGINEPATH)application.h $(SRCPATH)$(GAMEPATH)game.h 
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)application.o_d: $(SRCPATH)$(ENGINEPATH)application.cpp $(SRCPATH)$(ENGINEPATH)application.h $(SRCPATH)$(GAMEPATH)game.h $(SRCPATH)$(GAMEPATH)menu.h
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)menu.o_d: $(SRCPATH)$(GAMEPATH)menu.cpp $(SRCPATH)$(GAMEPATH)menu.h $(SRCPATH)$(ENGINEPATH)console.h
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)console.o_d: $(SRCPATH)$(ENGINEPATH)console.cpp $(SRCPATH)$(ENGINEPATH)console.h
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)game.o_d: $(SRCPATH)$(GAMEPATH)game.cpp $(SRCPATH)$(GAMEPATH)game.h $(SRCPATH)$(GAMEPATH)player.h $(SRCPATH)$(GAMEPATH)visualisation.h $(SRCPATH)$(ENGINEPATH)console.h $(SRCPATH)$(GAMEPATH)playfield.h 
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)localgame.o_d: $(SRCPATH)$(GAMEPATH)localgame.cpp $(SRCPATH)$(GAMEPATH)localgame.h $(SRCPATH)$(GAMEPATH)game.h 
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)servergame.o_d: $(SRCPATH)$(GAMEPATH)servergame.cpp $(SRCPATH)$(GAMEPATH)servergame.h $(SRCPATH)$(GAMEPATH)game.h $(SRCPATH)$(ENGINEPATH)network.h $(SRCPATH)$(GAMEPATH)player.h $(SRCPATH)$(ENGINEPATH)console.h $(SRCPATH)$(GAMEPATH)playfield.h 
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)clientgame.o_d: $(SRCPATH)$(GAMEPATH)clientgame.cpp $(SRCPATH)$(GAMEPATH)clientgame.h $(SRCPATH)$(GAMEPATH)game.h $(SRCPATH)$(ENGINEPATH)network.h $(SRCPATH)$(GAMEPATH)player.h $(SRCPATH)$(ENGINEPATH)console.h $(SRCPATH)$(GAMEPATH)playfield.h 
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)visualisation.o_d: $(SRCPATH)$(GAMEPATH)visualisation.cpp $(SRCPATH)$(GAMEPATH)visualisation.h $(SRCPATH)$(GAMEPATH)playfield.h $(SRCPATH)$(ENGINEPATH)console.h
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)client.o_d: $(SRCPATH)client.cpp $(SRCPATH)$(ENGINEPATH)client.h $(SRCPATH)$(ENGINEPATH)network.h $(SRCPATH)$(ENGINEPATH)console.h
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)server.o_d: $(SRCPATH)$(ENGINEPATH)server.cpp $(SRCPATH)$(ENGINEPATH)server.h $(SRCPATH)$(ENGINEPATH)network.h $(SRCPATH)$(ENGINEPATH)console.h
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)player.o_d: $(SRCPATH)$(GAMEPATH)player.cpp $(SRCPATH)$(GAMEPATH)player.h $(SRCPATH)$(ENGINEPATH)network.h $(SRCPATH)$(GAMEPATH)game.h $(SRCPATH)$(ENGINEPATH)console.h $(SRCPATH)$(GAMEPATH)playfield.h
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)playfield.o_d: $(SRCPATH)$(GAMEPATH)playfield.cpp $(SRCPATH)$(GAMEPATH)playfield.h
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

clean:
	$(RM) $(BIN) $(DBGBIN) $(DELOBJ) $(DELDBGOBJ)
