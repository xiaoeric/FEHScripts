#include <iostream>
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include <vector>

namespace FEHLib
{

using namespace std;

class Tile
{
  public:
    char col;
    int row;
    int xLow;
    int xHigh;
    int yLow;
    int yHigh;

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
      //TODO: move hero to tile
      tilePtr->copyFrom(tile);
    }

    void moveTo(char col, int row)
    {
      //TODO: move hero to tile
      Tile tile(col, row);
      tilePtr->copyFrom(tile);
    }

    void swapWith(Hero &swapee)
    {
      Tile temp = this->getTile();
      this->moveTo(swapee.getTile());
      swapee.setTile(temp);
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
