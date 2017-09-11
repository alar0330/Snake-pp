## Snake-pp

This is **Snake++**! A simple snake game for command prompt/terminal written in C++.

It is minimalistically cross-platform: currently Windows (MinGW/Cygwin) and Linux.

## Notes

*This code is a **proof of concept**, rather then elegance, efficiency, or cleanness -- there are lots of ways to improve it. This is my very first app with any kind of "graphics". Moreover, I wanted an implementation with self-made singly-linked lists for the sake of practice (e.g. using std::list would spare some code overhead, using mere array would make it even simpler).*

## Compile

If you **have** 'ncurses' libraries already pre-installed on your machine, compile with

- Linux:
```
g++ src/main.cpp src/nsnake.cpp src/game.cpp -lncurses -o bin/Snake-pp.bin
```

- Win:
```
g++ src\main.cpp src\nsnake.cpp src\game.cpp -lncursesw -o bin\Snake-pp.exe
```
