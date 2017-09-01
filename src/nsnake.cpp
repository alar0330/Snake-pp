#include "../inc/nsnake.hpp"
#include <cstdlib>
#include <ctime>

Link::Link(int x_, int y_, int h_, int v_) :
  next(nullptr),
  x(x_),
  y(y_),
  v(v_),
  h(h_) {
}

Link::~Link() {
  // empty
}

// CTOR: head is created even if size_ < 1
Snake::Snake(int xh_, int yh_, int hh_, int vh_, int size_) :
  head(xh_, yh_, hh_, vh_),
  length(1)
{
  // create body
  for (int i = 1; i < size_; i++) {
    grow();
  }
}

// DTOR
Snake::~Snake()
{
  while ( shrink() ) {
    // empty
  }
}

// Move snake
void Snake::advance()
{
  // move head
  head.x += head.h;
  head.y += head.v;

  int pv, ph, nv, nh;

  // save p
  pv = head.v;
  ph = head.h;

  Link* pnext = &head;

  while (pnext->getNext()) {
    pnext = pnext->getNext();

    nv = pnext->v;
    nh = pnext->h;

    pnext->x += nh;
    pnext->y += nv;

    pnext->v = pv;
    pnext->h = ph;

    pv = nv;
    ph = nh;
  }

  return;
}

// Force-move snake for Alpha-build
void Snake::advance(int h_, int v_)
{
  head.h = h_;
  head.v = v_;
  advance();
}

// Create new link at the end of snake
void Snake::grow()
{
  Link* plast = getLastLink();
  plast->setNext(new Link(plast->x - plast->h,
                          plast->y - plast->v,
                          plast->h, plast->v));
  ++length;
}

// Remove last link
bool Snake::shrink()
{
  if (length < 2) return false;

  Link* plast = &head;
  Link* pprev = nullptr;

  while (plast->getNext()) {   // while plast is not really *last* link
    pprev = plast;
    plast = plast->getNext();
  }
  delete plast;                // safe: we can't attempt to delete 'head'
  pprev->setNext(nullptr);
  --length;
  return true;
}

// Last link pointer
Link* Snake::getLastLink()
{
  Link* plast = &head;
  while (plast->getNext()) {
    plast = plast->getNext();
  }
  return plast;
}

bool Snake::inside(int x_, int y_)
{
  Link* pcheck = &head;
  while (pcheck) {
    if (x_ == pcheck->x && y_ == pcheck->y) return true;
    pcheck = pcheck->getNext();
  }
  return false;
}


Food::Food(int x_, int y_, int t_) :
  x(x_),
  y(y_),
  type(t_) {
}

void Food::renew(int h_, int w_, Snake& sn_) {
  srand(time(0));
  do {
      x = rand() % (w_ - 2) + 1;
      y = rand() % (h_ - 2) + 1;
  } while (sn_.inside(x,y));

  type = (rand() % 100 > 75)? 1 : 0;
}







