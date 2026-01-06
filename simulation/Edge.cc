 #include "Edge.h"

Define_Module(Edge);

// Mutex global pour synchroniser l'accès au fichier CSV
std::mutex csvMutex;
std::mutex csvMutex1;
std::mutex csvMutex2;
std::mutex csvMutex3;

void Edge::initialize_scenario() {
    nb_periodes_envoie = 10;
    time_periode_trust = 10;          //temp calcul de confaicne intra  1200s – 300s – 10s
}


void Edge::initialize_files() {
        //dataset.csv
        {
            std::lock_guard<std::mutex> guard(csvMutex);
            std::ofstream csvFile("dataset.csv", std::ios::trunc);
        }
        std::lock_guard<std::mutex> guard(csvMutex);
        std::ifstream csvFileCheck("dataset.csv");
        if (csvFileCheck.peek() == std::ifstream::traits_type::eof()) {
            std::ofstream csvFile("dataset.csv", std::ios::out | std::ios::app);
            if (csvFile.is_open()) {
                csvFile << "Label,NodeID,Value,Timestamp,packet_size\n";
            }
        }

        //knowledge_dataset.csv
        {
            std::lock_guard<std::mutex> guard1(csvMutex1);
            std::ofstream csvFile1("knowledge_dataset.csv", std::ios::trunc);
        }

        std::lock_guard<std::mutex> guard1(csvMutex1);
        std::ifstream csvFileCheck1("knowledge_dataset.csv");
        if (csvFileCheck1.peek() == std::ifstream::traits_type::eof()) {
            std::ofstream csvFile1("knowledge_dataset.csv", std::ios::out | std::ios::app);
            if (csvFile1.is_open()) {
                csvFile1 << "Label,NodeID,network_behaviour,data_collection_behaviour,Reward_punishment,periode\n";
            }
        }

        //Experiance_dataset.csv
        {
            std::lock_guard<std::mutex> guard2(csvMutex2);
            std::ofstream csvFile2("Experiance_dataset.csv", std::ios::trunc);
        }

        std::lock_guard<std::mutex> guard2(csvMutex2);
        std::ifstream csvFileCheck2("Experiance_dataset.csv");
        if (csvFileCheck2.peek() == std::ifstream::traits_type::eof()) {
            std::ofstream csvFile2("Experiance_dataset.csv", std::ios::out | std::ios::app);
            if (csvFile2.is_open()) {
                csvFile2 << "Label,NodeID,Recente,Ancienne,periode\n";
            }
        }

        //trust_dataset.csv
        {
            std::lock_guard<std::mutex> guard3(csvMutex3);
            std::ofstream csvFile3("trust_dataset.csv", std::ios::trunc);
        }

        std::lock_guard<std::mutex> guard3(csvMutex3);
        std::ifstream csvFileCheck3("trust_dataset.csv");
        if (csvFileCheck3.peek() == std::ifstream::traits_type::eof()) {
            std::ofstream csvFile3("trust_dataset.csv", std::ios::out | std::ios::app);
            if (csvFile3.is_open()) {
                csvFile3 << "Label,NodeID,knowledge,experiance,periode\n";
            }
        }
}


