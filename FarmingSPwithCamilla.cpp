#include "FEHLib.cpp"
#include <vector>
using namespace std;
using namespace FEHLib;

int trainingTeam[4] {0, 0, 0, 0};

class Gym
{
  public:
    static void train(int unit)
    {
      if (unit == 1) {
        autoTrain();
      } else if (unit == 2) {
        guidedTrain(trainingTeam);
      }
    }
    static void autoTrain(){}
    static void guidedTrain(int team[4]){}
    static void swap(int team[4]) //TODO: use Hero vector instead
    {
      //TODO: click on swap units
      if (team[0] != 1) {
        if (team[2] == 1) {
          //TODO: swap A7 and A8
          team[2] = team[0];
          team[0] = 1;
        } else if (team[3] == 1) {
          //TODO: swap A7 and B8
          team[3] = team[0];
          team[0] = 1;
        }
      }

      if (team[1] != 1) {
        if (team[2] == 1) {
          //TODO: swap B7 and A8
          team[2] = team[1];
          team[1] = 1;
        } else if (team[3] == 1) {
          //TODO: swap B7 and B8
          team[3] = team[1];
          team[1] = 1;
        }
      }

      if (team[2] == 9) {
        //TODO: swap A8 and B8
        team[2] = team[3];
        team[3] = 9;
      }
      //TODO: click on fight to resume
    }
    static std::vector<Hero> convert(int team[4])
    {
      std::vector<Hero> newTeam(4);
      newTeam[0].setData('A', 7, (team[0] == 1), (team[0] == 2), (team[0] == 3), (team[0] == 4));
      newTeam[1].setData('B', 7, (team[1] == 1), (team[1] == 2), (team[1] == 3), (team[1] == 4));
      newTeam[2].setData('A', 8, (team[2] == 1), (team[2] == 2), (team[2] == 3), (team[2] == 4));
      newTeam[3].setData('B', 8, (team[3] == 1), (team[3] == 2), (team[3] == 3), (team[3] == 4));
      return newTeam;
    }
};

int main()
{
  int trainingUnit, trainingPlan;

  cout << "Welcome to Camilla's SP Gym!" << endl << endl;
  cout << "Who's on your training team?" << endl;
  cout << "\t1: Strong, independent melee unit who don't need no tanks" << endl;
  cout << "\t2: Precious glass cannon who needs help" << endl;
  cin >> trainingUnit;

  if (trainingUnit == 1) {
    cout << endl << "Got it, we'll let them use the facility freely. Just make sure they can handle the training, okay?" << endl;
  } else if (trainingUnit == 2) {
    cout << endl << "Okay, one of our tacticians will spot them. We'll assume that they're strong enough to one-shot." << endl;

    cout << endl << "By the way, which slot is the unit in?" << endl;
    int trainingUnitSlot;
    cin >> trainingUnitSlot;
    trainingTeam[trainingUnitSlot - 1] = 9;

    cout << endl << "Who else is on your team? (list left to right)" << endl;
    cout << "\t1: Tank" << endl;
    cout << "\t2: Healer" << endl; //TODO: support for tanky healer
    cout << "\t3: Dancer" << endl;
    cout << "\t4: Cheerleader" << endl;
    cout << "\t5: No one else" << endl;
    int members = 1;
    int counter = 0;
    while (members < 4) {
      int response;
      cin >> response;
      if (response == 5) break;
      else {
        if (counter == trainingUnitSlot - 1) counter++;
        trainingTeam[counter] = response;
        counter++;
        members++;
      }
    }
  }

  cout << endl << "What's your workout plan for today?" << endl;
  cout << "\t1: Stamina Spending (use up remaining stamina)" << endl;
  cout << "\t2: SP Goal (reach certain amount of SP)" << endl;
  cin >> trainingPlan;

  int reps = 0;
  if (trainingPlan == 1) {
    int stamina;
    cout << endl << "Each rep uses up 10 stamina. How much stamina do you have?" << endl;
    cin >> stamina;
    while(stamina >= 10){
      stamina -= 10;
      Gym::train(trainingUnit);
      reps++;
      //TODO: add time tracking for stamina
      cout << "Current stamina: " << stamina << endl;
    }
    cout << endl << "Great workout! Your unit completed " << reps << " reps!" << endl;
  } else if (trainingPlan == 2) {
    int SPPerRun = 72;
    int SPMultiplier, SPGoal, SPCurrent;
    cout << endl << "If you have any SP bonuses, how many times more will you get? (otherwise enter 1)" << endl;
    cin >> SPMultiplier;
    SPPerRun *= SPMultiplier;
    cout << endl << "Each rep gets you " << SPPerRun << " SP. What's your SP goal?" << endl;
    //TODO: add SP goal calculator
    cin >> SPGoal;
    cout << endl << "How much SP does your unit currently have?" << endl;
    cin >> SPCurrent;
    while(SPCurrent < SPGoal) {
      Gym::train(trainingUnit);
      SPCurrent += SPPerRun;
      reps++;
    }
    cout << endl << "Great workout! Your unit now has " << SPCurrent << " SP after completing " << reps << " reps!" << endl;
  }
  cout << endl << "Thank you for your membership! Come back soon!" << endl;
  return 0;
}
