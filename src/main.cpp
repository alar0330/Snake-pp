#ifdef _WIN32
  #include "../inc/ncursesw/ncurses.h"
#elif __linux__
  #include "../inc/ncurses/ncurses.h"
#else
  // other systems
#endif

#include "../inc/nsnake.hpp"
#include "../inc/util.hpp"
#include <unistd.h>

int main()
{
  // Init game variables
  int mainLINES, mainCOLS;
  int ch = 0;
  bool alive = true;

  // Start nCurses mode
  initscr();
  getmaxyx(stdscr, mainLINES, mainCOLS);

  // Size and Color checks for the terminal
  if(checkTermSize(mainLINES, mainCOLS)) return 1;
  if(checkTermColor()) return 1;

  // Start color mode and init game colors
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);

  // Define Intro window parameters
  WINDOW* inWIN;
  int inH = 15;
  int inW = 60;
  int inY = (mainLINES - inH) / 2 + 4;
  int inX = (mainCOLS - inW) / 2;

  // Define Game window parameters
  WINDOW* gameWIN;
  int gameH = 17;
  int gameW = 22;
  int gameY = (mainLINES - gameH) / 2 + 4;
  int gameX = (mainCOLS - gameW) / 2;

  // Define GameOver window parameters
  WINDOW* overWIN;
  int ovH = 9;
  int ovW = 34;
  int ovY = (mainLINES - ovH) / 2 + 4;
  int ovX = (mainCOLS - ovW) / 2;

  // Define Logo window parameters
  WINDOW* logWIN;
  int loH = 8;
  int loW = 42;
  int loY = gameY - loH - 2;
  int loX = (mainCOLS - loW) / 2;

  // Input flow settings
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
  refresh();

  // Draw Logo
  logWIN = newwin(loH, loW, loY, loX);
  drawLogo(logWIN);


  // Draw Intro window
  inWIN = newwin(inH, inW, inY, inX);
  drawIntro(inWIN);

  // Create Game window
  gameWIN = newwin(gameH, gameW, gameY, gameX);
  wattron(gameWIN, A_BOLD);

  // Create Snake and Food objects
  Snake sn(gameW/2, gameH/2, -1, 0, 6);
  Food fd;
  fd.renew(gameH, gameW, sn);

  // Switch to continuous keyboard input
  nodelay(stdscr, TRUE);

  // THE GAME LOOP
  while(alive) {

    if( (ch = getch()) != ERR ) {
      processInput(ch, sn);                // process key input
    }


    drawSnake(gameWIN, sn, false);         // erase snake from the screen
    alive = updateWorld(gameWIN, sn, fd);  // perform interactions
    sn.advance();                          // move snake
    drawMap(gameWIN);                      // draw map
    drawFood(gameWIN, fd);                 // draw food
    drawSnake(gameWIN, sn);                // draw snake
    drawStats(stdscr, gameH + gameY, sn);  // draw score
    refresh();                             // flip graphics
    wrefresh(gameWIN);                     // flip graphics gameWIN
    usleep(400000);                        // sleep
  }

  // flush whatever is left in input buffer and pause
  for (int i = 0; i < 5; i ++) {
    usleep(400000);
    ch = getch();
  }

  // switch to normal input mode
  nodelay(stdscr, FALSE);

  // Draw GameOver window
  overWIN = newwin(ovH, ovW, ovY, ovX);
  drawGameOver(overWIN);

  // Exit nCurses mode
  delwin(logWIN);
  endwin();

  return 0;
}
