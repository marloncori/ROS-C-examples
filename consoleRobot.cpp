#include<iostream>
#include<cstdlib>
#include<vector>

void iterate(size_t, std::vector<std::string>);
void goRight(size_t, std::vector<std::string>);

int main(){
	
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
	
	size_t ahead = forward.size(); 
	iterate(ahead, forward);
	
	std::cout <<"\n It has moved " << ahead << " steps." << std::endl;
	
	std::cout << "\tNow the robot is turning right!" << std::endl;
	
	size_t turn = down.size(); 
	goRight(turn, down, right);
    
	std::cout <<"\n It has moved " << turn << " steps." << std::endl;
	
	std::cout << "\tNow the robot is moving backwards!" << std::endl;
	size_t repeat = backward.size(); 
	iterate(repeat, backward);
    
    std::cout <<"\n It has reversed " << repeat << " steps." << std::endl;
    
    std::cout <<"\t Thank you by now! " << std::endl;

	return 0;
}

void iterate(size_t times, std::vector<std::string> array){	
   for(std::vector<int>::size_type i = 0; i != times; i++){
		if(i == 0){
		std::cout << "\n\t" << array[i] << array[i+1];
	  } else if((i < times) && (i+1 < times)){
	  	std::cout << array[i] << array[i+1];
	  } else {
		break;
          }
    }
}

void goRight(size_t times, std::vector<std::string> array1, std::vector<std::string> array2){	
    for(std::vector<int>::size_type i = 0 ; i != times; i++){
	    if(i == 0){
		std::cout << "\n\t" << array1[i];
		std::cout << "\n\t" << array2[i];
	     } else {
	  	std::cout << array1[i];
	  	std::cout << array2[i];
	   }
    }  
}
