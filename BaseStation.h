/*
 * BaseStation.h
 *
 *  Created on: Jun 5, 2020
 *      Author: thanh
 */

#ifndef BASESTATION_H_
#define BASESTATION_H_

#include <omnetpp.h>
#include "ArpeesDef.h"
#include "SensorNode.h"
#include "NodeModul.h"
#include "MessageType_m.h"
using namespace omnetpp;
class BaseStation : public NodeModul
{
public:
    BaseStation(): NodeModul(){};
    void initNodes();
    virtual void initialize(void);
    virtual void handleMessage(cMessage * msg);
    //void resetStatus();
    void createEvents();
    //int selectClusterHead(int id);
    //void finish();
    int xpos;                   // just for simulation
    int ypos;
    int nrStatusRec;            // number of received status
    struct _adv advInfo[NUMBERNODES+4];
    cModule *nodePtr[NUMBERNODES+4];
    int xMax;
    int yMax;
    int numNodes;
    int roundsDone;
    int nrRounds;
    int firstDead;
    int redunNode;
    int roundTimes[NUMBERROUND];        // times when round starts
    int deadRound[NUMBERROUND];
    int nrHeads[NUMBERROUND];
    int totalDeadNodes[NUMBERROUND];
    int totalRedundance[NUMBERROUND];
    double totalEnRemain[NUMBERROUND];// stored energy remain after each round
    int calledEnd;
    int halfDead;
    int halfDeadCtr;
    int oldDeadNodes;
    int deadNodes;
    double P;
    int cHeadsRound;
    //tham so moi them vao
    int eventID;
    int nrNeighber;           //luu so hang xom
    int neighbers[MAXNEIGHBORS]; //LUU CAC ID MODULE HANG XOM
    int nrFrames;               //bien dem so luong frame mot round
    int cntData;            //so luong DATA nhan /round
};

#endif
/************************************************************************************/
 /* BASESTATION_H_ */