void Edge::initialize_experiance() {
    std::string name = getName();
    double ignore = std::numeric_limits<double>::quiet_NaN();
    if (name == "Edge_r1") {
        xps["s1_h1"].historique[1] = 0.5;   xps["s2_h1"].historique[1] = 0.5;   xps["s3_h1"].historique[1] = 0.5;    xps["s4_h1"].historique[1] = 0.5;
        xps["s1_h1"].historique[0] = ignore;    xps["s2_h1"].historique[0] = ignore;    xps["s3_h1"].historique[0] = ignore;     xps["s4_h1"].historique[0] = ignore;

        xps["s1_f1"].historique[1] = 0.5;   xps["s2_f1"].historique[1] = 0.5;   xps["s3_f1"].historique[1] = 0.5;    xps["s4_f1"].historique[1] = 0.5;
        xps["s1_f1"].historique[0] = ignore;    xps["s2_f1"].historique[0] = ignore;    xps["s3_f1"].historique[0] = ignore;     xps["s4_f1"].historique[0] = ignore;

        xps["s1_h2"].historique[1] = 0.5;   xps["s2_h2"].historique[1] = 0.5;   xps["s3_h2"].historique[1] = 0.5;    xps["s4_h2"].historique[1] = 0.5;
        xps["s1_h2"].historique[0] = ignore;    xps["s2_h2"].historique[0] = ignore;    xps["s3_h2"].historique[0] = ignore;     xps["s4_h2"].historique[0] = ignore;

        xps["s1_f2"].historique[1] = 0.5;   xps["s2_f2"].historique[1] = 0.5;   xps["s3_f2"].historique[1] = 0.5;    xps["s4_f2"].historique[1] = 0.5;
        xps["s1_f2"].historique[0] = ignore;    xps["s2_f2"].historique[0] = ignore;    xps["s3_f2"].historique[0] = ignore;     xps["s4_f2"].historique[0] = ignore;
    } else if (name == "Edge_r2") {
        xps["s1_h3"].historique[1] = 0.5;   xps["s2_h3"].historique[1] = 0.5;   xps["s3_h3"].historique[1] = 0.5;    xps["s4_h3"].historique[1] = 0.5;
        xps["s1_h3"].historique[0] = ignore;    xps["s2_h3"].historique[0] = ignore;    xps["s3_h3"].historique[0] = ignore;     xps["s4_h3"].historique[0] = ignore;

        xps["s1_f3"].historique[1] = 0.5;   xps["s2_f3"].historique[1] = 0.5;   xps["s3_f3"].historique[1] = 0.5;    xps["s4_f3"].historique[1] = 0.5;
        xps["s1_f3"].historique[0] = ignore;    xps["s2_f3"].historique[0] = ignore;    xps["s3_f3"].historique[0] = ignore;     xps["s4_f3"].historique[0] = ignore;

        xps["s1_h4"].historique[1] = 0.5;   xps["s2_h4"].historique[1] = 0.5;   xps["s3_h4"].historique[1] = 0.5;    xps["s4_h4"].historique[1] = 0.5;
        xps["s1_h4"].historique[0] = ignore;    xps["s2_h4"].historique[0] = ignore;    xps["s3_h4"].historique[0] = ignore;     xps["s4_h4"].historique[0] = ignore;
    } else if (name == "Edge_r3") {
        xps["s1_f4"].historique[1] = 0.5;   xps["s2_f4"].historique[1] = 0.5;   xps["s3_f4"].historique[1] = 0.5;    xps["s4_f4"].historique[1] = 0.5;
        xps["s1_f4"].historique[0] = ignore;    xps["s2_f4"].historique[0] = ignore;    xps["s3_f4"].historique[0] = ignore;     xps["s4_f4"].historique[0] = ignore;

        xps["s1_h5"].historique[1] = 0.5;   xps["s2_h5"].historique[1] = 0.5;   xps["s3_h5"].historique[1] = 0.5;    xps["s4_h5"].historique[1] = 0.5;
        xps["s1_h5"].historique[0] = ignore;    xps["s2_h5"].historique[0] = ignore;    xps["s3_h5"].historique[0] = ignore;     xps["s4_h5"].historique[0] = ignore;
    } else {
        xps["s1_f5"].historique[1] = 0.5;   xps["s2_f5"].historique[1] = 0.5;   xps["s3_f5"].historique[1] = 0.5;    xps["s4_f5"].historique[1] = 0.5;
        xps["s1_f5"].historique[0] = ignore;    xps["s2_f5"].historique[0] = ignore;    xps["s3_f5"].historique[0] = ignore;     xps["s4_f5"].historique[0] = ignore;
    }
}


void Edge::routing() {
    std::string name = getName();
    if (name == "Edge_r1") {
        static_route["h1"] = 0;     static_route["f1"] = 1;     static_route["h2"] = 2;     static_route["f2"] = 3;
    }else if (name == "Edge_r2") {
        static_route["h3"] = 0;     static_route["f3"] = 1;     static_route["h4"] = 2;
    }else if (name == "Edge_r3") {
        static_route["f4"] = 0;     static_route["h5"] = 1;
    }else {
        static_route["f5"] = 0;
    }
}


