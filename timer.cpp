#include <iostream>
#include <conio.h>
#include <chrono>
#include <ctime>

using namespace std;
int main( int argc, char** argv){
	while(1){
		auto start = std::chrono::system_clock::now();
    	// Some computation here
    	auto end = std::chrono::system_clock::now();

    	std::chrono::duration<double> elapsed_seconds = end-start;
    	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

		auto elapsed = elapsed_seconds.count();     
		if(elapsed == 0.4){
			cout << "4 seconds have passed!" << endl;
			start = end;
		}
	}
	getch();
	
	return 0;
}
