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
    //send the message with time
    //seq_number is next_frame_to_send
    int ack_expected = 0;
    int next_frame_to_send = 0;

    int i =0;

    //message = seq_number + frame + parity + frameType ack_expected
    while(i<5){

        // prepare the message
        CustomizedMsg_Base * sendMsg = new CustomizedMsg_Base("Send msg .."); //this the msg->getName() at receiver
        char * msgContent = framing("1",'$','/'); //get it from the file
        char msgParity = addParity(msgContent);
        sendMsg->setMsg_payload(msgContent);
        sendMsg->setSeq_num(next_frame_to_send);
        sendMsg->setFrame_type(0); // sender always send data only
        sendMsg->setMycheckbits(msgParity);

        // print data
        std::string thePayload;
        int modified = -1; //modified number is not random, don't modify in flag
        std::string loss = "No";
        int duplicate =0;
        int delay = 0;
        std::bitset<8> parity(msgParity);
        double time = 0;
        int property=0; //get it from the file

        switch (property)
        {
        case 0: //no err
            // add processing delay PT(0.5) and transmission delay TD(1) in case no delay, no duplication
            time = (double)getParentModule()->par("PT")+(int)getParentModule()->par("TD");
            break;
        case 1: //delay
            // add processing delay PT(0.5) and transmission delay TD(1) and Error delay ED(4) in case of delay
            time = (double)getParentModule()->par("PT")+(int)getParentModule()->par("TD")+(int)getParentModule()->par("ED");
            delay = (int)getParentModule()->par("ED") ; // not sure ?????????????
            break;
        case 2: //duplication
            duplicate = 1;
            //put the first time, same as case 0
            time = (double)getParentModule()->par("PT")+(int)getParentModule()->par("TD");
        case 3: //delay and duplication, apply now the delay only
            duplicate = 1;
            time = (double)getParentModule()->par("PT")+(int)getParentModule()->par("TD")+(int)getParentModule()->par("ED");
            delay = (int)getParentModule()->par("ED") ; // not sure ?????????????
            break;
        case 4: //loss
            loss = "Yes";
            break;
        case 5:
            loss = "Yes";
            break;
        case 6:
            loss = "Yes";
            break;
        case 7:
            loss = "Yes";
            break;
        case 8: //modify ,normal time
            modified = 1; //modify first bit in msg not in flag
            thePayload = sendMsg->getMsg_payload();
            thePayload[1]+=5;
            sendMsg->setMsg_payload(thePayload.c_str());
            time = (double)getParentModule()->par("PT")+(int)getParentModule()->par("TD");
            break;
        case 9: //modify and delay
            modified = 1;
            thePayload = sendMsg->getMsg_payload();
            thePayload[1]+=5;
            sendMsg->setMsg_payload(thePayload.c_str());
            time = (double)getParentModule()->par("PT")+(int)getParentModule()->par("TD")+(int)getParentModule()->par("ED");
            delay = (int)getParentModule()->par("ED") ; // not sure ?????????????
            break;
        case 10: //modify and duplicate, normal time
            duplicate = 1;
            modified = 1;
            thePayload = sendMsg->getMsg_payload();
            thePayload[1]+=5;
            sendMsg->setMsg_payload(thePayload.c_str());
            time = (double)getParentModule()->par("PT")+(int)getParentModule()->par("TD");
            break;
        case 11: //modify and duplicate and delay
            duplicate = 1;
            modified = 1;
            thePayload = sendMsg->getMsg_payload();
            thePayload[1]+=5;
            sendMsg->setMsg_payload(thePayload.c_str());
            time = (double)getParentModule()->par("PT")+(int)getParentModule()->par("TD")+(int)getParentModule()->par("ED");
            delay = (int)getParentModule()->par("ED") ; // not sure ?????????????
            break;
        case 12: //loss
            loss = "Yes";
            break;
        case 13: //loss
            loss = "Yes";
            break;
        case 14: //loss
            loss = "Yes";
            break;
        case 15: //loss
            loss = "Yes";
            break;
        }

        EV<<"At time: "<<time
                <<" Node: "<<0 //it's sender //need to be changed
                <<" sent frame with seq_num= "<<next_frame_to_send
                <<" and payload= "<<msgContent
                <<" and trailer= "<<parity
                <<", Modified bit number " << modified//not handled yet
                <<", Lost " <<loss //not handled yet
                <<", Duplicate "<<duplicate  //not handled yet
                <<", Delay " << delay //not handled yet
                <<endl;

        // send the message with a delay (even if there is no delay, put the time of sending msg PT+TD)
        if(time != 0) //time =0 : loss
        {
            sendDelayed(sendMsg,time, "portOut");
        }
        if (property == 2 or property == 3 or property == 10 or property == 11) //duplication
        {
            duplicate = 2;
            time += (int)getParentModule()->par("DD");
            EV<<"At time: "<<time
                            <<" Node: "<<0 //it's sender //need to be changed
                            <<" sent frame with seq_num= "<<next_frame_to_send
                            <<" and payload= "<<msgContent
                            <<" and trailer= "<<parity
                            <<", Modified bit number " << modified//not handled yet
                            <<", Lost " <<loss  //not handled yet
                            <<", Duplicate "<<duplicate  //not handled yet
                            <<", Delay "<< delay //not handled yet
                            <<endl;
            sendDelayed(sendMsg,time, "portOut");
        }

        //circular increment
        next_frame_to_send++;
        next_frame_to_send%= (int)getParentModule()->par("WS");

        i++;

        //to read the ack:
        //convert 'msg' to be CustomizedMsg_Base
        CustomizedMsg_Base * receivedMsg = check_and_cast<CustomizedMsg_Base *>(msg);

        //check if the ack as expected
        //ack: then shift the window
        if (ack_expected == receivedMsg->getN_ack_value())
        {
            //circular increment
            ack_expected++;
            ack_expected%= (int)getParentModule()->par("WS");

        }
    }

    // 1st msg: in case of duplication, add processing delay PT(0.5) and transmission delay TD(1)
    // 2nd msg: then add duplication delay DD(0.1)


}

char * Sender::framing(std::string msg, char flag, char escape)
{
    char* updated_msg = new char[3+msg.size()*2];
    updated_msg[0] = flag;
    int j=1;
    for(int i = 0; i<msg.size(); i++) { //get character at position i
          if( msg.at(i) == flag or msg.at(i) == escape)
          {
              updated_msg[j]=escape;
              j++;
          }
          updated_msg[j]=msg.at(i);
          j++;
     }
//    add flag at the end of the msg
    updated_msg[j] = flag;
    j++;
    updated_msg[j] = '\0';
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




