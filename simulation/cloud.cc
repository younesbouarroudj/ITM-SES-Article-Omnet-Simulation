#include "cloud.h"

Define_Module(cloud);

std::mutex csvMutex5;
std::mutex csvMutex6;
std::mutex csvMutex7;
std::mutex csvMutex8;


void cloud::sim_par() {
    time_per_periode = 10;         //temp calcul de confaicne intra 1200s – 300s – 10s
    session_time = static_cast<int> (time_per_periode) / (3);
    acceptable_trust = 0.5;
}


void cloud::initialize_friends() {
    friends["h1"].push_back("f1");      friends["h1"].push_back("h2");      friends["h1"].push_back("f3");
    friends["f1"].push_back("h1");      friends["f1"].push_back("f2");      friends["f1"].push_back("h3");      friends["f1"].push_back("h4");
    friends["h2"].push_back("h1");      friends["h2"].push_back("f3");      friends["h2"].push_back("f4");
    friends["f2"].push_back("f1");      friends["f2"].push_back("h3");      friends["f2"].push_back("h4");      friends["f2"].push_back("f4");      friends["f2"].push_back("h5");
    friends["h3"].push_back("f1");      friends["h3"].push_back("f2");      friends["h3"].push_back("f5");
    friends["f3"].push_back("h2");      friends["f3"].push_back("h5");      friends["f3"].push_back("h1");      friends["f3"].push_back("f5");
    friends["h4"].push_back("f2");      friends["h4"].push_back("f5");      friends["h4"].push_back("f1");
    friends["f4"].push_back("f2");      friends["f4"].push_back("h2");      friends["f4"].push_back("h5");
    friends["h5"].push_back("f3");      friends["h5"].push_back("f5");      friends["h5"].push_back("f4");      friends["h5"].push_back("f2");
    friends["f5"].push_back("h4");      friends["f5"].push_back("h5");      friends["f5"].push_back("h3");      friends["f5"].push_back("f3");
}


void cloud::initialize_sensor_trust_score() {
    sensors_trust_score["s1_h1"] = 0.5;     sensors_trust_score["s2_h1"] = 0.5;     sensors_trust_score["s3_h1"] = 0.5;     sensors_trust_score["s4_h1"] = 0.5;
    sensors_trust_score["s1_f1"] = 0.5;     sensors_trust_score["s2_f1"] = 0.5;     sensors_trust_score["s3_f1"] = 0.5;     sensors_trust_score["s4_f1"] = 0.5;
    sensors_trust_score["s1_h2"] = 0.5;     sensors_trust_score["s2_h2"] = 0.5;     sensors_trust_score["s3_h2"] = 0.5;     sensors_trust_score["s4_h2"] = 0.5;
    sensors_trust_score["s1_f2"] = 0.5;     sensors_trust_score["s2_f2"] = 0.5;     sensors_trust_score["s3_f2"] = 0.5;     sensors_trust_score["s4_f2"] = 0.5;
    sensors_trust_score["s1_h3"] = 0.5;     sensors_trust_score["s2_h3"] = 0.5;     sensors_trust_score["s3_h3"] = 0.5;     sensors_trust_score["s4_h3"] = 0.5;
    sensors_trust_score["s1_f3"] = 0.5;     sensors_trust_score["s2_f3"] = 0.5;     sensors_trust_score["s3_f3"] = 0.5;     sensors_trust_score["s4_f3"] = 0.5;
    sensors_trust_score["s1_h4"] = 0.5;     sensors_trust_score["s2_h4"] = 0.5;     sensors_trust_score["s3_h4"] = 0.5;     sensors_trust_score["s4_h4"] = 0.5;
    sensors_trust_score["s1_f4"] = 0.5;     sensors_trust_score["s2_f4"] = 0.5;     sensors_trust_score["s3_f4"] = 0.5;     sensors_trust_score["s4_f4"] = 0.5;
    sensors_trust_score["s1_h5"] = 0.5;     sensors_trust_score["s2_h5"] = 0.5;     sensors_trust_score["s3_h5"] = 0.5;     sensors_trust_score["s4_h5"] = 0.5;
    sensors_trust_score["s1_f5"] = 0.5;     sensors_trust_score["s2_f5"] = 0.5;     sensors_trust_score["s3_f5"] = 0.5;     sensors_trust_score["s4_f5"] = 0.5;
    devices();
}


