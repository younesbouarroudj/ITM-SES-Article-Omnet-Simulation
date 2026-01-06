#include "client.h"

std::vector<std::tuple<simtime_t ,std::string, double>> client::offers;
std::vector<std::tuple<simtime_t ,std::string, double>> client::requests;

Define_Module(client);


void client::sim_par() {
    sim_time = 18000;
    trust_periode = 10;         //temp calcul de confaince intra  1200s – 300s – 10s
}


void client::client_MB() {
    EV << "Initializing malicious nodes during the simulation\n";


    int fake_service = static_cast<int>(offers.size()) / 2;
    for (int j = 1; j <= fake_service; j++) {

        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> dist(0, offers.size() - 1);

        // Generate a random index
        int random_index = dist(gen);

        // Access the random element from the vector
        std::string random_MN = std::get<1>(offers[random_index]);
        FS[periode].push_back(random_MN);
    }

    int fake_feedback = static_cast<int>(requests.size()) / 2;
    for (int i = 1; i <= fake_feedback; i++) {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> dist(0, requests.size() - 1);

        // Generate a random index
        int random_index = dist(gen);

        // Access the random element from the vector
        std::string random_MN = std::get<1>(requests[random_index]);
        FF[periode].push_back(random_MN);
    }
}


void client::initialize_scenarios() {
    offers.clear();
    requests.clear();
    offerMessages.clear();
    requestMessages.clear();
    periode++;
    EV << "initialisation du scenario pour la periode " << periode << "\n";
    // Choose the number of SPs for the period
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<double> weights = {0.01, 0.01, 0.01, 0.01, 0.01, 0.02, 0.03, 0.05, 0.15, 0.3, 0.4};
    std::discrete_distribution<> dist(weights.begin(), weights.end());
    int nb_offers = dist(gen);
    EV << "nombre de SP " << nb_offers << "\n";
    for (int j = 0; j < nb_offers; j++) {
        std::vector<std::string> net1 = {"client_h1", "client_h2", "client_h3", "client_h4", "client_h5", "client_f1", "client_f2", "client_f3", "client_f4", "client_f5"};
        std::vector<double> prob1 = {0.05, 0.07, 0.06, 0.04, 0.03, 0.15, 0.17, 0.18, 0.14, 0.11};
        std::random_device rd1;
        std::mt19937 gen1(rd1());
        std::discrete_distribution<> weighted_distribution1(prob1.begin(), prob1.end());
        int sp_net_index = weighted_distribution1(gen1);
        std::string SP = net1[sp_net_index];

        double max;
        double min;
        if (simTime() < 1000) {
            max = 5;
            min = 1;
        } else if (simTime() < 3000) {
            max = 10;
            min = 5;
        } else if (simTime() < 6000) {
            max = 15;
            min = 10;
        } else if (simTime() < 9000) {
            max = 20;
            min = 10;
        } else {
            max = 30;
            min = 10;
        }
        int service = intuniform(static_cast<int>(min), static_cast<int>(max));
        simtime_t time = intuniform((periode - 1) * trust_periode + 0.1, (periode * trust_periode) - 1);
        offers.emplace_back(time, SP, service);
    }


    // Choose the number of SCs for the period
    std::random_device rd3;
    std::mt19937 gen3(rd3());
    std::vector<double> weights3 = {0.01, 0.01, 0.01, 0.01, 0.01, 0.02, 0.03, 0.05, 0.15, 0.3, 0.4};
    std::discrete_distribution<> dist3(weights3.begin(), weights3.end());
    int nb_requests = dist3(gen3);
    EV << "nombre de SC " << nb_requests << "\n";
    for (int j = 0; j < nb_requests; j++) {
        std::vector<std::string> net2 = {"client_h1", "client_h2", "client_h3", "client_h4", "client_h5", "client_f1", "client_f2", "client_f3", "client_f4", "client_f5"};
        std::vector<double> prob2 = {0.13, 0.07, 0.14, 0.06, 0.15, 0.08, 0.12, 0.09, 0.11, 0.05};
        std::random_device rd2;
        std::mt19937 gen2(rd2());
        std::discrete_distribution<> weighted_distribution2(prob2.begin(), prob2.end());
        int sc_net_index = weighted_distribution2(gen2);
        std::string SC = net2[sc_net_index];
        double max;
        double min;
        if (simTime() < 1000) {
            max = 5;
            min = 1;
        } else if (simTime() < 3000) {
            max = 8;
            min = 1;
        } else if (simTime() < 6000) {
            max = 10;
            min = 1;
        } else if (simTime() < 9000) {
            max = 15;
            min = 1;
        } else {
            max = 20;
            min = 1;
        }
        int request = intuniform(static_cast<int>(min), static_cast<int>(max));
        simtime_t time = intuniform((periode - 1) * trust_periode + 0.1, (periode * trust_periode) - 1);
        requests.emplace_back(time, SC, request);
    }
    client_MB();
    offers_requests = new cMessage("offers_requests");
    scheduleAt(simTime() + trust_periode, offers_requests);
}


