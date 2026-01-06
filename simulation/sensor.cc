#include "sensor.h"

std::map<int ,std::array<std::string, 30>> sensor::not_Send;
std::map<int ,std::array<std::string, 30>> sensor::Send_6;
std::map<int ,std::array<std::string, 30>> sensor::Send_2;
std::map<int ,std::array<std::string, 30>> sensor::Send_All_Fake;
std::map<int ,std::array<std::string, 30>> sensor::Send_8_Fake;
std::map<int ,std::array<std::string, 30>> sensor::Send_4_Fake;
std::map<int ,std::array<std::string, 30>> sensor::Send_4_Fake_Out_8;
std::map<int ,std::array<std::string, 30>> sensor::Send_4_Fake_Out_4;
std::map<int ,std::array<std::string, 30>> sensor::Send_2_Fake_Out_6;

Define_Module(sensor);

std::mutex csvMutex4;

void sensor::inti_par() {
    sim_time = 18000;

    freq_per_trust_periode = 1;             //capteur envoi chq ...  120s – 30s – 1s
    nb_send_per_trust_periode = 10;
    trust_periode = freq_per_trust_periode * nb_send_per_trust_periode;
}


void sensor::inti_batteries() {
    std::string name = getName();
    if (name == "s1_h1" || name == "s2_h1" || name == "s3_h1" || name == "s4_h1") {
        batterie = intuniform(0,3);
    }else if (name == "s1_f1" || name == "s2_f1" || name == "s3_f1" || name == "s4_f1") {
        batterie = intuniform(5,8);
    }else if (name == "s1_h2" || name == "s2_h2" || name == "s3_h2" || name == "s4_h2") {
        batterie = intuniform(3,6);
    }else if (name == "s1_f2" || name == "s2_f2" || name == "s3_f2" || name == "s4_f2") {
        batterie = intuniform(12,15);
    }else if (name == "s1_h3" || name == "s2_h3" || name == "s3_h3" || name == "s4_h3") {
        batterie = intuniform(10,13);
    }
    else if (name == "s1_f3" || name == "s2_f3" || name == "s3_f3" || name == "s4_f3") {
        batterie = intuniform(20,23);
    }else if (name == "s1_h4" || name == "s2_h4" || name == "s3_h4" || name == "s4_h4") {
        batterie = intuniform(0,3);
    }else if (name == "s1_f4" || name == "s2_f4" || name == "s3_f4" || name == "s4_f4") {
        batterie = intuniform(20,23);
    }else if (name == "s1_h5" || name == "s2_h5" || name == "s3_h5" || name == "s4_h5") {
        batterie = intuniform(7,10);
    }else if (name == "s1_f5" || name == "s2_f5" || name == "s3_f5" || name == "s4_f5") {
        batterie = intuniform(32,35);
    }

}

void sensor::inti_file() {
    //batterie.csv
    {
        std::lock_guard<std::mutex> guard(csvMutex4);
        std::ofstream csvFile4("batterie.csv", std::ios::trunc);
    }
    std::lock_guard<std::mutex> guard(csvMutex4);
    std::ifstream csvFileCheck("batterie.csv");
    if (csvFileCheck.peek() == std::ifstream::traits_type::eof()) {
        std::ofstream csvFile4("batterie.csv", std::ios::out | std::ios::app);
        if (csvFile4.is_open()) {
            csvFile4 << "NodeID,Timestamp,Value\n";
        }
    }
}


void sensor::initialize() {

    inti_par();
    inti_batteries();
    inti_file();

    periode_trust = 0;

    se_charger = new cMessage("se_charger");
    scheduleAt(simTime() + 140, se_charger);            //la batterie se charge de 1% chaque 140s

    std::string name = getName();

    if (name == "s1_h1") {
        initialize_script_rand();
    }
    sensor_beh();
}


void sensor::charge() {
    if (batterie < 100) {
        batterie ++;
    }
    save(batterie);
    scheduleAt(simTime() + 140, se_charger);
}


void sensor::save(int batterie) {
    std::string id = getName();
    simtime_t time = simTime();
    std::lock_guard<std::mutex> guard(csvMutex4); // Verrouiller le mutex
    std::ofstream csvFile4("batterie.csv", std::ios::out | std::ios::app);
    if (csvFile4.is_open()) {
        csvFile4 << id << "," << time << "," << batterie << "\n" ;
    }
}


void sensor::initialize_script_15p() {
    std::string name = getName();
    EV << name <<" --- script is initialized for all \n\n\n";

    //--------------periode 1
    not_Send[1] = {"s1_h1"};                    Send_6[1] = {"s1_f3"};               Send_2[1] = {};
    Send_All_Fake[1] = {};                      Send_8_Fake[1] = {};                 Send_4_Fake[1] = {"s3_f5"};
    Send_4_Fake_Out_8[1] = {};                  Send_4_Fake_Out_4[1] = {};           Send_2_Fake_Out_6[1] = {};

    //--------------periode 2
    not_Send[2] = {"s1_h1"};                    Send_6[2] = {"s3_f4"};               Send_2[2] = {};
    Send_All_Fake[2] = {};                      Send_8_Fake[2] = {};                 Send_4_Fake[2] = {"s2_h5"};
    Send_4_Fake_Out_8[2] = {"s2_h2"};           Send_4_Fake_Out_4[2] = {};           Send_2_Fake_Out_6[2] = {"s2_h3"};

    //--------------periode 3
    not_Send[3] = {};                            Send_6[3] = {"s3_f4"};               Send_2[3] = {};
    Send_All_Fake[3] = {};                       Send_8_Fake[3] = {};                 Send_4_Fake[3] = {};
    Send_4_Fake_Out_8[3] = {"s2_h3"};            Send_4_Fake_Out_4[3] = {};           Send_2_Fake_Out_6[3] = {};

    //--------------periode 4
    not_Send[4] = {};                            Send_6[4] = {};                      Send_2[4] = {};
    Send_All_Fake[4] = {};                       Send_8_Fake[4] = {};                 Send_4_Fake[4] = {};
    Send_4_Fake_Out_8[4] = {};                   Send_4_Fake_Out_4[4] = {};           Send_2_Fake_Out_6[4] = {};

    //--------------periode 5
    not_Send[5] = {};                           Send_6[5] = {};                       Send_2[5] = {};
    Send_All_Fake[5] = {};                      Send_8_Fake[5] = {};                  Send_4_Fake[5] = {};
    Send_4_Fake_Out_8[5] = {};                  Send_4_Fake_Out_4[5] = {};            Send_2_Fake_Out_6[5] = {};

    //--------------periode 6
    not_Send[6] = {"s1_h1"};                    Send_6[6] = {};                       Send_2[6] = {"s3_f4"};
    Send_All_Fake[6] = {};                      Send_8_Fake[6] = {};                  Send_4_Fake[6] = {"s2_h5"};
    Send_4_Fake_Out_8[6] = {};                  Send_4_Fake_Out_4[6] = {};            Send_2_Fake_Out_6[6] = {};

    //--------------periode 7
    not_Send[7] = {};                           Send_6[7] = {};                        Send_2[7] = {"s3_f4", "s1_f3"};
    Send_All_Fake[7] = {};                      Send_8_Fake[7] = {};                   Send_4_Fake[7] = {"s3_f1"};
    Send_4_Fake_Out_8[7] = {"s3_f5"};           Send_4_Fake_Out_4[7] = {};             Send_2_Fake_Out_6[7] = {};

    //--------------periode 8
    not_Send[8] = {};                           Send_6[8] = {"s1_f3"};                  Send_2[8] = {};
    Send_All_Fake[8] = {};                      Send_8_Fake[8] = {};                    Send_4_Fake[8] = {"s3_f1"};
    Send_4_Fake_Out_8[8] = {};                  Send_4_Fake_Out_4[8] = {};              Send_2_Fake_Out_6[8] = {};

    //--------------periode 9
    not_Send[9] = {};                           Send_6[9] = {};                         Send_2[9] = {};
    Send_All_Fake[9] = {};                      Send_8_Fake[9] = {};                    Send_4_Fake[9] = {};
    Send_4_Fake_Out_8[9] = {};                  Send_4_Fake_Out_4[9] = {};              Send_2_Fake_Out_6[9] = {};

    //--------------periode 10
    not_Send[10] = {"s3_f5"};                   Send_6[10] = {"s2_h5"};                 Send_2[10] = {};
    Send_All_Fake[10] = {};                     Send_8_Fake[10] = {};                   Send_4_Fake[10] = {};
    Send_4_Fake_Out_8[10] = {};                 Send_4_Fake_Out_4[10] = {};             Send_2_Fake_Out_6[10] = {};

    //--------------periode 11
    not_Send[11] = {"s3_f5"};                   Send_6[11] = {"s2_h5"};                 Send_2[11] = {};
    Send_All_Fake[11] = {};                     Send_8_Fake[11] = {};                   Send_4_Fake[11] = {};
    Send_4_Fake_Out_8[11] = {"s2_h2"};          Send_4_Fake_Out_4[11] = {};             Send_2_Fake_Out_6[11] = {"s2_h3"};

    //--------------periode 12
    not_Send[12] = {};                          Send_6[12] = {"s1_h1"};                 Send_2[12] = {"s3_f5"};
    Send_All_Fake[12] = {};                     Send_8_Fake[12] = {"s2_h2", "s3_f1"};   Send_4_Fake[12] = {};
    Send_4_Fake_Out_8[12] = {"s2_h3"};          Send_4_Fake_Out_4[12] = {};             Send_2_Fake_Out_6[12] = {};

    //--------------periode 13
    not_Send[13] = {"s1_h1"};                   Send_6[13] = {"s2_f2"};                 Send_2[13] = {"s3_f4"};
    Send_All_Fake[13] = {"s2_h2", "s2_h3"};     Send_8_Fake[13] = {};                   Send_4_Fake[13] = {};
    Send_4_Fake_Out_8[13] = {};                 Send_4_Fake_Out_4[13] = {"s3_f1"};      Send_2_Fake_Out_6[13] = {};

    //--------------periode 14
    not_Send[14] = {"s3_f4"};                   Send_6[14] = {"s1_f3"};                 Send_2[14] = {};
    Send_All_Fake[14] = {};                     Send_8_Fake[14] = {};                   Send_4_Fake[14] = {};
    Send_4_Fake_Out_8[14] = {};                 Send_4_Fake_Out_4[14] = {};             Send_2_Fake_Out_6[14] = {};

    //--------------periode 15
    not_Send[15] = {};                          Send_6[15] = {};                        Send_2[15] = {"s1_f3"};
    Send_All_Fake[15] = {};                     Send_8_Fake[15] = {};                   Send_4_Fake[15] = {};
    Send_4_Fake_Out_8[15] = {};                 Send_4_Fake_Out_4[15] = {};             Send_2_Fake_Out_6[15] = {};

}



