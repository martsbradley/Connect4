CC      = g++
CFLAGS  = `pkg-config --cflags SDL2_image sdl2 cppunit` -g
LDFLAGS = `pkg-config --libs SDL2_image sdl2 cppunit`

all: game test




game : main.o Board.o Game.o RenderCode.o PieceAnimation.o Connect4Grid.o SDLGraphics.o BoardStrength.o TreeBuilder.o
	$(CC) -o $@ $? $(LDFLAGS) 

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm *.o game test


test: TestRunner.o GameStateTest.o TreeBuilder.o BoardStrength.o Board.o BoardTest.o
	$(CC) -o $@ $+ $(LDFLAGS) 