void Edge::initialize() {
    periode = 0;
    initialize_scenario();
    initialize_files();
    initialize_experiance();
    routing();


    // Définir les différentes passerelles de sortie pour atteindre le cloud à chaque edge
    std::string name = getName();
    //pass vers le cloud pour chaque module
    if (name == "Edge_r1") {
        pass = 4;
    } else if (name == "Edge_r2") {
        pass = 3;
    } else if (name == "Edge_r3") {
        pass = 2;
    } else {
        pass = 1;
    }

    Trust_calcul = new cMessage("Trust_calcul");
    scheduleAt(simTime() + time_periode_trust, Trust_calcul);
}



void Edge::handleMessage(cMessage *msg) {
    if (dynamic_cast<values *>(msg) != nullptr) {
        recv_sink(msg);
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
    }else if (msg->isSelfMessage()) {
        trust();
    }
}

void Edge::recv_sink(cMessage *msg) {

    // Recevoir les messages
    values *msg_r = check_and_cast<values *>(msg);

    int label = msg_r->getLabel();
    std::string  id = msg_r->getId();
    int batterie = msg_r->getBatterie();
    simtime_t time = msg_r->getTime();
    int byteLength = msg_r->getByteLength();

    // Ajouter le message envoyé dans le dictionnaire au vecteur qui correspond à l'id de l'envoyeur
    std::array<int, 3> entry = {batterie, byteLength, label};
    nodemap[id].push_back(entry);

    // Sauvegarder le message dans un dataset
    save(label, id, batterie, time, byteLength);

}


void Edge::initialize_nodemap() {
    std::string name = getName();
    if (name == "Edge_r1") {
        nodemap["s1_h1"];       nodemap["s2_h1"];       nodemap["s3_h1"];     nodemap["s4_h1"];
        nodemap["s1_f1"];       nodemap["s2_f1"];       nodemap["s3_f1"];     nodemap["s4_f1"];
        nodemap["s1_h2"];       nodemap["s2_h2"];       nodemap["s3_h2"];     nodemap["s4_h2"];
        nodemap["s1_f2"];       nodemap["s2_f2"];       nodemap["s3_f2"];     nodemap["s4_f2"];
    } else if (name == "Edge_r2") {
        nodemap["s1_h3"];       nodemap["s2_h3"];       nodemap["s3_h3"];     nodemap["s4_h3"];
        nodemap["s1_f3"];       nodemap["s2_f3"];       nodemap["s3_f3"];     nodemap["s4_f3"];
        nodemap["s1_h4"];       nodemap["s2_h4"];       nodemap["s3_h4"];     nodemap["s4_h4"];
    } else if (name == "Edge_r3") {
        nodemap["s1_f4"];       nodemap["s2_f4"];       nodemap["s3_f4"];     nodemap["s4_f4"];
        nodemap["s1_h5"];       nodemap["s2_h5"];       nodemap["s3_h5"];     nodemap["s4_h5"];
    } else {
        nodemap["s1_f5"];       nodemap["s2_f5"];       nodemap["s3_f5"];     nodemap["s4_f5"];
    }
}



void Edge::trust() {
    initialize_nodemap();
    periode++;         // Nouvelle période de calcul de confiance

    // Étape 1 : Calculer la moyenne des valeurs capturées pour chaque période de calcul de confiance et remplir toute la liste "periode_avg"
    for (const auto& entry : nodemap) {
        periode_avg[entry.first] = calculateAverage_Sum(entry.second);         // Envoyer le vecteur de paires qui contient toutes les périodes
    }

    // Étape 2 : Score du network_behaviour
    for (const auto& entry : periode_avg) {
        network_behaviour(entry.second, entry.first);
    }

    // Étape 3 : Score du data_collection_behaviour
    data_collection_behaviour(periode_avg);

    // Étape 4 : Obtenir le score du Reward_punishment
    Reward_punishment(kn_trust_scores);

    // Étape 5 : Calcul le score du knowledge
    knowledge();

    // Étape 6 : Calcul le score de l'experiance
    experiance();

    // Étape 7 : calcul de la confiance final
    final_trust();

    // Étape 8 : Affichage
    affichage();

    // Étape 9 : sauvgarder la dernieres valleurs du knowledge pour la future experiance
    for (const auto& entry : trust_scores) {
        double kn = entry.second[1];
        std::string node = entry.first;
        for (const auto& entry1 : xps) {
            if (node == entry1.first) {
                xps[node].historique[0] = kn;
            }
        }
    }

    // Étape 10 : envoyer les valleur de confinace de chaque capteur du réseau vers le cloud
    send_trust_cloud();


    // Étape 11 : vider les structures de données périodiques
    nodemap.clear(); periode_avg.clear(); kn_trust_scores.clear();  trust_scores.clear();   final_score.clear();

    scheduleAt(simTime() + time_periode_trust, Trust_calcul);         // Calcul de la confiance chaque 20 min (1200s)
}