void sensor::initialize_script_60p() {
    std::string name = getName();
    EV << name <<" --- script is initialized for all \n\n\n";

    //--------------periode 1
    not_Send[1] = {"s1_h1"};                    Send_6[1] = {"s1_f3"};               Send_2[1] = {};
    Send_All_Fake[1] = {};                      Send_8_Fake[1] = {};                 Send_4_Fake[1] = {"s3_f5"};
    Send_4_Fake_Out_8[1] = {};                  Send_4_Fake_Out_4[1] = {};           Send_2_Fake_Out_6[1] = {};

    //--------------periode 2
    not_Send[2] = {"s1_h1"};                    Send_6[2] = {"s3_f4"};               Send_2[2] = {};
    Send_All_Fake[2] = {};                      Send_8_Fake[2] = {};                 Send_4_Fake[2] = {"s2_h5"};
    Send_4_Fake_Out_8[2] = {"s2_h2"};           Send_4_Fake_Out_4[2] = {};           Send_2_Fake_Out_6[2] = {"s2_h3"};

    //--------------periode 3
    not_Send[3] = {};                            Send_6[3] = {"s3_f4"};               Send_2[3] = {};
    Send_All_Fake[3] = {};                       Send_8_Fake[3] = {};                 Send_4_Fake[3] = {};
    Send_4_Fake_Out_8[3] = {"s2_h3"};            Send_4_Fake_Out_4[3] = {};           Send_2_Fake_Out_6[3] = {};

    //--------------periode 4
    not_Send[4] = {};                            Send_6[4] = {};                      Send_2[4] = {};
    Send_All_Fake[4] = {};                       Send_8_Fake[4] = {};                 Send_4_Fake[4] = {};
    Send_4_Fake_Out_8[4] = {};                   Send_4_Fake_Out_4[4] = {};           Send_2_Fake_Out_6[4] = {};

    //--------------periode 5
    not_Send[5] = {};                           Send_6[5] = {};                       Send_2[5] = {};
    Send_All_Fake[5] = {};                      Send_8_Fake[5] = {};                  Send_4_Fake[5] = {};
    Send_4_Fake_Out_8[5] = {};                  Send_4_Fake_Out_4[5] = {};            Send_2_Fake_Out_6[5] = {};

    //--------------periode 6
    not_Send[6] = {"s1_h1"};                    Send_6[6] = {};                       Send_2[6] = {"s3_f4"};
    Send_All_Fake[6] = {};                      Send_8_Fake[6] = {};                  Send_4_Fake[6] = {"s2_h5"};
    Send_4_Fake_Out_8[6] = {};                  Send_4_Fake_Out_4[6] = {};            Send_2_Fake_Out_6[6] = {};

    //--------------periode 7
    not_Send[7] = {};                           Send_6[7] = {};                        Send_2[7] = {"s3_f4", "s1_f3"};
    Send_All_Fake[7] = {};                      Send_8_Fake[7] = {};                   Send_4_Fake[7] = {"s3_f1"};
    Send_4_Fake_Out_8[7] = {"s3_f5"};           Send_4_Fake_Out_4[7] = {};             Send_2_Fake_Out_6[7] = {};

    //--------------periode 8
    not_Send[8] = {};                           Send_6[8] = {"s1_f3"};                  Send_2[8] = {};
    Send_All_Fake[8] = {};                      Send_8_Fake[8] = {};                    Send_4_Fake[8] = {"s3_f1"};
    Send_4_Fake_Out_8[8] = {};                  Send_4_Fake_Out_4[8] = {};              Send_2_Fake_Out_6[8] = {};

    //--------------periode 9
    not_Send[9] = {};                           Send_6[9] = {};                         Send_2[9] = {};
    Send_All_Fake[9] = {};                      Send_8_Fake[9] = {};                    Send_4_Fake[9] = {};
    Send_4_Fake_Out_8[9] = {};                  Send_4_Fake_Out_4[9] = {};              Send_2_Fake_Out_6[9] = {};

    //--------------periode 10
    not_Send[10] = {"s3_f5"};                   Send_6[10] = {"s2_h5"};                 Send_2[10] = {};
    Send_All_Fake[10] = {};                     Send_8_Fake[10] = {};                   Send_4_Fake[10] = {};
    Send_4_Fake_Out_8[10] = {};                 Send_4_Fake_Out_4[10] = {};             Send_2_Fake_Out_6[10] = {};

    //--------------periode 11
    not_Send[11] = {"s3_f5"};                   Send_6[11] = {"s2_h5"};                 Send_2[11] = {};
    Send_All_Fake[11] = {};                     Send_8_Fake[11] = {};                   Send_4_Fake[11] = {};
    Send_4_Fake_Out_8[11] = {"s2_h2"};          Send_4_Fake_Out_4[11] = {};             Send_2_Fake_Out_6[11] = {"s2_h3"};

    //--------------periode 12
    not_Send[12] = {};                          Send_6[12] = {"s1_h1"};                 Send_2[12] = {"s3_f5"};
    Send_All_Fake[12] = {};                     Send_8_Fake[12] = {"s2_h2", "s3_f1"};   Send_4_Fake[12] = {};
    Send_4_Fake_Out_8[12] = {"s2_h3"};          Send_4_Fake_Out_4[12] = {};             Send_2_Fake_Out_6[12] = {};

    //--------------periode 13
    not_Send[13] = {"s1_h1"};                   Send_6[13] = {"s2_f2"};                 Send_2[13] = {"s3_f4"};
    Send_All_Fake[13] = {"s2_h2", "s2_h3"};     Send_8_Fake[13] = {};                   Send_4_Fake[13] = {};
    Send_4_Fake_Out_8[13] = {};                 Send_4_Fake_Out_4[13] = {"s3_f1"};      Send_2_Fake_Out_6[13] = {};

    //--------------periode 14
    not_Send[14] = {"s3_f4"};                   Send_6[14] = {"s1_f3"};                 Send_2[14] = {};
    Send_All_Fake[14] = {};                     Send_8_Fake[14] = {};                   Send_4_Fake[14] = {};
    Send_4_Fake_Out_8[14] = {};                 Send_4_Fake_Out_4[14] = {};             Send_2_Fake_Out_6[14] = {};

    //--------------periode 15
    not_Send[15] = {};                          Send_6[15] = {};                        Send_2[15] = {"s1_f3"};
    Send_All_Fake[15] = {};                     Send_8_Fake[15] = {};                   Send_4_Fake[15] = {};
    Send_4_Fake_Out_8[15] = {};                 Send_4_Fake_Out_4[15] = {};             Send_2_Fake_Out_6[15] = {};

    //--------------periode 16
    not_Send[16] = {"s1_h1"};                   Send_6[16] = {"s3_f5"};                 Send_2[16] = {};
    Send_All_Fake[16] = {};                     Send_8_Fake[16] = {};                   Send_4_Fake[16] = {};
    Send_4_Fake_Out_8[16] = {};                 Send_4_Fake_Out_4[16] = {};             Send_2_Fake_Out_6[16] = {};

    //--------------periode 17
    not_Send[17] = {};                          Send_6[17] = {};                        Send_2[17] = {};
    Send_All_Fake[17] = {};                     Send_8_Fake[17] = {};                   Send_4_Fake[17] = {};
    Send_4_Fake_Out_8[17] = {};                 Send_4_Fake_Out_4[17] = {};             Send_2_Fake_Out_6[17] = {};

    //--------------periode 18
    not_Send[18] = {"s1_h1"};                   Send_6[18] = {};                        Send_2[18] = {"s3_f4"};
    Send_All_Fake[18] = {};                     Send_8_Fake[18] = {};                   Send_4_Fake[18] = {"s2_h5"};
    Send_4_Fake_Out_8[18] = {};                 Send_4_Fake_Out_4[18] = {};             Send_2_Fake_Out_6[18] = {};

    //--------------periode 19
    not_Send[19] = {};                          Send_6[19] = {"s3_f4"};                 Send_2[19] = {};
    Send_All_Fake[19] = {};                     Send_8_Fake[19] = {};                   Send_4_Fake[19] = {};
    Send_4_Fake_Out_8[19] = {};                 Send_4_Fake_Out_4[19] = {};             Send_2_Fake_Out_6[19] = {};

    //--------------periode 20
    not_Send[20] = {"s3_f5", "s1_h1"};          Send_6[20] = {};                        Send_2[20] = {};
    Send_All_Fake[20] = {};                     Send_8_Fake[20] = {};                   Send_4_Fake[20] = {"s2_h5", "s3_f1"};
    Send_4_Fake_Out_8[20] = {};                 Send_4_Fake_Out_4[20] = {};             Send_2_Fake_Out_6[20] = {};

    //--------------periode 21
    not_Send[21] = {};                          Send_6[21] = {};                        Send_2[21] = {};
    Send_All_Fake[21] = {};                     Send_8_Fake[21] = {};                   Send_4_Fake[21] = {};
    Send_4_Fake_Out_8[21] = {};                 Send_4_Fake_Out_4[21] = {};             Send_2_Fake_Out_6[21] = {};

    //--------------periode 22
    not_Send[22] = {"s3_f4"};                   Send_6[22] = {"s1_f3"};                 Send_2[22] = {};
    Send_All_Fake[22] = {};                     Send_8_Fake[22] = {};                   Send_4_Fake[22] = {};
    Send_4_Fake_Out_8[22] = {};                 Send_4_Fake_Out_4[22] = {};             Send_2_Fake_Out_6[22] = {};

    //--------------periode 23
    not_Send[23] = {"s1_h1"};                   Send_6[23] = {};                        Send_2[23] = {};
    Send_All_Fake[23] = {};                     Send_8_Fake[23] = {};                   Send_4_Fake[23] = {};
    Send_4_Fake_Out_8[23] = {};                 Send_4_Fake_Out_4[23] = {};             Send_2_Fake_Out_6[23] = {};

    //--------------periode 24
    not_Send[24] = {"s3_f5"};                   Send_6[24] = {"s2_h5"};                 Send_2[24] = {"s3_f4"};
    Send_All_Fake[24] = {};                     Send_8_Fake[24] = {};                   Send_4_Fake[24] = {};
    Send_4_Fake_Out_8[24] = {"s2_h3", "s2_h2"}; Send_4_Fake_Out_4[24] = {};             Send_2_Fake_Out_6[24] = {};

    //--------------periode 25
    not_Send[25] = {};                          Send_6[25] = {"s1_f3"};                 Send_2[25] = {};
    Send_All_Fake[25] = {};                     Send_8_Fake[25] = {"s2_f1"};            Send_4_Fake[25] = {};
    Send_4_Fake_Out_8[25] = {"s2_h3"};          Send_4_Fake_Out_4[25] = {};             Send_2_Fake_Out_6[25] = {};

    //--------------periode 26
    not_Send[26] = {};                          Send_6[26] = {};                        Send_2[26] = {"s3_f4"};
    Send_All_Fake[26] = {};                     Send_8_Fake[25] = {};                   Send_4_Fake[26] = {"s2_h5"};
    Send_4_Fake_Out_8[26] = {};                 Send_4_Fake_Out_4[26] = {};             Send_2_Fake_Out_6[26] = {};

    //--------------periode 27
    not_Send[27] = {};                          Send_6[27] = {};                        Send_2[27] = {};
    Send_All_Fake[27] = {};                     Send_8_Fake[27] = {};                   Send_4_Fake[27] = {};
    Send_4_Fake_Out_8[27] = {};                 Send_4_Fake_Out_4[27] = {};             Send_2_Fake_Out_6[27] = {};

    //--------------periode 28
    not_Send[28] = {"s1_h1"};                   Send_6[28] = {};                        Send_2[28] = {"s3_f5"};
    Send_All_Fake[28] = {};                     Send_8_Fake[28] = {};                   Send_4_Fake[28] = {};
    Send_4_Fake_Out_8[28] = {"s2_h2"};          Send_4_Fake_Out_4[28] = {};             Send_2_Fake_Out_6[28] = {"s2_h3"};

    //--------------periode 29
    not_Send[29] = {"s3_f4"};                   Send_6[29] = {};                        Send_2[29] = {};
    Send_All_Fake[29] = {};                     Send_8_Fake[29] = {};                   Send_4_Fake[29] = {};
    Send_4_Fake_Out_8[29] = {};                 Send_4_Fake_Out_4[29] = {};             Send_2_Fake_Out_6[29] = {};

    //--------------periode 30
    not_Send[30] = {};                          Send_6[30] = {};                        Send_2[30] = {"s1_f3"};
    Send_All_Fake[30] = {};                     Send_8_Fake[30] = {};                   Send_4_Fake[30] = {"s3_f1"};
    Send_4_Fake_Out_8[30] = {};                 Send_4_Fake_Out_4[30] = {};             Send_2_Fake_Out_6[30] = {};

    //--------------periode 31
    not_Send[31] = {};                          Send_6[31] = {};                        Send_2[31] = {};
    Send_All_Fake[31] = {};                     Send_8_Fake[31] = {};                   Send_4_Fake[31] = {};
    Send_4_Fake_Out_8[31] = {};                 Send_4_Fake_Out_4[31] = {};             Send_2_Fake_Out_6[31] = {};

    //--------------periode 32
    not_Send[32] = {};                          Send_6[32] = {};                        Send_2[32] = {"s3_f4"};
    Send_All_Fake[32] = {};                     Send_8_Fake[32] = {};                   Send_4_Fake[32] = {"s2_h5"};
    Send_4_Fake_Out_8[32] = {"s2_h2"};          Send_4_Fake_Out_4[32] = {};             Send_2_Fake_Out_6[32] = {};

    //--------------periode 33
    not_Send[33] = {"s3_f5"};                   Send_6[33] = {};                        Send_2[33] = {};
    Send_All_Fake[33] = {};                     Send_8_Fake[33] = {};                   Send_4_Fake[33] = {};
    Send_4_Fake_Out_8[33] = {};                 Send_4_Fake_Out_4[33] = {};             Send_2_Fake_Out_6[33] = {};

    //--------------periode 34
    not_Send[34] = {"s1_h1"};                   Send_6[34] = {};                        Send_2[34] = {"s3_f4"};
    Send_All_Fake[34] = {};                     Send_8_Fake[34] = {"s2_f1"};            Send_4_Fake[34] = {};
    Send_4_Fake_Out_8[34] = {"s2_h2", "s2_h3"}; Send_4_Fake_Out_4[34] = {};             Send_2_Fake_Out_6[34] = {};

    //--------------periode 35
    not_Send[35] = {"s3_f5"};                   Send_6[35] = {"s1_f3"};                 Send_2[35] = {};
    Send_All_Fake[35] = {};                     Send_8_Fake[35] = {};                   Send_4_Fake[35] = {"s3_f1", "s2_h5"};
    Send_4_Fake_Out_8[35] = {};                 Send_4_Fake_Out_4[35] = {};             Send_2_Fake_Out_6[35] = {};

    //--------------periode 36
    not_Send[36] = {"s1_h1"};                   Send_6[36] = {};                        Send_2[36] = {};
    Send_All_Fake[36] = {};                     Send_8_Fake[36] = {};                   Send_4_Fake[36] = {};
    Send_4_Fake_Out_8[36] = {};                 Send_4_Fake_Out_4[36] = {};             Send_2_Fake_Out_6[36] = {"s2_h3"};

    //--------------periode 37
    not_Send[37] = {};                          Send_6[37] = {};                        Send_2[37] = {};
    Send_All_Fake[37] = {};                     Send_8_Fake[37] = {};                   Send_4_Fake[37] = {};
    Send_4_Fake_Out_8[37] = {};                 Send_4_Fake_Out_4[37] = {};             Send_2_Fake_Out_6[37] = {};

    //--------------periode 38
    not_Send[38] = {"s3_f5"};                   Send_6[38] = {};                        Send_2[38] = {"s3_f4"};
    Send_All_Fake[38] = {};                     Send_8_Fake[38] = {};                   Send_4_Fake[38] = {};
    Send_4_Fake_Out_8[38] = {"s2_h2"};          Send_4_Fake_Out_4[38] = {};             Send_2_Fake_Out_6[38] = {};

    //--------------periode 39
    not_Send[39] = {};                          Send_6[39] = {};                        Send_2[39] = {};
    Send_All_Fake[39] = {};                     Send_8_Fake[39] = {};                   Send_4_Fake[39] = {"s2_h5"};
    Send_4_Fake_Out_8[39] = {};                 Send_4_Fake_Out_4[39] = {};             Send_2_Fake_Out_6[39] = {};

    //--------------periode 40
    not_Send[40] = {};                          Send_6[40] = {};                        Send_2[40] = {"s1_f3"};
    Send_All_Fake[40] = {};                     Send_8_Fake[40] = {};                   Send_4_Fake[40] = {"s3_f1"};
    Send_4_Fake_Out_8[40] = {};                 Send_4_Fake_Out_4[40] = {};             Send_2_Fake_Out_6[40] = {};

    //--------------periode 41
    not_Send[41] = {};                          Send_6[41] = {};                        Send_2[41] = {};
    Send_All_Fake[41] = {};                     Send_8_Fake[41] = {};                   Send_4_Fake[41] = {};
    Send_4_Fake_Out_8[41] = {};                 Send_4_Fake_Out_4[41] = {};             Send_2_Fake_Out_6[41] = {};

    //--------------periode 42
    not_Send[42] = {"s1_h1"};                   Send_6[42] = {};                        Send_2[42] = {"s3_f4"};
    Send_All_Fake[42] = {};                     Send_8_Fake[42] = {"s2_f1"};            Send_4_Fake[42] = {};
    Send_4_Fake_Out_8[42] = {"s2_h3"};          Send_4_Fake_Out_4[42] = {};             Send_2_Fake_Out_6[42] = {};

    //--------------periode 43
    not_Send[43] = {};                          Send_6[43] = {"s2_h5"};                 Send_2[43] = {};
    Send_All_Fake[43] = {};                     Send_8_Fake[43] = {};                   Send_4_Fake[43] = {};
    Send_4_Fake_Out_8[43] = {};                 Send_4_Fake_Out_4[43] = {};             Send_2_Fake_Out_6[43] = {};

    //--------------periode 44
    not_Send[44] = {"s3_f5"};                   Send_6[44] = {};                        Send_2[44] = {};
    Send_All_Fake[44] = {};                     Send_8_Fake[44] = {};                   Send_4_Fake[44] = {"s3_f1"};
    Send_4_Fake_Out_8[44] = {"s2_h2"};          Send_4_Fake_Out_4[44] = {};             Send_2_Fake_Out_6[44] = {};

    //--------------periode 45
    not_Send[45] = {};                          Send_6[45] = {};                        Send_2[45] = {"s1_f3"};
    Send_All_Fake[45] = {};                     Send_8_Fake[45] = {};                   Send_4_Fake[45] = {};
    Send_4_Fake_Out_8[45] = {};                 Send_4_Fake_Out_4[45] = {};             Send_2_Fake_Out_6[45] = {"s2_h3"};

    //--------------periode 46
    not_Send[46] = {};                          Send_6[46] = {};                        Send_2[46] = {};
    Send_All_Fake[46] = {};                     Send_8_Fake[46] = {};                   Send_4_Fake[46] = {};
    Send_4_Fake_Out_8[46] = {};                 Send_4_Fake_Out_4[46] = {};             Send_2_Fake_Out_6[46] = {};

    //--------------periode 47
    not_Send[47] = {"s1_h1"};                   Send_6[47] = {};                        Send_2[47] = {};
    Send_All_Fake[47] = {};                     Send_8_Fake[47] = {};                   Send_4_Fake[47] = {};
    Send_4_Fake_Out_8[47] = {};                 Send_4_Fake_Out_4[47] = {};             Send_2_Fake_Out_6[47] = {};

    //--------------periode 48
    not_Send[48] = {};                          Send_6[48] = {};                        Send_2[48] = {"s3_f4"};
    Send_All_Fake[48] = {};                     Send_8_Fake[48] = {};                   Send_4_Fake[48] = {"s2_h5"};
    Send_4_Fake_Out_8[48] = {"s2_h2"};          Send_4_Fake_Out_4[48] = {};             Send_2_Fake_Out_6[48] = {};

    //--------------periode 49
    not_Send[49] = {"s3_f5"};                   Send_6[49] = {"s1_f3"};                 Send_2[49] = {};
    Send_All_Fake[49] = {};                     Send_8_Fake[49] = {};                   Send_4_Fake[49] = {};
    Send_4_Fake_Out_8[49] = {};                 Send_4_Fake_Out_4[49] = {};             Send_2_Fake_Out_6[49] = {};

    //--------------periode 50
    not_Send[50] = {"s1_h1"};                   Send_6[50] = {};                        Send_2[50] = {};
    Send_All_Fake[50] = {};                     Send_8_Fake[50] = {"s2_f1"};            Send_4_Fake[50] = {"s3_f1"};
    Send_4_Fake_Out_8[50] = {"s2_h3"};          Send_4_Fake_Out_4[50] = {};             Send_2_Fake_Out_6[50] = {};

    //--------------periode 51
    not_Send[51] = {};                          Send_6[51] = {};                        Send_2[51] = {"s3_f4"};
    Send_All_Fake[51] = {};                     Send_8_Fake[51] = {};                   Send_4_Fake[51] = {};
    Send_4_Fake_Out_8[51] = {};                 Send_4_Fake_Out_4[51] = {};             Send_2_Fake_Out_6[51] = {};

    //--------------periode 52
    not_Send[52] = {};                          Send_6[52] = {};                        Send_2[52] = {};
    Send_All_Fake[52] = {};                     Send_8_Fake[52] = {};                   Send_4_Fake[52] = {};
    Send_4_Fake_Out_8[52] = {};                 Send_4_Fake_Out_4[52] = {};             Send_2_Fake_Out_6[52] = {};

    //--------------periode 53
    not_Send[53] = {"s3_f5"};                   Send_6[53] = {"s1_f3"};                 Send_2[53] = {};
    Send_All_Fake[53] = {};                     Send_8_Fake[53] = {};                   Send_4_Fake[53] = {};
    Send_4_Fake_Out_8[53] = {};                 Send_4_Fake_Out_4[53] = {};             Send_2_Fake_Out_6[53] = {};

    //--------------periode 54
    not_Send[54] = {};                          Send_6[54] = {};                        Send_2[54] = {};
    Send_All_Fake[54] = {};                     Send_8_Fake[54] = {};                   Send_4_Fake[54] = {"s2_h5", "s3_f1"};
    Send_4_Fake_Out_8[54] = {};                 Send_4_Fake_Out_4[54] = {};             Send_2_Fake_Out_6[54] = {"s2_h3"};

    //--------------periode 55
    not_Send[55] = {"s1_h1"};                   Send_6[55] = {};                        Send_2[55] = {"s3_f4"};
    Send_All_Fake[55] = {};                     Send_8_Fake[55] = {"s2_f1"};            Send_4_Fake[55] = {};
    Send_4_Fake_Out_8[55] = {"s2_h2"};          Send_4_Fake_Out_4[55] = {};             Send_2_Fake_Out_6[55] = {};

    //--------------periode 56
    not_Send[56] = {"s3_f5"};                   Send_6[56] = {};                        Send_2[56] = {};
    Send_All_Fake[56] = {};                     Send_8_Fake[56] = {};                   Send_4_Fake[56] = {"s3_f1"};
    Send_4_Fake_Out_8[56] = {};                 Send_4_Fake_Out_4[56] = {};             Send_2_Fake_Out_6[56] = {};

    //--------------periode 57
    not_Send[57] = {};                          Send_6[57] = {};                        Send_2[57] = {};
    Send_All_Fake[57] = {};                     Send_8_Fake[57] = {};                   Send_4_Fake[57] = {};
    Send_4_Fake_Out_8[57] = {};                 Send_4_Fake_Out_4[57] = {};             Send_2_Fake_Out_6[57] = {};

    //--------------periode 58
    not_Send[58] = {};                          Send_6[58] = {};                        Send_2[58] = {"s3_f4"};
    Send_All_Fake[58] = {};                     Send_8_Fake[58] = {};                   Send_4_Fake[58] = {"s2_h5"};
    Send_4_Fake_Out_8[58] = {"s2_h3"};          Send_4_Fake_Out_4[58] = {};             Send_2_Fake_Out_6[58] = {};

    //--------------periode 59
    not_Send[59] = {"s1_h1"};                   Send_6[59] = {};                        Send_2[59] = {};
    Send_All_Fake[59] = {};                     Send_8_Fake[59] = {};                   Send_4_Fake[59] = {};
    Send_4_Fake_Out_8[59] = {};                 Send_4_Fake_Out_4[59] = {};             Send_2_Fake_Out_6[59] = {};

    //--------------periode 60
    not_Send[60] = {};                          Send_6[60] = {"s1_f3"};                 Send_2[60] = {};
    Send_All_Fake[60] = {};                     Send_8_Fake[60] = {"s2_f1"};            Send_4_Fake[60] = {};
    Send_4_Fake_Out_8[60] = {};                 Send_4_Fake_Out_4[60] = {};             Send_2_Fake_Out_6[60] = {};
}



