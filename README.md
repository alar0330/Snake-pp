## Snake-pp

This is **Snake++**! A simple snake game for command prompt/terminal written in C++ for practice.

It is minimalistically cross-platform: currently Windows (MinGW/Cygwin) and Linux.

## Dependencies

Linux: **ncurses**
Win: **ncursesw**

## Compile

Given the **ncurses libraries** are in PATHs, compile as

- Linux:
```
g++ src/main.cpp src/nsnake.cpp src/game.cpp -lncurses -o bin/Snake-pp.bin
```

- Win:
```
g++ src\main.cpp src\nsnake.cpp src\game.cpp -lncursesw -o bin\Snake-pp.exe
```
