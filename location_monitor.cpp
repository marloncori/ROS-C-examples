#include <math.h>
#include <vector>
#include <string>

#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "location_monitor/LandmarkDistance.h"

using namespace location_monitor::LandmarkDistance;
using namespace std::vector;
using namespace std::string;

class Landmark{
	public:
		Landmark(string name, double x, double y)
			: name(name), x(x), y(y) {}
		string name;
		double x;
		double y;
};

class LandmarkMonitor{
	public:
		LandmarkMonitor(): landmarks_() {
			InitLandmarks();
		}
		void OdomCallback(const nav_msgs::Odometry::ConstPtr& msg){
			double x = msg->pose.pose.position.x;
			double y = msg->pose.pose.position.y;
			ROS_INFO("x: %f, y: %f", x, y);
		}
	private:
		vector<Landmark> landmarks_;
		LandmarkDistance FindClosest(double x, double y){
			LandmarkDistance result;
			result.distance = -1;
			
			for(size_t i = 0; i < landmarks_.size(); i++){
				const Landmark& landmark = landmarks_[i];
				double xd = landmark.x - x;
				double yd = landmark.y - y;
				double distance = sqrt(xd*xd + yd*yd);
				
				if(result.distance < 0 || distance < result.distance){
					result.name = landmark.name;
					result.distance = distance;
				}
			}
		 return result;
		}
		void InitLandmarks(){
			landmarks_.push_back(Landmark("Cube", 0.31, -0.99));
			landmarks_.push_back(Landmark("Dumpster", 0.11, -2.42));
			landmarks_.push_back(Landmark("Cylinder", -1.14, -2.88));
			landmarks_.push_back(Landmark("Barrier", -2.59, -0.83));
			landmarks_.push_back(Landmark("Bookshelf", -0.09, 0.53));			
		}
};
	
	int main( int argc, char** argv ){
		
		ros::init(argc, argv, "location_monitor");
		ros::NodeHandle nh;
		LandmarkMonitor monitor;
		ros::Subscriber sub = nh.subscriber("odom", 10, &LandmarkMonitor::OdomCallback, &monitor);
		ros::spin();
			
		return 0;
	}