void cloud::initialize_reputations() {
    std::vector<std::string> networks = {"h1", "f1", "h2", "f2", "h3", "f3", "h4", "f4", "h5", "f5"};
    for (const auto& net : networks) {
        reputations[net].push_back(0.5);
    }
}


void cloud::initialize_experiance() {
    std::vector<std::string> networks = {"h1", "f1", "h2", "f2", "h3", "f3", "h4", "f4", "h5", "f5"};
    for (const auto& net1 : networks) {
        for (const auto& net2 : networks) {
            if (net1 != net2) { // Avoid self-pairing
                xps[{net1, net2}].push_back(0.5);
            }
        }
    }
}


void cloud::getAllClientsCoordinates() {
    cModule *parentModule = getParentModule();  // Assuming `cloud` is a submodule of the network module
    for (cModule::SubmoduleIterator it(parentModule); !it.end(); ++it) {
        cModule *submodule = *it;
        if (strcmp(submodule->getModuleType()->getName(), "client") == 0) {  // Check if the submodule is of type 'sink'
            client *clientModule = check_and_cast<client*>(submodule);
            double x, y, z;
            clientModule->getCoordinates(x, y, z);
            EV << "client module: " << clientModule->getFullName() << " Coordinates: (" << x << ", " << y << ", " << z << ")\n";
            networks_localisation[clientModule->getFullName()] = {x, y, z};
        }
    }
}


double cloud::calculateDistance(double x1, double y1, double x2, double y2, double z1, double z2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double dz = z2 - z1;
    return sqrt(dx * dx + dy * dy + dz * dz);
}


void cloud::co_localisation() {
    for (const auto& entry1 : networks_localisation) {
        std::string net1 = entry1.first.substr(entry1.first.size() - 2);
        double x1 = entry1.second[0];
        double y1 = entry1.second[1];
        double z1 = entry1.second[2];
        for (const auto& entry2 : networks_localisation) {
            if (entry1.first != entry2.first) {
                std::string net2 = entry2.first.substr(entry2.first.size() - 2);
                double x2 = entry2.second[0];
                double y2 = entry2.second[1];
                double z2 = entry2.second[2];
                double distance = calculateDistance(x1, y1, x2, y2, z1, z2);
                double loc = static_cast<double> (distance) / (3000);
                loc = 1 - loc;
                if (loc < 0) {loc = 0;}
                //EV << "distance entre " << net1 << " et " << net2 << " est de : " << distance << " le score est de : " << loc << "\n";
                trust_localisation[{net1, net2}] =  loc;
            }
        }
    }
}


void cloud::routing() {
    static_route["h1"] = 0;     static_route["f1"] = 0;     static_route["h2"] = 0;     static_route["f2"] = 0;
    static_route["h3"] = 1;     static_route["f3"] = 1;     static_route["h4"] = 1;
    static_route["f4"] = 2;     static_route["h5"] = 2;
    static_route["f5"] = 3;
}


