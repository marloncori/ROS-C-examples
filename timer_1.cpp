#include<iostream>
#include<conio.h>
#include<chrono>
#include<ctime>

using namespace std;
using namespace chrono;

int main(){
	
	steady_clock::time_point intervalo;
	steady_clock::time_point intervalo2;
	seconds sec(4);
	seconds secs(6);
	
	while(true){
		steady_clock::time_point agora = steady_clock::now();
		//duration<double> elapsedTime = duration_cast<duration<double>>(end-start);
		if(agora >= intervalo && intervalo != intervalo2){	
		//if(elapsedTime.count() <= 500){
			cout << "\tLED is on... \n" << endl;
			intervalo = agora + sec;
		}
		if(agora >= intervalo2){	
		//if(elapsedTime.count() <= 500){
			cout << "\tLED is off... \n" << endl;
			intervalo2 = agora + secs;
		}
	}
	
    getch();	
	return 0;
}