void sensor::initialize_script_new_15p() {
    std::string name = getName();
    EV << name <<" --- script is initialized for all \n\n\n";

    //--------------periode 1
    not_Send[1] = {"s1_h1"};                    Send_6[1] = {"s1_f2"};               Send_2[1] = {};
    Send_All_Fake[1] = {"s2_h3"};               Send_8_Fake[1] = {};                 Send_4_Fake[1] = {"s3_f5"};
    Send_4_Fake_Out_8[1] = {};                  Send_4_Fake_Out_4[1] = {};           Send_2_Fake_Out_6[1] = {};

    //--------------periode 2
    not_Send[2] = {"s1_h1"};                    Send_6[2] = {"s1_f3"};               Send_2[2] = {"s2_f5"};
    Send_All_Fake[2] = {};                      Send_8_Fake[2] = {"s3_f4"};          Send_4_Fake[2] = {};
    Send_4_Fake_Out_8[2] = {"s3_f2"};           Send_4_Fake_Out_4[2] = {};           Send_2_Fake_Out_6[2] = {"s2_h1"};

    //--------------periode 3
    not_Send[3] = {"s3_f5"};                     Send_6[3] = {};                      Send_2[3] = {"s2_h2"};
    Send_All_Fake[3] = {};                       Send_8_Fake[3] = {"s1_f1"};          Send_4_Fake[3] = {};
    Send_4_Fake_Out_8[3] = {};                   Send_4_Fake_Out_4[3] = {};           Send_2_Fake_Out_6[3] = {};

    //--------------periode 4
    not_Send[4] = {};                            Send_6[4] = {};                      Send_2[4] = {};
    Send_All_Fake[4] = {};                       Send_8_Fake[4] = {};                 Send_4_Fake[4] = {};
    Send_4_Fake_Out_8[4] = {};                   Send_4_Fake_Out_4[4] = {};           Send_2_Fake_Out_6[4] = {};

    //--------------periode 5
    not_Send[5] = {};                           Send_6[5] = {};                       Send_2[5] = {};
    Send_All_Fake[5] = {};                      Send_8_Fake[5] = {};                  Send_4_Fake[5] = {};
    Send_4_Fake_Out_8[5] = {};                  Send_4_Fake_Out_4[5] = {};            Send_2_Fake_Out_6[5] = {};

    //--------------periode 6
    not_Send[6] = {"s2_h1"};                    Send_6[6] = {};                       Send_2[6] = {"s1_f4"};
    Send_All_Fake[6] = {};                      Send_8_Fake[6] = {};                  Send_4_Fake[6] = {"s3_f3"};
    Send_4_Fake_Out_8[6] = {};                  Send_4_Fake_Out_4[6] = {};            Send_2_Fake_Out_6[6] = {};

    //--------------periode 7
    not_Send[7] = {};                           Send_6[7] = {};                         Send_2[7] = {"s2_f3", "s1_h3"};
    Send_All_Fake[7] = {"s2_h4"};               Send_8_Fake[7] = {};                    Send_4_Fake[7] = {"s3_f4"};
    Send_4_Fake_Out_8[7] = {"s3_f1"};           Send_4_Fake_Out_4[7] = {};              Send_2_Fake_Out_6[7] = {};

    //--------------periode 8
    not_Send[8] = {"s1_f4"};                    Send_6[8] = {"s1_f2", "s2_h5"};         Send_2[8] = {};
    Send_All_Fake[8] = {};                      Send_8_Fake[8] = {};                    Send_4_Fake[8] = {"s3_f1"};
    Send_4_Fake_Out_8[8] = {};                  Send_4_Fake_Out_4[8] = {};              Send_2_Fake_Out_6[8] = {};

    //--------------periode 9
    not_Send[9] = {};                           Send_6[9] = {};                         Send_2[9] = {};
    Send_All_Fake[9] = {};                      Send_8_Fake[9] = {};                    Send_4_Fake[9] = {};
    Send_4_Fake_Out_8[9] = {};                  Send_4_Fake_Out_4[9] = {};              Send_2_Fake_Out_6[9] = {};

    //--------------periode 10
    not_Send[10] = {"s3_f5"};                   Send_6[10] = {"s2_h5"};                 Send_2[10] = {};
    Send_All_Fake[10] = {};                     Send_8_Fake[10] = {"s1_h2"};            Send_4_Fake[10] = {};
    Send_4_Fake_Out_8[10] = {};                 Send_4_Fake_Out_4[10] = {};             Send_2_Fake_Out_6[10] = {};

    //--------------periode 11
    not_Send[11] = {"s3_f5"};                   Send_6[11] = {"s2_f2"};                 Send_2[11] = {"s1_f4"};
    Send_All_Fake[11] = {"s1_h3"};              Send_8_Fake[11] = {};                   Send_4_Fake[11] = {};
    Send_4_Fake_Out_8[11] = {"s2_h2"};          Send_4_Fake_Out_4[11] = {};             Send_2_Fake_Out_6[11] = {"s2_h3"};

    //--------------periode 12
    not_Send[12] = {};                          Send_6[12] = {"s1_h1"};                 Send_2[12] = {"s3_f4"};
    Send_All_Fake[12] = {};                     Send_8_Fake[12] = {"s2_h2"};            Send_4_Fake[12] = {};
    Send_4_Fake_Out_8[12] = {"s2_f1"};          Send_4_Fake_Out_4[12] = {};             Send_2_Fake_Out_6[12] = {};

    //--------------periode 13
    not_Send[13] = {"s1_h1"};                   Send_6[13] = {"s2_f2"};                 Send_2[13] = {"s3_f4"};
    Send_All_Fake[13] = {"s2_h2", "s2_h3"};     Send_8_Fake[13] = {"s3_f3"};            Send_4_Fake[13] = {};
    Send_4_Fake_Out_8[13] = {};                 Send_4_Fake_Out_4[13] = {"s2_f1"};      Send_2_Fake_Out_6[13] = {};

    //--------------periode 14
    not_Send[14] = {"s3_f4"};                   Send_6[14] = {"s1_f3"};                 Send_2[14] = {};
    Send_All_Fake[14] = {"s2_h4"};              Send_8_Fake[14] = {};                   Send_4_Fake[14] = {};
    Send_4_Fake_Out_8[14] = {};                 Send_4_Fake_Out_4[14] = {};             Send_2_Fake_Out_6[14] = {};

    //--------------periode 15
    not_Send[15] = {};                          Send_6[15] = {};                        Send_2[15] = {"s1_f3"};
    Send_All_Fake[15] = {};                     Send_8_Fake[15] = {};                   Send_4_Fake[15] = {"s3_f2"};
    Send_4_Fake_Out_8[15] = {};                 Send_4_Fake_Out_4[15] = {};             Send_2_Fake_Out_6[15] = {};

}


