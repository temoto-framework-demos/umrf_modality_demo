
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
#include "ta_move/temoto_action.h"
#include "ta_move/macros.h"

// Include the sevice header
#include "std_srvs/SetBool.h"

/* 
 * ACTION IMPLEMENTATION of TaMove 
 */
class TaMove : public TemotoAction
{
public:

// Constructor. REQUIRED BY TEMOTO
TaMove()
{
  // ---> YOUR CONSTRUCTION ROUTINES HERE <--- //
  std::cout << __func__ << " constructed\n";
}

// REQUIRED BY TEMOTO
void executeTemotoAction()
{
  // Input parameters
  double distance = GET_PARAMETER("distance", double);
  std::string verb = GET_PARAMETER("verb", std::string);

  // Create a node handle
  ros::NodeHandle nh;

  // Create a service client
  ros::ServiceClient srv_client = nh.serviceClient<std_srvs::SetBool>("set_bool_client_topic");

  // Create a service message and fill it out
  std_srvs::SetBool srv_msg;
  srv_msg.request.data = true;

  // Call the server
  if (srv_client.call(srv_msg))
  {
    TEMOTO_INFO_STREAM("The responce I received:" << srv_msg.response);
  }
  else
  {
    TEMOTO_ERROR("Failed to reach the bool server");
  }

  TEMOTO_INFO_STREAM("The verb that I received: '" << verb << "'");
  TEMOTO_INFO_STREAM("The number that I received: '" << distance << "'");
}

// Destructor
~TaMove()
{
  // ---> YOUR CONSTRUCTION ROUTINES HERE <--- //
  TEMOTO_PRINT_OF("Destructor", getUmrfPtr()->getName());
}

}; // TaMove class

/* REQUIRED BY CLASS LOADER */
CLASS_LOADER_REGISTER_CLASS(TaMove, ActionBase);
