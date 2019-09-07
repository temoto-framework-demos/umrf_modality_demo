
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
  std::string verb = GET_PARAMETER("verb", std::string);
  
  cmi_.initialize(this);
  ComponentTopicsRes topics = cmi_.startComponent("stt");
  std::string chatter_data_topic = topics.getOutputTopic("chatter_data");

  TEMOTO_INFO_STREAM("Receiving chatter data on topic: " << chatter_data_topic);
  chatter_sub_ = nh_.subscribe(chatter_data_topic, 1, &TaNlpUmrf::chatterSubscriber, this);
  umrf_graph_pub_ = nh_.advertise<temoto_action_engine::UmrfJsonGraph>("/umrf_graph_topic", 1);
}

/**
 * @brief chatter data subscriber callback
 * 
 * @param msg 
 */
void chatterSubscriber(const std_msgs::String& msg)
{
  TEMOTO_INFO_STREAM("got: " << msg.data);

  if (msg.data == "stop")
  {
    /*
     * Construct UMRF manually
     */ 
    Umrf umrf;
    umrf.setName("Stop");
    umrf.setSuffix("0");
    umrf.setEffect("synchronous");

    ActionParameters ap;
    ActionParameters::ParameterContainer p0("verb", "string");
    p0.setData(boost::any_cast<std::string>(std::string("stop")));
    ap.setParameter(p0);
    umrf.setInputParameters(ap);

    /*
     * Construct UMRF graph message
     */
    temoto_action_engine::UmrfJsonGraph umrf_graph_msg;
    umrf_graph_msg.graph_name = "Stop";
    umrf_graph_msg.umrf_json_strings.push_back(umrf_json_converter::toUmrfJsonStr(umrf));
    umrf_graph_msg.targets.push_back("Jack");
    umrf_graph_pub_.publish(umrf_graph_msg);
  }

  else if (msg.data == "move forward")
  {
    /*
     * Construct UMRF manually
     */ 
    Umrf umrf;
    umrf.setName("MoveForward");
    umrf.setSuffix("0");
    umrf.setEffect("synchronous");

    ActionParameters ap;
    ActionParameters::ParameterContainer p0("verb", "string");
    p0.setData(boost::any_cast<std::string>(std::string("move")));
    ap.setParameter(p0);

    ActionParameters::ParameterContainer p1("direction", "string");
    p0.setData(boost::any_cast<std::string>(std::string("forward")));
    ap.setParameter(p1);
    umrf.setInputParameters(ap);

    /*
     * Construct UMRF graph message
     */
    temoto_action_engine::UmrfJsonGraph umrf_graph_msg;
    umrf_graph_msg.graph_name = "Move Forward Graph";
    umrf_graph_msg.umrf_json_strings.push_back(umrf_json_converter::toUmrfJsonStr(umrf));
    umrf_graph_msg.targets.push_back("Jack");
    umrf_graph_pub_.publish(umrf_graph_msg);
  }

  else if (msg.data == "go back")
  {
    /*
     * Construct UMRF manually
     */ 
    Umrf umrf;
    umrf.setName("MoveBack");
    umrf.setSuffix("0");
    umrf.setEffect("synchronous");

    ActionParameters ap;
    ActionParameters::ParameterContainer p0("verb", "string");
    p0.setData(boost::any_cast<std::string>(std::string("move")));
    ap.setParameter(p0);

    ActionParameters::ParameterContainer p1("direction", "string");
    p0.setData(boost::any_cast<std::string>(std::string("back")));
    ap.setParameter(p1);
    umrf.setInputParameters(ap);

    /*
     * Construct UMRF graph message
     */
    temoto_action_engine::UmrfJsonGraph umrf_graph_msg;
    umrf_graph_msg.graph_name = "Move Back Graph";
    umrf_graph_msg.umrf_json_strings.push_back(umrf_json_converter::toUmrfJsonStr(umrf));
    umrf_graph_msg.targets.push_back("Jack");
    umrf_graph_pub_.publish(umrf_graph_msg);
  }
}

// Destructor
~TaNlpUmrf()
{
  // ---> YOUR CONSTRUCTION ROUTINES HERE <--- //
  TEMOTO_PRINT_OF("Destructor", getUmrfPtr()->getName());
}

ros::NodeHandle nh_;
temoto_component_manager::ComponentManagerInterface<TaNlpUmrf> cmi_;
ros::Subscriber chatter_sub_;
ros::Publisher umrf_graph_pub_;

}; // TaNlpUmrf class

/* REQUIRED BY CLASS LOADER */
CLASS_LOADER_REGISTER_CLASS(TaNlpUmrf, ActionBase);
