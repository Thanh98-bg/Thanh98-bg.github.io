//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
message ClusterMessage
{    
        int proto;
        int srcAddress;
        int destAddress;
}
//REQ_CLUSTER MESSAGE 
message ReqClusterMessage extends ClusterMessage{
		int energy;
		//int id;
		double FCH;
		//string displayString = "i=no,no,30%";
		int nrMemEvent; //luu so luong cac node trong su 
}
//TDMA MESSAGE
message TDMAMessage extends ClusterMessage{
    int frames; 	//so luong frame/round
    int frameTime;  //so luong TS/frame
    int tdma[]; 	//mang luu ID cua cac member trong cum
}
//DATA TO CH
message DataToCHMessage extends ClusterMessage{
    int clusterHead;
    int data;
}
//ACK RELAY REPLY TO CH
message ACKRelayMessage extends ClusterMessage{
	int energy;//nl con lai cua node
	int distBS;
	int status;
	int xpos;
	int ypos;
}
//DATA TO BS MESSAGE
message Data2BSMessage extends ClusterMessage{
    int data;
}