void cloud::initialize_file() {
    //part2_dataset.csv
            {
                std::lock_guard<std::mutex> guard5(csvMutex5);
                std::ofstream csvFile5("part2_dataset.csv", std::ios::trunc);
            }

            std::lock_guard<std::mutex> guard5(csvMutex5);
            std::ifstream csvFileCheck5("part2_dataset.csv");
            if (csvFileCheck5.peek() == std::ifstream::traits_type::eof()) {
                std::ofstream csvFile5("part2_dataset.csv", std::ios::out | std::ios::app);
                if (csvFile5.is_open()) {
                    csvFile5 << "SC,SP,Periode,Device_trust,Friendship,Localisation,Reputation,Experiance\n";
                }
            }


     //SP_counts_dataset_040.csv
            {
                std::lock_guard<std::mutex> guard6(csvMutex6);
                std::ofstream csvFile6("SP_counts_dataset_040.csv", std::ios::trunc);
            }
            std::lock_guard<std::mutex> guard6(csvMutex6);
            std::ifstream csvFileCheck6("SP_counts_dataset_040.csv");
            if (csvFileCheck6.peek() == std::ifstream::traits_type::eof()) {
                std::ofstream csvFile6("SP_counts_dataset_040.csv", std::ios::out | std::ios::app);
                if (csvFile6.is_open()) {
                    csvFile6 << "SC,count_total,Trustworthy,Untrustworthy,periode\n";
                }
            }

       //SP_counts_dataset_050.csv
             {
                 std::lock_guard<std::mutex> guard7(csvMutex7);
                 std::ofstream csvFile7("SP_counts_dataset_050.csv", std::ios::trunc);
             }
             std::lock_guard<std::mutex> guard7(csvMutex7);
             std::ifstream csvFileCheck7("SP_counts_dataset_050.csv");
             if (csvFileCheck7.peek() == std::ifstream::traits_type::eof()) {
                 std::ofstream csvFile7("SP_counts_dataset_050.csv", std::ios::out | std::ios::app);
                 if (csvFile7.is_open()) {
                     csvFile7 << "SC,count_total,Trustworthy,Untrustworthy,periode\n";
                 }
             }

       //SP_counts_dataset_065.csv
             {
                 std::lock_guard<std::mutex> guard8(csvMutex8);
                 std::ofstream csvFile8("SP_counts_dataset_065.csv", std::ios::trunc);
             }
             std::lock_guard<std::mutex> guard8(csvMutex8);
             std::ifstream csvFileCheck8("SP_counts_dataset_065.csv");
             if (csvFileCheck8.peek() == std::ifstream::traits_type::eof()) {
                 std::ofstream csvFile8("SP_counts_dataset_065.csv", std::ios::out | std::ios::app);
                 if (csvFile8.is_open()) {
                     csvFile8 << "SC,count_total,Trustworthy,Untrustworthy,periode\n";
                 }
             }
}


void cloud::initialize() {
    routing();
    initialize_friends();
    initialize_sensor_trust_score();
    initialize_reputations();
    initialize_experiance();
    getAllClientsCoordinates();

    co_localisation();
    devices();
    initialize_file();
    sim_par();
    compteur = 0;
    periode = 1;

    reputation_calcul = new cMessage("reputation_calcul");
    scheduleAt(simTime() + time_per_periode , reputation_calcul); // Calcul de la reputation chaque 300s
}




void cloud::handleMessage(cMessage *msg) {
    if (dynamic_cast<sensors_trust *>(msg) != nullptr) {
        recv_edge(msg);
    }else if (dynamic_cast<request *>(msg) != nullptr) {
        recv_request(msg);
    }else if (dynamic_cast<offer *>(msg) != nullptr) {
        recv_offer(msg);
    }else if (dynamic_cast<req_to_sp *>(msg) != nullptr) {
        recv_req_to_sp(msg);
    }else if (dynamic_cast<ser_to_sc *>(msg) != nullptr) {
        recv_ser_to_sc(msg);
    }else if (dynamic_cast<fb_to_cloud *>(msg) != nullptr) {
        recv_fb_to_cloud(msg);
    }else if (strcmp(msg->getName(), "deleteMsg") == 0) {
        del_session_trust(msg);
    }else if (msg->isSelfMessage()) {
        reputation();
    }
    delete msg;
}

void cloud::del_session_trust(cMessage *msg) {
    auto it = messageMap.find(msg);
    if (it != messageMap.end()) {
        std::string sc = it->second[0];
        std::string sp = it->second[1];
        EV << "time to delete the periodique trust between " << sc << " and " << sp << "\n";

        providers_trust.erase(std::remove_if(providers_trust.begin(), providers_trust.end(),
            [&sc, &sp](const auto& entry) {
                return entry.sc == sc && entry.sp == sp && entry.act_ses;
            }), providers_trust.end());

        messageMap.erase(it);
    }
}