void sensor::initialize_nodes_mali() {
    //initializer le type de comportement des noeuds
    malicious_nodes["notsend"];         malicious_nodes["send6"];           malicious_nodes["send2"];
    malicious_nodes["sendallfake"];     malicious_nodes["send8fake"];       malicious_nodes["send4fake"];
    malicious_nodes["send4fake8"];      malicious_nodes["send4fake4"];      malicious_nodes["send2fake6"];
}



void sensor::initialize_script_rand() {

    int nb_trust_periodes = sim_time / trust_periode;

    for (int i=1; i<=nb_trust_periodes; i++) {
        initialize_nodes_mali();                                    //creer un vector avec tout les noeuds du réseau + initialiser le dictionaire malicious_nodes

        //low
        //std::vector<double> prob = {0.25, 0.3, 0.2, 0.1, 0.05, 0.025, 0.025, 0.0125, 0.0125, 0.0125, 0.0125};

        //mid
        std::vector<double> prob = {0.039318090214219774, 0.06166303999316262, 0.08750401900190527,
        0.11235738446077344, 0.1305406566899133, 0.1372336192800513, 0.1305406566899133,
        0.11235738446077344, 0.08750401900190527, 0.06166303999316262, 0.039318090214219774};

        //high
        //std::vector<double> prob= {0.0125, 0.0125, 0.0125, 0.0125, 0.025, 0.025, 0.05, 0.1, 0.2, 0.25, 0.3};

        std::random_device rd;
        std::mt19937 gen(rd());
        std::discrete_distribution<> weighted_distribution(prob.begin(), prob.end());
        int nb_noeud_malicieux = weighted_distribution(gen);

        std::vector<std::string> choisen;
        std::string node;
        for (int j =0; j<nb_noeud_malicieux; j++) {
            bool keep_looking = true;
            while (keep_looking) {
                //---------chose the network
                std::vector<std::string> net = {"h1", "h2" , "h3", "h4", "h5", "f1", "f2", "f3", "f4", "f5"};
                std::vector<double> prob1 = {0.24, 0.05, 0.15, 0.01, 0.05, 0.05, 0.15, 0.01, 0.24, 0.05};
                std::random_device rd1;
                std::mt19937 gen1(rd1());
                std::discrete_distribution<> weighted_distribution1(prob1.begin(), prob1.end());
                int net_index = weighted_distribution1(gen1);
                std::string network = net[net_index];
                //---------chose the sensor on the choisen network
                std::vector<std::string> sens = {"s1", "s2" , "s3", "s4"};
                std::vector<double> prob2 = {0.7, 0.05, 0.15, 0.1};
                std::random_device rd2;
                std::mt19937 gen2(rd2());
                std::discrete_distribution<> weighted_distribution2(prob2.begin(), prob2.end());
                int sens_index = weighted_distribution2(gen2);
                std::string sensor = sens[sens_index];
                //---------concatinate sensor+network == s1_f1
                node = sensor+"_"+network;

                int comp = 0;
                std::string choisen_node_network;
                for (const auto& entry : choisen) {
                    choisen_node_network = entry.substr(entry.size()- 2);
                    if (network == choisen_node_network) {
                        break;
                    }else {
                        comp ++;
                    }
                }
                if ( comp == choisen.size()) {
                    choisen.push_back(node);
                    keep_looking = false;
                }
            }


            std::vector<double> probabilities = {0.25, 0.2, 0.15, 0.1, 0.1, 0.07, 0.05, 0.05, 0.03};       //choix des attaques à executer

            std::random_device rd;
            std::mt19937 gen(rd());
            std::discrete_distribution<> weighted_distribution(probabilities.begin(), probabilities.end());

            int choise = weighted_distribution(gen);

            if (choise == 0) {
                malicious_nodes["notsend"].push_back(node);

            }else if (choise == 1 ) {
                malicious_nodes["sendallfake"].push_back(node);

            }else if (choise ==2) {
                malicious_nodes["send6"].push_back(node);

            }else if (choise == 3) {
                malicious_nodes["send8fake"].push_back(node);

            }else if (choise == 4) {
                malicious_nodes["send4fake8"].push_back(node);

            }else if (choise == 5) {
                malicious_nodes["send2"].push_back(node);

            }else if (choise == 6) {
                malicious_nodes["send4fake"].push_back(node);

            }else if (choise == 7) {
                malicious_nodes["send2fake6"].push_back(node);

            }else if (choise == 8) {
                malicious_nodes["send4fake4"].push_back(node);
            }
        }

        std::copy(malicious_nodes["notsend"].begin(), malicious_nodes["notsend"].end(), not_Send[i].begin());
        std::copy(malicious_nodes["send6"].begin(), malicious_nodes["send6"].end(), Send_6[i].begin());
        std::copy(malicious_nodes["send2"].begin(), malicious_nodes["send2"].end(), Send_2[i].begin());
        std::copy(malicious_nodes["sendallfake"].begin(), malicious_nodes["sendallfake"].end(), Send_All_Fake[i].begin());
        std::copy(malicious_nodes["send8fake"].begin(), malicious_nodes["send8fake"].end(), Send_8_Fake[i].begin());
        std::copy(malicious_nodes["send4fake"].begin(), malicious_nodes["send4fake"].end(), Send_4_Fake[i].begin());
        std::copy(malicious_nodes["send4fake8"].begin(), malicious_nodes["send4fake8"].end(), Send_4_Fake_Out_8[i].begin());
        std::copy(malicious_nodes["send4fake4"].begin(), malicious_nodes["send4fake4"].end(), Send_4_Fake_Out_4[i].begin());
        std::copy(malicious_nodes["send2fake6"].begin(), malicious_nodes["send2fake6"].end(), Send_2_Fake_Out_6[i].begin());

        malicious_nodes.clear();
        choisen.clear();
    }
    std::string name = getName();
    EV << name <<" --- script is initialized for all \n\n\n";
}





