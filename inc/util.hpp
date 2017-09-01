#ifndef _UTIL_HPP_
#define _UTIL_HPP_

void drawMap(WINDOW*);
void drawSnake(WINDOW*, Snake&);
void drawFood(WINDOW*, Food&);
void processInput(int, Snake&);
bool updateWorld(WINDOW*, Snake&, Food&);
int getScore();
void drawLogo(WINDOW*);
void drawStats(WINDOW*, int, Snake&);
bool checkTermSize(int, int);
bool checkTermColor();
void drawIntro(WINDOW*);
void drawGameOver(WINDOW*);

#endif
