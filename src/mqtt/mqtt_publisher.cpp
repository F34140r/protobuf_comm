//
// Created by feanor on 12/20/15.
//

#include <mqtt_publisher.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>


using namespace std;
using namespace mosqpp;

namespace protobuf_comm {
#if 0 /* just to make Emacs auto-indent happy */
    }
#endif



    MqttPublisher::MqttPublisher(string team_name, string host, unsigned int port, bool cleanSession)
            : MqttClient("pub_"+ boost::uuids::to_string(boost::uuids::random_generator()()), host, port, cleanSession)
    {
        team_name_ = team_name;
        is_retain_ = true;
        qos_ = 1;
    }

    MqttPublisher::~MqttPublisher()
    {
    }

    void MqttPublisher::publish_to_team(std::shared_ptr <google::protobuf::Message> &m)
    {
        this->publish(team_name_ + "/" + m->GetDescriptor()->full_name(), *m);
    }

    void MqttPublisher::publish_to_team(google::protobuf::Message &m)
    {
        this->publish(team_name_ + "/" + m.GetDescriptor()->full_name() , m);
    }

    void MqttPublisher::publish(string topic, std::shared_ptr <google::protobuf::Message> &m)
    {
        std::cout << "to topic " << topic <<std::endl;
        this->publish(topic,*m);
    }

    void MqttPublisher::publish(string topic, google::protobuf::Message &m)
    {
        string data;
        if(m.SerializeToString(&data)){
            mosquittopp::publish(NULL, topic.c_str(), data.size(), data.c_str(), qos_, is_retain_);
        }else{
            sig_pub_error_("Serializsation failed", clientID_, topic_);
        }
    }

    void MqttPublisher::set_retain(bool is_retain){
        is_retain_ = is_retain;
    }

    void MqttPublisher::set_qos(int qos){
        qos_ = qos;
    }

    void MqttPublisher::on_error()
    {
        sig_pub_error_("fatal error", clientID_, topic_);
    }

    void MqttPublisher::check_error(int ret)
    {
        if(0 < ret) sig_pub_error_(mosqpp::strerror(ret), clientID_, topic_);
    }

    void MqttPublisher::on_publish(int rc)
    {
        sig_pub_(rc);
    }
}