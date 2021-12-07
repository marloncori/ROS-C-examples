#include<iostream>
#include<cstdlib>
#include<vector>
#include <chrono>
#include <thread>

void iterate(const int*, std::vector<std::string>, std::chrono::milliseconds*);
void goRight(const int*, std::vector<std::string>, std::vector<std::string>, std::chrono::milliseconds*);

int main(){
	
	std::chrono::milliseconds timespan(2000);
	
	std::string lines = "->->->->->->->->->->";
	std::string back = "<-<-<-<-<-<-<-<-<-<-";
	std::string guards = "|||||||||||||";
	std::string arrows = "vvvvvvvvvvvvvvvv";
	
	std::vector<std::string> forward;
	forward.push_back(lines);
	
	std::vector<std::string> backward;
	backward.push_back(back);
	
	std::vector<std::string> down;
	down.push_back(guards);
	
	std::vector<std::string> right;
	right.push_back(arrows);
	
	std::this_thread::sleep_for(timespan);
	std::cout << "\tThe robot is moving forward!" << std::endl;
	
	const int ahead = forward.size(); 
	iterate(&ahead, forward, &timespan);
	
	std::cout <<"\n It has moved " << ahead << " steps." << std::endl;
	std::this_thread::sleep_for(timespan);
	
	std::cout << "\tNow the robot is turning right!" << std::endl;
	
	const int turn = down.size(); 
	goRight(&turn, down, right, &timespan);
    
	std::cout <<"\n It has moved " << turn << " steps." << std::endl;
	std::this_thread::sleep_for(timespan);
	
	std::cout << "\tNow the robot is moving backwards!" << std::endl;
	const int repeat = backward.size(); 
	iterate(&repeat, backward, &timespan);
    
    std::cout <<"\n It has reversed " << repeat << " steps." << std::endl;
    std::this_thread::sleep_for(timespan);
    
    std::cout <<"\t Thank you by now! " << std::endl;

	return 0;
}

void iterate(const int* times, std::vector<std::string> array, std::chrono::milliseconds* delay){	
   for(size_t i{0}; i < *times; i++){
		if(i == 0){
		std::cout << "\n\t" << array[i] << array[i+1];
		std::this_thread::sleep_for(*delay);
	  } else if((i < *times) && (i+1 < *times)){
	  	std::cout << array[i] << array[i+1];
	  	std::this_thread::sleep_for(*delay);
	  }
	}
}

void goRight(const int* times, std::vector<std::string> array1, std::vector<std::string> array2, std::chrono::milliseconds* delay){	
   for(size_t i{0}; i < *times; i++){
		if(i == 0 && j == 0){
		std::cout << "\n\t" << array1[i];
		std::cout << "\n\t" << array2[i];
		std::this_thread::sleep_for(*delay);
	   } else {
	  	std::cout << array1[i];
	  	std::cout << array2[i];
	  	std::this_thread::sleep_for(*delay);
	   }
     }  
}
