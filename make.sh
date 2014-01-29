#g++ test.cpp -o program -D_REENTRANT -I/usr/include/SDL2  -lSDL2  -lSDL2 
rm *.o
g++ -c Board.cpp  
g++ BoardTest.cpp -c `pkg-config --libs cppunit`
g++ SDLGraphics.cpp -c `pkg-config --cflags SDL2_image sdl2`
g++ Game.cpp  -c `pkg-config --cflags SDL2_image sdl2`
g++ RenderCode.cpp -c `pkg-config --cflags SDL2_image sdl2`
g++ PeiceAnimation.cpp -c `pkg-config --cflags SDL2_image sdl2`
g++ Connect4Grid.cpp -c `pkg-config --cflags SDL2_image sdl2`
g++ TestRunner.cpp -o bin/tests `pkg-config --libs --cflags cppunit` BoardTest.o Board.o
echo "Linking..."
g++ main.cpp -c `pkg-config --cflags sdl2 SDL2_image` 
g++ -o bin/game  main.o SDLGraphics.o Board.o Game.o RenderCode.o Connect4Grid.o PeiceAnimation.o `pkg-config --cflags --libs SDL2_image sdl2 `
#pkg-config --cflags --libs SDL2_image
