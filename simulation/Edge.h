#ifndef EDGE_H_
#define EDGE_H_

#include "group_m.h"
#include <omnetpp.h>
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <fstream>
#include <mutex>
#include <algorithm>
#include <cmath>
#include <array>
#include <limits>

using namespace omnetpp;

class Edge : public cSimpleModule {
    int pass;
    int nb_periodes_envoie;
    int time_periode_trust;
    int periode;                                                                            // la période de calcul de la confiance

    std::map<std::string, std::vector<std::array<int, 3>>> nodemap;                         // clé : nom du noeud, contenu : [{valeur, taille du paquet}, ...]
    std::map<std::string, std::tuple<double, int, double>> periode_avg;                     // clé : nom du noeud, contenu : [valeurs moyennes, somme de la taille des paquets, label]
    std::map<std::string, std::array<double, 4>> kn_trust_scores;                           // clé : id du noeud, contenu [Label, NT_B, DC_B, interaction]

    struct XPSData {
        double Lab;
        std::array<double, 2> historique;
    };
    std::map<std::string, XPSData> xps;

    std::map<std::string, std::array<double, 3>> trust_scores;
    std::map<std::string, double> final_score;

    std::map<std::string, int> static_route;               //réseau   passerelle depuis le Edge vers le réseau

    std::ofstream csvFile;
    std::ofstream csvFile1;
    std::ofstream csvFile2;
    std::ofstream csvFile3;



protected:
    cMessage *Trust_calcul = nullptr;

    virtual void initialize() override;
    virtual void initialize_scenario();
    virtual void initialize_files();
    virtual void initialize_experiance();
    virtual void routing();

    virtual void handleMessage(cMessage *msg) override;
    virtual void recv_sink(cMessage *msg);
    virtual void recv_request(cMessage *msg);
    virtual void recv_offer(cMessage *msg);
    virtual void recv_sp_to_sc(cMessage *msg);
    virtual void recv_req_to_sp(cMessage *msg);
    virtual void recv_ser_to_sc(cMessage *msg);
    virtual void recv_fb_to_cloud(cMessage *msg);

    virtual void trust();
    virtual void initialize_nodemap();

    std::tuple<double, int, double> calculateAverage_Sum(const std::vector<std::array<int, 3>> &vec);
    virtual void network_behaviour(const std::tuple<double, int, double> &tup, std::string node);
    virtual void data_collection_behaviour(const std::map<std::string, std::tuple<double, int, double>> &dict);
    double median(std::vector<double> &data);
    double mean(const std::vector<double> &data);
    double meanExcludingOutliers(std::vector<double> data);
    virtual void Reward_punishment(const std::map<std::string, std::array<double, 4>> &dict);
    virtual void knowledge();

    virtual void experiance();

    virtual void final_trust();

    virtual void send_trust_cloud();

    virtual void affichage();

    virtual void save(int label, std::string id, int batterie, simtime_t time, int byteLength);


};

#endif /* EDGE_H_ */
