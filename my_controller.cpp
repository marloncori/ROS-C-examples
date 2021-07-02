#include <controller_interface/controller.h>
#include <hardwarte_interface/joint_command_interface.h>
#include <pluginlib/class_list_macros.h>
#include <std_msgs/Float64.h>

namespace my_controller_ns
{
	class MyPositionController : public controller_interface::Controller<hardware_interface::EffortJointInterface>
	{
		bool init(hardware_interface::EffortJointInterface* hw, ros::NodeHandle &n){
			
				std::string my_joint;
				if(!n.getParam("joint", my_joint)){
					ROS_ERROR("Could not find joit name");
					return false;
				}
				joint_ = hw->getHandle(my_joint); //throws on failure
				command_ = joint_.getPosition();
				//set the current joint goal to the current joint position
				
				//load gain using gains set on parameter server
				if(!n.getParam("gain", gain_)){
					ROS_ERROR("Could not find the gain paramter value");
					return false;
				}
				//start command subscriber for receiving desired joint positions
				sub_command_ = n.subscribe<std_msgs::Float64>("command", 1, &MyPositionController::setCommandCB, this);
				return true;
		}
		void update(const ros::Time& time, const ros::Duration& period){
			
			double error = command_ - joint_.getPosition();
			double commanded_effort = error*gain_;
			joint_.setCommand(commanded_effort);
		}
		
		void setCommandCB(const std_msgs::Float64ConstPtr& msg){
			command_ = msg->data;
		}
		
		void starting(const ros::Time& time){
		}
		void stopping(const ros::Time& time){
		}
		
		private:
			hardware_interface::JointHandle joint_;
			double gain_;
			double command_;
			ros::Subscriber sub_command_;
	};
	//call a special macro plugin for the class to be 
	//dynamically loaded
	PLUGINLIB_EXPORT_CLASS(my_controller_ns::MyPositionController, controller_interface::ControllerBase);

	/* create in the package a file named controller_puglins.xml
	It is a description of the controller and it indicates the path
	where the library will be placed when we compile the controller
	as well as the name, type and class of the controller 
	
	<library path="lib/libmy_controller_lib">
	   <class name="my_controller/MyPositionController"
	          type="my_controller_ns::MyPositionController"
	          base_class_type="controller_interface::ControllerBase" />
	</library>
	
	And now in the package.xml file, inside the <export> place the following line
	
	<controller_interface plugin="S{prefix}/controller_plugins.xml"/>
	
	
	and in the CMakeList.txt add the following
	
	add_library(my_controller_lib src/my_controller_lib) 
	target_link_libraries(my_controller_lib S{catkin_LIBRARIES})
	
	after catkin_make chek if it is properly registered:
	rospack plugins --attrib=plugin controller_interface | grep my_controller
	
	
	Now modify the configuration file
	Go to the controller config file and modify the controller for the
	head_pan_joint to use the new one
	
	head_pan_joint_position_controller:
	    type: my_controller/MyPositionController
		joit: head_pan_joint
		gain: 0.1
		
		*/	
}