void sensor::sensor_beh() {
    periode_trust++;
    std::string name = getName();
    mauv_periode = 0;

    auto find_not_send = std::find(not_Send[periode_trust].begin(), not_Send[periode_trust].end(), name);
    auto find_Send_6 = std::find(Send_6[periode_trust].begin(), Send_6[periode_trust].end(), name);
    auto find_Send_2 = std::find(Send_2[periode_trust].begin(), Send_2[periode_trust].end(), name);
    auto find_Send_All_Fake = std::find(Send_All_Fake[periode_trust].begin(), Send_All_Fake[periode_trust].end(), name);
    auto find_Send_8_Fake = std::find(Send_8_Fake[periode_trust].begin(), Send_8_Fake[periode_trust].end(), name);
    auto find_Send_4_Fake = std::find(Send_4_Fake[periode_trust].begin(), Send_4_Fake[periode_trust].end(), name);
    auto find_Send_4_Fake_Out_8 = std::find(Send_4_Fake_Out_8[periode_trust].begin(), Send_4_Fake_Out_8[periode_trust].end(), name);
    auto find_Send_4_Fake_Out_4 = std::find(Send_4_Fake_Out_4[periode_trust].begin(), Send_4_Fake_Out_4[periode_trust].end(), name);
    auto find_Send_2_Fake_Out_6 = std::find(Send_2_Fake_Out_6[periode_trust].begin(), Send_2_Fake_Out_6[periode_trust].end(), name);


    if (find_not_send != not_Send[periode_trust].end()) {
        EV << name <<": not_send \n";
        not_send = new cMessage("not_send");
        scheduleAt(simTime(), not_send);

    }else if (find_Send_6 != Send_6[periode_trust].end()) {
        EV << name <<": send6 \n";
        send_6 = new cMessage("send_6");
        scheduleAt(simTime(), send_6);

    }else if (find_Send_2 != Send_2[periode_trust].end()){
        EV << name <<": send2 \n";
        send_2 = new cMessage("send_2");
        scheduleAt(simTime(), send_2);

    }else if (find_Send_All_Fake != Send_All_Fake[periode_trust].end()) {
        EV << name <<": sendallfake \n";
        send_all_fake= new cMessage("send_all_fake");
        scheduleAt(simTime(), send_all_fake);

    }else if (find_Send_8_Fake != Send_8_Fake[periode_trust].end()) {
        EV << name <<": send8fake \n";
        send_8_fake = new cMessage("send_8_fake");
        scheduleAt(simTime(), send_8_fake);

    }else if (find_Send_4_Fake != Send_4_Fake[periode_trust].end()) {
        EV << name <<": send4fake \n";
        send_4_fake = new cMessage("Send_4_Fake");
        scheduleAt(simTime(), send_4_fake);

    }else if (find_Send_4_Fake_Out_8 != Send_4_Fake_Out_8[periode_trust].end()) {
        EV << name <<": send4fake8 \n";
        send_4_fake_out_8 = new cMessage("send_4_fake_out_8");
        scheduleAt(simTime(), send_4_fake_out_8);

    }else if (find_Send_4_Fake_Out_4 != Send_4_Fake_Out_4[periode_trust].end()) {
        EV << name <<": send4fake4 \n";
        send_4_fake_out_4 = new cMessage("send_4_fake_out_4");
        scheduleAt(simTime(), send_4_fake_out_4);

    }else if (find_Send_2_Fake_Out_6 != Send_2_Fake_Out_6[periode_trust].end()) {
        EV << name <<": send2fake6 \n";
        send_2_fake_out_6 = new cMessage("send_2_fake_out_6");
        scheduleAt(simTime(), send_2_fake_out_6);

    }else{
        EV << name <<"\n";
        envoyer = new cMessage("envoyer");
        scheduleAt(simTime(), envoyer);
    }

    behaviour = new cMessage("behaviour");
    scheduleAt(simTime() + trust_periode, behaviour);            //comportement des sensors pour chaque periode de calcul de confiance
}