void client::client_beh() {
    std::string name = getName();
    for (const auto& tup : offers) {
        simtime_t temp = std::get<0>(tup);
        std::string provider = std::get<1>(tup);
        if (provider == name) {
            cMessage *offre = new cMessage("offre");
            offerMessages.push_back(offre);
            if (temp > simTime()) {
                scheduleAt(temp, offre);
            }
        }
    }
    for (const auto& tup : requests) {
        simtime_t temp = std::get<0>(tup);
        std::string client = std::get<1>(tup);
        if (client == name) {
            cMessage *req = new cMessage("req");
            requestMessages.push_back(req);
            if (temp > simTime()) {
                scheduleAt(temp, req);
            }
        }
    }

    behaviour = new cMessage("behaviour");
    scheduleAt(simTime() + trust_periode, behaviour);
}


void client::initialize() {
    sim_par();
    periode = 0;
    std::string name = getName();

    if (name == "client_h1") {
        initialize_scenarios();
    }
    client_beh();
}


void client::handleMessage(cMessage *msg) {

    if (dynamic_cast<sp_to_sc *>(msg) != nullptr) {
        recv_sp_to_sc(msg);
    }else if (dynamic_cast<req_to_sp *>(msg) != nullptr) {
        recv_req_to_sp(msg);
    }else if (dynamic_cast<ser_to_sc *>(msg) != nullptr) {
        recv_ser_to_sc(msg);
    }

    else if (msg->isSelfMessage()) {
        if (std::find(offerMessages.begin(), offerMessages.end(), msg) != offerMessages.end()) {
              send_offer();
        }else if (std::find(requestMessages.begin(), requestMessages.end(), msg) != requestMessages.end()) {
              send_request();
        }else if (msg == offers_requests) {
            initialize_scenarios();
        }else if (msg == behaviour) {
            client_beh();
        }
    }
}


void client::send_offer() {
    std::string name = getName();
    double offre;
    for (const auto& tup : offers) {
        simtime_t temp = std::get<0>(tup);
        if (simTime() == temp && name == std::get<1>(tup)) {
            offre = std::get<2>(tup);
        }
    }
    offer *msg = new offer("offer");
    msg->setNode(name.c_str());
    msg->setOffre(offre);

    send(msg, "pas$o", 0);
}


void client::send_request() {
    std::string name = getName();
    double need;
    for (const auto& tup : requests) {
        simtime_t temp = std::get<0>(tup);
        if (simTime() == temp && name == std::get<1>(tup)) {
            need = std::get<2>(tup);
        }
    }
    request *msg = new request("request");
    msg->setNode(name.c_str());
    msg->setNeed(need);

    send(msg, "pas$o", 0);
}


void client::recv_sp_to_sc(cMessage *msg){
    std::string name = getName();
    sp_to_sc *msg_r = check_and_cast<sp_to_sc *>(msg);

    std::string sc_net = msg_r->getSc();
    std::string sp_net = msg_r->getSp();
    double need = msg_r->getNeed();
    double offre = msg_r->getService();


    //SC sends the request to the SP
    req_to_sp *msg1 = new req_to_sp("req_to_sp");
    msg1->setSp(sp_net.c_str());
    msg1->setSc(sc_net.c_str());
    msg1->setNeed(need);
    msg1->setService(offre);

    send(msg1, "pas$o", 0);

}


