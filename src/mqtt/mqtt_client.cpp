//
// Created by feanor on 12/4/15.
//

#include "mqtt_client.h"
#include <google/protobuf/descriptor_database.h>
#include <google/protobuf/dynamic_message.h>
#include <unistd.h>


using namespace std;
using namespace mosqpp;

namespace protobuf_comm {
#if 0 /* just to make Emacs auto-indent happy */
    }
#endif


    MqttClient::MqttClient(string clientID, string host, unsigned int port, bool cleanSession) :
            mosquittopp(clientID.c_str(), cleanSession)
    {
        lib_init();
        clientID_             = clientID;
        host_                 = host;
        port_                 = port;
        keepAlive_            = 60;
        bConnected_           = false;
        bAutoReconnect_       = true;
    }

    MqttClient::~MqttClient()
    {
    }

    void MqttClient::connect()
    {
        mosquittopp::connect(host_.c_str(), port_, keepAlive_);
        run_mqtt();
    }

    void MqttClient::connect(string bindAddress)
    {
        mosquittopp::connect(host_.c_str(), port_, keepAlive_, bindAddress.c_str());
    }

    void MqttClient::reinitialise(bool cleanSession)
    {
        this->reinitialise(clientID_);
    }

    void MqttClient::reinitialise(string clientID, bool cleanSession)
    {
        clientID_ = clientID;
        mosquittopp::reinitialise(clientID_.c_str(), cleanSession);
    }
    void MqttClient::reconnect()
    {
        mosquittopp::reconnect();
    }

    void MqttClient::disconnect()
    {
        mosquittopp::disconnect();
    }

    void MqttClient::on_connect(int rc)
    {
        if (MOSQ_ERR_SUCCESS == rc) {
            bConnected_ = true;
            sig_connected_(rc, clientID_);
        }
    }

    void MqttClient::on_disconnect(int rc) {
        if (MOSQ_ERR_SUCCESS == rc) {
            bConnected_ = false;
            sig_disconnected_(rc, clientID_);
        }
    }

    void MqttClient::setUsernameAndPassword(string username, string password)
    {
        username_ = username;
        password_ = password;
        check_error(username_pw_set(username_.c_str(), password_.c_str()));
    }

    void MqttClient::setTls(string cafile, string capath, string certfile)
    {
        check_error(tls_set(cafile.c_str(), capath.c_str(), certfile.c_str()));
    }

    void MqttClient::setTlsOptions(int verifyMode, string version, string ciphers)
    {
        check_error(tls_opts_set(verifyMode, version.c_str(), ciphers.c_str()));
    }

    void MqttClient::setTlsInsecure(bool insecure)
    {
        check_error(tls_insecure_set(insecure));
    }

    void MqttClient::setPSK(string psk, string identity, string ciphers)
    {
        check_error(tls_psk_set(psk.c_str(), identity.c_str(), ciphers.c_str()));
    }

    void MqttClient::on_log(int level, const char *str)
    {

    }

    void MqttClient::run_mqtt()
    {
        loop_start();
    }
}