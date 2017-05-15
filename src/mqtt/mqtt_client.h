//
// Created by feanor on 12/4/15.
//

#pragma once

#include <mosquittopp.h>
#include <message_register.h>

#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <boost/asio.hpp>
#include <boost/signals2.hpp>

#include <string>

namespace protobuf_comm {
#if 0 /* just to make Emacs auto-indent happy */
    }
#endif



    class MqttClient : public mosqpp::mosquittopp
    {
    public:
        typedef std::string ClientID;

        MqttClient(std::string clientID, std::string host, unsigned int port, bool cleanSession = true);
        ~MqttClient();

        std::string getClientID() { return clientID_;}
        std::string getHost() { return host_;}
        int getPort() {return port_;}

        void reinitialise(bool cleanSession = true);
        void reinitialise(std::string clientID, bool cleanSession = true);
        void connect();
        void connect(std::string bindAddress);
        void reconnect();
        void disconnect();

        void setUsernameAndPassword(std::string username, std::string password);
        void setKeepAlive(int keepAlive);
        void setAutoReconnect(bool reconnect);
        void setTls(std::string cafile, std::string capath=NULL, std::string certfile=NULL);
        void setTlsOptions(int verifyMode, std::string version=NULL, std::string ciphers=NULL);
        void setTlsInsecure(bool insecure);
        void setPSK(std::string psk, std::string identity, std::string ciphers=NULL);

        /** Boost signal for on connect */
        typedef
        boost::signals2::signal<void(int, std::string)>
                signal_on_connect;
        /** Boost signal for on disconnect */
        typedef
        boost::signals2::signal<void(int, std::string)>
                signal_on_disconnect;


        /** Signal that is invoked when the connection has been established.
        * @return signal
        */
        signal_on_connect & signal_connected()
        { return sig_connected_; }

        /** Signal that is invoked when the connection is closed.
        * @return signal
        */
        signal_on_disconnect & signal_disconnected()
        { return sig_disconnected_; }

    protected:

        unsigned int    port_;
        int    keepAlive_;
        bool   bConnected_;
        bool   bAutoReconnect_;

        ClientID    clientID_;
        std::string host_;
        std::string username_;
        std::string password_;
        std::string topic_;

    private:
        signal_on_connect        sig_connected_;
        signal_on_disconnect     sig_disconnected_;
        //signal_error_type        sig_error_;

        void on_connect(int rc);
        void on_disconnect(int rc);
        virtual void on_publish(int rc) {return;};
        virtual void on_subscribe(int rc){return;};
        virtual void on_message(const struct mosquitto_message *message){return;};
        void on_log(int level, const char *str);
        virtual void on_error() { std::cout << "Error"; }
        virtual void check_error(int ret) { std::cout << mosqpp::strerror(ret); }

        void run_mqtt();
    };
} // end namespace protobuf_comm