std::tuple<double, int, double> Edge::calculateAverage_Sum(const std::vector<std::array<int, 3>>& vec) {
    double avg = 0;
    int sum = 0;
    double label = 0;

    int nb_envoie = 0;
    nb_envoie = vec.size();         //pas tjr qu'il envoie 5 fois

    if (nb_envoie > 0) {
        for (const auto& val : vec) {
            avg = avg + val[0];
            sum = sum + val[1];
            label = label + val[2];
        }
        avg = static_cast<double> (avg) / (nb_envoie);
        label = static_cast<double> (label) / (nb_periodes_envoie);
        return std::make_tuple(avg, sum, label);

    }else{
    return std::make_tuple(-1, 0 ,0);         //-1 pour qu'elle soit ignorée
    }
}



void Edge::network_behaviour(const std::tuple<double, int, double> &tup, std::string node) {

    double label = std::get<2>(tup);
    xps[node].Lab = std::get<2>(tup);
    int size_total = std::get<1>(tup);              // nombre d'oct total envoyée pour cetet periode de calcul de confiance
    double NB;

    int expected = nb_periodes_envoie * 128;               // Le nombre normal de données attendu : 128 octets * nb de périodes
    NB = static_cast<double>(size_total) / expected;

    kn_trust_scores[node][1] = NB;
    kn_trust_scores[node][0] = label;
}




double Edge::median(std::vector<double> &data) {
    std::sort(data.begin(), data.end());
    size_t n = data.size();
    if (n % 2 == 0) {
        return (data[n / 2 - 1] + data[n / 2]) / 2.0;
    } else {
        return data[n / 2];
    }
}

double Edge::mean(const std::vector<double> &data) {
    double sum = 0.0;
    for (double value : data) {
        sum += value;
    }
    return sum / data.size();
}

double Edge::meanExcludingOutliers(std::vector<double> data) {
    if (data.empty()) {
        throw std::invalid_argument("Data vector is empty");
        return 0;
    }else {
        // Step 1: Compute the median
        double med = median(data);

        // Step 2: Compute the absolute deviations from the median
        std::vector<double> absDeviations;
        for (double value : data) {
            absDeviations.push_back(std::abs(value - med));
        }

        // Step 3: Compute the MAD
        double mad = median(absDeviations);

        // Step 4: Identify and remove outliers using a threshold of 3 * MAD
        double threshold = 3.0 * mad;
        std::vector<double> nonOutliers;
        for (double value : data) {
            if (std::abs(value - med) <= threshold) {
                nonOutliers.push_back(value);
            }
        }

        // Step 5: Compute the mean of the non-outliers
        if (nonOutliers.empty()) {
            throw std::runtime_error("All values are considered outliers");
        }
        return mean(nonOutliers);
    }
}

void Edge::data_collection_behaviour(const std::map<std::string, std::tuple<double, int, double>> &dict) {
    for (const auto& entry : dict) {
        std::string node = entry.first;
        std::string node_network = node.substr(node.size() - 2); // Réseau du noeud ('f1', 'h1', etc.)

        // Traitement pour le réseau pour avoir la moyenne des valleurs capturee pour ce réseau
        std::vector<double> avg_values;
        for (const auto& entry1 : periode_avg) {
            std::string new_node = entry1.first;
            std::string new_node_network = new_node.substr(new_node.size() - 2);
            if (new_node_network == node_network) {
                if (std::get<0>(entry1.second) != -1 ){
                    avg_values.push_back(std::get<0>(entry1.second));
                }
            }
        }
        // Calculer la moyenne
        double avg = meanExcludingOutliers(avg_values);

        //calculer l'attribur data collection behaviour
        double value = std::get<0>(entry.second);
        double DB;
        if (value == -1) {
            DB= 0;
        }else {
             DB= static_cast<double>(std::fabs(value - avg)) / (50);
             DB = 1 - DB;
        }

        //enregistrer la valleur
        if (DB < 0) {    DB = 0; }
        kn_trust_scores[entry.first][2] = DB;
    }
}



