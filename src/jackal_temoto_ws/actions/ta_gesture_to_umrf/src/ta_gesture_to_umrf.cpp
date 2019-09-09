
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
#include "ta_gesture_to_umrf/temoto_action.h"
#include "ta_gesture_to_umrf/macros.h"

#include "temoto_component_manager/component_manager_interface.h"
#include "temoto_action_engine/UmrfJsonGraph.h"
#include "temoto_action_engine/umrf_json_converter.h"
#include "std_msgs/Int16.h"

/* 
 * ACTION IMPLEMENTATION of TaGestureToUmrf 
 */
class TaGestureToUmrf : public TemotoAction
{
public:

// Constructor. REQUIRED BY TEMOTO
TaGestureToUmrf()
{
  // ---> YOUR CONSTRUCTION ROUTINES HERE <--- //
  std::cout << __func__ << " constructed\n";
}

// REQUIRED BY TEMOTO
void executeTemotoAction()
{
  // Input parameters
  detect_gestures = GET_PARAMETER("detect_gestures", std::string);
  umrf_target = GET_PARAMETER("umrf_target", std::string);

  TEMOTO_INFO_STREAM("Invoking gesture detection pipe ...");
  cmi_.initialize(this);
  temoto_core::TopicContainer pipe_topics = cmi_.startPipe("gesture_detection");
  std::string gesture_topic = pipe_topics.getOutputTopic("detected_gesture");

  TEMOTO_INFO_STREAM("Setting up publishers and subscribers ...");
  gesture_sub_ = nh_.subscribe(gesture_topic, 1, &TaGestureToUmrf::gestureCallback, this);
  umrf_graph_pub_ = nh_.advertise<temoto_action_engine::UmrfJsonGraph>("/umrf_graph_topic", 1);

  TEMOTO_INFO_STREAM("Gesture to UMRF parser is good to go");
}

/**
 * @brief Gesture messasge callback
 * 
 * @param incoming_gesture_msg 
 */
void gestureCallback(const std_msgs::Int16& incoming_gesture_msg)
{
  if (incoming_gesture_msg.data != gesture_msg_.data)
  {
    temoto_action_engine::UmrfJsonGraph umrf_json_graph_msg;
    gesture_msg_.data = incoming_gesture_msg.data;
    TEMOTO_INFO_STREAM("Changed gesture to: " << gesture_msg_.data);

    // Publish an UMRF based on the detected gesture
    if (gesture_msg_.data == 0)
    {
      umrf_json_graph_msg = generateUmrfGraphMsg("stop", "", umrf_target);
    }

    // Publish the umrf graph
    umrf_graph_pub_.publish(umrf_json_graph_msg);
  }
}

/**
 * @brief Generates umrf message based on verb and direction
 * 
 * @param verb 
 * @param direction 
 * @return Umrf 
 */
temoto_action_engine::UmrfJsonGraph generateUmrfGraphMsg(const std::string& verb, const std::string& direction, const std::string target)
{
  /*
   * Construct UMRF manually
   */
  temoto_action_engine::UmrfJsonGraph umrf_graph_msg;
  umrf_graph_msg.targets.push_back(target);
  Umrf umrf;

  if (verb == "stop")
  {
    umrf_graph_msg.graph_name = "Stop Graph";
    umrf.setName("TaStop");
    umrf.setSuffix("0");
    umrf.setEffect("aynchronous");

    ActionParameters ap;
    ap.setParameter("verb", "string", boost::any_cast<std::string>(std::string(verb)));
    umrf.setInputParameters(ap);
  }
  else
  {
    umrf_graph_msg.graph_name = "Drive Graph";
    umrf.setName("TaDrive");
    umrf.setSuffix("0");
    umrf.setEffect("aynchronous");

    ActionParameters ap;
    ap.setParameter("direction", "string", boost::any_cast<std::string>(std::string(direction)));
    ap.setParameter("verb", "string", boost::any_cast<std::string>(std::string(verb)));
    umrf.setInputParameters(ap);
  }

  umrf_graph_msg.umrf_json_strings.push_back(umrf_json_converter::toUmrfJsonStr(umrf));
  return umrf_graph_msg;
}

// Destructor
~TaGestureToUmrf()
{
  // ---> YOUR CONSTRUCTION ROUTINES HERE <--- //
  TEMOTO_PRINT_OF("Destructor", getUmrfPtr()->getName());
}

ros::NodeHandle nh_;
ros::Subscriber gesture_sub_;
ros::Publisher umrf_graph_pub_;
temoto_component_manager::ComponentManagerInterface<TaGestureToUmrf> cmi_;
std_msgs::Int16 gesture_msg_;

// Action parameters
std::string detect_gestures;
std::string umrf_target;

}; // TaGestureToUmrf class

/* REQUIRED BY CLASS LOADER */
CLASS_LOADER_REGISTER_CLASS(TaGestureToUmrf, ActionBase);
