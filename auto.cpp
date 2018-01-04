#include <iostream>
#include <unistd.h>
#include <time.h>
using namespace std;

int points;
int scorePerRun;
int reward;
int target;
int staminaPerRun;
int stamina;

int main()
{
  cout << "What's your current score?" << endl;
  cin >> points;

  cout << "What's your average score per run?" << endl;
  cin >> scorePerRun; //302 for Hard 4

  cout << "What's your next reward score?" << endl;
  cin >> reward;

  cout << "What's your target score?" << endl;
  cin >> target;

  cout << "What's the stamina used per run?" << endl;
  cin >> staminaPerRun;

  cout << "What's your current stamina?" << endl;
  cin >> stamina;

  int time_stop = 0;
  int time_start = 0;
  int seconds = 0;

  while(true){
    time_t now = time(0);

    system("adb shell input tap 500 1800"); //Hard 4
    sleep(.5);
    system("adb shell input tap 500 1300"); //Confirm fight

    if(stamina < staminaPerRun){
      sleep(.5);
      system("adb shell input tap 500 1200"); //Confirm refill
      stamina += 99;
      sleep(1);
      system("adb shell input tap 500 1200"); //Close
    }

    stamina -= staminaPerRun;

    sleep(5);

    system("adb shell input tap 800 2000"); //Auto Battle
    sleep(.25);
    system("adb shell input tap 500 1100"); //Confirm auto battle

    sleep(75);

    points += scorePerRun;

    system("adb shell input tap 500 1100"); //Stage clear
    sleep(6);

    system("adb shell input tap 500 1800"); //Ok
    sleep(1);

    if(points >= reward){
      system("adb shell input tap 500 1400"); //Redeem
      reward += 2500;
      sleep(1);
    }

    time_t after = time(0);
    seconds += after - now;

    if(seconds >= 300){
      stamina += 1;
      seconds -= 300;
    }

    if(points >= target){
      break;
    }
    sleep(1);
  }

  return 0;
}
