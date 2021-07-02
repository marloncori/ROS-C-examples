#include <iostream>
#include <pigpiod_if2.h>

using namespace std;

int main(){
	
	//initialize connection with pigpio daemon
	char *addrStr = NULL;
	char *portStr = NULL;
	int pi = gpio_start(addStr, portStr);
	
	//open serial port connection
	int UARTHandle = serial_open(pi, "/dev/ttyAMA0", 115200, 0);
	//gpio serial pins 14 and 15
	
	//int UARTHandle = serial_open(pi, "/dev/ttyUSB0", 115200, 0)
	//for use with FTDI USB device
	cout << "UARTHangle = " << UARTHandle << endl;
	time_sleep(.1);
	
	//check serial buffer
	cout << "Data available start: " << serial_data_available(pi, UARTHandle) << " bytes" << endl;
	
	//write a few test bytes
	serial_write_byte(pi, UARTHandle, 6);
	serial_write_byte(pi, UARTHandle, 'f');
	serial_write_byte(pi, UARTHandle, 'F');
	
	//give time to transmit
	time_sleep(.1);
	
	//check serial buffer again
	cout << "Data available after writing: " << serial_data_available(pi, UARTHandle) << " bytes" << endl;
	
	//read and display one byte
	cout <<"Byte read = " << serial_read_byte(pi, UARTHandle)<< endl;

	//check serial buffer again
	cout << "Data available after reading a byte: " << serial_data_available(pi, UARTHandle)<< " bytes" << endl;
	
	//read and display last two bytes
	char inA = serial_read_byte(pi, UARTHandle);
	cout << "Byte read = " << inA << endl;
	char inB = serial_read_byte(pi, UARTHandle);
	cout << "Byte read = " << inB << endl;
	
	serial_close(pi, UARTHandle);
	pigpio_stop(pi);
	return 0;
}
