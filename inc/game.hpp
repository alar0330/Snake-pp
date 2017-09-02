#ifndef _GAME_HPP_
#define _GAME_HPP_

class Game
{
  private:
    int score;
    int gameSpeed;
    int speedLevel;

    const static int chHead = 'O';
    const static int chBody = 'o';
    const static int chGoodFood = 'Q';
    const static int chBadFood = 'T';

    enum { MIN_H = 40, MIN_W = 60 };

  public:
    Game();

    void drawMap(WINDOW*);
    void drawSnake(WINDOW*, Snake&, bool b = true);
    void drawFood(WINDOW*, Food&);
    void processInput(int, Snake&);
    bool updateWorld(WINDOW*, Snake&, Food&);
    void drawLogo(WINDOW*);
    void drawStats(WINDOW*, int, Snake&);
    bool checkTermSize(int, int);
    bool checkTermColor();
    void drawIntro(WINDOW*);
    void drawGameOver(WINDOW*);
    int getGameSpeed();
    int getScore();
};

#endif // _GAME_HPP_
