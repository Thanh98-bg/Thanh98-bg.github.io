/*
 * NodeModul.cc
 *
 *  Created on: Jun 5, 2020
 *      Author: thanh
 */
#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include <NodeModul.h>

using namespace omnetpp;

void NodeModul::updateStats(){
    this->numberMsgs++;
}
void NodeModul::initStats(){
    this->numberMsgs = 0;
    this->numberData = 0;
}
void NodeModul::finish()
{
//#if 0
    EV << "NodeModul:finish() was called \n";
    EV << "finished node id: ";
    EV << this->myId;
    EV << " numberMsgs: ";
    EV << this->numberMsgs;
    EV << "    numberData ";
    EV << this->numberData;
    EV << "\n";
//#endif

//#if 0
    recordScalar("numberMsgs", this->numberMsgs);
    recordScalar("numberData", this->numberData);
//#endif
}


