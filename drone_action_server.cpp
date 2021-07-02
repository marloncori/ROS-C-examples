/* action file MyMsgAction.action

#goal
float64 x
float64 y
float64 z
---
#result
string status
---
#feedback
float64 distance 


Parrot Ar.Drone simulation*/

#include "ros/ros.h"
#include "actionlib/server/simple_action_server.h"
#include "actions_example/MyMsgAction.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Empty.h"
#include "std_msgs/Bool.h"
#include "std_msgs/String.h"
#include "math.h"

//class containing action server methods
class MoveDroneAction{
	
	protected:
		ros::NodeHandle nh_;
		actionlib::SimpleActionServer<actions_example::MyMsgAction>action_server_;
		std::string action_name_;
		
		actions_example::MyMsgActionFeedback feedback_;
		actions_example::MyMsgActionResult result_;
		
		//define your subscriber
		ros::Subscriber get_pos_sub_;
		geometry_msgs::Pose pose_info_;
		
		ros::Publisher cmd_vel_pub_;
		ros::Publisher posctrl_pub_;
		ros::Publisher takeoff_pub_;
		std_msgs::Empty lift;
	
	public:
		MoveDroneAction(std::string name):
			action_server_(nh_, name, boost::bind(&MoveDroneAction::actionCb, this, _1), false),
			action_name_(name)
		{
			initializeSubscribers();
			initializePublishers();
			action_server_.start();
		}
		~MoveDroneAction(void){
			
		}
	
	private: 
		void initializeSubscribers(void){
			gt_pos_sb_ = nh_.subscribe("/drone/gt_pose", 1, &MoveDroneAction::subscriberCb, this);
			ROS_INFO("Subscribers initialized!");
		}
		void initializePublishers(void){
			cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
			poscrtrl_pub_ = nh_.advertise<std_msgs::Bool>("/drone/posctrl", 1);
			takeoff_pub_ = nh_.advertise<std_msgs::Empty>("/drone/takeoff", 1);
			ROS_INFO("Publishers initialized!");
		}
		void subscriberCb(const geometry_msg::PoseConstPtr &info){
			pos_info_.position.x = info-> position.x;
			pos_info_.position.y = info-> position.y;
			pos_info_.position.z = info-> position.z;
		}
		double callDistance(geometry_msgs::Pose current, const actions_example::MyMsgActionGoalConstPtr &goal){
			double dist;
			dist = sqrt((goal->x - current.position.x), 2) + pow((goal->y));
			std::cout << "distance: " << dist <<"\n";
			return dist;
		}
		//main action server callback
		void actionCb(cosnt actions_example::MyMsgActionGoalConstPtr &goal){
			ros::Rate rate(50);
			bool success = true;
			
			geometry_msgs::Twist move;
			move.linear.x = goal->x;
			move.linear.x = goal->y;
			move.linear.x = goal->z;
			takeoff_pub_.publish(lift_);
			std_msgs::Bool temp;
			temp.data = true;
			posctrl_pub_.publish(temp);
			std::cout << "Received position coordinates: \n";
			std::cout << "x: "<<goal->x<<"\ny: "<<goal->y<<"\nz: "<<goal->z<<"\n";
			
			do{
				cmd_vel_pub_.publish(move);
				feedback_.distance = callDistance(pos_info_, goal);
				action_server_.publishFeedback(feedback_);
				
				if(action_server_.isPreemptRequested() || ros::ok()){
					move.linear.x = pos_info_.position.x;
					move.linear.x = pos_info_.position.y;
					move.linear.x = pos_info_.position.z;
					cmb_vel_pub_.publish(move);
					ROS_INFO("%s: Preempted", action_name_.c_str());
					action_server_.setPreempted();
					success = false;
					break;
				}
				rate.sleep();
			}while(feeback_.distance > 0.1);
			
			if(success){
				result_.status = "Arrived at destination!";
				ROS_INFO("%s: Succeeded", action_name_.c_str());
				action_server_.setSuceeded(result_);
			}
		}
};

int main( argc, char** argv){
	ros::init(argc, argv, "drone_action_server");
	MoveDroneAction drone("go_to_point_A5");
	ros::Rate loop_rate(0.5);
	int n=0;
	while(ros::ok()){
		ros::spinOnce();
		ROS_INFO("%d", n);
		n++;
		rate.sleep();
	}
	
	return 0;
}
/* 

find_package(catkin_REQUIERED_COMPONENTS
actionlib
actionlib_msgs
message_generation
roscpp
std_msgs
)

find_package(Boost_REQUIERED_COMPONENTS_system)

add_action_files(
FILES
MyMsgAction.action
)
generate_messages8
DEPENDENCIES
actionlib_msgs  std_msgs
)

On terminal:
rostopic echo /go_to_point_A5/result */
