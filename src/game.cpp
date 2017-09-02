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

Game::Game() :
  score(0), gameSpeed(400000), speedLevel(0)
{}

void Game::drawMap(WINDOW* _scr)
{
  box(_scr, 0, 0);
}

int Game::getGameSpeed()
{
  return gameSpeed;
}

void Game::drawSnake(WINDOW* _scr, Snake& _sn, bool _draw)
{
  if (_draw){
    wattron(_scr, COLOR_PAIR(3));
    mvwaddch(_scr, _sn.head.y, _sn.head.x, chHead);

    Link* pnext = _sn.head.getNext();
    while (pnext) {
      mvwaddch(_scr, pnext->y, pnext->x, chBody);
      pnext = pnext->getNext();
    }
    wattroff(_scr, COLOR_PAIR(3));
  }
  else {
    Link* pnext = &_sn.head;
    while (pnext) {
      mvwaddch(_scr, pnext->y, pnext->x, ' ');
      pnext = pnext->getNext();
    }
  }

}

void Game::drawFood(WINDOW* _scr, Food& _fd)
{
  if (_fd.type == 0) {
    wattron(_scr, COLOR_PAIR(2));
    mvwaddch(_scr, _fd.y, _fd.x, chGoodFood);
  }
  else {
    wattron(_scr, COLOR_PAIR(1));
    mvwaddch(_scr, _fd.y, _fd.x, chBadFood);
  }
  wattroff(_scr, COLOR_PAIR(1));
}

bool Game::updateWorld(WINDOW* _scr, Snake& _sn, Food& _fd)
{
  int mapH, mapW;
  getmaxyx(_scr, mapH, mapW);

  if (_sn.inside(_fd.x, _fd.y)) {
    if (_fd.type) {
        _sn.shrink();
        gameSpeed = (int) gameSpeed*0.95;
        speedLevel++;
    }
    else {
        _sn.grow();
    }

    _fd.renew(mapH, mapW, _sn);
    ++score;
  }

  if (_sn.inside(_sn.head.x + _sn.head.h, _sn.head.y + _sn.head.v)) {
    return false;
  }

  if (_sn.head.x + _sn.head.h < 1 || _sn.head.x + _sn.head.h > mapW - 2) {
    return false;
  }

  if (_sn.head.y + _sn.head.v < 1 || _sn.head.y + _sn.head.v > mapH - 2) {
    return false;
  }

  return true;
}

void Game::processInput(int _ch, Snake& _sn)
{

  switch(_ch) {
    case KEY_UP :
      _sn.head.v = (_sn.head.v == 1 )? 1 : -1;
      _sn.head.h = 0;
      break;

    case KEY_DOWN :
      _sn.head.v = (_sn.head.v == -1 )? -1 : 1;
      _sn.head.h = 0;
      break;

    case KEY_LEFT :
      _sn.head.v = 0;
      _sn.head.h = (_sn.head.h == 1 )? 1 : -1;
      break;

    case KEY_RIGHT :
      _sn.head.v = 0;
      _sn.head.h = (_sn.head.h == -1 )? -1 : 1;
      break;

    case 'a' :
      _sn.grow();
      break;

    case 's' :
      _sn.shrink();
      break;

    default :
      break;
  }
}

int Game::getScore() {
  return score;
}

void Game::drawLogo(WINDOW* _scr)
{
  int x, y;

  y = 0;
  x = 0;
  mvwprintw(_scr, ++y, x,"  XXX   X   X     XX  X   X  XXXX ");
  mvwprintw(_scr, ++y, x," X      X   X    X X  X  X   X    ");
  mvwprintw(_scr, ++y, x," X      XX  X    X X  X X    X    ");
  mvwprintw(_scr, ++y, x,"  XX    X X X   X  X  XXX    X    ");
  mvwprintw(_scr, ++y, x,"    X   X  XX   XXXX  X  X   X    ");
  mvwprintw(_scr, ++y, x,"    X   X   X  X   X  X  X   X    ");
  mvwprintw(_scr, ++y, x," XXx    X   X  X   X  X   X  XXXX ");

  y = 2;
  x += 30;
  wattron(_scr, COLOR_PAIR(1));
  mvwprintw(_scr, ++y, x,"   X     X   ");
  mvwprintw(_scr, ++y, x," xxXxx xxXxx ");
  mvwprintw(_scr, ++y, x,"   X     X   ");
  wattroff(_scr, COLOR_PAIR(1));

  wrefresh(_scr);
}

