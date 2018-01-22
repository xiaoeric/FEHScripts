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

  cout << endl;

  while(true){
    time_t now = time(0);

    cout << "Initiating battle!" << endl;
    system("adb shell input tap 500 1800"); //Hard 4
    sleep(.5);
    system("adb shell input tap 540 1450"); //Confirm fight

    if(stamina < staminaPerRun){
      cout << "Only " << stamina << " stamina left! Refilling..." << endl;
      sleep(.5);
      system("adb shell input tap 500 1200"); //Confirm refill
      stamina += 99;
      sleep(1);
      system("adb shell input tap 500 1200"); //Close
      cout << "Stamina refilled!" << endl;
    }

    stamina -= staminaPerRun;

    sleep(5);

    cout << "Initiating auto-battle!" << endl;
    system("adb shell input tap 800 2000"); //Auto Battle
    sleep(.25);
    system("adb shell input tap 500 1100"); //Confirm auto battle

    cout << "Waiting for battle to finish..." << endl;
    sleep(80);

    points += scorePerRun;

    system("adb shell input tap 500 1100"); //Stage clear
    cout << "Battle completed! Waiting for confirmation..." << endl;

    sleep(8);

    cout << "Confirmed!" << endl;
    system("adb shell input tap 500 1800"); //Ok
    sleep(1);

    if(points >= reward){
      cout << "You've unlocked an award at " << reward << " points!" << endl;
      system("adb shell input tap 500 1400"); //Redeem
      //reward += 2500; normal TT
      reward += 1250; //mini TT
      cout << "You're next award is available at " << reward << " points!" << endl;
      sleep(1);
    }

    time_t after = time(0);
    seconds += after - now;

    if(seconds >= 300){
      stamina += 1;
      seconds -= 300;
    }

    cout << "--Postbellum Report--" << endl;
    cout << "Stamina: " << stamina << endl;
    cout << "Points: " << points << endl;

    if(points >= target){
      cout << "You've reached your target!" << endl;
      break;
    }
    sleep(1);
  }

  return 0;
}
