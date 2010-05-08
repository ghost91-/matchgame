VERSION    = 0.0.5
CC         = g++
cc         = gcc
CFLAGS     = -Wall
DBGFLAGS   = -g
SYSTEM     = $(shell $(cc) -dumpmachine)
OBJECTS    = main.o application.o menu.o console.o game.o visualisation.o net.o server.o client.o player.o playfield.o
OBJPATH    = objects/
SRCPATH    = src/
OBJ        = $(OBJECTS:%.o=$(OBJPATH)%.o)
DBGOBJ     = $(OBJ:%.o=%.o_d)
BINNAME    = matchgame
DBGBINNAME = $(BINNAME:%=%_d)
ifeq ($(findstring mingw32, $(SYSTEM)), mingw32)
LDFLAGS    = /mingw/lib/libws2_32.a
RM         = del /FQ
BIN        = $(BINNAME:%=%.exe)
BIN        = $(DBGBINNAME:%=%.exe)
else
LDFLAGS    =
RM         = rm -rf
BIN        = $(BINNAME)
DBGBIN        = $(DBGBINNAME)
endif

all: $(BIN)

debug: $(DBGBIN)

$(BIN):  $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ) $(LDFLAGS)

$(DBGBIN): $(DBGOBJ)
	$(CC) $(CFLAGS) -o $(DBGBIN) $(DBGOBJ) $(LDFLAGS)

$(OBJPATH)main.o: $(SRCPATH)main.cpp $(SRCPATH)application.h $(SRCPATH)game.h 
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)application.o: $(SRCPATH)application.cpp $(SRCPATH)application.h $(SRCPATH)game.h $(SRCPATH)menu.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)menu.o: $(SRCPATH)menu.cpp $(SRCPATH)menu.h $(SRCPATH)console.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)console.o: $(SRCPATH)console.cpp $(SRCPATH)console.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)game.o: $(SRCPATH)game.cpp $(SRCPATH)game.h $(SRCPATH)net.h $(SRCPATH)player.h $(SRCPATH)visualisation.h $(SRCPATH)console.h $(SRCPATH)playfield.h 
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)visualisation.o: $(SRCPATH)visualisation.cpp $(SRCPATH)visualisation.h $(SRCPATH)playfield.h $(SRCPATH)console.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)net.o: $(SRCPATH)net.cpp $(SRCPATH)net.h $(SRCPATH)server.h $(SRCPATH)client.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)server.o: $(SRCPATH)server.cpp $(SRCPATH)server.h $(SRCPATH)console.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)client.o: $(SRCPATH)client.cpp $(SRCPATH)client.h $(SRCPATH)console.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)player.o: $(SRCPATH)player.cpp $(SRCPATH)player.h $(SRCPATH)net.h $(SRCPATH)game.h $(SRCPATH)console.h $(SRCPATH)playfield.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)playfield.o: $(SRCPATH)playfield.cpp $(SRCPATH)playfield.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJPATH)main.o_d: $(SRCPATH)main.cpp $(SRCPATH)application.h $(SRCPATH)game.h 
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)application.o_d: $(SRCPATH)application.cpp $(SRCPATH)application.h $(SRCPATH)game.h $(SRCPATH)menu.h
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)menu.o_d: $(SRCPATH)menu.cpp $(SRCPATH)menu.h $(SRCPATH)console.h
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)console.o_d: $(SRCPATH)console.cpp $(SRCPATH)console.h
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)game.o_d: $(SRCPATH)game.cpp $(SRCPATH)game.h $(SRCPATH)net.h $(SRCPATH)player.h $(SRCPATH)visualisation.h $(SRCPATH)console.h $(SRCPATH)playfield.h 
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)visualisation.o_d: $(SRCPATH)visualisation.cpp $(SRCPATH)visualisation.h $(SRCPATH)playfield.h $(SRCPATH)console.h
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)net.o_d: $(SRCPATH)net.cpp $(SRCPATH)net.h $(SRCPATH)server.h $(SRCPATH)client.h
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)server.o_d: $(SRCPATH)server.cpp $(SRCPATH)server.h $(SRCPATH)console.h
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)client.o_d: $(SRCPATH)client.cpp $(SRCPATH)client.h $(SRCPATH)console.h
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)player.o_d: $(SRCPATH)player.cpp $(SRCPATH)player.h $(SRCPATH)net.h $(SRCPATH)game.h $(SRCPATH)console.h $(SRCPATH)playfield.h
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

$(OBJPATH)playfield.o_d: $(SRCPATH)playfield.cpp $(SRCPATH)playfield.h
	$(CC) $(CFLAGS) $(DBGFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ) $(DBGOBJ) $(BIN) $(DBGBIN)

