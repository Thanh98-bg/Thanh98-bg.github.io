/*
 * BaseStation.cc
 *
 *  Created on: Jun 5, 2020
 *      Author: thanh
 */
#include <stdio.h>
#include <string.h>

#include <omnetpp.h>
#include "SensorNode.h"
#include "NodeModul.h"
#include "BaseStation.h"

using namespace omnetpp;
Define_Module(BaseStation);

void BaseStation::initialize(){
        int i;
        cModule *parent = getParentModule();
        this->myId = getId();
        this->nrGates = (int) parent->par("numNodes");
        this->xpos = (int) par("xpos");
        this->ypos = (int) par("ypos");
        this->nrNodes = (int) parent->par("numNodes");
        this->xMax = (int) parent->par("xMax");
        this->yMax = (int) parent->par("yMax");
        this->numNodes = (int) parent->par("numNodes");
        this->roundsDone = 0;
        this->nrRounds = (int) parent->par("rounds");
        this->firstDead = 0;
        this->calledEnd = 0;               //controling the type of ended simulation
        this->halfDead = 0;                //number of node die
        this->halfDeadCtr = 0;             //control number of node die
        this->deadNodes = 0;               //
        this->oldDeadNodes = 0;
        this->P = 0.05;
        this->cHeadsRound = 0;
        this->nrNeighber = 0;
        this->nrFrames = (int) parent->par("frames");
        this->cntData = 0;
        // Display base station
        this->setDisplayString("p=$xpos,$ypos;i=device/antennatower_l;o=blue");
        for (i = 0; i < NUMBERNODES+3; i++)
        {
            advInfo[i].id = 0;
            advInfo[i].energy = 0;
            advInfo[i].status = 0;
        }

        for (i = 0; i < NUMBERROUND; i++)
        {
            this->roundTimes[i] = 0;
            this->deadRound[i] = 0;
            this->nrHeads[i]= 0;
            this->totalEnRemain[i] = 0;
            this->totalDeadNodes[i] = 0;
        }

        EV << "BS info (ID = " << this->getId() << ", Number of Gates: "
           << this->nrGates <<", Xpos " << this->xpos << ", Ypos " << this->ypos << "\n";
        {
            cMessage *cmsg = new cMessage();
            cmsg->setKind(SMSG_INIT);
            scheduleAt(simTime(), cmsg);
            cMessage *emsg = new cMessage();
            emsg->setKind(SMSG_CRE_EVENT);
            scheduleAt(simTime()+ INIT_WAIT*2, emsg);
        }
}
void BaseStation::handleMessage(cMessage * msg){
    take(msg);
    if(msg->isSelfMessage()){
        if(msg->getKind()==SMSG_INIT){
            this->initNodes();
        }
        if(msg->getKind()==SMSG_CRE_EVENT){
            this->createEvents();
        }
    }else{
        if(((ClusterMessage *) msg)->getProto()==CL_DATA2BS){
            this->cntData++;
            EV<<"BS DA NHAN DATA TU CH, cntData: "<<this->cntData<<"\n";
            if(this->cntData == this->nrFrames){
            //Thuc hien tinh tong nang luong con lai cua mang sau moi round
                int en=0;
                for (int i = 3; i <= getSimulation()->getLastComponentId(); i++){
                    //scan the simulation module vector
                    cModule *mod = (cModule *) getSimulation()->getModule(i);
                    en = en + ((SensorNode *)mod)->energy;
                }
                totalEnRemain[this->roundsDone]=en;
                EV<<"Tong nang luong con lai sau "<<this->roundsDone+1<<" rounds la: "<<en<<"\n";
                this->roundsDone++;
            //Lap lich cho su kien tiep theo
                cMessage *emsg = new cMessage();
                emsg->setKind(SMSG_CRE_EVENT);
                scheduleAt(simTime()+ INIT_WAIT*2, emsg);
                this->cntData = 0;
            }
        }
    }
}
void BaseStation::initNodes(){
    int i;
        cModule *parent = getParentModule();
        cModule *mod;
        int numNodes;
        int trRange;
        numNodes = (int) parent->par("numNodes");
        EV << "BS numNodes is: " << numNodes << "\n";
        trRange = (int) parent->par("trRange");
        EV << "BS trRange is: " << trRange << "\n";
        for (i = 1; i <= getSimulation()->getLastComponentId(); i++)
        {
            int x, y, id;
            //scan the simulation module vector
            mod = (cModule *) getSimulation()->getModule(i);
            if (strcmp(mod->getName(), "node") == 0)
            {
                id = ((SensorNode *) mod)->myId;
                x =  ((SensorNode *) mod)->xpos;
                y =  ((SensorNode *) mod)->ypos;
                nodePtr[id] = ((SensorNode *) mod);
                int dist =(int) std::sqrt((x-this->xpos) * (x-this->xpos) + (y-this->ypos) * (y-this->ypos));
                EV<<"DISTANCE = "<<dist<<"\n";
                if(dist <= trRange){
              //khoi tao cac node hang xom
                    EV <<"BS: " << this->myId <<"(" << this->xpos << "," << this->ypos
                       << ") tim duoc node: " << (id - 3) << " at(" << x << "," << y << ")\n";
                    this->neighbers[this->nrNeighber] = ((SensorNode *) mod)->myId;
                    this->nrNeighber++;
                }
            }
        }
}
void BaseStation::createEvents(){
    //Ham se tao su kien bang cach chan ngau nhien 1 nut lam noi xay ra su kien
    //Enter_Method("createEvents");
    //this->roundsDone++;
    if(this->roundsDone==this->nrRounds){
        endSimulation();
    }
    cModule *mod;
        int random_id =  3 + rand() % (this->nrNodes + 1 - 3);
        this->eventID = random_id;
        mod = (cModule *) getSimulation()->getModule(eventID);
        cDisplayString& dispStr = mod->getDisplayString();
        dispStr.parse("i=misc/node_vs,#ff0000");
        ((SensorNode *) mod)->startEvent();
}