void Game::drawStats(WINDOW* _scr, int _shift, Snake& _sn)
{
  int ys;
  int xs;
  getmaxyx(_scr, ys, xs);

  mvwprintw(_scr, _shift +1, xs/2-10, " MEALS: %3d times", getScore());
  mvwprintw(_scr, _shift + 2, xs/2-10, "   FAT: %3d kg", _sn.length);
  mvwprintw(_scr, _shift + 3, xs/2-10, " SPEED: %3d lvl", speedLevel);
}

void Game::drawIntro(WINDOW* _scr)
{
  //wattron(_inw, COLOR_PAIR(1));
  box(_scr, 0, 0);
  wmove(_scr, 1,0);

  wprintw(_scr, "  Greeting! This is Snake++ text game written in C++. \n\n");
  wprintw(_scr, "  Version: ");
  wattron(_scr, A_BOLD);
  wprintw(_scr, " v1.3a (alpha)\n");
  wattroff(_scr, A_BOLD);
  wprintw(_scr, "  Author:  ");
  wattron(_scr, A_BOLD);
  wprintw(_scr, " Alaroff\n\n");
  wattroff(_scr, A_BOLD);
  wprintw(_scr, "  Game intructions:  \n");
  wprintw(_scr, "            - use keypad to command your snake\n");
  wprintw(_scr, "            - eat apples (Q) to grow\n");
  wprintw(_scr, "            - if you eat mushroom (T) you'll lose weight,\n");
  wprintw(_scr, "                   but your snake will start running faster!\n");
  wprintw(_scr, "            - don't hit walls and try to eat yourself\n");
  wprintw(_scr, "            - have fun!\n\n");
  wattron(_scr, A_BOLD);
  wprintw(_scr, "                      HIT ANY KEY                   \n");
  wattroff(_scr, A_BOLD);

	wrefresh(_scr);
	getch();
	wclear(_scr);
	wrefresh(_scr);
	delwin(_scr);
}

void Game::drawGameOver(WINDOW* _scr)
{
  box(_scr, 0, 0);
  wmove(_scr, 1,0);

  wattron(_scr, COLOR_PAIR(1));
  wattron(_scr, A_BOLD);
  wprintw(_scr, "            GAME OVER! \n\n\n");
  wattroff(_scr, A_BOLD);
  wattroff(_scr, COLOR_PAIR(1));

  wprintw(_scr, "       Try better next time! \n\n\n");
  wattron(_scr, A_BOLD);
  wprintw(_scr, "           HIT ANY KEY   \n");
  wattroff(_scr, A_BOLD);
	wrefresh(_scr);

	getch();
	wclear(_scr);
	wrefresh(_scr);
	delwin(_scr);
}

bool Game::checkTermColor()
{
  if(!has_colors())
	{
	  printw(".--------------------------------------------------.\n");
    printw("| Your terminal does not support color mode.       |\n");
    printw("| Please change your terminal settings or          |\n");
    printw("|                      try using another terminal! |\n");
    printw(".--------------------------------------------------.\n");
    printw("                     HIT ANY KEY                   \n");
    getch();
    endwin();
    return true;
  }
  return false;
}

bool Game::checkTermSize(int _h, int _w)
{
  if (_h < MIN_H || _w < MIN_W) {
    printw(".--------------------------------------------------.\n");
    printw("| Your window has %3d lines and %3d colums.        |\n", _h, _w);
    printw("| Please resize it to have at least                |\n");
    printw("|         %3d lines and %3d columns and try again! |\n", MIN_H, MIN_W);
    printw(".--------------------------------------------------.\n");
    printw("                     HIT ANY KEY                   \n");
    getch();
    endwin();
    return true;
  }
  return false;
}


