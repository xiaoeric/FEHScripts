#include <iostream>
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include <vector>

namespace FEHLib
{

using namespace std;

class Selectable
{
  public:
    int xLow;
    int xHigh;
    int yLow;
    int yHigh;
    Selectable(){}
    Selectable(int xLow, int yLow, int xHigh, int yHigh)
    {
      this->xLow = xLow;
      this->xHigh = xHigh;
      this->yLow = yLow;
      this->yHigh = yHigh;
    }
};

class Tile: public Selectable
{
  public:
    char col;
    int row;

    Tile(){}
    Tile(char col, int row)
    {
      this->col = col;
      this->row = row;
      if (col == 'A') {
        xLow = 25;
        xHigh = 180;
      } else if (col == 'B') {
        xLow = 180;
        xHigh = 360;
      } else if (col == 'C') {
        xLow = 360;
        xHigh = 540;
      } else if (col == 'D') {
        xLow = 540;
        xHigh = 720;
      } else if (col == 'E') {
        xLow = 720;
        xHigh = 900;
      } else if (col == 'F') {
        xLow = 900;
        xHigh = 1050;
      }

      if (row == 1) {
        yLow = 540;
        yHigh = 630;
      } else if (row == 2) {
        yLow = 630;
        yHigh = 810;
      } else if (row == 3) {
        yLow = 810;
        yHigh = 990;
      } else if (row == 4) {
        yLow = 990;
        yHigh = 1170;
      } else if (row == 5) {
        yLow = 1170;
        yHigh = 1350;
      } else if (row == 6) {
        yLow = 1350;
        yHigh = 1530;
      } else if (row == 7) {
        yLow = 1530;
        yHigh = 1710;
      } else if (row == 8) {
        yLow = 1710;
        yHigh = 1890;
      }
    }

    void copyFrom(Tile other)
    {
      this->col = other.col;
      this->row = other.row;
      this->xLow = other.xLow;
      this->xHigh = other.xHigh;
      this->yLow = other.yLow;
      this->yHigh = other.yHigh;
    }

    static Tile tileAt(char col, int row)
    {
      Tile newTile(col, row);
      return newTile;
    }
};

class ADB {
  public:
    static void tap(int x, int y)
    {system("adb shell input tap " + x + ' ' + y);}

    static void swipe(int x1, int y1, int x2, int y2)
    {system("adb shell input swipe " + x1 + ' ' + y1
      + ' ' + x2 + ' ' + y2);}

    static void tapRand(int xLow, int xHigh, int yLow, int yHigh)
    {tap(genRand(xLow, xHigh), genRand(yLow, yHigh));}

    static void tapRand(Selectable s)
    {tap(genRand(s.xLow, s.xHigh), genRand(s.yLow, s.yHigh));}

    static void swipeRand(Selectable from, Selectable to)
    {swipe(genRand(from.xLow, from.xHigh), genRand(from.yLow, from.yHigh),
            genRand(to.xLow, to.xHigh), genRand(to.yLow, to.yHigh));}

    static int genRand(int low, int high)
    {
      srand((unsigned)time(0));
      int range = high - low + 1;
      int random = low + int(range * rand() / (RAND_MAX + 1.0));
      return random;
    }

    static void endTurnSeq(double wait)
    {
      tapRand(endTurn);
      sleep(0.125);
      tapRand(confirmAction);
      sleep(wait);
    }

    static const Selectable confirmFight;
    static const Selectable autoBattle;
    static const Selectable confirmAction; //Used for end turn and auto battle
    static const Selectable stageClear;
    static const Selectable swapSpaces;
    static const Selectable resumeFight;
    static const Selectable endTurn;
};

const Selectable ADB::confirmFight(195, 1110, 890, 1220);
const Selectable ADB::autoBattle(750, 1900, 910, 2050);
const Selectable ADB::confirmAction(195, 1350, 885, 1145);
const Selectable ADB::stageClear(200, 750, 900, 1500);
const Selectable ADB::swapSpaces(575, 1900, 720, 2050);
const Selectable ADB::resumeFight(480, 1920, 875, 2040);
const Selectable ADB::endTurn(400, 1900, 550, 2050);

class Hero
{
  public:
    Hero(){}
    Hero(char col, int row, bool tank, bool healer, bool dancer, bool cheerleader)
    {
      tilePtr = new Tile(col, row);
      roles[0] = tank;
      roles[1] = healer;
      roles[2] = dancer;
      roles[3] = cheerleader;
    }
    Hero(char col, int row, bool tank, bool healer, bool dancer)
    {
      tilePtr = new Tile(col, row);
      roles[0] = tank;
      roles[1] = healer;
      roles[2] = dancer;
    }
    Hero(char col, int row, bool cheerleader)
    {
      tilePtr = new Tile(col, row);
      roles[3] = cheerleader;
    }
    Hero(char col, int row)
    {
      tilePtr = new Tile(col, row);
    }
    Hero(const Hero& hero) {deepCopy(hero);}
    Hero& operator=(const Hero& hero) {deepCopy(hero); return *this;}
    ~Hero() {delete tilePtr;}

    void moveTo(Tile tile)
    {
      ADB::swipeRand(*tilePtr, tile);
      tilePtr->copyFrom(tile);
      sleep(0.25);
    }

    void moveTo(char col, int row)
    {
      Tile tile(col, row);
      ADB::swipeRand(*tilePtr, tile);
      tilePtr->copyFrom(tile);
      sleep(0.25);
    }

    void swapWith(Hero &swapee)
    {
      Tile temp = this->getTile();
      this->moveTo(swapee.getTile());
      swapee.setTile(temp);
      sleep(0.25);
    }

    void swapRoles(Hero &swapee) {swap(this->roles, swapee.roles);}

    bool isTank() {return roles[0];}
    bool isHealer() {return roles[1];}
    bool isDancer() {return roles[2];}
    bool isCheerleader() {return roles[3];}
    bool isTrainee() {
      if(  roles[0] == true
        || roles[1] == true
        || roles[2] == true
        || roles[3] == true) return false;
      else return true;
    }
    vector<bool> getRoles() {return roles;}
    Tile getTile() {return *tilePtr;}

    void setData(char col, int row, bool tank, bool healer, bool dancer, bool cheerleader)
    {
      tilePtr = new Tile(col, row);
      roles[0] = tank;
      roles[1] = healer;
      roles[2] = dancer;
      roles[3] = cheerleader;
    }

    void setTile(Tile tile) {tilePtr->copyFrom(tile);}

    void setTile(char col, char row)
    {
      Tile tile(col, row);
      tilePtr->copyFrom(tile);
    }

    void setRoles(bool tank, bool healer, bool dancer, bool cheerleader)
    {
      roles[0] = tank;
      roles[1] = healer;
      roles[2] = dancer;
      roles[3] = cheerleader;
    }

    void setRoles(vector<bool> roles)
    {
      this->roles[0] = roles[0];
      this->roles[1] = roles[1];
      this->roles[2] = roles[2];
      this->roles[3] = roles[3];
    }

    void deepCopy(Hero other)
    {
      tilePtr = other.tilePtr;
      roles[0] = other.roles[0];
      roles[1] = other.roles[1];
      roles[2] = other.roles[2];
      roles[3] = other.roles[3];
    }
  private:
    vector<bool> roles = {false, false, false, false};
    Tile *tilePtr;
};

} //Don't worry this is part of namespace declaration
