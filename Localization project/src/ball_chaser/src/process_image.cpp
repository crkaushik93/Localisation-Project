#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>
#include <numeric>

using namespace std;

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the comman_robot service to drive the robot in the
// specified direction
void drive_robot(float lin_x, float ang_z)
{
// TODO: Request a service and pass the velocities to it to drive the robot
  ball_chaser::DriveToTarget srv;
  srv.request.linear_x = lin_x;
  srv.request.angular_z = ang_z;
  
  // Call the DriveToTarget service and pass the requested velocities
  if (!client.call(srv)) {
	 ROS_ERROR("Failed to call service DriveToTarget.");
     }

}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
  // TODO: Loop through each pixel in the image and check if there's a bright white one
  // Then, identify if this pixel falls in the left, mid, or right side of the image
  // Depending on the white ball position, call the drive_bot function and pass velocities to it
  // Request a stop when there's no white ball seen by the camera

  int start = img.data.size() / 3;
  int stop = img.data.size() * 2 / 3;

  int value_white = 0;
  int position_x = 0;

  // Scan each pixel looking for a white one
  for (int i=start; i+2<stop; i+=3) {

    int color_r = img.data[i];
    int color_g = img.data[i+1];
    int color_b = img.data[i+2];

    if (color_r == 255 && color_g == 255 && color_b == 255)
    {
      int position_x_new = (i % (img.width * 3)) / 3;
      position_x += position_x_new;
      value_white += 1;
    }
  }

  float x = 0.0;
  float z = 0.0;

  if (value_white == 0)
  {
    x = 0.0; 
    z = 0.0;
  }
  else
  {
    int x_mean = position_x / value_white;
    if (x_mean < img.width / 3)
    {
      x = 0.5; 
      z = 0.5;
    }
    else if (x_mean > img.width * 2 / 3)
    {
      x = 0.5; 
      z = -0.5;
    }
    else
    {
      x = 0.5; 
      z = 0.0;
    }
  }
 drive_robot(x,z);
}

int main(int argc, char** argv)
{
  // Initialize the process_image node and create a handle to it
  ros::init(argc, argv, "process_image");
  ros::NodeHandle n;

  // Define a client service capable of requesting services from command_robot
  client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

  // Subscribe to /camera/rgb/image_raw topic to read the image data inside the
  // process_image_callback function
  ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

  // Handle ROS communication events
  ros::spin();

  return 0;
}





