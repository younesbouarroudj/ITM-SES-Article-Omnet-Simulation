simple sensor
{
    gates:
        inout pas[];
}

simple sink
{
    gates:
        inout pas[];
}

simple Edge
{
    gates:
        inout pas[];
}

simple cloud
{
    gates:
        inout pas[];
}

simple client
{
    gates:
        inout pas[];
}

network res
{
    @display("bgb=3455.7188,1880.7488");
    submodules:

        //----------------------------------------------region 1
        s1_h1: sensor {
            @display("p=3220.1326,102.7325;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s2_h1: sensor {
            @display("p=3057.1775,102.7325;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s3_h1: sensor {
            @display("p=2894.2224,102.7325;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s4_h1: sensor {
            @display("p=2717.0974,102.7325;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        client_h1: client {
            @display("p=2503.4512,95.1225;i=taw3i/client");
        }
        sink_h1: sink {
            @display("p=2929.6475,382.59;i=taw3i/PA_omnet_no_bg");
        }

        s1_f1: sensor {
            @display("p=3229.8413,583.70624;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s2_f1: sensor {
            @display("p=3229.8413,778.275;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s3_f1: sensor {
            @display("p=3220.1326,1034.41;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s4_f1: sensor {
            @display("p=3220.1326,1215.0775;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        client_f1: client {
            @display("p=2948.88,695.3325;i=taw3i/client");
        }
        sink_f1: sink {
            @display("p=2929.6475,885.625;i=taw3i/antenne1_omnet_no_bg");
        }

        s1_h2: sensor {
            @display("p=3237.9038,1717.3875;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s2_h2: sensor {
            @display("p=3124.8074,1717.3875;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s3_h2: sensor {
            @display("p=2999.145,1717.3875;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s4_h2: sensor {
            @display("p=2877.6711,1717.3875;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        client_h2: client {
            @display("p=3350.9062,1547.9025;i=taw3i/client");
        }
        sink_h2: sink {
            @display("p=3021.7524,1466.595;i=taw3i/PA_omnet_no_bg");
        }

        s1_f2: sensor {
            @display("p=2674.5874,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s2_f2: sensor {
            @display("p=2550.5999,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s3_f2: sensor {
            @display("p=2447.8674,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s4_f2: sensor {
            @display("p=2341.5925,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        client_f2: client {
            @display("p=2668.2336,1415.7975;i=taw3i/client");
        }
        sink_f2: sink {
            @display("p=2504.5474,1399.2875;i=taw3i/antenne1_omnet_no_bg");
        }

        Edge_r1: Edge {
            @display("p=2504.5474,885.625;i=taw3i/cloud_server_omnet_no_bg");
        }

        //----------------------------------------------region 2
        s1_h3: sensor {
            @display("p=2146.755,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s2_h3: sensor {
            @display("p=2033.395,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s3_h3: sensor {
            @display("p=1920.0349,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s4_h3: sensor {
            @display("p=1803.1324,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        client_h3: client {
            @display("p=2224.2263,1415.7975;i=taw3i/client");
        }
        sink_h3: sink {
            @display("p=1976.715,1399.2875;i=taw3i/PA_omnet_no_bg");
        }

        s1_f3: sensor {
            @display("p=1615.38,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s2_f3: sensor {
            @display("p=1502.02,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s3_f3: sensor {
            @display("p=1395.745,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s4_f3: sensor {
            @display("p=1285.9275,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        client_f3: client {
            @display("p=1641.99,1415.7975;i=taw3i/client");
        }
        sink_f3: sink {
            @display("p=1448.8824,1399.2875;i=taw3i/antenne1_omnet_no_bg");
        }

        s1_h4: sensor {
            @display("p=1105.26,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s2_h4: sensor {
            @display("p=991.89996,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s3_h4: sensor {
            @display("p=882.08246,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s4_h4: sensor {
            @display("p=765.18,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        client_h4: client {
            @display("p=1139.34,1415.7975;i=taw3i/client");
        }
        sink_h4: sink {
            @display("p=910.4225,1399.2875;i=taw3i/PA_omnet_no_bg");
        }


        Edge_r2: Edge {
            @display("p=1448.8824,988.3575;i=taw3i/cloud_server_omnet_no_bg");
        }

        //----------------------------------------------region 3
        s1_f4: sensor {
            @display("p=513.6625,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s2_f4: sensor {
            @display("p=403.845,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s3_f4: sensor {
            @display("p=311.74,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s4_f4: sensor {
            @display("p=184.20999,1718.1124;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        client_f4: client {
            @display("p=544.5375,1415.7975;i=taw3i/client");
        }
        sink_f4: sink {
            @display("p=347.165,1417;i=taw3i/antenne1_omnet_no_bg");
        }

        s1_h5: sensor {
            @display("p=74.3925,1494.9349;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s2_h5: sensor {
            @display("p=74.3925,1307.1825;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s3_h5: sensor {
            @display("p=74.3925,1126.515;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s4_h5: sensor {
            @display("p=74.3925,935.22;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        client_h5: client {
            @display("p=311.74,843.115;i=taw3i/client");
        }
        sink_h5: sink {
            @display("p=309.9375,1091.6687;i=taw3i/PA_omnet_no_bg");
        }


        Edge_r3: Edge {
            @display("p=843.115,988.3575;i=taw3i/cloud_server_omnet_no_bg");
        }

        //----------------------------------------------region 4
        s1_f5: sensor {
            @display("p=74.3925,673.075;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s2_f5: sensor {
            @display("p=74.3925,481.78;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s3_f5: sensor {
            @display("p=74.3925,294.0275;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        s4_f5: sensor {
            @display("p=74.3925,102.7325;i=taw3i/Batterie-solaire__1_-removebg-preview");
        }
        client_f5: client {
            @display("p=311.31,95.1225;i=taw3i/client");
        }
        sink_f5: sink {
            @display("p=481.78,382.59;i=taw3i/antenne1_omnet_no_bg");
        }

        Edge_r4: Edge {
            @display("p=956.475,382.59;i=taw3i/cloud_server_omnet_no_bg");
        }


        cloud: cloud {
            @display("p=1452.4249,386.1325;i=taw3i/internet_omnet_no_bg");
        }







    connections:
        s1_h1.pas++ <--> {  delay = 1ms;@display("ls=,,d"); } <--> sink_h1.pas++;
        s2_h1.pas++ <--> {  delay = 1ms;@display("ls=,,d"); } <--> sink_h1.pas++;
        s3_h1.pas++ <--> {  delay = 1ms;@display("ls=,,d"); } <--> sink_h1.pas++;
        s4_h1.pas++ <--> {  delay = 1ms;@display("ls=black,,d"); } <--> sink_h1.pas++;
        client_h1.pas++ <--> {  delay = 1ms; } <--> sink_h1.pas++;


        s1_f1.pas++ <--> {  delay = 1ms; } <--> sink_f1.pas++;
        s2_f1.pas++ <--> {  delay = 1ms; } <--> sink_f1.pas++;
        s3_f1.pas++ <--> {  delay = 1ms; } <--> sink_f1.pas++;
        s4_f1.pas++ <--> {  delay = 1ms; } <--> sink_f1.pas++;
        client_f1.pas++ <--> {  delay = 1ms; } <--> sink_f1.pas++;


        s1_h2.pas++ <--> {  delay = 1ms; } <--> sink_h2.pas++;
        s2_h2.pas++ <--> {  delay = 1ms; } <--> sink_h2.pas++;
        s3_h2.pas++ <--> {  delay = 1ms; } <--> sink_h2.pas++;
        s4_h2.pas++ <--> {  delay = 1ms; } <--> sink_h2.pas++;
        client_h2.pas++ <--> {  delay = 1ms; } <--> sink_h2.pas++;

        s1_f2.pas++ <--> {  delay = 1ms; } <--> sink_f2.pas++;
        s2_f2.pas++ <--> {  delay = 1ms; } <--> sink_f2.pas++;
        s3_f2.pas++ <--> {  delay = 1ms; } <--> sink_f2.pas++;
        s4_f2.pas++ <--> {  delay = 1ms; } <--> sink_f2.pas++;
        client_f2.pas++ <--> {  delay = 1ms; } <--> sink_f2.pas++;


        s1_h3.pas++ <--> {  delay = 1ms; } <--> sink_h3.pas++;
        s2_h3.pas++ <--> {  delay = 1ms; } <--> sink_h3.pas++;
        s3_h3.pas++ <--> {  delay = 1ms; } <--> sink_h3.pas++;
        s4_h3.pas++ <--> {  delay = 1ms; } <--> sink_h3.pas++;
        client_h3.pas++ <--> {  delay = 1ms; } <--> sink_h3.pas++;


        s1_f3.pas++ <--> {  delay = 1ms; } <--> sink_f3.pas++;
        s2_f3.pas++ <--> {  delay = 1ms; } <--> sink_f3.pas++;
        s3_f3.pas++ <--> {  delay = 1ms; } <--> sink_f3.pas++;
        s4_f3.pas++ <--> {  delay = 1ms; } <--> sink_f3.pas++;
        client_f3.pas++ <--> {  delay = 1ms; } <--> sink_f3.pas++;


        s1_h4.pas++ <--> {  delay = 1ms; } <--> sink_h4.pas++;
        s2_h4.pas++ <--> {  delay = 1ms; } <--> sink_h4.pas++;
        s3_h4.pas++ <--> {  delay = 1ms; } <--> sink_h4.pas++;
        s4_h4.pas++ <--> {  delay = 1ms; } <--> sink_h4.pas++;
        client_h4.pas++ <--> {  delay = 1ms; } <--> sink_h4.pas++;

        s1_f4.pas++ <--> {  delay = 1ms; } <--> sink_f4.pas++;
        s2_f4.pas++ <--> {  delay = 1ms; } <--> sink_f4.pas++;
        s3_f4.pas++ <--> {  delay = 1ms; } <--> sink_f4.pas++;
        s4_f4.pas++ <--> {  delay = 1ms; } <--> sink_f4.pas++;
        client_f4.pas++ <--> {  delay = 1ms; } <--> sink_f4.pas++;


        s1_h5.pas++ <--> {  delay = 1ms; } <--> sink_h5.pas++;
        s2_h5.pas++ <--> {  delay = 1ms; } <--> sink_h5.pas++;
        s3_h5.pas++ <--> {  delay = 1ms; } <--> sink_h5.pas++;
        s4_h5.pas++ <--> {  delay = 1ms; } <--> sink_h5.pas++;
        client_h5.pas++ <--> {  delay = 1ms; } <--> sink_h5.pas++;

        s1_f5.pas++ <--> {  delay = 1ms; } <--> sink_f5.pas++;
        s2_f5.pas++ <--> {  delay = 1ms; } <--> sink_f5.pas++;
        s3_f5.pas++ <--> {  delay = 1ms; } <--> sink_f5.pas++;
        s4_f5.pas++ <--> {  delay = 1ms; } <--> sink_f5.pas++;
        client_f5.pas++ <--> {  delay = 1ms; } <--> sink_f5.pas++;



        sink_h1.pas++ <--> {  delay = 1ms; } <--> Edge_r1.pas++;
        sink_f1.pas++ <--> {  delay = 1ms; } <--> Edge_r1.pas++;
        sink_h2.pas++ <--> {  delay = 1ms; } <--> Edge_r1.pas++;
        sink_f2.pas++ <--> {  delay = 1ms; } <--> Edge_r1.pas++;

        sink_h3.pas++ <--> {  delay = 1ms; } <--> Edge_r2.pas++;
        sink_f3.pas++ <--> {  delay = 1ms; } <--> Edge_r2.pas++;
        sink_h4.pas++ <--> {  delay = 1ms; } <--> Edge_r2.pas++;

        sink_f4.pas++ <--> {  delay = 1ms; } <--> Edge_r3.pas++;
        sink_h5.pas++ <--> {  delay = 1ms; } <--> Edge_r3.pas++;

        sink_f5.pas++ <--> {  delay = 1ms; } <--> Edge_r4.pas++;


        Edge_r1.pas++ <--> {  delay = 1ms; } <--> cloud.pas++;
        Edge_r2.pas++ <--> {  delay = 1ms; } <--> cloud.pas++;
        Edge_r3.pas++ <--> {  delay = 1ms; } <--> cloud.pas++;
        Edge_r4.pas++ <--> {  delay = 1ms; } <--> cloud.pas++;
}
