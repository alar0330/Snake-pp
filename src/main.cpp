#include <ncursesw/ncurses.h>
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

    wclear(gameWIN);                       // clear Gmae window
                                           //    (lazy way to do this)

    if( (ch = getch()) != ERR ) {
      processInput(ch, sn);                // process key input
    }

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

  usleep(10000);            // flush whatever is left in input buffer
  nodelay(stdscr, FALSE);   // switch to normal input mode

  // Draw GameOver window
  overWIN = newwin(ovH, ovW, ovY, ovX);
  drawGameOver(overWIN);

  // Exit nCurses mode
  delwin(logWIN);
  endwin();

  return 0;
}