void cloud::recv_offer(cMessage *msg) {
    //recevoir les message
    offer *msg_r = check_and_cast<offer *>(msg);

    std::string node = msg_r->getNode();
    double offre = msg_r->getOffre();

    std::string node_net = node.substr(node.size() - 2);
    EV << "received the offer from "<< node_net << " "<< offre <<"\n";

    service_providers[node_net] = offre;

    //si la confiance est deja calculee alors il ajoute la nouvelle offre
    for (auto& entry : providers_trust) {
        if (entry.sp == node_net && entry.act_ses) {
            entry.offer = offre;
        }
    }
}


void cloud::recv_request(cMessage *msg) {
    //recevoir les message
    request *msg_r = check_and_cast<request *>(msg);

    std::string node = msg_r->getNode();
    double need = msg_r->getNeed();

    std::string req_node_net = node.substr(node.size() - 2);
    EV << "received the request from "<< req_node_net <<" he needs " << need <<"%\n\n";

    friendship(req_node_net);
    knowledge(req_node_net);
    experiance(req_node_net);
    trust();
    affichage(req_node_net);
    chose_provider(req_node_net, need);

    trust_friendship.clear();
}


void cloud::recv_edge(cMessage *msg) {
    // Recevoir les messages
    sensors_trust *msg_r = check_and_cast<sensors_trust *>(msg);
    std::string  node = msg_r->getNode();
    double node_trust = msg_r->getTr();

    // Ajouter la valleur de confiance au noeud a chaque repection periodique du message (recoit ce message chaque freq_envoi_sensor * 10 )
    sensors_trust_score[node] = node_trust;
    compteur++;
    if (compteur == 40) {
        devices();
    }
}

void cloud::devices() {
    EV << "updating the network devices trust\n";
    for (const auto& entry : sensors_trust_score) {
        std::string node = entry.first;
        std::string node_network = node.substr(node.size() - 2);

        std::vector<double> net_trust_values;
        for (const auto& entry1 : sensors_trust_score) {
            std::string new_node = entry1.first;
            std::string new_node_network = new_node.substr(new_node.size() - 2);
            if (new_node_network == node_network) {
                net_trust_values.push_back(entry1.second);
            }
        }
        net_devices_trust[node_network] = *std::max_element(net_trust_values.begin(), net_trust_values.end());
        //net_devices_trust[node_network] = mean(net_trust_values);
    }
    compteur=0;
}






std::vector<std::string> cloud::findCommonFriends(const std::string& network1, const std::string& network2) {
    std::vector<std::string> commonFriends;
    const std::vector<std::string>& friends1 = friends.at(network1);
    const std::vector<std::string>& friends2 = friends.at(network2);

    // Sort the friends lists to use set_intersection
    std::vector<std::string> sortedFriends1 = friends1;
    std::vector<std::string> sortedFriends2 = friends2;
    std::sort(sortedFriends1.begin(), sortedFriends1.end());
    std::sort(sortedFriends2.begin(), sortedFriends2.end());

    // Use the algorithm library to find the intersection
    std::set_intersection(
        sortedFriends1.begin(), sortedFriends1.end(),
        sortedFriends2.begin(), sortedFriends2.end(),
        std::back_inserter(commonFriends)
    );
    return commonFriends;
}

