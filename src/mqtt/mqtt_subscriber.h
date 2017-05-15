//
// Created by feanor on 12/20/15.
//

#pragma once

#include <mqtt_client.h>
#include <message_register.h>

namespace protobuf_comm {
#if 0 /* just to make Emacs auto-indent happy */
    }
#endif

    class MqttSubscriber : public MqttClient
    {
    public:
        /** Constructor for Subscriber */
        MqttSubscriber(std::string host, int port, bool cleanSession = true);

        ~MqttSubscriber();
        template <class MT>
        typename std::enable_if<std::is_base_of<google::protobuf::Message, MT>::value, void>::type
        subscribe(std::string team)
        {
            MT m;
            this->subscribe(team, m.GetDescriptor()->full_name());
        }
        void subscribe(std::string team, std::shared_ptr <google::protobuf::Message>&);
        void subscribe(std::string team, google::protobuf::Message &);
        void subscribe(std::string team, std::string msg_type, int qos = 1);

        /** Boost signal for on subscribe */
        typedef
        boost::signals2::signal<void(int, std::string, int, const int*)>
                signal_on_subscribe;

        /** Boost signal for an error during subscribe a message. */
        typedef
        boost::signals2::signal<void (std::string, std::string, std::string, std::string)>
                signal_subscriber_error_type;

        /** Boost signal for specific received message */
        typedef
        boost::signals2::signal<void(std::string, uint16_t, uint16_t, std::string,
                                     std::shared_ptr<google::protobuf::Message>)>
                signal_received_type;

        /** Signal that is invoked when the on subscribe.
        * @return signal
        */
        signal_on_subscribe & signal_subscribed()
        { return sig_sub_; }

        /** Signal that is invoked when subscribe failed.
        * @return signal
        */
        signal_subscriber_error_type &  signal_subscriber_error()
        { return sig_sub_error_; }

        /** Signal that is invoked when a message has been received.
        * @return signal
        */
        signal_received_type &  signal_received()
        { return sig_rcvd_; }

    private:

        MessageRegister *message_register_;
        bool             own_message_register_;

        signal_on_subscribe             sig_sub_;
        signal_received_type            sig_rcvd_;
        signal_subscriber_error_type    sig_sub_error_;

        std::string                     msg_type_;

        void on_message(const struct mosquitto_message *message);
        void on_subscribe(int mid, int qos_count, const int *granted_qos);
        void on_error();
        void check_error(int rt);

    };
}
