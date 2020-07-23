/*
 * NodeModul.h
 *
 *  Created on: Jun 5, 2020
 *      Author: thanh
 */

#ifndef NODEMODUL_H_
#define NODEMODUL_H_

#include <omnetpp.h>
#include "ArpeesDef.h"
using namespace omnetpp;

class NodeModul : public cSimpleModule
{
    //Module_Class_Members(NodeBase, cSimpleModule,0);
public:
    NodeModul(): cSimpleModule(){};
  protected:
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;
    virtual void finish();
    void updateStats();
    void initStats();

  public:
    int myId;
    int myStatus;
    int numberMsgs;
    int numberData;
    // how many gates
    int nrGates;
    int nrNodes;
};

#endif /* NODEMODUL_H_ */