void sensor::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        if (msg == se_charger) {
             charge();
        }else if (msg == behaviour) {
            sensor_beh();

        }else if (msg == not_send) {
            notSend();
        }else if (msg == send_6) {
            Send6();
        } else if (msg == send_2) {
            Send2();
        }else if (msg == send_all_fake) {
            SendAllFake();
        }else if (msg == send_8_fake) {
            Send8Fake();
        }else if (msg == send_4_fake) {
            Send4Fake();
        }else if (msg == send_4_fake_out_8) {
            Send4FakeOut8();
        }else if (msg == send_4_fake_out_4) {
            Send4FakeOut4();
        }else if (msg == send_2_fake_out_6) {
            Send2FakeOut6();
        }else if (msg == envoyer) {
            SendValues();
        }
    }
}




void sensor::SendValues() {
    std::string id = getName();
    simtime_t time = simTime();

    values *msg = new values("sensor");
    msg->setLabel(1);
    msg->setId(id.c_str());
    msg->setBatterie(batterie);
    msg->setTime(time);
    msg->setByteLength(1024 / 8);

    send(msg, "pas$o", 0);
    if (simTime() < (periode_trust * trust_periode) - freq_per_trust_periode) {
         envoyer = new cMessage("envoyer");
         scheduleAt(simTime() + freq_per_trust_periode, envoyer);
    }
}