void cloud::friendship(std::string &req_node_net) {
    // calcule le nombre d'amis du SC
    int nb_friends_req = friends.at(req_node_net).size();

    // selectione un noeud du réseau et verifie si le noeud selectionée est 1 - SP       2 - sa confiance pas encore expirée     3 - ne se selecionne pas lui meme
    for (const auto& entry : friends) {
        const std::string& net_sp = entry.first;

        bool isServiceProvider = service_providers.find(net_sp) != service_providers.end();

        bool isInProvidersTrust = false;
        for (const auto& entry1 : providers_trust) {
            if (entry1.sc == req_node_net && entry1.sp == net_sp && entry1.act_ses) {
                isInProvidersTrust = true;
            }
        }


        if (net_sp != req_node_net && isServiceProvider && !isInProvidersTrust) {
            std::vector<std::string> common = findCommonFriends(req_node_net, net_sp);
            double fr;
            if (nb_friends_req == 1 && common.size() == 1) {
                fr = 1; // Avoid division by zero, or set to 0 if only one friend
            } else {
                 fr = static_cast<double>(common.size()) / (nb_friends_req - 1);
                 if (fr > 1) {
                     fr = 1;
                 }
            }
                 EV << "friendship relation entre SC et new SP " << req_node_net << "--" << net_sp << " : " << fr << "\n";
                 trust_friendship[{req_node_net, net_sp}] = fr;
        }
    }
}



double cloud::calculateIQR(std::vector<double>& data) {
    std::sort(data.begin(), data.end());
    size_t n = data.size();

    double Q1 = data[n / 4];
    double Q3 = data[(3 * n) / 4];
    return Q3 - Q1;
}

std::vector<double> cloud::filterOutliers(const std::vector<double>& data) {
    std::vector<double> filteredData;
    if (data.empty()) { return filteredData; }

    std::vector<double> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end());
    double IQR = calculateIQR(sortedData);
    double Q1 = sortedData[sortedData.size() / 4];
    double Q3 = sortedData[(3 * sortedData.size()) / 4];

    double lowerBound = Q1 - 0.2 * IQR;
    double upperBound = Q3 + 0.2 * IQR;

    for (double value : data) {
        if (value >= lowerBound && value <= upperBound) {
            filteredData.push_back(value);
        }
    }
    return filteredData;
}

double cloud::calculateAverageFeedback(const std::vector<double>& data) {
    if (data.empty()) return 0.0;
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    double avg = static_cast<double> (sum) / (data.size()) ;
    return avg;
}

double cloud::calculateUpdatedReputation(double historicalReputation, double avgFeedback) {
    double decayFactor = 0.8;
    return decayFactor * historicalReputation + (1 - decayFactor) * avgFeedback;
}

void cloud::reputation() {
    service_providers.clear();
    providers_trust.clear();
    periode++;

    for (const auto& SpFeedback : feedbacks) {
        std::string SP_name = SpFeedback.first;
        std::vector<double> sp_feedbacks_list = SpFeedback.second;
        if (sp_feedbacks_list.size() > 7) {

            // Filter out outliers from feedbacks
            std::vector<double> filtered_sp_Feedbacks_list = filterOutliers(sp_feedbacks_list);

            // Calculate average feedback (F_avg)
            double avg = calculateAverageFeedback(filtered_sp_Feedbacks_list);

            // avg historique
            double R_historical;
            for (const auto& entry : reputations) {
                if (entry.first == SP_name) {
                    R_historical = mean(entry.second);
                    break;
                }
            }

            // Calculate updated reputation (R_updated)
            double R_updated = calculateUpdatedReputation(R_historical, avg);

            // Store updated feedback on the reputations list
            reputations[SP_name].push_back(R_updated);

            //suprimer les feedback procesée
            feedbacks[SP_name].clear();
        }
    }
    reputation_calcul = new cMessage("reputation_calcul");
    scheduleAt(simTime() + time_per_periode , reputation_calcul);
}



