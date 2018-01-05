#include <iostream>
#include <unistd.h>
#include <ctime>
#include <cstdlib>

namespace FEHLib
{

using namespace std;

class Tile
{
  public:
    int xLow;
    int xHigh;
    int yLow;
    int yHigh;

    Tile(){}
    Tile(char col, int row)
    {
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

    void copyFrom(Tile &other)
    {
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

class Hero
{
  public:
    Hero(){}
    Hero(char col, int row, bool tank, bool healer, bool dancer, bool cheerleader)
    {
      tilePtr = new Tile(col, row);
      this->tank = tank;
      this->healer = healer;
      this->dancer = dancer;
      this->cheerleader = cheerleader;
    }
    Hero(char col, int row, bool tank, bool healer, bool dancer)
    {
      tilePtr = new Tile(col, row);
      this->tank = tank;
      this->healer = healer;
      this->dancer = dancer;
    }
    Hero(char col, int row, bool cheerleader)
    {
      tilePtr = new Tile(col, row);
      this->cheerleader = cheerleader;
    }
    Hero(char col, int row)
    {
      tilePtr = new Tile(col, row);
    }
    Hero(const Hero& hero) {deepCopy(hero);}
    Hero& operator=(const Hero& hero) {deepCopy(hero); return *this;}
    ~Hero() {delete tilePtr;}

    void moveTo(Tile &tile)
    {
      //TODO: move hero to tile
      tilePtr->copyFrom(tile);
    }

    void moveTo(char col, int row)
    {
      //TODO: move hero to tile
      Tile tile(col, row);
      tilePtr->copyFrom(tile);
    }

    bool isTank() {return tank;}
    bool isHealer() {return healer;}
    bool isDancer() {return dancer;}
    bool isCheerleader() {return cheerleader;}

    void setData(char col, int row, bool tank, bool healer, bool dancer, bool cheerleader)
    {
      tilePtr = new Tile(col, row);
      this->tank = tank;
      this->healer = healer;
      this->dancer = dancer;
      this->cheerleader = cheerleader;
    }

    void deepCopy(Hero other)
    {
      this->tilePtr = other.tilePtr;
      this->tank = other.tank;
      this->healer = other.healer;
      this->dancer = other.dancer;
      this->cheerleader = other.cheerleader;
    }
  private:
    bool tank = false;
    bool healer = false;
    bool dancer = false;
    bool cheerleader = false;
    Tile *tilePtr;
};

static void tap(int x, int y)
{
  system("adb shell input tap " + x + ' ' + y);
}

static void swipe(int x1, int y1, int x2, int y2)
{
  system("adb shell input swipe " + x1 + ' ' + y1
          + ' ' + x2 + ' ' + y2);
}

static void tapRand(int xLow, int xHigh, int yLow, int yHigh)
{
  srand((unsigned)time(0));
  int xRange = xHigh - xLow + 1;
  int xRand = xLow + int(xRange * rand() / (RAND_MAX + 1.0));
  int yRange = yHigh - yLow + 1;
  int yRand = xLow + int(xRange * rand() / (RAND_MAX + 1.0));
  tap(xRand, yRand);
}

static void tapRand(Tile &t)
{
  srand((unsigned)time(0));
  int xRange = t.xHigh - t.xLow + 1;
  int xRand = t.xLow + int(xRange * rand() / (RAND_MAX + 1.0));
  int yRange = t.yHigh - t.yLow + 1;
  int yRand = t.xLow + int(xRange * rand() / (RAND_MAX + 1.0));
  tap(xRand, yRand);
}

}
