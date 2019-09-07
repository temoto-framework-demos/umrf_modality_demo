#include "ros/ros.h"
#include "std_msgs/String.h"
#include "temoto_action_engine/umrf.h"
#include "temoto_action_engine/umrf_json_converter.h"
#include "temoto_action_engine/UmrfJsonGraph.h"

class TextToUmrf
{
public:
  TextToUmrf()
  {
    umrf_graph_pub_ = nh_.advertise<temoto_action_engine::UmrfJsonGraph>("named_umrf_graph_topic", 1);
    chatter_data_sub_ = nh_.subscribe("chatter_data_topic", 1, &TextToUmrf::chatterSubscriberCallback, this);
    ROS_INFO("Text to UMRF node is ready to go.");
  }

private:
  /**
   * @brief chatter data subscriber callback
   * 
   * @param msg 
   */
  void chatterSubscriberCallback(const std_msgs::String& msg)
  {
    ROS_INFO_STREAM("got: " << msg.data);

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
      p1.setData(boost::any_cast<std::string>(std::string("forward")));
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

  ros::NodeHandle nh_;
  ros::Subscriber chatter_data_sub_;
  ros::Publisher umrf_graph_pub_;
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "text_to_umrf");
  TextToUmrf ttu;

  ros::AsyncSpinner spinner(0);
  spinner.start();
  ros::waitForShutdown();
}