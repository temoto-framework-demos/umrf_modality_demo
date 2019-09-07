
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
#include "ta_nlp_umrf/temoto_action.h"
#include "ta_nlp_umrf/macros.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "temoto_er_manager/temoto_er_manager_interface.h"
#include "temoto_component_manager/component_manager_interface.h"
#include "temoto_action_engine/UmrfJsonGraph.h"
#include "temoto_action_engine/umrf_json_converter.h"

/* 
 * ACTION IMPLEMENTATION of TaNlpUmrf 
 */
class TaNlpUmrf : public TemotoAction
{
public:

// Constructor. REQUIRED BY TEMOTO
TaNlpUmrf()
{
  // ---> YOUR CONSTRUCTION ROUTINES HERE <--- //
  std::cout << __func__ << " constructed\n";
}

// REQUIRED BY TEMOTO
void executeTemotoAction()
{
  // Input parameters
  std::string verb = GET_PARAMETER("speech_to_text", std::string);
  
  TEMOTO_INFO_STREAM("Invoking Speech To UMRF pipe ...");
  cmi_.initialize(this);
  ermi_.initialize(this);

  temoto_core::TopicContainer pipe_topics = cmi_.startPipe("speech_to_umrf");
  std::string umrf_graph_topic = pipe_topics.getOutputTopic("named_umrf_graph");
  std::string relay_args = umrf_graph_topic + " " + "/umrf_graph_topic";

  TEMOTO_INFO_STREAM("Setting up a topic relay");
  ermi_.loadResource("topic_tools", "relay", relay_args);
}

// Destructor
~TaNlpUmrf()
{
  // ---> YOUR CONSTRUCTION ROUTINES HERE <--- //
  TEMOTO_INFO_STREAM("Destructor");
}

temoto_component_manager::ComponentManagerInterface<TaNlpUmrf> cmi_;
temoto_er_manager::ERManagerInterface<TaNlpUmrf> ermi_;


}; // TaNlpUmrf class

/* REQUIRED BY CLASS LOADER */
CLASS_LOADER_REGISTER_CLASS(TaNlpUmrf, ActionBase);