void sensor::notSend() {
    mauv_periode++;
    if ( mauv_periode <= nb_send_per_trust_periode) {
        if (simTime() < (periode_trust * trust_periode) - freq_per_trust_periode) {
            not_send = new cMessage("not_send");
            scheduleAt(simTime() + freq_per_trust_periode, not_send);
        }
    }else{
        envoyer = new cMessage("envoyer");
        scheduleAt(simTime() + 0, envoyer);
    }
}



void sensor::Send6() {
    mauv_periode++;
    if (mauv_periode <= (nb_send_per_trust_periode - 6) ) {
        if ((simTime() < (periode_trust * trust_periode) - freq_per_trust_periode)) {
            send_6 = new cMessage("send_6");
            scheduleAt(simTime() + freq_per_trust_periode, send_6);
        }
    }else {
        envoyer = new cMessage("envoyer");
        scheduleAt(simTime() + 0, envoyer);
    }
}



void sensor::Send2() {
    mauv_periode++;
    if (mauv_periode <= (nb_send_per_trust_periode - 2)) {
        if ((simTime() < (periode_trust * trust_periode) - freq_per_trust_periode)) {
            send_2 = new cMessage("send_2");
            scheduleAt(simTime() + freq_per_trust_periode, send_2);
        }
    }else {
        envoyer = new cMessage("envoyer");
        scheduleAt(simTime() + 0, envoyer);
    }
}



