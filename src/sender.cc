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

#include "sender.h"
#include "customizedMsg_m.h"

Define_Module(Sender);

void Sender::initialize()
{
    // TODO - Generated method body
    EV<<"Begin sender"<<endl;
    cMessage * msgc= new cMessage("Sned 1st msg ..");
    send(msgc, "portOut");
}

void Sender::handleMessage(cMessage *msg) //msg is ack/nack
{
    // TODO - Generated method body
    //wait for ack or timeout
    //send the message
    //seq_number is next_frame_to_send
//    int ack_expected = 0;
    int next_frame_to_send = 1;

    int i =0;

    //message = seq_number + frame + parity + frameType ack_expected
    while(i<10){

        // prepare the message
        CustomizedMsg_Base * sendMsg = new CustomizedMsg_Base("Send msg ..");
        char * msgContent = framing("msg payload",'$','/'); //should get this from the file
        char msgParity = addParity(msgContent);
        sendMsg->setMsg_payload(msgContent);
        sendMsg->setSeq_num(next_frame_to_send);
        sendMsg->setFrame_type(0); // sender always send data only
        sendMsg->setMycheckbits(msgParity);


        // print data
        std::bitset<8> parity(msgParity);
        double time = 0;
        // add processing delay PT(0.5) and transmission delay TD(1) in case no delay, no duplication
        time = (double)getParentModule()->par("PT")+(int)getParentModule()->par("TD");

        // add processing delay PT(0.5) and transmission delay TD(1) and Error delay ED(4) in case of delay
        time = (double)getParentModule()->par("PT")+(int)getParentModule()->par("TD")+(int)getParentModule()->par("ED");

        EV<<"At time: "<<time
                <<" Node: "<<0 //it's sender
                <<" sent frame with seq_num= "<<next_frame_to_send
                <<" and payload= "<<msgContent
                <<" and trailer= "<<parity
                <<", Modified bit number " //not handled yet
                <<", Lost " //not handled yet
                <<", Duplicate " //not handled yet
                <<", Delay "
                <<endl;

        // send the message
        send(sendMsg, "portOut");

        next_frame_to_send++;
        next_frame_to_send%= (int)getParentModule()->par("WS");

        i++;
    }

    // 1st msg: in case of duplication, add processing delay PT(0.5) and transmission delay TD(1)
    // 2nd msg: then add duplication delay DD(0.1)


}

char * Sender::framing(std::string msg, char flag, char escape)
{
//    char * updated_msg;
    char* updated_msg = new char[msg.size()*2];
//    char * updated_msg[msg.size()*2];
//    char *updated_msg = (char*)malloc(msg.size()*2*sizeof(char));
    //    add flag at the beginning of the msg
    updated_msg[0] = flag;
    printf(updated_msg);
    int j=1;
    for(int i = 0; i<msg.size(); i++) { //get character at position i // or msg.size()
          if( msg.at(i) == flag or msg.at(i) == escape)
          {
              updated_msg[j]=escape;
              j++;
          }
          updated_msg[i]=msg.at(i);
          printf(updated_msg);
          j++;
     }
//    add flag at the end of the msg
    updated_msg[j] = flag;
    printf(updated_msg);
    return updated_msg;
}

char Sender::addParity(char * frame)
{
    std::bitset<8> parity(frame[0]); //fill the parity with first character
    int Size = 0;
    while (frame[Size] != '\0') Size++;
    for(int i = 1; i<Size; i++) { //get character at position i // or frame.size()
        std::bitset<8> charBits(frame[i]);//turn char to bits
        parity^=charBits; //xor all characters to get the parity
    }
    return (char)parity.to_ulong(); //convert the parity bits to be 1 char
}




