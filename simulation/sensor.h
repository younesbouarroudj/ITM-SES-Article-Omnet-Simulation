#ifndef SENSOR_H_
#define SENSOR_H_
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
#include <random>
#include <map>
#include <tuple>
#include <fstream>
#include <mutex>
#include <algorithm>
#include <array>
#include <cmath>

using namespace omnetpp;

class sensor :
     public cSimpleModule {

        int batterie;                                                        // niveau de la batterie
        int mauv_periode;                                                    // compteur des mauvauis comportement consucutives
        int periode_trust;                                                   // compteur du nombre de periode de calcul de confiance ecoulée
        int freq_per_trust_periode;                                          // la frequance d'envoi des capteur (chaque 2min / 4min etc..)
        int nb_send_per_trust_periode;                                       // nombre de fois que le sensor envoi par periode de calcul de confiance
        int trust_periode;                                                   // le temp pour le calcul periodique de confiance
        int sim_time;

        std::map<std::string, std::vector<std::string>> malicious_nodes;    //key : comportement     array : les noeuds

        std::ofstream csvFile4;          //stocker les valleur de la batterie avec le temp

        static std::map<int ,std::array<std::string, 30>> not_Send;
        static std::map<int ,std::array<std::string, 30>> Send_6;
        static std::map<int ,std::array<std::string, 30>> Send_2;
        static std::map<int ,std::array<std::string, 30>> Send_All_Fake;
        static std::map<int ,std::array<std::string, 30>> Send_8_Fake;
        static std::map<int ,std::array<std::string, 30>> Send_4_Fake;
        static std::map<int ,std::array<std::string, 30>> Send_4_Fake_Out_8;
        static std::map<int ,std::array<std::string, 30>> Send_4_Fake_Out_4;
        static std::map<int ,std::array<std::string, 30>> Send_2_Fake_Out_6;

        protected:


           cMessage *se_charger = nullptr;           //pour charger la batterie chaque +2min 140

           cMessage *behaviour = nullptr;            //defenir le type de comportement u noeud dans la periode T = 20min

           cMessage *envoyer = nullptr;              //envoyer la valleur capturée chaque 2min (120s)

           cMessage *not_send = nullptr;             //envoie 0/10 periodes
           cMessage *send_2 = nullptr;               //envoie 2/10 periodes
           cMessage *send_6 = nullptr;               //envoie 6/10 periodes

           cMessage *send_all_fake = nullptr;        //envoie 0/10 fakes
           cMessage *send_8_fake = nullptr;          //envoie 6/10 fakes
           cMessage *send_4_fake = nullptr;          //envoie 2/10 fakes

           cMessage *send_4_fake_out_8 = nullptr;    //envoie 4/8 fakes
           cMessage *send_4_fake_out_4 = nullptr;    //envoie 4/4 fakes
           cMessage *send_2_fake_out_6 = nullptr;    //envoie 2/6 fakes



           virtual void initialize();
           virtual void inti_par();
           virtual void inti_batteries();
           virtual void inti_file();
           virtual void charge();
           virtual void save(int batterie);

           virtual void initialize_script_15p();
           virtual void initialize_script_60p();
           virtual void initialize_script_new_15p();


           virtual void initialize_script_rand();        //a ignorer car random
           virtual void initialize_nodes_mali();


           virtual void sensor_beh();

           virtual void handleMessage(cMessage *msg);

           virtual void SendValues();

           virtual void notSend();
           virtual void Send6();
           virtual void Send2();

           virtual void SendAllFake();
           virtual void Send8Fake();
           virtual void Send4Fake();

           virtual void Send4FakeOut8();
           virtual void Send4FakeOut4();
           virtual void Send2FakeOut6();

        public:
            double getBatterie() const { return batterie; }
            void setBatterie(double value) { batterie = value; }
};

#endif /* SENSOR_H_ */







