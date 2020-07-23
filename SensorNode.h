/*
 * SensorNode.h
 *
 *  Created on: Jun 5, 2020
 *      Author: thanh
 */

#ifndef SENSORNODE_H_
#define SENSORNODE_H_

#include <omnetpp.h>
#include <string.h>
#include "ArpeesDef.h"
#include "NodeModul.h"
#include "BaseStation.h"
#include "MessageType_m.h"
class SensorNode : public NodeModul
{
public:
    SensorNode(): NodeModul(){};
    void startEvent();
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage * msg);
    //virtual void finish();
    void initNodes();
    void broadcastReqCL();
    void sendTDMA();
    void sendDataToCHead(int clusterHead);
    void sendData2RNBS();
    void energyReceive(int bits);
    void energyTransmit(int bits, int dist);
    void energyDataAggr(int signals);
    void findNextHop();
    void resetRound();
    void resetHop(SensorNode *hop);
  public:
    int distanceCal(int x1, int y1, int x2, int y2);
    int xpos;                   // just for simulation
    int ypos;
    int nrRounds;               // number of rounds (each round starts with setups)
    int nrFrames;               // number of "rounds in a round" (called frames)
    int curFrame;
    int frameTime;              // how many slots has one frame
    int trRange;
    int ssRange;
    int protocol;
    int myData;
    int mySlot;                 // slot in current frame
    int bsId;                   // ID of base station
    int eventID;               //ID CUA NODE XAY RA SU KIEN
    int nrNeighber;           //luu so hang xom
    int neighbers[MAXNEIGHBORS]; //LUU CAC id MODULE HANG XOM
    int energy;              // energy in microJoule
    int bsDist;                 // distance from node to BS
    int evDist;                 //khoang cach den su kien
    int myAction;               // sleep/active/listen status
    double FCH ;
    SensorNode *nodePtr[NUMBERNODES+3];
    int cHead;                  // flag denoting if I this node is cluster head
    int headId;                 // id of cluster head (my cluster)
    int nrDataPackets;          // nr of data packets head has received in this frame
    int nrMemEvent;            // so luong node tham gia vao su kien
    SensorNode *myRN;         //con tro luu Relay node cua node
    SensorNode *prRN;         //con tro luu HOP dung truoc cua hop
    double FRN;               //Tinh FRN de tim relay node
    int cntACK;               //bien dem so luong ACK_RELAY CH(RN) nhan duoc
    SensorNode *candidate[MAXNEIGHBORS];
};



#endif /* SENSORNODE_H_ */
