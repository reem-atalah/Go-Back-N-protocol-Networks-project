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
//    CustomizedMsg_Base * msgc= new CustomizedMsg_Base("Hello from Hub");
    EV<<"Begin hub"<<endl;
    seq_num=0;
//    send(msgc, "portOut");
}

void Hub::handleMessage(cMessage *msg)
{
    // TODO - Generated method body

    CustomizedMsg_Base * receivedMsg = check_and_cast<CustomizedMsg_Base *>(msg);

//    if(receivedMsg->getSeq_num() == seq_num)
//    {
        char parity_hat= checkParity((char*)receivedMsg->getMsg_payload());
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
            double prob1 = 0.1;
            // At time[.. starting sending time after processing….. ], Node[id] Sending [ACK/NACK] with number […] , loss [Yes/No ]
            double uniformProb= uniform(0, 1);
        //    EV<<" uniformProb: "<<uniformProb <<endl;
            if (uniformProb > prob1){
        //    if(true){
                CustomizedMsg_Base * dupreceivedMsg = receivedMsg->dup();
                EV<<"At time: "<<simTime()
                        <<" frame type: " <<receivedMsg->getFrame_type()
                        <<" ack/nack value: "<< receivedMsg-> getN_ack_value()
                        <<" loss: No"<<endl;
                sendDelayed(dupreceivedMsg,time, "portOut");
            }
            else
            {
                bubble("message lost");
                EV<<"At time: "<<simTime()
                   <<" frame type: " <<receivedMsg->getFrame_type()
                   <<" ack/nack value: "<< receivedMsg-> getN_ack_value()
                   <<" loss: Yes"<<endl;
            }
//        seq_num++;
//    }

}

char Hub::checkParity(char * frame)
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