void cloud::knowledge(std::string &req_node_net) {
    double fr;
    double loc;
    double dv;
    double rp;
    double offre;
    for (const auto& entry1 : trust_friendship) {
        if (entry1.first[0] == req_node_net ) {
              std::string net_sc = entry1.first[0];
              std::string net_sp = entry1.first[1];
              fr = entry1.second;

              for (const auto& entry2 : trust_localisation) {
                     if (entry2.first[0] == net_sc && entry2.first[1] == net_sp) {
                          loc = entry2.second;
                          break;
                     }
              }

              for (const auto& entry3 : net_devices_trust) {
                  if (entry3.first == net_sp) {
                      dv = entry3.second;
                      break;
                  }
             }

             for (const auto& entry4 : reputations) {
                   if (entry4.first == net_sp) {
                        std::vector<double> vec = entry4.second;
                        rp = vec.back();
                        break;
                   }
             }

             for (const auto& entry5 :service_providers) {
                 if (entry5.first == net_sp) {
                     offre = entry5.second;
                 }
             }

             double kn = 0.25 * dv + 0.25 * fr + 0.25 * loc + 0.25 * rp;

             providers_trust.emplace_back(net_sc, net_sp, offre, dv, fr, loc, rp, kn, 0, 0, false);
         }
     }
}



double cloud::mean(const std::vector<double> &data) {
    double sum = 0.0;
    for (double value : data) {
        sum += value;
    }
    return sum / data.size();
}

void cloud::experiance(std::string &req_node_net) {
    for (const auto& entry : xps) {
        const std::string& net_sc = entry.first[0];
        const std::string& net_sp = entry.first[1];

        bool isRequester = (net_sc == req_node_net);

        bool isServiceProvider = (service_providers.find(net_sp) != service_providers.end());

        bool isInProvidersTrust = false;
        for (const auto& entry1 : providers_trust) {
            if (entry1.sc == req_node_net && entry1.sp == net_sp && entry1.act_ses) {
                isInProvidersTrust = true;
            }
        }

        if (isRequester && isServiceProvider && !isInProvidersTrust) {
            const std::vector<double>& vec = entry.second;
            double xp, recent, old;

            if (vec.size() == 1) {
                xp = recent = old = vec.back();
            } else {
                recent = vec.back();
                if (vec.size() > 20) {
                    std::vector<double> old_vec(vec.end() - 21, vec.end() - 1);
                    old = mean(old_vec);
                } else {
                    std::vector<double> old_vec(vec.begin(), vec.end() - 1);
                    old = mean(old_vec);
                }
                xp = 0.4 * recent + 0.6 * old;
            }

           for (auto& entry5 : providers_trust) {
                if (entry5.sc == net_sc && entry5.sp == net_sp && !entry5.act_ses) {
                    entry5.xp = xp;
                    break;
                }
          }
       }
    }
}



void cloud::trust() {
    for (auto& entry : providers_trust) {
        if (!entry.act_ses) {
            std::string net_sc = entry.sc;
            std::string net_sp = entry.sp;
            double kn = entry.kn;
            double xp = entry.xp;

            double trust = 0.45 * kn + 0.55 * xp;

            entry.trust = trust;
            entry.act_ses = true;

            cMessage *deleteMsg = new cMessage("deleteMsg");        //self message pour garder la confaince que pour 100s
            messageMap[deleteMsg] = {net_sc, net_sp};
            scheduleAt(simTime() + 100, deleteMsg);
        }
    }
}


void cloud::affichage(std::string &req_node_net) {
    EV  << "-----service consumer " << req_node_net <<" trust towards other SP : \n";

    for (const auto& entry : providers_trust) {
          if (entry.sc == req_node_net) {
              std::string net_sp = entry.sp;
              std::string net_sc = entry.sc;
              double offre = entry.offer;
              double dv = entry.dv;
              double fr= entry.fr;
              double loc= entry.loc;
              double rp= entry.rp;
              double kn = entry.kn;
              double xp = entry.xp;
              double tr = entry.trust;

              EV  << "-------------service provider " << net_sp << " offer " << offre << "\n";
              EV  << " data collection beh : " << dv << " ---- friendship : " << fr << " ----localisation : " << loc << " ----reputation : " << rp << "\n";
              EV  << " score knowledge : " << kn << "\n";
              EV  << " score experiance : " << xp << "\n";
              EV  << " score de confiance : " << tr << "\n\n";
              if (tr )
              save(net_sc, net_sp, dv, fr, loc, rp, xp);
          }
    }
}



