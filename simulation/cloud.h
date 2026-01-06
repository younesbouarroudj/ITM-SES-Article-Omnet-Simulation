#ifndef CLOUD_H_
#define CLOUD_H_
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
#include <cmath>
#include <unordered_map>
#include <array>
#include "client.h"
using namespace omnetpp;

class cloud :
     public cSimpleModule {

        int compteur;
        int time_per_periode;
        int periode;
        int session_time;
        double acceptable_trust;
        std::ofstream csvFile5;

        std::ofstream csvFile6;
        std::ofstream csvFile7;
        std::ofstream csvFile8;

        std::map<std::string, int> static_route;                                                //réseau   passerelle depuis le cloud vers le réseau
        std::map<std::string, std::vector<std::string>> friends;                                //réseau       {"f1", "f2" ...}
        std::map<std::string, double> sensors_trust_score;                                      //sensor_net   trust value intra
        std::map<std::string, std::array <double, 3>> networks_localisation;                    //réseau       [x,y,z]

        std::map<std::string, double> service_providers;                                        // SP   offer
                                                                         //le temp de validite du calcul de confiance entre un SC et un SP

        std::map<std::string, double> net_devices_trust;                                          // service provider       devices_trust
        std::map<std::array<std::string, 2>, double> trust_localisation;                          // [net1, net2] : distance
        std::map<std::array<std::string, 2>, double> trust_friendship;                            // [SC, SP] : friendship score

        std::map<std::string, std::vector<double>> reputations;                                   // SP            {0.5, rep1, rep2, rep3....}

        std::map<std::array<std::string, 2>, std::vector<double>> xps;                            // [SC, SP]       {0.5, fb1, fb2, fb3....}


        struct mystruct {
            std::string sc;
            std::string sp;
            double offer;
            double dv;
            double fr;
            double loc;
            double rp;
            double kn;
            double xp;
            double trust;
            bool act_ses;

            mystruct(const std::string& sc, const std::string& sp, double offer, double dv, double fr, double loc, double rp, double kn, double xp, double trust, bool act_ses)
                : sc(sc), sp(sp), offer(offer), dv(dv), fr(fr), loc(loc), rp(rp), kn(kn), xp(xp), trust(trust), act_ses(act_ses) {}
        };

        std::vector<mystruct> providers_trust;                                                    // { [sc,sp trust, offer], [sc, sp, trust, offer]..... }         don't change to map!!! i will sort it on chose provider

        std::map<cMessage*, std::array<std::string, 2>> messageMap;                                // map de self message pour supprimer la valleur de confiance pares 100s de son calcul


        std::map<std::string, std::vector<double>> feedbacks;                                     // SP      {fb1, fb2, fb3....}        general view of the SP to be used on the reputation fct


        protected:

            cMessage *reputation_calcul = nullptr;

            virtual void initialize_friends();
            virtual void initialize_sensor_trust_score();
            virtual void getAllClientsCoordinates();
            double calculateDistance(double x1, double y1, double x2, double y2, double z1, double z2);
            virtual void routing();
            virtual void sim_par();
            virtual void initialize_reputations();
            virtual void initialize_experiance();
            virtual void initialize_file();
            virtual void save(std::string net_sc, std::string net_sp, double dv, double fr, double loc, double rp, double xp);


           virtual void initialize();

           virtual void handleMessage(cMessage *msg);

           virtual void recv_edge(cMessage *msg);
           virtual void recv_offer(cMessage *msg);
           virtual void recv_request(cMessage *msg);
           virtual void recv_req_to_sp(cMessage *msg);
           virtual void recv_ser_to_sc(cMessage *msg);
           virtual void recv_fb_to_cloud(cMessage *msg);

           virtual void del_session_trust(cMessage *msg);


           virtual void co_localisation();

           std::vector<std::string> findCommonFriends(const std::string& network1, const std::string& network2);
           virtual void friendship(std::string &req_node_net);

           virtual void devices();


           double calculateIQR(std::vector<double>& data);
           std::vector<double> filterOutliers(const std::vector<double>& data);
           double calculateAverageFeedback(const std::vector<double>& data);
           double calculateUpdatedReputation(double historicalReputation, double avgFeedback);
           virtual void reputation();


           virtual void knowledge(std::string &req_node_net);


           double mean(const std::vector<double> &data);
           virtual void experiance(std::string &req_node_net);

           virtual void trust();
           virtual void affichage(std::string &req_node_net);


           virtual void chose_provider(std::string &req_node_net, double &need);

           virtual void nb_providers_log(std::string &req_node_net, double &need);


           virtual void send_sp_to_sc(std::string &sc_net, std::string &sp_net, double &need, double &offre);
};

#endif /* CLOUD_H_ */