void client::recv_req_to_sp(cMessage *msg) {
    std::string name = getName();
    req_to_sp *msg_r = check_and_cast<req_to_sp *>(msg);

    std::string sp_net = msg_r->getSp();
    std::string sc_net = msg_r->getSc();
    double need = msg_r->getNeed();
    double offre = msg_r->getService();
    double give;
    //here attacks de fake service
    bool found = false;
    for(const auto& entry : FS){
        if(entry.first == periode) {
            std::vector<std::string> Vec = entry.second;
            found = std::find(Vec.begin(), Vec.end(), getName()) != Vec.end();
            break;
        }
    }
    if (found){
        EV <<  "fake service attack\n";
       if (need < offre) {
           give = need;
       }else {
           give = offre;
       }
       give = intuniform(0,static_cast<int>(give/10));
    }
    else {
       if (need < offre) {
           give = need;
       }else {
           give = offre;
       }
    }
    EV << "je suis " << sp_net << " (" << name << ") je doit retirer " << give << " de la batterie de la maison \n";
    std::array<std::string, 4> sensorNames = {
        std::string("s1_") + sp_net,
        std::string("s2_") + sp_net,
        std::string("s3_") + sp_net,
        std::string("s4_") + sp_net
    };

    for (const auto& sensorName : sensorNames) {
        // Obtenir un pointeur vers le module sensor
        cModule* sensorModule = getParentModule()->getSubmodule(sensorName.c_str());

        if (sensorModule) {
            // accéder aux méthodes spécifiques du capteur
            sensor* sen = check_and_cast<sensor*>(sensorModule);

            // obtenir la valeur de la batterie
            double batterieValue = sen->getBatterie();

            // modifier la valeur de la batterie
            if (batterieValue - give  < 0 ){
                batterieValue = 0;
            }else {batterieValue = batterieValue - give; }

            sen->setBatterie( batterieValue );
            EV << "Le capteur " << sensorName << " a ete modifiee" << endl;
        } else {
            EV << "Le capteur " << sensorName << " n'a pas ete trouve" << endl;
        }
    }

    //envoyer le service vers le SC
    ser_to_sc *msg1 = new ser_to_sc("ser_to_sc");
    msg1->setSc(sc_net.c_str());
    msg1->setSp(sp_net.c_str());
    msg1->setNeed(need);
    msg1->setService(give);

    send(msg1, "pas$o", 0);
}


void client::recv_ser_to_sc(cMessage *msg) {
    ser_to_sc *msg_r = check_and_cast<ser_to_sc *>(msg);
    std::string sp_net = msg_r->getSp();
    std::string sc_net = msg_r->getSc();
    double need = msg_r->getNeed();
    double offre = msg_r->getService();
    //here attacks de feedback attack
    bool found= false;
    double feedback;
    for(const auto& entry : FF){
         if(entry.first == periode){
             std::vector<std::string> Vec = entry.second;
             found = std::find(Vec.begin(), Vec.end(), getName()) != Vec.end();
             break;
         }
     }
     if(found){
          EV <<  "fake feedback attack\n";
          feedback = static_cast<double> (offre) / (need);
          if (feedback > 0.5) {
              feedback = 0.1;
          } else {
              feedback =0.9;
          }
     } else {
          feedback = static_cast<double> (offre) / (need);
          if (feedback > 1) {
               feedback = 1;
          }
     }
    //send feedback to the cloud
    fb_to_cloud *msg1 = new fb_to_cloud("fb_to_cloud");

    msg1->setSp(sp_net.c_str());
    msg1->setSc(sc_net.c_str());
    msg1->setFb(feedback);

    send(msg1, "pas$o", 0);
}


void client::getCoordinates(double& x, double& y, double& z) {
    const char *dispStr = getDisplayString().getTagArg("p", 0);
    x = atof(dispStr ? dispStr : "0");
    dispStr = getDisplayString().getTagArg("p", 1);
    y = atof(dispStr ? dispStr : "0");
    dispStr = getDisplayString().getTagArg("p", 2);
    z = atof(dispStr ? dispStr : "0");
}
