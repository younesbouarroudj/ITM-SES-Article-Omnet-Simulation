message values {
    	int label;
    	string id; 
    	simtime_t time;             
        int batterie;
        int byteLength;
}

message sensors_trust { 
	string node;
	double tr;
}

message request { 
	string node;
	double need;
}

message offer { 
	string node;
	double offre;
}



message sp_to_sc { 
	string sc;
	string sp;
	double need;
	double service;
}

message req_to_sp { 
    string sp;
	string sc;
	double need;
	double service;
}

message ser_to_sc { 
	string sc;
	string sp;
	double need;
	double service;
}

message fb_to_cloud { 
	string sp;
	string sc;
	double fb;
}