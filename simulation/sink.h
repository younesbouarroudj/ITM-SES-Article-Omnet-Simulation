#ifndef SINK_H_
#define SINK_H_
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
using namespace omnetpp;

class sink :
     public cSimpleModule {

        std::string net_client;
        protected:
           virtual void initialize();
           virtual void handleMessage(cMessage *msg);
           virtual void send_edge(cMessage *msg);
           virtual void recv_offer(cMessage *msg);
           virtual void recv_request(cMessage *msg);
           virtual void recv_sp_to_sc(cMessage *msg);
           virtual void recv_req_to_sp(cMessage *msg);
           virtual void recv_ser_to_sc(cMessage *msg);
           virtual void recv_fb_to_cloud(cMessage *msg);

};

#endif /* SINK_H_ */