void cloud::chose_provider(std::string &req_node_net, double &need) {
    //tri en se bassant sur la confiance
    std::sort(providers_trust.begin(), providers_trust.end(), [](const mystruct& a, const mystruct& b) {
        return a.trust > b.trust; // Sort in descending order of trust
    });

    //selectionner le fournisseur de service si y'en a
    bool found = false;
    std::string sc_net;
    std::string sp_net;
    double trust;
    double offre;
    for (const auto& entry : providers_trust) {
        sc_net = entry.sc;
        sp_net = entry.sp;
        trust = entry.trust;
        offre = entry.offer;
        if (sc_net == req_node_net && offre >= need &&  trust > acceptable_trust) {
            found = true;
            break;
        }
    }

    if (!found) {
        EV  << "pas de SP pour satisfaire pour le SC " << req_node_net << " voir d'autre SP en mode degradee \n";
        for (const auto& entry : providers_trust) {
            sc_net = entry.sc;
            sp_net = entry.sp;
            trust = entry.trust;
            offre = entry.offer;
            if (sc_net == req_node_net && trust > acceptable_trust) {
              found = true;
              break;
            }
        }
    }
    if (!found) {
        EV  << "the Service can't be satisfied\n\n";
    }

    //add the number of SP for the SC request to the logs
    nb_providers_log(req_node_net, need);

    if (found)  {
        EV  << "Le SP sera " << sp_net << " le service fourni sera " << offre << " / " << need  <<" a celui de demendee par "<< sc_net <<"\n";
        service_providers[sp_net] = service_providers[sp_net] - need;
        if (service_providers[sp_net] <= 0) {
            service_providers.erase(sp_net);
        }

        for (auto it = providers_trust.begin(); it != providers_trust.end(); ) {
             if (it->sp == sp_net) {
                 it->offer = it->offer - need;
                 if (it->offer <= 0) {
                     it = providers_trust.erase(it);
                 } else {
                     ++it;
                 }
             } else {
                 ++it;
             }
        }
        send_sp_to_sc(sc_net, sp_net, need, offre);     //envoyer au SC l'offre du meilleur SP
    }

}


void cloud::nb_providers_log(std::string &req_node_net, double &need) {

    int count_total = 0;                //the total number of SP
    int count_acceptable_th1 = 0;       //the number of SPs who the SC can trust
    int count_unacceptable_th1 = 0;     //the number of SPs who the SC can't trust

    int count_acceptable_th2 = 0;       //the number of SPs who the SC can trust
    int count_unacceptable_th2 = 0;     //the number of SPs who the SC can't trust

    int count_acceptable_th3 = 0;       //the number of SPs who the SC can trust
    int count_unacceptable_th3 = 0;     //the number of SPs who the SC can't trust

    double th1 = 0.4;
    double th2 = 0.5;
    double th3 = 0.65;

    std::string sc_net;
    std::string sp_net;
    double trust;
    double offre;

    for (const auto& entry : providers_trust) {
        sc_net = entry.sc;
        sp_net = entry.sp;
        trust = entry.trust;
        offre = entry.offer;

        if (sc_net == req_node_net) {
            count_total++;
        }
        if (sc_net == req_node_net && trust > th1) {
            count_acceptable_th1++;
        }
        if (sc_net == req_node_net && trust > th2) {
            count_acceptable_th2++;
        }
        if (sc_net == req_node_net && trust > th3) {
            count_acceptable_th3++;
        }

        count_unacceptable_th1 = count_total - count_acceptable_th1;
        count_unacceptable_th2 = count_total - count_acceptable_th2;
        count_unacceptable_th3 = count_total - count_acceptable_th3;
    }

    std::lock_guard<std::mutex> guard6(csvMutex6);
    std::ofstream csvFile6("SP_counts_dataset_040.csv", std::ios::out | std::ios::app);
    if (csvFile6.is_open()) {
        csvFile6 << req_node_net << "," <<count_total << "," << count_acceptable_th1 << "," << count_unacceptable_th1 << "," << periode << "\n";
    }

    std::lock_guard<std::mutex> guard7(csvMutex7);
    std::ofstream csvFile7("SP_counts_dataset_050.csv", std::ios::out | std::ios::app);
    if (csvFile7.is_open()) {
        csvFile7 << req_node_net << "," <<count_total << "," << count_acceptable_th2 << "," << count_unacceptable_th2 << "," << periode << "\n";
    }

    std::lock_guard<std::mutex> guard8(csvMutex8);
    std::ofstream csvFile8("SP_counts_dataset_065.csv", std::ios::out | std::ios::app);
    if (csvFile8.is_open()) {
        csvFile8 << req_node_net << "," <<count_total << "," << count_acceptable_th3 << "," << count_unacceptable_th3 << "," << periode << "\n";
    }
}



