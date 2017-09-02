// Snake++ project: main.cpp file

/**
 *  This is Snake++! A simple snake game for
 *                            command prompt/terminal written in C++.
 *
 *  @version  v1.3a (02.09.2017)
 *  @author   Alaroff
 *
 * INFO:
 *
 *   - It is minimalistically cross-platform:
 *                          currently Windows (under MinGW) and Linux.
 *
 *   - This repo (https://github.com/alar0330/Snake-pp) contains all the
 *     neccessary ncurses Win- and Lin-libraries, so that Snake++ can be
 *     readily compiled into a binary without needing to fetch/install
 *     ncurses libraries manually.
 *
 * NOTES:
 *
 *   - This code is a proof of concept, rather then elegance, efficiency,
 *     or cleanness -- there are lots of ways to improve it. This is my
 *     very first app with any kind of "graphics" an which I didn't want
 *     to spend more than a day of coding. Moreover, I wanted to avoid the
 *     std-libraries for the sake of practice (e.g. using std::list would
 *     spare some code overhead).
 *
 *   - This code uses nowadays depricated (?) POSIX function 'usleep()',
 *     since 'std::thread' is not fully supported in MinGW32 and I did't
 *     want to spend time looking for more elegant solutions. Anyway,
 *     Win-library of ncurses is POSIX-based through e.g. MinGW anyhow.
 */


// if compile with destributed copy of ncurses library
#ifdef GIVEMEYOURCURSES
  #ifdef _WIN32
    #include "../inc/ncursesw/ncurses.h"
  #elif __linux__
    #include "../inc/ncurses/curses.h"
  #else
    // other systems
  #endif

// if compile with already pre-installed libraries of ncurses
#else
  #ifdef _WIN32
    #include <ncursesw/ncurses.h>
  #elif __linux__
    #include <ncurses/ncurses.h>
  #else
    // other systems
  #endif
#endif

#include "../inc/nsnake.hpp"
#include "../inc/game.hpp"
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

  // create THE Game object
  Game game;

  // Size and Color checks for the terminal
  if(game.checkTermSize(mainLINES, mainCOLS)) return 1;
  if(game.checkTermColor()) return 1;

  // Start color mode and init game colors
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);

  // Define Intro window parameters
  WINDOW* inWIN;
  int inH = 16;
  int inW = 62;
  int inY = (mainLINES - inH) / 2 + 4;
  int inX = (mainCOLS - inW) / 2;

  // Define Game window parameters
  WINDOW* gameWIN;
  int gaH = 17;
  int gaW = 22;
  int gaY = (mainLINES - gaH) / 2 + 4;
  int gaX = (mainCOLS - gaW) / 2;

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
  int loY = gaY - loH - 2;
  int loX = (mainCOLS - loW) / 2;

  // Input flow settings
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
  refresh();

  // Draw Logo
  logWIN = newwin(loH, loW, loY, loX);
  game.drawLogo(logWIN);


  // Draw Intro window
  inWIN = newwin(inH, inW, inY, inX);
  game.drawIntro(inWIN);

  // Create Game window
  gameWIN = newwin(gaH, gaW, gaY, gaX);
  wattron(gameWIN, A_BOLD);

  // Create Snake and Food objects
  Snake sn(gaW/2, gaH/2, -1, 0, 6);
  Food fd;
  fd.renew(gaH, gaW, sn);

  // Switch to continuous keyboard input
  nodelay(stdscr, TRUE);

  // THE GAME LOOP
  while(alive) {

    if( (ch = getch()) != ERR ) {
      game.processInput(ch, sn);                // process key input
    }

    game.drawSnake(gameWIN, sn, false);         // erase snake from the screen
    alive = game.updateWorld(gameWIN, sn, fd);  // perform interactions
    sn.advance();                            // move snake
    game.drawMap(gameWIN);                      // draw map
    game.drawFood(gameWIN, fd);                 // draw food
    game.drawSnake(gameWIN, sn);                // draw snake
    game.drawStats(stdscr, gaH + gaY, sn);  // draw score
    refresh();                                  // flip graphics
    wrefresh(gameWIN);                          // flip graphics gameWIN
    usleep(game.getGameSpeed());                // sleep
  }

  // flush whatever is left in input buffer and pause
  for (int i = 0; i < 5; i ++) {
    usleep(300000);
    ch = getch();
  }

  // switch to normal input mode
  nodelay(stdscr, FALSE);

  // Draw GameOver window
  overWIN = newwin(ovH, ovW, ovY, ovX);
  game.drawGameOver(overWIN);

  // Exit nCurses mode
  delwin(logWIN);
  endwin();

  return 0;
}
