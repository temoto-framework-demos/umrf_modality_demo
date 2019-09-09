
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
#include "temoto_action_engine/umrf_json_converter.h"
#include "temoto_action_engine/umrf.h"
#include "temoto_action_engine/UmrfJsonGraph.h"
#include "ros/ros.h"

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
  
  // Advertise the publisher
  umrf_graph_pub_ = nh_.advertise<temoto_action_engine::UmrfJsonGraph>("/umrf_graph_topic", 1);

  // Execute the command
  onParameterUpdate();
}

void onParameterUpdate()
{
  /*
   * Construct UMRF manually
   */ 
  Umrf umrf;
  umrf.setName("Nameless");
  umrf.setSuffix("0");
  umrf.setEffect("synchronous");

  ActionParameters ap;
  ap.setParameter("direction", "string", boost::any_cast<std::string>(std::string("none")));
  ap.setParameter("verb", "string", boost::any_cast<std::string>(std::string("stop ")));
  umrf.setInputParameters(ap);

  /*
   * Construct UMRF graph message
   */
  temoto_action_engine::UmrfJsonGraph umrf_graph_msg;
  umrf_graph_msg.graph_name = "Web Agent Graph";
  umrf_graph_msg.umrf_json_strings.push_back(umrf_json_converter::toUmrfJsonStr(umrf));
  umrf_graph_msg.targets.push_back("Jack");

  // Publish the message
  umrf_graph_pub_.publish(umrf_graph_msg);
}

// Destructor
~TaStop()
{
  // ---> YOUR CONSTRUCTION ROUTINES HERE <--- //
  TEMOTO_PRINT_OF("Destructor", getUmrfPtr()->getName());
}

ros::NodeHandle nh_;
ros::Publisher umrf_graph_pub_;

}; // TaStop class

/* REQUIRED BY CLASS LOADER */
CLASS_LOADER_REGISTER_CLASS(TaStop, ActionBase);
