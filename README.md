## Snake-pp

This is **Snake++**! A simple snake game for command prompt written in C++.

It is minimalistically cross-platform: currently Windows (under MinGW) and Linux.

It uses nowadays depricated 'usleep()', since 'std::thread' is not fully supported in MinGW32
and I did't want to spend time looking for more elegant solutions.

## Compile

Linux:
```
(coming soon)
```

Win (under MinGW):
```
g++ -Iinc -Llib src\main.cpp src\nsnake.cpp src\util.cpp -lncursesw -o bin\Snake-pp.exe
```
