
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
#include "ta_start_camera/temoto_action.h"
#include "ta_start_camera/macros.h"
#include "temoto_component_manager/component_manager_interface.h"

/* 
 * ACTION IMPLEMENTATION of TaStartCamera 
 */
class TaStartCamera : public TemotoAction
{
public:

// Constructor. REQUIRED BY TEMOTO
TaStartCamera()
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

  cmi_.initialize(this);
  ComponentTopicsRes topics = cmi_.startComponent("2d_camera");
  std::string camera_data_topic = topics.getOutputTopic("camera_data");
  for (const auto& tpc : topics.getOutputTopics())
  {
    TEMOTO_WARN_STREAM(tpc.first << " " << tpc.second);
  }

  TEMOTO_INFO_STREAM("Receiving camera data on topic: " << camera_data_topic);
}

// Destructor
~TaStartCamera()
{
  // ---> YOUR CONSTRUCTION ROUTINES HERE <--- //
  TEMOTO_PRINT_OF("Destructor", getUmrfPtr()->getName());
}

temoto_component_manager::ComponentManagerInterface<TaStartCamera> cmi_;

}; // TaStartCamera class

/* REQUIRED BY CLASS LOADER */
CLASS_LOADER_REGISTER_CLASS(TaStartCamera, ActionBase);
