#include <iostream>
#include <pigpiod_if2.h>

using namespace std;

const int button = 27;

//this callback function runs when a change of gpio pin state happens
void button_event(int pi, unsigned int gpio, unsigned int edge, unsigned int foo){
	
	static int i = 0;
	cout << "Button pressed! Press count = " << i++ << endl;
}

int main(){
	
   char *addrStr = NULL;
   char *portStr = NULL;
   int pi = pigpio_start(addrStr, portStr);
   
   if(pi>=0)
   {
      cout<<"daemon interface started ok at "<<pi<<endl;
   }
   else
   {
      cout<<"Failed to connect to PIGPIO Daemon - Try running sudo pigpiod and try again."<<endl;
      return -1;
   }
   set_mode(pi, button, PI_INPUT);
   set_pull_up_down(pi, button, PI_PUD_UP);
   
   int callbackID = callback(pi, button, RISING_EDGE, button_event);
	time_sleep(60);
	cout << "60 seconds have elapsed. Program ending." << endl;
	
	callback_cancel(callbakID);
	pigpio_stop(pi);
	return 0;
}
