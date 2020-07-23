/*
 * ArpeesDef.h
 *
 *  Created on: Jun 5, 2020
 *      Author: thanh
 */

#ifndef ARPEESDEF_H_
#define ARPEESDEF_H_

#define NANO 0.001
#define PICO 0.000001
//#define M_PI 3.1415926535

#define NUMBERNODES  1500
#define NUMBERROUND  1000
#define MAXEVENTS    50         // max number of events
#define MAXNEIGHBORS 50

#define SIGNAL      25*8        // 25 bytes
#define DATA        500*8       // 500 bytes
#define SIGNAL2BS   25

// node status
#define STATUS_LIVE       1
#define STATUS_DEAD       2
#define STATUS_REDUN      3

// messagetypes for clusters
#define CL_TOBS           3
#define CL_TOHEAD         4
#define CL_TDMA           5
#define CL_CHDATA         6
#define CL_RNDATA         7
#define CL_DATA2BS       8
#define CL_TO_FREE_NODE     18
#define CL_TO_REDUN_NODE    19
#define CL_TO_DEAD_NODE     20
#define REQ_CLUSTER        21
#define REQ_RELAY          22
#define ACK_RELAY          23
#define FIND_HOP           24
#define RREP               25
// self message types
#define SMSG_DATA2RNBS    8
#define SMSG_DATA2BS      9       // cluster head sends data to RN/BS
#define SMSG_DATA_NODE2CH   10      // node send data to cluster head
#define SMSG_STATUS2BS      14      // nodes send their new status to BS
#define SMSG_INIT           15      // init updates
#define SMSG_MAKETDMA       16
#define BROADCAST           17
#define SMSG_CRE_EVENT      11      //TAO SU KIEN
#define SMSG_FIND_RN        24      //thong bao tim RN
struct _adv
{
    int id;
    int energy;
    int status;
    int xpos;
    int ypos;
    int kd;
    int delay;  //mirco-second
    int hop;
};
// define some events and times
#define INIT_WAIT   1     // wait to init nodes
#define ON          1
#define OFF         0

#endif /* ARPEESDEF_H_ */
