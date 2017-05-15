//
// Created by feanor on 12/20/15.
//

#include <mqtt_subscriber.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace std;
using namespace mosqpp;

namespace protobuf_comm {
#if 0 /* just to make Emacs auto-indent happy */
    }
#endif


    MqttSubscriber::MqttSubscriber(std::string host, int port, bool cleanSession) :
            MqttClient("sub_"+boost::uuids::to_string(boost::uuids::random_generator()()), host, port, cleanSession)
    {

        message_register_     = new MessageRegister();
        own_message_register_ = true;
    }

    MqttSubscriber::~MqttSubscriber()
    {
    }

    void MqttSubscriber::subscribe(std::string team, std::shared_ptr <google::protobuf::Message> &m)
    {
        this->subscribe(team, m->GetDescriptor()->full_name());
    }

    void MqttSubscriber::subscribe(std::string team, google::protobuf::Message &m)
    {
        this->subscribe(team, m.GetDescriptor()->full_name());
    }
    void MqttSubscriber::subscribe(string team, string msg_type, int qos)
    {

        int mid;

        msg_type_ = msg_type;
        message_register_->add_message_type(msg_type_);

        topic_ = team + "/" + msg_type_;
        mosquittopp::subscribe(&mid, topic_.c_str(), 1);
    }


    void MqttSubscriber::on_message(const struct mosquitto_message *message)
    {
        string recvmesg = string((char*)message->payload, (char*)message->payload + message->payloadlen);
        google::protobuf::Message* m = message_register_->create_msg(msg_type_);
        m->ParseFromString(recvmesg);

        const google::protobuf::Descriptor *desc = m->GetDescriptor();
        const google::protobuf::EnumDescriptor *enumdesc = desc->FindEnumTypeByName("CompType");
        if (! enumdesc) {
            throw std::logic_error("Message does not have CompType enum");
        }
        const google::protobuf::EnumValueDescriptor *compdesc =
                enumdesc->FindValueByName("COMP_ID");
        const google::protobuf::EnumValueDescriptor *msgtdesc =
                enumdesc->FindValueByName("MSG_TYPE");
        if (! compdesc || ! msgtdesc) {
            throw std::logic_error("Message CompType enum hs no COMP_ID or MSG_TYPE value");
        }
        int comp_id = compdesc->number();
        int msg_type = msgtdesc->number();
        if (comp_id < 0 || comp_id > std::numeric_limits<uint16_t>::max()) {
            throw std::logic_error("Message has invalid COMP_ID");
        }
        if (msg_type < 0 || msg_type > std::numeric_limits<uint16_t>::max()) {
            throw std::logic_error("Message has invalid MSG_TYPE");
        }
        sig_rcvd_(message->topic, comp_id, msg_type, clientID_, shared_ptr<google::protobuf::Message>(m));
    }

    void MqttSubscriber::on_subscribe(int mid, int qos_count, const int *granted_qos)
    {
        sig_sub_(mid, topic_, qos_count, granted_qos);
    }

    void MqttSubscriber::on_error()
    {
        sig_sub_error_("fatal error", clientID_, topic_, msg_type_);
    }

    void MqttSubscriber::check_error(int ret)
    {
        if(0 < ret) sig_sub_error_(mosqpp::strerror(ret), clientID_, topic_, msg_type_);
    }
}