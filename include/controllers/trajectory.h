#include <ros/ros.h>
#include <iostream>
#include <fstream>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>
#include <rosgraph_msgs/Clock.h>
#include <dynamic_reconfigure/server.h>
#include <controllers/setTrajectoryConfig.h>
#include <Eigen/Dense>
#include <ros/package.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float64.h>


using namespace geometry_msgs;
using namespace std;
using namespace ros;
using namespace Eigen;

using Eigen::Vector4d;

// Subscribers
ros::Subscriber attitude_subscriber;
ros::Subscriber command_subscriber;
ros::Subscriber local_pos_subscriber;

// Publishers
ros::Publisher trajectory_publisher;
ros::Publisher velocity_publisher;
ros::Publisher trajectory_type_pub;
ros::Publisher angular_pub;
ros::Publisher speed_pub;
ros::Publisher scale_pub;

std_msgs::Int32 traj_type;

// Pose
Vector4d pose_d;
Vector4d pose_act;

// Trajectory type
int trajectory_type;

// Trajectory speed
double speed;
double straight_speed;
std_msgs::Float64 ang_v;
std_msgs::Float64 speed_no;
std_msgs::Float64 scale_no;

// Trajectory size
double scale;

// Yaw angle
double yaw_d, initial_local_yaw, last_yaw;

// Waypoints
MatrixXd waypoints;
int waypoint;
MatrixXd curve_parameters_pose;
MatrixXd curve_parameters_velocity;
double time_end = 0;

// Time
double t;
double t_straight;

class Trajectory{
        public:
          Trajectory(int, char**);
          ~Trajectory();
          void run();
        private:
          double denormalizeAngle(double a1);
          double distance(Vector4d v1, Vector4d v2);
          void readWaypoints(std::string fileName);
          void readWaypointsStamped(std::string fileName);
          void curveFitting(MatrixXd waypoints);
};
