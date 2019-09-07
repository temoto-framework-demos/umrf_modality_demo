
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
#include "ta_drive/temoto_action.h"
#include "ta_drive/macros.h"
#include "ros/ros.h"
#include "drive_action_host/AngDrive.h"
#include "drive_action_host/LinDrive.h"


/* 
 * ACTION IMPLEMENTATION of TaDrive 
 */
class TaDrive : public TemotoAction
{
public:

// Constructor. REQUIRED BY TEMOTO
TaDrive()
{
  // ---> YOUR CONSTRUCTION ROUTINES HERE <--- //
  std::cout << __func__ << " constructed\n";
}

// REQUIRED BY TEMOTO
void executeTemotoAction()
{
  // Input parameters
  std::string verb = GET_PARAMETER("verb", std::string);
  std::string direction = GET_PARAMETER("direction", std::string);
  
  // Create a node handle
  ros::NodeHandle nh;
   
  // Handle translation commands
  if ((verb == "go")||(verb == "move")||(verb == "drive"))
  {
    // Initialize service client and message
    ros::ServiceClient lin_srv_client = nh.serviceClient<drive_action_host::LinDrive>("lin_drive");
    drive_action_host::LinDrive lin_msg;
   
    // if direction = positive
    if ((direction == "foreward"||(direction == "forewards"))||(direction == "ahead")||(direction == "forth")||(direction == "ahead")||(direction == "fore"))
    {
      // Complete message and call service to affect linear motion
      lin_msg.request.move_fwd = true;
      lin_msg.request.move_bkwd = false;
      
      if (lin_srv_client.call(lin_msg)) 
      {
        TEMOTO_INFO_STREAM("Linear Drive service response:" << lin_msg.response);
      } 
      else 
      {
        TEMOTO_ERROR("Failed to call Linear Drive service");
      }
   	}

    // if direction = negative 
    else if ((direction == "backward") ||
             (direction == "rearward") ||
             (direction == "rearwards") ||
             (direction == "rear") ||
             (direction == "back") ||
             (direction == "backwards") ||
             (direction == "aft")) 
    {
   		// Complete message and call service to affect linear motion
   		lin_msg.request.move_fwd = false;
   		lin_msg.request.move_bkwd = true;
   		
   		if (lin_srv_client.call(lin_msg)) 
      {
   			TEMOTO_INFO_STREAM("Linear Drive service response:" << lin_msg.response);
   		} 
      else 
      {
   			TEMOTO_ERROR("Failed to call Linear Drive service");
   		}
   	}
    // otherwise
    else 
    {
   		//direction error
   		TEMOTO_ERROR("Can't move in that direction");
   	} //end translation direction
   
  // Handle rotation commands
  } 
  else if ((verb == "rotate")||(verb=="turn"))
  {   	
   	// Initialize service client and message
   	ros::ServiceClient ang_srv_client = nh.serviceClient<drive_action_host::AngDrive>("ang_drive");
   	drive_action_host::AngDrive ang_msg;
   	
   	// if direction = positive (left, counterclockwise, anti
   	if ((direction == "left")||(direction == "counter clockwise")||(direction == "anti clockwise")) {

   		// Complete message and call service to affect angular motion
   		ang_msg.request.rotate_ccw = true;
   		ang_msg.request.rotate_cw = false;
   		
   		if (ang_srv_client.call(ang_msg)) 
      {
   			TEMOTO_INFO_STREAM("Angular Drive service response:" << ang_msg.response);
   		}
      else 
      {
   			TEMOTO_ERROR("Failed to call Angular Drive service");
   		}
   	}

    // else if direction = negative (right, clockwise)
    else if ((direction == "right")||(direction == "clockwise"))
    {
   		// Complete message and call service to affect angular motion
   		ang_msg.request.rotate_ccw = false;
   		ang_msg.request.rotate_cw = true;
   		
   		if (ang_srv_client.call(ang_msg)) 
      {
   			TEMOTO_INFO_STREAM("Angular Drive service response: " << ang_msg.response);
   		}
      else 
      {
   			TEMOTO_ERROR("Failed to call Angular Drive service");
   		}
   		
   	}
    else
    { 
   		//direction error
   		TEMOTO_ERROR("Can't turn in that direction");   	
   	} //end rotation direction
  }
  else 
  {
    // verb error
    TEMOTO_ERROR("Can't execute that verb");
  }
}

// Destructor
~TaDrive()
{
  // ---> YOUR CONSTRUCTION ROUTINES HERE <--- //
  TEMOTO_PRINT_OF("Destructor", getUmrfPtr()->getName());
}

}; // TaDrive class

/* REQUIRED BY CLASS LOADER */
CLASS_LOADER_REGISTER_CLASS(TaDrive, ActionBase);
