#g++ test.cpp -o program -D_REENTRANT -I/usr/include/SDL2  -lSDL2  -lSDL2 
g++ -c Board.cpp  
g++ game.cpp -o bin/game `pkg-config --cflags --libs SDL2_image sdl2` Board.o
g++ BoardTest.cpp -c `pkg-config --libs cppunit`
g++ SDLGraphics.cpp -c `pkg-config --cflags --libs SDL2_image sdl2`
g++ TestRunner.cpp -o bin/tests `pkg-config --cflags --libs cppunit` BoardTest.o Board.o
#pkg-config --cflags --libs SDL2_image
