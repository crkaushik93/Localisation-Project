# Where-Am-I---Localisation-Project---RSEND-project-3

Project will create a 2D occupancy grid and 3D octomap from a simulated environment using your own robot with the RTAB-Map package.

RTAB-Map (Real-Time Appearance-Based Mapping) is a popular solution for SLAM to develop robots that can map environments in 3D. RTAB-Map has good speed and memory management, and it provides custom developed tools for information analysis.

Being able to leverage RTAB-Map with your own robots will lead to a solid foundation for mapping and localization.

For this project we will be using the #rtabmap_ros package, which is a ROS wrapper (API) for interacting with RTAB-Map. 

We will develop our own package to interface with the #rtabmap_ros package.

We will build upon our localization project to make the necessary changes to interface the robot with RTAB-Map. An example of this is the addition of an RGB-D camera.

We will need to generate the appropriate launch files to launch the robot and map its surrounding environment.

When our robot is launched we will #teleop around the room to generate a proper map of the environment.

the recommended robot configuration requires: 
1) A 2D Laser, providing #sensor_msgs/LaserScan messages
2) Odometry sensors, providing #nav_msgs/Odometry messages
3) 3D Camera, compatible with #openni_launch, #openni2_launch or #freenect_launch ROS packages

