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
}
