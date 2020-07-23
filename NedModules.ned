
// Base Station
simple BaseStation
{
    parameters:
        @display("i=device/antennatower_l");
        int id;
        int randInit;
        int numNodes;
        int xpos;
        int ypos;
    gates:
        input in @directIn;
}
// Sensor node
simple SensorNode
{
    parameters:
        @display("i=misc/node_vs");
        int id;
        int energy;
        int xpos;
        int ypos;
    gates:
        input in @directIn;
}

// ARPEES network
network WSN
{
    parameters:
        int energy;
        int numNodes;
        int trRange;
        int protocol;
        int showHideRange;
        int ssRange;
        int kRequire;
        int rounds;
        int frames;
        int sRand;
        int xMax;
        int yMax;
        @display("p=0,0;b=$xMax,$yMax,rect;o=white");
    submodules:
        bs: BaseStation {
            parameters:
                id = 1;
                randInit = sRand;
                xpos = int (xMax/2);               
                ypos = yMax+40;
                numNodes = numNodes;
        }
        node[numNodes]: SensorNode {
            parameters:
                energy = energy;
                id = index+2;
                xpos = intuniform(10,xMax-10);
                ypos = intuniform(10,yMax-10);
        }
    connections allowunconnected:

}

