#ifndef CLIENT_H_
#define CLIENT_H_

#include "group_m.h"
#include <omnetpp.h>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <utility>
#include <algorithm>
#include <list>
#include <string>
#include <tuple>
#include <array>
#include "sensor.h"

using namespace omnetpp;

class client : public cSimpleModule {
    std::map<std::string, double> trust_score;
    int sim_time;
    int trust_periode;
    int periode;

    static std::vector<std::tuple<simtime_t, std::string, double>> offers;
    static std::vector<std::tuple<simtime_t, std::string, double>> requests;

    std::map<int, std::vector<std::string>> FS;
    std::map<int, std::vector<std::string>> FF;

protected:
    virtual void initialize_scenarios();
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void recv_sp_to_sc(cMessage *msg);
    virtual void recv_req_to_sp(cMessage *msg);
    virtual void recv_ser_to_sc(cMessage *msg);

    virtual void send_request();
    virtual void send_offer();
    virtual void client_beh();
    virtual void client_MB();
    virtual void sim_par();

    std::vector<cMessage*> offerMessages;
    std::vector<cMessage*> requestMessages;
    cMessage *offers_requests = nullptr;
    cMessage *behaviour = nullptr;

public:
    virtual void getCoordinates(double& x, double& y, double& z);
};

#endif /* CLIENT_H_ */
