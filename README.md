## Snake-pp

This is **Snake++**! A simple snake game for command prompt/terminal written in C++.

It is minimalistically cross-platform: currently Windows (under MinGW) and Linux.

## Notes

- *This repo (https://github.com/alar0330/Snake-pp) contains all the neccessary 'ncurses' Win- and Lin-libraries, so that Snake++ can be readily compiled into a binary without needing to fetch/install 'ncurses' libraries manually.*

- *This code is a **proof of concept**, rather then elegance, efficiency, or cleanness -- there are lots of ways to improve it. This is my very first app with any kind of "graphics" and I didn't want to spend more than a **day** of coding. Moreover, I wanted to avoid the std-libraries for the sake of practice (e.g. using std::list would spare some code overhead).*

## Compile

- If you **have** 'ncurses' libraries already pre-installed on your machine, compile with

-- Linux:
```
g++ -Iinc -Llib src/main.cpp src/nsnake.cpp src/game.cpp -lncurses -o bin/Snake-pp.bin
```

-- Win (under MinGW):
```
g++ -Iinc -Llib src\main.cpp src\nsnake.cpp src\game.cpp -lncursesw -o bin\Snake-pp.exe
```

- If you **don't have** 'ncurses' libraries, you can download the 'ncurses-local.zip' from this repo, unzip it directly into the main repo-folder (so that, *e.g.*, repo's inc/ merges with unzipped inc/), and compile with the additional 
```
-DGIVEMEYOURCURSES
```
flag.
