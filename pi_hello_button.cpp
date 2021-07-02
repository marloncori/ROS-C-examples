#include <pigpiod_if2.h>
#include <iostream>

const int led = 5;
const int button = 27;

using namespace std;

int PigpioSetup(){
	char *addrStr = NULL;
	char *portStr = NULL;
	int pi = pigpio_start(addrStr, portStr);
	
	set_mode(pi, led, PI_OUTPUT);
	gpio_write(pi, led, 0);
	
	set_mode(pi, button, PI_INPUT);
	set_pull_up_down(pi, button, PI_PUD_UP);
	
	return pi;
}

int main( int argc, char** argv){
	
	int pin = PigpioSetup();
	if(pi >= 0){
		cout << "Daemon interface succesfully started at " << pi << endl;
	}
	else{
		cout << "Failed to connect to PIGPIO daemon - Try running sudo pigpiod "<<endl;
		return -1;
	}
	while(1){
		if(gpio_read(pi, button) == false){
			gpio_write(pi, led, 1);
			time_sleep(1.5);
			gpio_write(pi, led, 0);
		}
	}

	pigpio_stop(pi);
	return 0;
}
