#include "sink.h"

Define_Module(sink);



void sink::initialize() {
    std::string name = getName();

    if (name == "sink_h1") {
        net_client = "h1";
    }else if (name == "sink_f1") {
        net_client = "f1";
    }else if (name == "sink_h2") {
        net_client = "h2";
    }else if (name == "sink_f2") {
        net_client = "f2";
    }else if (name == "sink_h3") {
        net_client = "h3";
    }else if (name == "sink_f3") {
        net_client = "f3";
    }else if (name == "sink_h4") {
        net_client = "h4";
    }else if (name == "sink_f4") {
        net_client = "f4";
    }else if (name == "sink_h5") {
        net_client = "h5";
    }else if (name == "sink_f5") {
        net_client = "f5";
    }
}


void sink::handleMessage(cMessage *msg) {
    if (dynamic_cast<values *>(msg) != nullptr) {
        send_edge(msg);
    }else if (dynamic_cast<request *>(msg) != nullptr) {
        recv_request(msg);
    }else if (dynamic_cast<offer *>(msg) != nullptr) {
        recv_offer(msg);
    }else if (dynamic_cast<sp_to_sc *>(msg) != nullptr) {
        recv_sp_to_sc(msg);
    }else if (dynamic_cast<req_to_sp *>(msg) != nullptr) {
        recv_req_to_sp(msg);
    }else if (dynamic_cast<ser_to_sc *>(msg) != nullptr) {
        recv_ser_to_sc(msg);
    }else if (dynamic_cast<fb_to_cloud *>(msg) != nullptr) {
        recv_fb_to_cloud(msg);
    }
}


void sink::send_edge(cMessage *msg) {
    //recevoir les message
    values *msg_r = check_and_cast<values *>(msg);

    int label = msg_r->getLabel();
    std::string id = msg_r->getId();
    int batterie = msg_r->getBatterie();
    simtime_t time = msg_r->getTime();
    int byteLength = msg_r->getByteLength();

    delete msg_r;

    //envoie vers edge
    values *msg1 = new values("sensors");

    msg1->setLabel(label);
    msg1->setId(id.c_str());
    msg1->setBatterie(batterie);
    msg1->setTime(time);
    msg1->setByteLength(byteLength);

    send(msg1, "pas$o",5);
}


void sink::recv_offer(cMessage *msg) {
    //recevoir les message
    offer *msg_r = check_and_cast<offer *>(msg);

    std::string node = msg_r->getNode();
    double offre = msg_r->getOffre();

    delete msg_r;

    //envoie vers edge
    offer *msg1 = new offer("offer");

    msg1->setNode(node.c_str());
    msg1->setOffre(offre);
    send(msg1, "pas$o",5);
}



void sink::recv_request(cMessage *msg) {
    //recevoir les message
    request *msg_r = check_and_cast<request *>(msg);

    std::string node = msg_r->getNode();
    double need = msg_r->getNeed();
    delete msg_r;

    //envoie vers edge
    request *msg1 = new request("request");

    msg1->setNode(node.c_str());
    msg1->setNeed(need);
    send(msg1, "pas$o",5);
}


void sink::recv_sp_to_sc(cMessage *msg) {
    //recevoir les message
    sp_to_sc *msg_r = check_and_cast<sp_to_sc *>(msg);

    std::string sc_net = msg_r->getSc();
    std::string sp_net = msg_r->getSp();
    double need = msg_r->getNeed();
    double offre = msg_r->getService();

    //envoie vers le Edge
    sp_to_sc *msg1 = new sp_to_sc("sp_to_sc");

    msg1->setSc(sc_net.c_str());
    msg1->setSp(sp_net.c_str());
    msg1->setNeed(need);
    msg1->setService(offre);

    send(msg1, "pas$o",4);
}


void sink::recv_req_to_sp(cMessage *msg) {
    //recevoir le message
    req_to_sp *msg_r = check_and_cast<req_to_sp *>(msg);

    std::string sp_net = msg_r->getSp();
    std::string sc_net = msg_r->getSc();
    double need = msg_r->getNeed();
    double offre = msg_r->getService();

    bool here = false;
    if (net_client == sp_net) {
        here = true;
    }
    req_to_sp *msg1 = new req_to_sp("req_to_sp");
    msg1->setSp(sp_net.c_str());
    msg1->setSc(sc_net.c_str());
    msg1->setNeed(need);
    msg1->setService(offre);
    if (here) {
        send(msg1, "pas$o",4);
    }else {
        send(msg1, "pas$o",5);
    }
}


void sink::recv_ser_to_sc(cMessage *msg) {
    //recevoir le message
    ser_to_sc *msg_r = check_and_cast<ser_to_sc *>(msg);

    std::string sc_net = msg_r->getSc();
    std::string sp_net = msg_r->getSp();
    double need = msg_r->getNeed();
    double offre = msg_r->getService();

    bool here = false;
    if (net_client == sc_net) {
        here = true;
    }
    ser_to_sc *msg1 = new ser_to_sc("req_to_sp");
    msg1->setSc(sc_net.c_str());
    msg1->setSp(sp_net.c_str());
    msg1->setNeed(need);
    msg1->setService(offre);
    if (here) {
        send(msg1, "pas$o",4);
    }else {
        send(msg1, "pas$o",5);
    }
}


void sink::recv_fb_to_cloud(cMessage *msg) {
    //recevoir le message
    fb_to_cloud *msg_r = check_and_cast<fb_to_cloud *>(msg);

    std::string sp_net = msg_r->getSp();
    std::string sc_net = msg_r->getSc();
    double feedback = msg_r->getFb();

    fb_to_cloud *msg1 = new fb_to_cloud("fb_to_cloud");
    msg1->setSp(sp_net.c_str());
    msg1->setSc(sc_net.c_str());
    msg1->setFb(feedback);

    send(msg1, "pas$o", 5);
}


