#include <ncursesw/ncurses.h>
#include "../inc/nsnake.hpp"

static int chHead = 'O';
static int chBody = 'o';
static int chGoodFood = 'Q';
static int chBadFood = 'T';
static int score = 0;

const int MIN_H = 40;
const int MIN_W = 60;

void drawMap(WINDOW* _scr)
{
  box(_scr, 0 , 0);
}

void drawSnake(WINDOW* _scr, Snake& _sn)
{
  wattron(_scr, COLOR_PAIR(3));
  mvwaddch(_scr, _sn.head.y, _sn.head.x, chHead);

  Link* pnext = _sn.head.getNext();
  while (pnext) {
    mvwaddch(_scr, pnext->y, pnext->x, chBody);
    pnext = pnext->getNext();
  }
  wattroff(_scr, COLOR_PAIR(3));
}

void drawFood(WINDOW* _scr, Food& _fd)
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

bool updateWorld(WINDOW* _scr, Snake& _sn, Food& _fd)
{
  int mapH, mapW;
  getmaxyx(_scr, mapH, mapW);

  if (_sn.inside(_fd.x, _fd.y)) {
    if (_fd.type) {
        _sn.shrink();
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

void processInput(int _ch, Snake& _sn)
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

int getScore() {
  return score;
}

void drawLogo(WINDOW* _logw)
{
  int x, y;

  y = 0;
  x = 0;
  mvwprintw(_logw, ++y, x,"  XXX   X   X     XX  X   X  XXXX ");
  mvwprintw(_logw, ++y, x," X      X   X    X X  X  X   X    ");
  mvwprintw(_logw, ++y, x," X      XX  X    X X  X X    X    ");
  mvwprintw(_logw, ++y, x,"  XX    X X X   X  X  XXX    XXXX ");
  mvwprintw(_logw, ++y, x,"    X   X  XX   XXXX  X  X   X    ");
  mvwprintw(_logw, ++y, x,"    X   X   X  X   X  X  X   X    ");
  mvwprintw(_logw, ++y, x," XXx    X   X  X   X  X   X  XXXX ");

  y = 2;
  x += 30;
  wattron(_logw, COLOR_PAIR(1));
  mvwprintw(_logw, ++y, x,"   X     X   ");
  mvwprintw(_logw, ++y, x," xxXxx xxXxx ");
  mvwprintw(_logw, ++y, x,"   X     X   ");
  wattroff(_logw, COLOR_PAIR(1));

  wrefresh(_logw);
}

void drawStats(WINDOW* _s, int _shift, Snake& _sn)
{
  int ys;
  int xs;
  getmaxyx(_s, ys, xs);

  mvwprintw(_s, _shift +1, xs/2-10, " MEALS: %d times", getScore());
  mvwprintw(_s, _shift + 2, xs/2-10, "   FAT: %d kg", _sn.length);
}

void drawIntro(WINDOW* _inw)
{
  //wattron(_inw, COLOR_PAIR(1));
  box(_inw, 0, 0);
  wmove(_inw, 1,0);

  wprintw(_inw, "  Greeting! This is Snake++ text game written in C++. \n\n");
  wprintw(_inw, "  Version: ");
  wattron(_inw, A_BOLD);
  wprintw(_inw, " v1.1a (alpha)\n");
  wattroff(_inw, A_BOLD);
  wprintw(_inw, "  Author:  ");
  wattron(_inw, A_BOLD);
  wprintw(_inw, " Alaroff\n\n");
  wattroff(_inw, A_BOLD);
  wprintw(_inw, "  Game intructions:  \n");
  wprintw(_inw, "            - use keypad to command your snake\n");
  wprintw(_inw, "            - eat apples (Q) to grow\n");
  wprintw(_inw, "            - if you eat mushroom (T) you'll lose weight\n");
  wprintw(_inw, "            - don't hit walls and try to eat yourself\n");
  wprintw(_inw, "            - have fun!\n\n");
  wattron(_inw, A_BOLD);
  wprintw(_inw, "                      HIT ANY KEY                   \n");
  wattroff(_inw, A_BOLD);

	wrefresh(_inw);
	getch();
	wclear(_inw);
	wrefresh(_inw);
	delwin(_inw);
}

void drawGameOver(WINDOW* _inw)
{
  box(_inw, 0, 0);
  wmove(_inw, 1,0);

  wattron(_inw, COLOR_PAIR(1));
  wattron(_inw, A_BOLD);
  wprintw(_inw, "            GAME OVER! \n\n\n");
  wattroff(_inw, A_BOLD);
  wattroff(_inw, COLOR_PAIR(1));

  wprintw(_inw, "       Try better next time! \n\n\n");
  wattron(_inw, A_BOLD);
  wprintw(_inw, "           HIT ANY KEY   \n");
  wattroff(_inw, A_BOLD);
	wrefresh(_inw);

	getch();
	wclear(_inw);
	wrefresh(_inw);
	delwin(_inw);
}

bool checkTermColor()
{
  if(!has_colors())
	{
	  printw(".--------------------------------------------------.\n");
    printw("| Your terminal does not support color mode.       |\n");
    printw("| Please change your terminal settings or          |\n");
    printw("|              try using another another terminal! |\n");
    printw(".--------------------------------------------------.\n");
    printw("                     HIT ANY KEY                   \n");
    getch();
    endwin();
    return true;
  }
  return false;
}

bool checkTermSize(int _h, int _w)
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
