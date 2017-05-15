//
// Created by feanor on 12/20/15.
//
#pragma once

#include <mqtt_client.h>

namespace protobuf_comm {
#if 0 /* just to make Emacs auto-indent happy */
    }
#endif


    class MqttPublisher: public MqttClient
    {
    public:
        /* Constructor for Publisher */
        MqttPublisher(std::string ,std::string, unsigned int, bool cleanSession = true);

        ~MqttPublisher();

        /** Boost signal for on publish */
        typedef
        boost::signals2::signal<void(int)>
                signal_on_publish;

        /** Boost signal for an error during publish a message. */
        typedef
        boost::signals2::signal<void (std::string, std::string, std::string)>
                signal_publisher_error_type;


        /** Signal that is invoked when the on publish.
        * @return signal
        */
        signal_on_publish & signal_published()
        { return sig_pub_; }

        /** Signal that is invoked when publish a message failed.
        * @return signal
        */
        signal_publisher_error_type &  signal_publisher_error()
        { return sig_pub_error_; }

        void set_retain(bool);
        void set_qos(int);
        void publish_to_team(std::shared_ptr <google::protobuf::Message>&);
        void publish_to_team(google::protobuf::Message &);

        void publish(std::string, std::shared_ptr <google::protobuf::Message>&);
        void publish(std::string, google::protobuf::Message &);

        std::string getTeam(){return team_name_;}

    private:
        std::string team_name_;
        bool  is_retain_;
        unsigned int qos_;

        signal_on_publish           sig_pub_;
        signal_publisher_error_type sig_pub_error_;

        void on_publish(int rc);
        void on_error();
        void check_error(int rt);

    };
}