void Edge::Reward_punishment(const std::map<std::string, std::array<double, 4>> &dict) {
    for (const auto& entry : dict) {
        std::string node = entry.first;

        double NT_B = entry.second[1];
        double DC_B = entry.second[2];

        double interaction_score = (0.5 * DC_B) + (0.5 * NT_B);

        int interaction_total = nb_periodes_envoie;

        // Connaître le nombre d'interactions négatives
        int interaction_pos = std::round(interaction_total * interaction_score);
        int interaction_neg = interaction_total - interaction_pos;

        // Exécuter la formule de récompense et punition
        double a, b, xpo, RW;
        a = static_cast<double> (std::fabs(static_cast<double>(interaction_total - interaction_neg))) / (interaction_total);
        b = static_cast<double> (interaction_neg) / interaction_total;
        xpo = std::exp(-b);
        RW = a * xpo;

        kn_trust_scores[node][3] = RW;
    }
}



void Edge::knowledge() {
    for (const auto& entry : kn_trust_scores) {
        std::string node = entry.first;
        double label = entry.second[0];
        double NT_B = entry.second[1];
        double DC_B = entry.second[2];
        double RW = entry.second[3];

        double kn = 9.29571740e-12 * NT_B + 1.37638516e-01 * DC_B + 8.62361484e-01 * RW;
        trust_scores[node][1] = kn;

        std::lock_guard<std::mutex> guard1(csvMutex1); // Verrouiller le mutex
        std::ofstream csvFile1("knowledge_dataset.csv", std::ios::out | std::ios::app);
        if (csvFile1.is_open()) {
            csvFile1 << label << "," << node << "," << NT_B << "," << DC_B << "," << RW << "," << periode << "\n";
        }
    }
}



void Edge::experiance() {
    double xp;
    double recent;
    double old;
    std::string node;
    std::vector<double> vec;
    for (const auto& entry : xps) {
        node = entry.first;
        double label = xps[node].Lab;
        recent = entry.second.historique[0];
        old = entry.second.historique[1];

        if (std::isnan(recent)) {
            xp = old;
        }else {
            xp = 0.41923579 * recent + 0.58076421 * old;
        }

        for (const auto& entry1 : xps) {
            if (node == entry1.first) {
               xps[node].historique[1] = xp;
            }
        }
        trust_scores[node][0] = label;
        trust_scores[node][2] = xp;

        std::lock_guard<std::mutex> guard2(csvMutex2); // Verrouiller le mutex
        std::ofstream csvFile2("Experiance_dataset.csv", std::ios::out | std::ios::app);
        if (csvFile2.is_open()) {
            csvFile2 << label << "," << node << "," << recent << "," << old << "," << periode <<"\n";
        }
    }
}



void Edge::final_trust() {
    std::string node;
    double kn;
    double xp;
    double label;
    double tr;

    for (const auto& entry : trust_scores) {
        node = entry.first;
        label = entry.second[0];
        kn = entry.second[1];
        xp = entry.second[2];

        tr = 0.80205309 * kn + 0.19794691 * xp;
        final_score[node] = tr;

        std::lock_guard<std::mutex> guard3(csvMutex3); // Verrouiller le mutex
        std::ofstream csvFile3("trust_dataset.csv", std::ios::out | std::ios::app);
        if (csvFile3.is_open()) {
            csvFile3 << label << "," << node << "," << kn << "," << xp <<  "," << periode << "\n";
        }
    }
}



void Edge::affichage() {
    std::string name = getName();
    EV << name << " ----------------calcul de la confiance pour la periode : " << periode << " ----------------------\n";

    for (const auto& entry : kn_trust_scores) {
        std::string node = entry.first;
        double label = entry.second[0];      double NT_B = entry.second[1];     double DC_B = entry.second[2];      double RW = entry.second[3];
        double kn;          double xp;      double tr;

        for (const auto& entry1 : trust_scores) {
            if (entry1.first == node) {
                kn = entry1.second[1];
                xp = entry1.second[2];
                break;
            }
        }

        for (const auto& entry2 : final_score) {
            if (entry2.first == node) {
                tr = entry2.second;
                break;
            }
        }

        EV << "-----Node: " << node << " ------\n";
        EV << "Resultat attendu : " << label << "\n";
        EV << "data collection behaviour: " << DC_B << " -- " << "network behaviour: " << NT_B << " -- " << "Reward / punishment: " << RW << "\n";
        EV << "knowledge predit : " << kn << "\n";
        EV << "Experiance predite : " << xp << "\n";
        EV << "confiance predite : " << tr << "\n";
    }
}