void cloud::send_sp_to_sc(std::string &sc_net, std::string &sp_net, double &need, double &offre) {
    int pass;
    for (const auto& entry : static_route) {
        if (entry.first == sc_net) {
            pass = entry.second;
        }
    }
    sp_to_sc *msg = new sp_to_sc("sp_to_sc");

    msg->setSc(sc_net.c_str());
    msg->setSp(sp_net.c_str());
    msg->setNeed(need);
    msg->setService(offre);
    send(msg, "pas$o",pass);
}



void cloud::recv_req_to_sp(cMessage *msg) {
    //recevoir le message
    req_to_sp *msg_r = check_and_cast<req_to_sp *>(msg);

    std::string sp_net = msg_r->getSp();
    std::string sc_net = msg_r->getSc();
    double need = msg_r->getNeed();
    double offre = msg_r->getService();

    int passerelle;
    for (const auto& entry : static_route) {
        if (entry.first == sp_net) {
            passerelle = entry.second;
        }
    }
    //envoie vers le Edge
    req_to_sp *msg1 = new req_to_sp("req_to_sp");

    msg1->setSp(sp_net.c_str());
    msg1->setSc(sc_net.c_str());
    msg1->setNeed(need);
    msg1->setService(offre);

    send(msg1,"pas$o", passerelle);
}



void cloud::recv_ser_to_sc(cMessage *msg) {
    //recevoir le message
    ser_to_sc *msg_r = check_and_cast<ser_to_sc *>(msg);

    std::string sc_net = msg_r->getSc();
    std::string sp_net = msg_r->getSp();
    double need = msg_r->getNeed();
    double offre = msg_r->getService();

    int passerelle;
    for (const auto& entry : static_route) {
        if (entry.first == sc_net) {
            passerelle = entry.second;
        }
    }

    ser_to_sc *msg1 = new ser_to_sc("req_to_sp");

    msg1->setSc(sc_net.c_str());
    msg1->setSp(sp_net.c_str());
    msg1->setNeed(need);
    msg1->setService(offre);

    send(msg1,"pas$o", passerelle);
}



void cloud::recv_fb_to_cloud(cMessage *msg) {
    //recevoir le message
    fb_to_cloud *msg_r = check_and_cast<fb_to_cloud *>(msg);

    std::string sp_net = msg_r->getSp();
    std::string sc_net = msg_r->getSc();
    double feedback = msg_r->getFb();

    EV << "feedback donnee par sc : " << sc_net << " au sp : " << sp_net << " est = " << feedback << "\n";

    // save the feedbacks
    feedbacks[sp_net].push_back(feedback);
    xps[{sc_net, sp_net}].push_back(feedback);
}




void cloud::save(std::string net_sc, std::string net_sp, double dv, double fr, double loc, double rp, double xp) {
    std::lock_guard<std::mutex> guard5(csvMutex5); // Verrouiller le mutex
    std::ofstream csvFile5("part2_dataset.csv", std::ios::out | std::ios::app);
    if (csvFile5.is_open()) {
        csvFile5 << net_sc << "," <<net_sp << "," << periode << "," << dv << "," << fr << "," << loc << "," << rp << "," << xp <<"\n";
    }
}









