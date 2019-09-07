
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
  ros::ServiceClient ang_srv_client = nh.serviceClient<drive_action_host::AngDrive>("/ang_drive");
  ros::ServiceClient lin_srv_client = nh.serviceClient<drive_action_host::LinDrive>("/lin_drive");
  drive_action_host::AngDrive ang_msg;
  drive_action_host::LinDrive lin_msg;
  
  // Complete message and call service to affect linear motion
  ang_msg.request.rotate_cw = false;
  ang_msg.request.rotate_ccw = false;
  lin_msg.request.move_fwd = false;
  lin_msg.request.move_bkwd = false;
  
  // Stop angular motion
  if (ang_srv_client.call(ang_msg)) {
     TEMOTO_INFO_STREAM("Angular Drive service response:" << ang_msg.response);
  } else {
     TEMOTO_ERROR("Failed to call Angular Drive service");
  }
  
  // Stop linear motion
  if (lin_srv_client.call(lin_msg)) {
     TEMOTO_INFO_STREAM("Linear Drive service response:" << lin_msg.response);
  } else {
     TEMOTO_ERROR("Failed to call Linear Drive service");
  }

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
