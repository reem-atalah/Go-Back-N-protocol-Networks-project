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

#include "Hub.h"
#include "customizedMsg_m.h"

Define_Module(Hub);

void Hub::initialize()
{
    // TODO - Generated method body
//    getParentModule()->par("n");
    CustomizedMsg_Base * msgc= new CustomizedMsg_Base("Hello from Hub");
    EV<<"Begin hub"<<endl;
    send(msgc, "portOut");
}

void Hub::handleMessage(cMessage *msg)
{
    // TODO - Generated method body

    CustomizedMsg_Base * receivedMsg = check_and_cast<CustomizedMsg_Base *>(msg);
        EV<<"received: seq_num: "<<receivedMsg->getSeq_num()
                <<" payload: "<<receivedMsg->getMsg_payload()
                <<" parity: "<< receivedMsg->getMycheckbits();

        send(receivedMsg, "portOut");
    EV<<msg->getName()<<endl;
//     cancelAndDelete(msg);

    char parity_hat= addParity((char*)receivedMsg->getMsg_payload());
    if (parity_hat==receivedMsg->getMycheckbits()){
        EV<<"parity check passed"<<endl;
        // send ack
        receivedMsg-> setN_ack_value(receivedMsg->getSeq_num());
        receivedMsg -> setFrame_type(1);



    }
    else{
        EV<<"parity check failed"<<endl;
        // send nack
        receivedMsg-> setN_ack_value(receivedMsg->getSeq_num());
        receivedMsg -> setFrame_type(2);
    }
    double time = (int)getParentModule()->par("TD")+(double)getParentModule()->par("PT");
    double prob1 = 0.9;
    if (uniform(0, 1) > prob1){
        sendDelayed(receivedMsg,time, "portOut");
    }


}

char Hub::addParity(char * frame)
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
