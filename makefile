CC      = g++
CFLAGS  = `pkg-config --cflags SDL2_image sdl2 cppunit` -g -std=c++11 -Wall
LDFLAGS = `pkg-config --libs SDL2_image sdl2 cppunit`

all: game test




game : main.o Board.o Game.o RenderCode.o PieceAnimation.o SDLGraphics.o BoardStrength.o TreeBuilder.o Connect4Grid.o \
        ScoreVisitor.o DisplayVisitor.o ComputerPlayer.o
	$(CC) -g -o $@ $+ $(LDFLAGS) 

%.o: %.cpp
	$(CC) -g -c $(CFLAGS) $< -o $@

clean:
	rm *.o game test


test: TestRunner.o GameStateTest.o TreeBuilder.o BoardStrength.o Board.o BoardTest.o \
        StrengthSearchTest.o BoardStrengthTest.o ScoreVisitor.o DisplayVisitor.o
	$(CC) -o $@ $+ $(LDFLAGS) 

