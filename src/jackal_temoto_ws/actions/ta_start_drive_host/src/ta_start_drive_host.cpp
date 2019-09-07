
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
#include "ta_start_drive_host/temoto_action.h"
#include "ta_start_drive_host/macros.h"
#include "temoto_er_manager/temoto_er_manager_interface.h"

/* 
 * ACTION IMPLEMENTATION of TaStartDriveHost 
 */
class TaStartDriveHost : public TemotoAction
{
public:

// Constructor. REQUIRED BY TEMOTO
TaStartDriveHost()
{
  // ---> YOUR CONSTRUCTION ROUTINES HERE <--- //
  std::cout << __func__ << " constructed\n";
}

// REQUIRED BY TEMOTO
void executeTemotoAction()
{
  // Input parameters
  std::string verb = GET_PARAMETER("verb", std::string);
  std::string noun = GET_PARAMETER("noun", std::string);

  TEMOTO_INFO_STREAM("Starting the Jackal drive host ...");
  ermi_.initialize(this);
  ermi_.loadResource("drive_action_host", "drive_host.py");
  TEMOTO_INFO_STREAM("Jackal drive host invoked successfully");
}

// Destructor
~TaStartDriveHost()
{
  // ---> YOUR CONSTRUCTION ROUTINES HERE <--- //
  TEMOTO_INFO_STREAM("Destructor");
}

temoto_er_manager::ERManagerInterface<TaStartDriveHost> ermi_;

}; // TaStartDriveHost class

/* REQUIRED BY CLASS LOADER */
CLASS_LOADER_REGISTER_CLASS(TaStartDriveHost, ActionBase);
