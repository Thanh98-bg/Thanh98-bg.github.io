/*
 * SensorNode.cc
 *
 *  Created on: Jun 5, 2020
 *      Author: thanh
 */

#include <stdio.h>
#include <string.h>

#include <omnetpp.h>
#include "SensorNode.h"
#include "BaseStation.h"

using namespace std;
Define_Module(SensorNode);
void SensorNode::initialize(){
    cModule *parent = getParentModule();
    this->initStats();
    this->myId = getId();
    this->xpos = par("xpos");
    this->ypos = par("ypos");
    this->energy = (int) par("energy");
    this->nrNodes = (int) parent->par("numNodes");
    this->nrFrames = (int) parent->par("frames");
    this->nrRounds = (int) parent->par("rounds");
    this->trRange = (int) parent->par("trRange");
    this->ssRange = (int) parent->par("ssRange");
    this->protocol = (int) parent->par("protocol");
    this->myAction = OFF;
    this->evDist = 0;
    this->myRN = nullptr;
    this->prRN = nullptr;
    this->eventID=0;
    this->cHead = 2; //2 la trang thai chua xac dinh
    this->nrDataPackets = 0;
    this->FRN = 0.0;      //phuc vu cho viec tim RN sau nay
    this->cntACK = 0;
    this->myData = 0;
    this->curFrame = 0;
    this->nrNeighber = 0;
    this->nrMemEvent = 0;
    // set network default
    this->myStatus = STATUS_LIVE;
    this->setDisplayString("p=$xpos,$ypos;i=misc/node_vs"); // grey color is default
    EV <<"getid "<<this->getId()<<" myid "<<this->myId <<" energy: "<<energy<<" status: "<<this->myStatus<<"\n";
    {
        cMessage *cmsg = new cMessage();
        cmsg->setKind(SMSG_INIT);                      //17, init updates
        scheduleAt(simTime() + INIT_WAIT, cmsg);
    }
}
/**************************************************************************************/
void SensorNode::handleMessage(cMessage* msg){
    take(msg);
    if(msg->isSelfMessage()){ // Neu tin nhan thuoc loai selt message
         if(msg->getKind()==SMSG_INIT){
             this->initNodes();
         }
         if(msg->getKind()==SMSG_MAKETDMA){
             this->curFrame = 0;
             this->sendTDMA();
         }
         if(msg->getKind()==SMSG_DATA_NODE2CH){
             if(this->myAction==ON){
                 int clusterHead = 0;
                 // node has been woken up to transmit data to clusterhead
                  EV << this->myId -3 << " gui data den dau cum\n";
                  this->sendDataToCHead(clusterHead);
                 this->curFrame++;
                 if (this->curFrame < this->nrFrames)
                 {
                     // sleep until slot time, then wake up and send data
                     cMessage *cmsg = new cMessage();
                     cmsg->setKind(SMSG_DATA_NODE2CH);
                     scheduleAt(simTime() + this->frameTime, cmsg);
                 }
             }
         }

         if(msg->getKind()==SMSG_DATA2RNBS){
             int dist;
             //kiem tra xem BS co trong pham vi truyen du lieu
             if(this->bsDist < this->trRange){
                 EV<<"BS nam trong pham vi truyen du lieu\n";
                 if(this->prRN == nullptr){
                    this->sendData2RNBS();
                 }
              //Kiem tra xem da ket thuc round hay chua
                 if(this->curFrame == this->nrFrames){
                  EV<<"curFrame: "<<this->curFrame<<",ket thuc round\n";
                  cMessage *cmsg = new cMessage();
                  cmsg->setKind(SMSG_STATUS2BS);
                  EV << "node gui status den bs: " << this->myId -3<< endl;
                  scheduleAt(simTime()+INIT_WAIT, cmsg);
                  this->curFrame=0;
                 }
             }else{
                 EV<<"CURFRAME: "<<this->curFrame<<"\n";
                 if(this->curFrame == 1){
                     EV<<"Broadcast REQ_RELAY\n";
                 //Broadcast REQ_RELAY de tim relay node
                     ClusterMessage * rmsg = new ClusterMessage();
                     rmsg->setProto(REQ_RELAY);
                     rmsg->setSrcAddress(this->myId);
                     for(int i=0; i<this->nrNeighber;i++){
                         if(this->neighbers[i]!=this->eventID){
                             cModule *mod = getSimulation()->getModule(this->neighbers[i]);
                             if(((SensorNode *)mod)->energy>10){
                                 sendDirect(rmsg->dup(),mod,"in");
                                 dist = distanceCal(this->xpos,this->ypos,((SensorNode *)mod)->xpos,((SensorNode *)mod)->ypos);
                                 energyTransmit(SIGNAL,dist*dist);
                             }
                         }
                     }
                 }
                 if(this->curFrame > 1){
                    this->sendData2RNBS();
                 }
                 if(this->curFrame == this->nrFrames){
                     EV<<"curFrame: "<<this->curFrame<<",ket thuc round\n";
                     cMessage *cmsg = new cMessage();
                     cmsg->setKind(SMSG_STATUS2BS);
                     EV << "node gui status den bs: " << this->myId -3<< endl;
                     scheduleAt(simTime()+INIT_WAIT, cmsg);
                     this->curFrame=0;
                 }
             }
         }
         //CH (RN) tim RN TIEP theo
         if(msg->getKind()== SMSG_FIND_RN){
               int maxFRN = 0;
               int bestId = 0;
               int i;
               EV<<"CH tim RN, cntACK= "<<this->cntACK<<"\n";
               for(i=0;i<this->cntACK;i++){
                   if(this->candidate[i]->FRN > maxFRN){
                       maxFRN = this->candidate[i]->FRN;
                       bestId = i;
                   }
               }
               this->cntACK = 0;
               this->myRN = candidate[bestId];
               candidate[bestId]->prRN =(SensorNode *) getSimulation()->getModule(this->myId);
               cDisplayString& dispStr = this->myRN->getDisplayString();
               dispStr.parse("i=misc/node_vs,blue");
               EV<<"node "<<this->myRN->myId - 3<<" la RN\n";
               this->myRN ->findNextHop();
         }

         //CH bat dau gui DATA den BS
         if(msg->getKind()==SMSG_DATA2BS){
             this->sendData2RNBS();

         }

         //CH bat dau reset lai round, chuan bi cho round ke tiep
         if(msg->getKind()==SMSG_STATUS2BS){
             EV<<"CH RESET ROUND"<<"\n";
             this->resetRound();
         }
    }else{ //Tin nhan KHONG PHAI selt-message
        //Cac node nhan ban tin REQ_CL tu cac node khac de xac dinh dau cum
        if(((ClusterMessage *) msg)->getProto()==REQ_CLUSTER){
             int headId;
             this->energyReceive(SIGNAL);
             ReqClusterMessage *rmsg = (ReqClusterMessage *) msg;
             this->nrMemEvent--;
             double FCHmsg = rmsg->getFCH();
             EV<<"so luong node tham gia su kien: "<<rmsg->getNrMemEvent()<<"\n";
             EV<<"Node "<<this->myId - 3<<" da nhan REQ_CLUSTER tu node "<<rmsg->getSrcAddress() -3<<"\n";
             if(FCHmsg > this->FCH){
                 this->cHead = OFF;//node khong phai dau cum
             }
             if(FCHmsg == this->FCH){
                 int id_src = rmsg->getSrcAddress();
                 cModule *tmp_src = getSimulation()->getModule(id_src);
                 SensorNode *src = (SensorNode *) tmp_src;
                 int en_src = src->energy;
                 if(en_src > this->energy) this->cHead = OFF;
                 if(en_src == this->energy){
                     if(id_src > this->myId) this->cHead = OFF;
                 }
             }
             //neu node da nhan du tin nhan REQ-CL
             if(this->nrMemEvent==1){
                 if(this->cHead != OFF){
                     this->cHead = ON;
                     this->nrMemEvent = rmsg->getNrMemEvent();
                     EV<<"Node "<<this->myId-3<<" la DAU CUM, FCH= "<<this->FCH<<"\n";
                     this->prRN = nullptr;
                     //doi mau cho CH
                     cDisplayString& dispStr = this->getDisplayString();
                     dispStr.parse("i=misc/node_vs,blue");
                     //Lap lich tao TDMA message
                     cMessage *cmsg = new cMessage();
                     cmsg->setKind(SMSG_MAKETDMA);
                     scheduleAt(simTime() + INIT_WAIT, cmsg);
                 }else {
                     EV<<"Node "<<this->myId-3<<" KHONG PHAI dau cum, FCH= "<<this->FCH<<"\n";
                 }
             }
        }
        if(((ClusterMessage *) msg)->getProto()==CL_TDMA){
           int i;
           int sTime;
           // reset data and counters
           this->myData = 0;   // reset myData
           this->curFrame = 0;
            EV<<"Node "<<this->myId -3<<" da nhan TDMA tu CH\n";
            energyReceive(SIGNAL);
            //doc tin nhan TDMA
            this->nrFrames = ((TDMAMessage *) msg)->getFrames();
            this->frameTime = ((TDMAMessage *) msg)->getFrameTime();
            this->headId = ((TDMAMessage *) msg)->getSrcAddress();
            EV <<this->myId <<": da nhan TDMA frameTime: "<<this->frameTime <<"\n";
            // find time slot for this node
            for(i = 0; i<this->frameTime;i++){
                if(this->myId == ((TDMAMessage *)msg)->getTdma(i) && ((TDMAMessage *)msg)->getTdma(i)!=0){
                    EV<<"Node "<<this->myId-3<<" tim thay time slots "<<i+1<<"\n";
                    sTime = i+1;
                    this->mySlot = sTime;
                    cMessage *cmsg = new cMessage();
                    cmsg->setKind(SMSG_DATA_NODE2CH);
                    this->scheduleAt(simTime()+sTime,cmsg);
                    break;
                }
            }
        }

        if(((ClusterMessage *) msg)->getProto()==CL_CHDATA){
            EV<<"CH "<<this->myId-3<<" da nhan data tu node "<< ((ClusterMessage *) msg)->getSrcAddress()-3<<"\n";
            energyReceive(DATA);
            this->nrDataPackets++;
            EV<<"Number data packet: "<<this->nrDataPackets<<"\n";
            if(this->nrDataPackets == this->nrMemEvent -1){
                this->nrDataPackets = 0;
                ClusterMessage *cmsg = new ClusterMessage();
                cmsg->setKind(SMSG_DATA2RNBS);
                cmsg->setSrcAddress(this->myId);
                //scheduleAt(simTime()+2,cmsg);     MOI DONG, CAN CHECK LAI
                scheduleAt(simTime() + INIT_WAIT,cmsg);
                    this->curFrame++;
                    EV<<"curframes: "<<this->curFrame<<"\n";
                    EV<<"Chuyen den frame tiep theo";
                //}
            }
            //delete msg;
        }
/*****************Cac Node nhan tin nhan REQ_RELAY tu CH (RN)**************************/

        if(((ClusterMessage *) msg)->getProto()==REQ_RELAY){
            int dist;
            EV<<"Node "<<this->myId -3<<" da nhan duoc REQ_RELAY\n";
            energyReceive(SIGNAL);
            ACKRelayMessage *ack = new ACKRelayMessage();
            ack->setProto(ACK_RELAY);
            ack->setEnergy(this->energy);
            ack->setSrcAddress(this->myId);
            ack->setDistBS(this->bsDist);
            ack->setXpos(this->xpos);
            ack->setYpos(this->ypos);
            cModule *ch = getSimulation()->getModule(((ClusterMessage *) msg)->getSrcAddress());
            sendDirect(ack,ch,"in");
            dist = distanceCal(this->xpos,this->ypos,((SensorNode *)ch)->xpos,((SensorNode *)ch)->ypos);
            energyTransmit(SIGNAL,dist*dist);
        }
/******************CH (RN) nhan ACK_REPLY ***************************/
        if(((ClusterMessage *) msg)->getProto()==ACK_RELAY){
            EV<<"CH "<<this->myId-3<<" da nhan ACK_RELAY tu node "<<((ClusterMessage *) msg)->getSrcAddress() -3<<"\n";
            energyReceive(SIGNAL);
            //Tinh FRN cua ung cu vien RN
            ACKRelayMessage *ack = (ACKRelayMessage *) msg;
            cModule *mo= getSimulation()->getModule(ack->getSrcAddress());
            SensorNode *mod = check_and_cast<SensorNode *>(mo);
            long en = (long)ack->getEnergy();
            long distRN_BS = (long)ack->getDistBS();
            long distRN_CH = (long)this->distanceCal(this->xpos, this->ypos, ack->getXpos(), ack->getYpos());
            long distCH_BS = (long)this->bsDist;
            //double FRN_msg = (en*distRN_CH*cosa/distRN_BS);
            long TS = (long) en*distRN_CH*distRN_CH;
            TS = TS + en*distCH_BS*distCH_BS;
            TS = TS - en*distRN_BS*distRN_BS;
            long MS = distRN_BS*2*distCH_BS;
            double FRN_msg = TS/MS;
            mod->FRN = FRN_msg;
            //luu lai cac FRN
            this->candidate[this->cntACK] = mod;
            this->cntACK++;
            EV<<"NODE"<<mod->myId -3 <<" co FRN= "<<FRN_msg<<"\n";
            EV<<"so luong hang xom : "<<this->nrNeighber<<"\n";
            EV<<"cnt ACK: "<<this->cntACK<<"\n";
            if(this->cntACK == this->nrNeighber-1){
                cMessage *msg = new cMessage();
                msg->setKind(SMSG_FIND_RN);
                scheduleAt(simTime()/*+INIT_WAIT*/,msg);
            }

        }
/****************************RN nhan tin nhan RREP***************************/
        if(((ClusterMessage *) msg)->getProto()==RREP){
            energyReceive(SIGNAL);
            int dist;
            if(this->prRN == nullptr){
                EV<<"CH CHUAN BI gui du lieu den BS\n";
                cMessage *msg = new cMessage();
                msg->setKind(SMSG_DATA2BS);
                scheduleAt(simTime()+INIT_WAIT,msg);
            }else{
                ClusterMessage *rmsg = new ClusterMessage();
                 rmsg->setProto(RREP);
                 rmsg->setSrcAddress(this->myId);
                 sendDirect(rmsg,this->prRN,"in");
                 dist = distanceCal(this->xpos,this->ypos,this->prRN->xpos,this->prRN->ypos);
                 energyTransmit(SIGNAL,dist*dist);
            }
        }
/****************************RN nhan tin nhan CL_DATA2BS***************************/
        if(((ClusterMessage *) msg)->getProto()==CL_DATA2BS){
            this->myData = ((Data2BSMessage *)msg)->getData();
            this->sendData2RNBS();
            energyReceive(DATA);
        }
/**************************************************************************************/
   }
}
/**************************************************************************************/
void SensorNode::initNodes(){
    int i;
        cModule *parent = this->getParentModule();
        cModule *mod;
        int numNodes;
        int ritems;
        int trRange = (int) parent->par("trRange");
        numNodes = (int) parent->par("numNodes");
        EV << "numNodes is: " << numNodes << " energy: " << energy << "\n";
        for (i = 1; i <= getSimulation()->getLastComponentId(); i++)
        {
            int x, y, id;

            //scan the simulation module vector
            mod = (cModule *) getSimulation()->getModule(i);

            // check for nodes in transmission range
            if ((strcmp(mod->getName(), "node") == 0) || (strcmp(mod->getName(), "bs") == 0))
            {
                if (strcmp(mod->getName(), "node") == 0)
                {
                    id = ((SensorNode *) mod)->myId;
                    x = ((SensorNode *) mod)->xpos;
                    y = ((SensorNode *) mod)->ypos;
                    nodePtr[id] = ((SensorNode *) mod);
                }
                if (strcmp(mod->getName(), "bs") == 0)
                {
                    id = ((BaseStation *) mod)->myId;
                    this->bsId = id;
                    x = ((BaseStation *) mod)->xpos;
                    y = ((BaseStation *) mod)->ypos;

                    this->bsDist =(int) std::sqrt((x - this->xpos) * (x - this->xpos) + (y - this->ypos) * (y - this->ypos));
                }
                if (id != this->myId)//khoi tao cac node hang xom
                {
                    if(id != this->bsId){
                        int dist = distanceCal(x, y,this->xpos,this->ypos);
                        if (dist <= trRange)
                        {
                            this->neighbers[this->nrNeighber] = ((SensorNode *) mod)->myId;
                            this->nrNeighber++;
                        }
                    }
                }
            }
        }
        // send energy status to BS
}
/**************************************************************************************/
void SensorNode::startEvent(){
    Enter_Method("startEvent()");
    int i;
    EV<<"BAT DAU SU KIEN TAI NODE "<<this->myId - 3<<"\n";
    this->myAction = OFF;
    int ssRange = (int) this->getParentModule()->par("ssRange");
    //Tim cac hang xom co the cam bien duoc su kien (d<= ssRange)
    SensorNode *memberEvents[this->nrNeighber];
    int nrMember = 0;
    for(i=0; i<this->nrNeighber;i++){
       cModule *mod = getSimulation()->getModule(neighbers[i]); //lay ra hang xom i
       if(mod->getId() != this->bsId){
           SensorNode * neighber = check_and_cast<SensorNode *>(mod);
           int dist = distanceCal(this->xpos, this->ypos, neighber->xpos, neighber->ypos);
           neighber->evDist = dist;
           EV<<"Node "<<neighber->getId() -3<<" cach su kien mot khoang: "<<dist<<" (m)\n";
           if(dist <= ssRange){
               if(neighber->energy > 10){
                   cDisplayString& dispStr = neighber->getDisplayString();
                           dispStr.parse("i=misc/node_vs,#00ff00");
                   memberEvents[nrMember] = neighber;
                   neighber->eventID = this->myId;
                   neighber->myAction = ON;
                   neighber->FCH = neighber->energy / neighber->evDist;
                   EV<<"Node "<<neighber->getId() -3<<" co FCH: "<<neighber->FCH<<"\n";
                   EV<<"Node "<<neighber->getId() -3<<" action: "<<neighber->myAction<<"\n";
                   nrMember ++;
               }
           }
       }
    }
    if(nrMember <= 1){
        this->resetRound();
        BaseStation *bs = (BaseStation *)getSimulation()->getModule(this->bsId);
        bs->createEvents();
    }
    if(nrMember >1){
        for(i=0; i<nrMember;i++){
                memberEvents[i]->nrMemEvent = nrMember;
                memberEvents[i]->broadcastReqCL();
            }
    }

}
/**************************************************************************************/
void SensorNode::broadcastReqCL(){
    Enter_Method("broadcastReqCL()");
    int i;
    ReqClusterMessage *rmsg = new ReqClusterMessage();
                   rmsg->setProto(REQ_CLUSTER);
                   rmsg->setSrcAddress(this->myId);
                   rmsg->setFCH(this->energy / this->evDist);
                   rmsg->setNrMemEvent(this->nrMemEvent);
                   //rmsg->getDisplayString()
                   //rmsg->setDisplayString("i=misc/node2_vs,#ff0000");
    for(i=0;i<this->nrNeighber;i++){
        cModule* mod = getSimulation()->getModule(this->neighbers[i]); //lay ra hang xom i
        if(mod->getId() != this->bsId){
           SensorNode * neighber = check_and_cast<SensorNode *>(mod);
           if(neighber->myAction == ON){
               //send(rmsg->dup(),"out",i);
               sendDirect((cMessage *)rmsg ->dup(),neighber,"in");
               int dist = distanceCal(this->xpos,this->ypos,neighber->xpos,neighber->ypos);
               energyTransmit(SIGNAL,dist*dist);
           }
        }
    }
}
/**************************************************************************************/
void SensorNode::sendTDMA(){
    EV << "sendTDMA was called\n";
    int nrPeers = 0;
    int i;
    SensorNode *CL_Members[this->nrMemEvent-1];//luu cac member trong cum
    TDMAMessage *tmsg = new TDMAMessage();
    tmsg->setProto(CL_TDMA);
    tmsg->setTdmaArraySize(this->nrMemEvent + 1);
    tmsg->setSrcAddress(this->myId);
    //tmsg->setDestAddress(BROADCAST);
    //Tao TDMA[] chua cac id cua member trong cum
    //Duyet cac hang xom
    for(i=0;i<this->nrNeighber;i++){
        SensorNode *mod = (SensorNode *) getSimulation()->getModule(this->neighbers[i]);
        if(mod->myAction==ON){
            tmsg->setTdma(nrPeers,mod->myId);
            EV << "tdma " << nrPeers << " to node ID : " << mod->myId -3 << "\n";
            CL_Members[nrPeers]=mod;
            nrPeers++;
        }
    }
    tmsg->setFrames(this->nrFrames);
    tmsg->setFrameTime(nrPeers+2);
    //Danh 2 slots cuoi cho CH trong moi frame
    tmsg->setTdma(nrPeers,this->myId);
    tmsg->setTdma(nrPeers + 1, this->myId);
    //Gui TDMA cho cac members
    for(i=0;i<nrPeers;i++){
        sendDirect(tmsg->dup(),CL_Members[i],"in");
        int dist = distanceCal(this->xpos,this->ypos,CL_Members[i]->xpos,CL_Members[i]->ypos);
        this->energyTransmit(SIGNAL,dist*dist);
    }

}
/**************************************************************************************/
void SensorNode::sendDataToCHead(int clusterHead){
    int dist;
    cModule *mod = getSimulation()->getModule(this->headId);
    SensorNode *ch = check_and_cast<SensorNode *>(mod);
    DataToCHMessage *dmsg = new DataToCHMessage();
    dmsg->setProto(CL_CHDATA);
    dmsg->setSrcAddress(this->myId); //  node id
    dmsg->setDestAddress(this->headId);
    dmsg->setData(this->myData);
    this->myData++;
    dmsg->setClusterHead(clusterHead);
    //gui DATA den dau cum
    int id_gate = ch->gate("in")->getId();
    sendDirect((cMessage *)dmsg,mod,id_gate);
    dist = this->distanceCal(this->xpos, this->ypos, ch->xpos, ch->ypos);
    this->energyTransmit(DATA,dist*dist);
}
/**************************************************************************************/
void SensorNode::sendData2RNBS(){
   // Enter_Method("sendData2RNBS()");
    int dist;
    Data2BSMessage *dmsg = new Data2BSMessage();
    dmsg->setProto(CL_DATA2BS);
    dmsg->setSrcAddress(this->myId);
    if(this->prRN == nullptr){
         this->myData++;
         energyDataAggr(this->nrMemEvent-1);
    }
    dmsg->setData(this->myData);
    if(this->bsDist <= this->trRange){
         dmsg->setDestAddress(this->bsId);
         BaseStation *bs = (BaseStation *) getSimulation()->getModule(this->bsId);
         sendDirect(dmsg,bs,"in");
         dist = distanceCal(this->xpos,this->ypos, bs->xpos, bs->ypos);
     }else{
         dist = distanceCal(this->xpos,this->ypos, this->myRN->xpos, this->myRN->ypos);
         dmsg->setDestAddress(this->myRN->getId());
         sendDirect(dmsg,this->myRN,"in");
     }
    energyTransmit(DATA,dist*dist);
}
/**************************************************************************************/
void SensorNode::findNextHop(){
    Enter_Method("findNextHop()");
    int dist;
 //Kiem tra xem BS co trong pham vi truyen du lieu
    if(this->bsDist < this->trRange){
        EV<<"BS nam trong pham vi truyen du lieu\n";
        //Neu this khong phai CH
         if(this->prRN != nullptr){
                 //gui tin nhan RREP, thong bao cho CH gui data den BS
                 ClusterMessage *rmsg = new ClusterMessage();
                 rmsg->setProto(RREP);
                 rmsg->setSrcAddress(this->myId);
                 sendDirect(rmsg,this->prRN,"in");
                 dist = distanceCal(this->xpos,this->ypos,this->prRN->xpos,this->prRN->ypos);
                 energyTransmit(SIGNAL,dist*dist);
         }
         //Neu this la CH, senddata2BS
         if(this->prRN == nullptr){
             this->sendData2RNBS();
         }
    }else{
        EV<<"Broadcast REQ_RELAY\n";
    //Broadcast REQ_RELAY de tim relay node
        ClusterMessage * rmsg = new ClusterMessage();
        rmsg->setProto(REQ_RELAY);
        rmsg->setSrcAddress(this->myId);
        for(int i=0; i<this->nrNeighber;i++){
                cModule *mod = getSimulation()->getModule(this->neighbers[i]);
                if(((SensorNode *)mod)->energy>10){
                    sendDirect(rmsg->dup(),mod,"in");
                    dist = distanceCal(this->xpos,this->ypos,((SensorNode *)mod)->xpos,((SensorNode *)mod)->ypos);
                    energyTransmit(SIGNAL,dist*dist);
                }
        }
    }
}
int SensorNode::distanceCal(int x1, int y1, int x2, int y2){
    int d = (int) std::sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    return d;
}
/**************************************************************************************/
void SensorNode::resetRound(){
    for (int i = 3; i <= getSimulation()->getLastComponentId(); i++){
        SensorNode *mod = (SensorNode *)getSimulation()->getModule(i);
        mod->curFrame = 0;
        mod->frameTime = 0;
        //mod->hopCount = 0;
        mod->myData = 0;
        mod->evDist = 0;
        mod->mySlot = 0;
        mod->eventID = 0;
        //mod->FCH = 0.0;
        //mod->headDist =0;
        mod->headId = 0;
        mod->myAction = OFF;
        mod->cHead =2;
        mod->prRN = nullptr;
        mod->myRN = nullptr;
        mod->FRN = 0.0;
        mod->cntACK = 0;
        mod->nrDataPackets = 0;
        mod->nrMemEvent = 0;
        //Reset lai mau cho node
        cDisplayString& dispStr = mod->getDisplayString();
        dispStr.parse("i=misc/node_vs");
        /*for(int j=0;j<MAXNEIGHBORS;j++){
            mod->candidate[i]=nullptr;
        }*/
    }
}

