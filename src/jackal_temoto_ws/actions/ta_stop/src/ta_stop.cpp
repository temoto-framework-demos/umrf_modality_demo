
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *
 *  The basis of this file has been automatically generated
 *  by the TeMoto action package generator. Modify this file
 *  as you wish but please note:
 *
 *    WE HIGHLIY RECOMMEND TO REFER TO THE TeMoto ACTION
 *    IMPLEMENTATION TUTORIAL IF YOU ARE UNFAMILIAR WITH
 *    THE PROCESS OF CREATING CUSTOM TeMoto ACTION PACKAGES
 *    
 *  because there are plenty of components that should not be
 *  modified or which do not make sence at the first glance.
 *
 *  See TeMoto documentation & tutorials at: 
 *    https://temoto-telerobotics.github.io
 *
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

/* REQUIRED BY TEMOTO */
#include <class_loader/class_loader.h>
#include "ta_stop/temoto_action.h"
#include "ta_stop/macros.h"

// Include the service headers
#include "drive_action_host/AngDrive.h"
#include "drive_action_host/LinDrive.h"


/* 
 * ACTION IMPLEMENTATION of TaStop 
 */
class TaStop : public TemotoAction
{
public:

// Constructor. REQUIRED BY TEMOTO
TaStop()
{
  // ---> YOUR CONSTRUCTION ROUTINES HERE <--- //
  std::cout << __func__ << " constructed\n";
}

// REQUIRED BY TEMOTO
void executeTemotoAction()
{
  // Input parameters
  std::string verb = GET_PARAMETER("verb", std::string);
  
  // Create a node handle
  ros::NodeHandle nh;
  
  // Initialize service clients and messages
  ros::Publisher lin_drive_pub = nh.advertise<drive_action_host::LinDrive>("lin_drive", 10);
  ros::Publisher ang_drive_pub = nh.advertise<drive_action_host::LinDrive>("ang_drive", 10);

  TEMOTO_INFO_STREAM("Waiting for subscribers");
  while ((ang_drive_pub.getNumSubscribers() < 1) || (lin_drive_pub.getNumSubscribers() < 1))
  {
    ros::Duration(0.1).sleep();
  }

  drive_action_host::AngDrive ang_msg;
  drive_action_host::LinDrive lin_msg;
  
  // Complete message and call service to affect linear motion
  ang_msg.rotate_cw = false;
  ang_msg.rotate_ccw = false;
  lin_msg.move_fwd = false;
  lin_msg.move_bkwd = false;
  
  // Stop angular motion
  lin_drive_pub.publish(lin_msg);
  ang_drive_pub.publish(ang_msg);
  ros::Duration(0.5).sleep();
}

// Destructor
~TaStop()
{
  // ---> YOUR CONSTRUCTION ROUTINES HERE <--- //
  TEMOTO_PRINT_OF("Destructor", getUmrfPtr()->getName());
}

}; // TaStop class

/* REQUIRED BY CLASS LOADER */
CLASS_LOADER_REGISTER_CLASS(TaStop, ActionBase);