void Edge::send_trust_cloud() {
    std::string node;
    double tr;
    for (const auto& entry : final_score) {
        node = entry.first;
        tr = entry.second;
        sensors_trust *msg1 = new sensors_trust("trust");
        msg1->setNode(node.c_str());
        msg1->setTr(tr);

        // Send the message without deleting it
        send(msg1, "pas$o", pass);
    }
}



void Edge::save(int label, std::string id, int batterie, simtime_t time,  int byteLength) {
    std::lock_guard<std::mutex> guard(csvMutex); // Verrouiller le mutex
    std::ofstream csvFile("dataset.csv", std::ios::out | std::ios::app);
    if (csvFile.is_open()) {
        csvFile << label << "," << id << "," << batterie << "," << time << "," << byteLength << "\n";
    }
}




void Edge::recv_offer(cMessage *msg) {
    //recevoir les message
    offer *msg_r = check_and_cast<offer *>(msg);

    std::string node = msg_r->getNode();
    double offre = msg_r->getOffre();

    delete msg_r;

    //envoie vers edge
    offer *msg1 = new offer("offer");

    msg1->setNode(node.c_str());
    msg1->setOffre(offre);
    send(msg1, "pas$o",pass);
}


void Edge::recv_request(cMessage *msg) {
    //recevoir les message
    request *msg_r = check_and_cast<request *>(msg);

    std::string node = msg_r->getNode();
    double need = msg_r->getNeed();

    delete msg_r;

    //envoie vers le cloud
    request *msg1 = new request("request");

    msg1->setNode(node.c_str());
    msg1->setNeed(need);

    send(msg1, "pas$o",pass);
}



void Edge::recv_sp_to_sc(cMessage *msg) {

    //recevoir les message
    sp_to_sc *msg_r = check_and_cast<sp_to_sc *>(msg);

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
    //envoie vers le cloud
    sp_to_sc *msg1 = new sp_to_sc("sp_to_sc");

    msg1->setSc(sc_net.c_str());
    msg1->setSp(sp_net.c_str());
    msg1->setNeed(need);
    msg1->setService(offre);

    send(msg1, "pas$o",passerelle);
}



void Edge::recv_req_to_sp(cMessage *msg) {
    //recevoir le message
    req_to_sp *msg_r = check_and_cast<req_to_sp *>(msg);

    std::string sp_net = msg_r->getSp();
    std::string sc_net = msg_r->getSc();
    double need = msg_r->getNeed();
    double offre = msg_r->getService();

    int passerelle = pass;      //par deffault vers le cloud si il ne trouve pas
    for (const auto& entry : static_route) {
        if (entry.first == sp_net) {
            passerelle = entry.second;
        }
    }
    req_to_sp *msg1 = new req_to_sp("req_to_sp");

    msg1->setSp(sp_net.c_str());
    msg1->setSc(sc_net.c_str());
    msg1->setNeed(need);
    msg1->setService(offre);

    send(msg1,"pas$o", passerelle);
}


void Edge::recv_ser_to_sc(cMessage *msg) {
    //recevoir le message
    ser_to_sc *msg_r = check_and_cast<ser_to_sc *>(msg);

    std::string sc_net = msg_r->getSc();
    std::string sp_net = msg_r->getSp();
    double need = msg_r->getNeed();
    double offre = msg_r->getService();

    int passerelle = pass;      //par deffault vers le cloud si il ne trouve pas
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


void Edge::recv_fb_to_cloud(cMessage *msg) {
    //recevoir le message
    fb_to_cloud *msg_r = check_and_cast<fb_to_cloud *>(msg);

    std::string sp_net = msg_r->getSp();
    std::string sc_net = msg_r->getSc();
    double feedback = msg_r->getFb();

    fb_to_cloud *msg1 = new fb_to_cloud("req_to_sp");
    msg1->setSp(sp_net.c_str());
    msg1->setSc(sc_net.c_str());
    msg1->setFb(feedback);

    send(msg1, "pas$o",pass);
}