// energy consumption for reception of bits
void SensorNode::energyReceive(int bits)
{
    double en;
    if (this->myStatus == STATUS_LIVE)
    {
        en = (double) bits * 50.0 * NANO;
        EV <<"Nang luong de nhan tin nhan: "<<bits <<"(bits) la " <<en <<" (microJ)\n";
        this->energy = this->energy - en;
        EV <<"Nang luong con lai "<<this->energy<<"\n";
    }
}
/**************************************************************************************/
void SensorNode::energyTransmit(int bits, int dist)
{
    double en;
    int transmisionRange;
    cModule *parent = getParentModule();
    transmisionRange = (int) parent->par("trRange");
    if (this->energy <= 0) EV <<"out of energy: " << this->myId << endl;
    if (this->myStatus == STATUS_LIVE)
    {
        if (sqrt(dist) <= transmisionRange)
        {
            en = ((double) bits *50.0 * NANO) + ((double)bits * 10 * PICO * dist) ;
            EV << "Nang luong can de truyen " << bits << "(bits) di "
               <<(int) sqrt(dist) << " (m) la: " << en << " (microJ)\n";
        }
        else
        {
            en = ((double)bits *50.0 * NANO)+((double)bits * 0.0013*PICO*dist*dist) ;
            EV << "Nang luong can de truyen " << bits << "(bits) di "
               <<(int) sqrt(dist) << " (m) la: " << en << " (microJ)\n";
        }
        this->energy = this->energy - en;
        EV<<"Nang luong con lai: "<<this->energy<<"\n";
    }
}
/**************************************************************************************/
void SensorNode::energyDataAggr(int signals)
{
    double en;

    if (this->myStatus == STATUS_LIVE)
    {
        en = 5 * NANO * signals;
        EV << "Nang luong mat di do tong hop du lieu: " << en << "\n";
        this->energy = this->energy - en;
    }
}