void sensor::SendAllFake() {
    std::string id = getName();
    simtime_t time = simTime();
    mauv_periode++;
    if (mauv_periode <= nb_send_per_trust_periode) {
        values *msg = new values("sensor");
        msg->setLabel(0);
        msg->setId(id.c_str());
        int falsevalue;
        if (batterie <= 50) {
            falsevalue = intuniform(85,100);;
        }else {
            falsevalue = intuniform(0,15);
        }
        msg->setBatterie(falsevalue);
        msg->setTime(time);
        msg->setByteLength(1024 / 8);

        send(msg, "pas$o", 0);

        if ((simTime() < (periode_trust * trust_periode) - freq_per_trust_periode)) {
            send_all_fake = new cMessage("send_all_fake");
            scheduleAt(simTime() + freq_per_trust_periode, send_all_fake);
        }
    }else {
        envoyer = new cMessage("envoyer");
        scheduleAt(simTime() + 0, envoyer);
    }
}



void sensor::Send8Fake() {
    std::string id = getName();
    simtime_t time = simTime();

    mauv_periode++;
    if (mauv_periode <= 8) {
        values *msg = new values("sensor");
        msg->setLabel(0);
        msg->setId(id.c_str());
        int falsevalue;
        if (batterie <= 50) {
            falsevalue = intuniform(80,100);;
        }else {
            falsevalue = intuniform(0,20);
        }
        msg->setBatterie(falsevalue);
        msg->setTime(time);
        msg->setByteLength(1024 / 8);

        send(msg, "pas$o", 0);

        if ((simTime() < (periode_trust * trust_periode) - freq_per_trust_periode)) {
            send_8_fake = new cMessage("Send_8_Fake");
            scheduleAt(simTime() + freq_per_trust_periode, send_8_fake);
        }
    }else {
        envoyer = new cMessage("envoyer");
        scheduleAt(simTime() + 0, envoyer);
    }
}



void sensor::Send4Fake() {
    std::string id = getName();
    simtime_t time = simTime();

    mauv_periode++;
    if (mauv_periode <= 4) {
        values *msg = new values("sensor");
        msg->setLabel(0);
        msg->setId(id.c_str());
        int falsevalue;
        if (batterie <= 50) {
            falsevalue = intuniform(80,100);;
        }else {
            falsevalue = intuniform(0,20);
        }
        msg->setBatterie(falsevalue);
        msg->setTime(time);
        msg->setByteLength(1024 / 8);

        send(msg, "pas$o", 0);

        if ((simTime() < (periode_trust * trust_periode) - freq_per_trust_periode)) {
            send_4_fake = new cMessage("Send_4_Fake");
            scheduleAt(simTime() + freq_per_trust_periode, send_4_fake);
        }
    }else {
        envoyer = new cMessage("envoyer");
        scheduleAt(simTime() + 0, envoyer);
    }
}



void sensor::Send4FakeOut8() {
    std::string id = getName();
    simtime_t time = simTime();
    mauv_periode++;
    if (mauv_periode <=  (2 + 4) ) {
        if (mauv_periode <= 2) {
            //ne rien faire (pas envoyer)
        }else {
            //send random values
            values *msg = new values("sensor");
            msg->setLabel(0);
            msg->setId(id.c_str());
            int falsevalue;
            if (batterie <= 50) {
                falsevalue = intuniform(80,100);;
            }else {
                falsevalue = intuniform(0,20);
            }
            msg->setBatterie(falsevalue);
            msg->setTime(time);
            msg->setByteLength(1024 / 8);              // 1024 bits = 128 octets envoyée

            send(msg, "pas$o", 0);
        }
        if ((simTime() < (periode_trust * trust_periode) - freq_per_trust_periode)) {
            send_4_fake_out_8 = new cMessage("send_4_fake_out_8");
            scheduleAt(simTime() + freq_per_trust_periode, send_4_fake_out_8);
        }
    }else {
        envoyer = new cMessage("envoyer");
        scheduleAt(simTime() + 0, envoyer);
    }
}



void sensor::Send4FakeOut4() {
    std::string id = getName();
    simtime_t time = simTime();
    mauv_periode++;
    if (mauv_periode <= (4 + 6) ){
        if (mauv_periode <= 6) {
            //ne rien faire (pas envoyer)
        }else {
            //send random values
            values *msg = new values("sensor");
            msg->setLabel(0);
            msg->setId(id.c_str());
            int falsevalue;
            if (batterie <= 50) {
                falsevalue = intuniform(80,100);
            }else {
                falsevalue = intuniform(0,20);
            }
            msg->setBatterie(falsevalue);
            msg->setTime(time);
            msg->setByteLength(1024 / 8);              // 1024 bits = 128 octets envoyée

            send(msg, "pas$o", 0);
        }
        if ((simTime() < (periode_trust * trust_periode) - freq_per_trust_periode)) {
            send_4_fake_out_4 = new cMessage("send_4_fake_out_4");
            scheduleAt(simTime() + freq_per_trust_periode, send_4_fake_out_4);
        }

    }else {
        envoyer = new cMessage("envoyer");
        scheduleAt(simTime() + 0, envoyer);
    }
}



void sensor::Send2FakeOut6() {
    std::string id = getName();
    simtime_t time = simTime();
    mauv_periode++;
    if (mauv_periode <= (2 + 4)) {
        if (mauv_periode <= 4) {
            //ne rien faire (pas envoyer)
        }else {
            //send random values
            values *msg = new values("sensor");
            msg->setLabel(0);
            msg->setId(id.c_str());
            int falsevalue;
            if (batterie <= 50) {
                falsevalue = intuniform(80,100);;
            }else {
                falsevalue = intuniform(0,20);
            }
            msg->setBatterie(falsevalue);
            msg->setTime(time);
            msg->setByteLength(1024 / 8);              // 1024 bits = 128 octets envoyée

            send(msg, "pas$o", 0);
        }
        if ((simTime() < (periode_trust * trust_periode) - freq_per_trust_periode)) {
            send_2_fake_out_6 = new cMessage("send_2_fake_out_6");
            scheduleAt(simTime() + freq_per_trust_periode, send_2_fake_out_6);
        }

    }else {
        envoyer = new cMessage("envoyer");
        scheduleAt(simTime() + 0, envoyer);
    }
}












