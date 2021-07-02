/* Arduino Code */

#include <ros.h>
#include <ros/time.h>
#include <std_msgs/Int32.h>

int min = 1;
int max = 5000;
int rand_num;


ros::NodeHandle nh;
std_msgs::Int32 rand_msg;
ros::Publisher pub_random("/random_number", &rand_msg);

char frameid[] = "/random_data";

//this function returns a random number
int RandomNumber(){
	rand_num = random(min, max);
	return rand_num;
}

void setup(){
	nh.initNode();
	nh.advertise(pub_random);
}

void loop(){
	rand_msg.data = RandomNumber();
	pub_random.publish(&rand_msg);
	nh.spinOnce();
	delay(1000);
}
	
	
	
}
