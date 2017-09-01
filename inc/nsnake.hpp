#ifndef _NSNAKE_HPP_
#define _NSNAKE_HPP_

class Link {

  private:
    Link* next;

  public:
    int x, y, v, h;

    Link(int, int, int, int);

    Link* getNext() const { return next; }
    void setNext(Link* next_) { next = next_; }
};

class Snake {

  public:
    Link head;
    int length;

    Snake(int, int, int, int, int);
    ~Snake();

    Link* getLastLink();
    void grow();
    bool shrink();
    void advance();
    void advance(int, int);
    bool inside(int, int);
};

class Food {
  public:
    int x, y;
    int type;

    Food(int x=0, int y=0, int t=0);
    void renew(int h, int w, Snake& s);
};

#endif
