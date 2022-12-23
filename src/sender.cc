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
int Sf = 0;
int Sn;
int Sl;
int i = 0;

void Sender::initialize()
{
    //     // TODO - Generated method body
    //     EV<<"Begin sender"<<endl;
    // //    CustomizedMsg_Base * msgc= new CustomizedMsg_Base("Sned 1st msg ..");
    // //    send(msgc, "portOut");
    //     readFile("input0.txt");
    //     Sl = (int)getParentModule()->par("WS");
    //     scheduleAt(simTime() + (double)getParentModule()->par("PT"),
    //                     new cMessage(("S" + std::to_string(0)).c_str()));
    //     int property = msgs[0].first;
    //     if (property == 2 or property == 3 or property == 10 or property == 11)
    //                         scheduleAt(simTime() + (double)getParentModule()->par("PT")
    //                         + (double)getParentModule()->par("DD"),
    //                         new cMessage(("D" + std::to_string(0)).c_str()));

    //     acks = std::vector<bool> (Sl, false);
    isFirstMessageFromCoordinator = 0;
}

void Sender::handleMessage(cMessage *msg) // msg is ack/nack
{
    // message from hub (hub will be now the coordinator)
    if (isFirstMessageFromCoordinator == 0)
    {
        // read message , normal message not custom one
        // if message content is "kak" then it is the first message from the coordinato
        std::string msg_content = msg->getName();

        if (msg_content == "kak") // if the message is from the coordinator
        {
            isFirstMessageFromCoordinator = 1;
            // init sender

            // TODO - Generated method body
            EV << "Begin sender" << endl;
            // CustomizedMsg_Base * msgc= new CustomizedMsg_Base("Sned 1st msg ..");
            // send(msgc, "portOut");
            readFile("input0.txt");
            Sl = (int)getParentModule()->par("WS");
            scheduleAt(simTime() + (double)getParentModule()->par("PT"),
                       new cMessage(("S" + std::to_string(0)).c_str()));
            int property = msgs[0].first;
            if (property == 2 or property == 3 or property == 10 or property == 11)
                scheduleAt(simTime() + (double)getParentModule()->par("PT") + (double)getParentModule()->par("DD"),
                           new cMessage(("D" + std::to_string(0)).c_str()));

            acks = std::vector<bool>(Sl, false);
            isFirstMessageFromCoordinator = 0;
        }
        else
        {
            isFirstMessageFromCoordinator = 2;
            // init receiver
            seq_num = 0;
            EV << "Begin receiver" << endl;
        }
    }
    if (isFirstMessageFromCoordinator == 2)
    {
        // receiver logic

        CustomizedMsg_Base *receivedMsg = check_and_cast<CustomizedMsg_Base *>(msg);

        if (receivedMsg->getSeq_num() == seq_num)
        {
            char parity_hat = checkParity((char *)receivedMsg->getMsg_payload());
            if (parity_hat == receivedMsg->getMycheckbits())
            {
                EV << "parity check passed" << endl;
                // send ack
                receivedMsg->setN_ack_value(receivedMsg->getSeq_num());
                receivedMsg->setFrame_type(1);
                seq_num++;
            }
            else
            {
                EV << "parity check failed" << endl;
                // send nack
                receivedMsg->setN_ack_value(receivedMsg->getSeq_num());
                receivedMsg->setFrame_type(2);
            }

            double time = (int)getParentModule()->par("TD") + (double)getParentModule()->par("PT");
            //            double prob1 = 0.1;
            // At time[.. starting sending time after processing�.. ], Node[id] Sending [ACK/NACK] with number [�] , loss [Yes/No ]
            double uniformProb = uniform(0, 1);
            //    EV<<" uniformProb: "<<uniformProb <<endl;
            if (uniformProb > (double)getParentModule()->par("LP"))
            {
                //    if(true){
                CustomizedMsg_Base *dupreceivedMsg = receivedMsg->dup();
                EV << "At time: " << simTime()
                   << " frame type: " << receivedMsg->getFrame_type()
                   << " ack/nack value: " << receivedMsg->getN_ack_value()
                   << " loss: No" << endl;
                sendDelayed(dupreceivedMsg, time, "portOut");
            }
            else
            {
                bubble("message lost");
                EV << "At time: " << simTime()
                   << " frame type: " << receivedMsg->getFrame_type()
                   << " ack/nack value: " << receivedMsg->getN_ack_value()
                   << " loss: Yes" << endl;
            }
        }
        EV << "seq_num: " << seq_num << endl;
    }
    else if (isFirstMessageFromCoordinator == 1)
    {
        // sender logic

        for (int i = 0; i < acks.size(); i++)
        {
            EV << acks[i] << " ";
        }
        EV << endl;
        EV << Sf << " " << Sn << " " << Sl << endl;

        if (msg->isSelfMessage())
        {
            std::string self_msg = msg->getName();
            if (self_msg.size() > 0)
            {
                Sn = atoi(self_msg.substr(1, self_msg.size() - 1).c_str());

                // prepare the message
                CustomizedMsg_Base *sendMsgInit = new CustomizedMsg_Base("Send msg .."); // this the msg->getName() at receiver
                char *msgContent = framing(msgs[Sn].second, '$', '/');                   // get it from the file
                char msgParity = addParity(msgContent);
                sendMsgInit->setMsg_payload(msgContent);
                sendMsgInit->setSeq_num(Sn);
                sendMsgInit->setFrame_type(0); // sender always send data only
                sendMsgInit->setMycheckbits(msgParity);

                CustomizedMsg_Base *sendMsg = sendMsgInit->dup();

                // print data
                std::string thePayload = msgContent;
                int modified = -1; // modified number is not random, don't modify in flag
                std::string loss = "No";
                int duplicate = 0;
                int delay = 0;
                std::bitset<8> parity(msgParity);
                double time = 0;
                // Include The "T" condition ?
                char tag = msg->getName()[0];
                int property = (tag != 'T') ? msgs[Sn].first : 0; // get it from the file
                if (tag == 'T')
                {
                    EV << "Timeout on: " << sendMsgInit->getSeq_num() << endl;
                    for (int i = Sn + 1; i < Sl; i++)
                    {
                        if (timeouts[i])
                            cancelEvent(timeouts[i]);
                    }
                }

                switch (property)
                {
                case 0: // no err
                    // add processing delay PT(0.5) and transmission delay TD(1) in case no delay, no duplication
                    time = (int)getParentModule()->par("TD");
                    break;
                case 1: // delay
                    // add processing delay PT(0.5) and transmission delay TD(1) and Error delay ED(4) in case of delay
                    time = (int)getParentModule()->par("TD") + (int)getParentModule()->par("ED");
                    delay = (int)getParentModule()->par("ED"); // not sure ?????????????
                    break;
                case 2: // duplication
                    duplicate = 1;
                    // put the first time, same as case 0
                    time = (int)getParentModule()->par("TD");
                case 3: // delay and duplication, apply now the delay only
                    duplicate = 1;
                    time = (int)getParentModule()->par("TD") + (int)getParentModule()->par("ED");
                    delay = (int)getParentModule()->par("ED"); // not sure ?????????????
                    break;
                case 4: // loss
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
                case 8:           // modify ,normal time
                    modified = 1; // modify first bit in msg not in flag
                    thePayload = sendMsg->getMsg_payload();
                    thePayload[1] += 5;
                    sendMsg->setMsg_payload(thePayload.c_str());
                    time = (int)getParentModule()->par("TD");
                    break;
                case 9: // modify and delay
                    modified = 1;
                    thePayload = sendMsg->getMsg_payload();
                    thePayload[1] += 5;
                    sendMsg->setMsg_payload(thePayload.c_str());
                    time = (int)getParentModule()->par("TD") + (int)getParentModule()->par("ED");
                    delay = (int)getParentModule()->par("ED"); // not sure ?????????????
                    break;
                case 10: // modify and duplicate, normal time
                    duplicate = 1;
                    modified = 1;
                    thePayload = sendMsg->getMsg_payload();
                    thePayload[1] += 5;
                    sendMsg->setMsg_payload(thePayload.c_str());
                    printf("%s", thePayload.c_str());
                    time = (int)getParentModule()->par("TD");
                    break;
                case 11: // modify and duplicate and delay
                    duplicate = 1;
                    modified = 1;
                    thePayload = sendMsg->getMsg_payload();
                    thePayload[1] += 5;
                    sendMsg->setMsg_payload(thePayload.c_str());
                    time = (int)getParentModule()->par("TD") + (int)getParentModule()->par("ED");
                    delay = (int)getParentModule()->par("ED"); // not sure ?????????????
                    break;
                case 12: // loss and modify
                    modified = 1;
                    thePayload = sendMsg->getMsg_payload();
                    thePayload[1] += 5;
                    sendMsg->setMsg_payload(thePayload.c_str());
                    loss = "Yes";
                    break;
                case 13: // loss
                    modified = 1;
                    thePayload = sendMsg->getMsg_payload();
                    thePayload[1] += 5;
                    sendMsg->setMsg_payload(thePayload.c_str());
                    loss = "Yes";
                    break;
                case 14: // loss
                    modified = 1;
                    thePayload = sendMsg->getMsg_payload();
                    thePayload[1] += 5;
                    sendMsg->setMsg_payload(thePayload.c_str());
                    loss = "Yes";
                    break;
                case 15: // loss
                    modified = 1;
                    thePayload = sendMsg->getMsg_payload();
                    thePayload[1] += 5;
                    sendMsg->setMsg_payload(thePayload.c_str());
                    loss = "Yes";
                    break;
                }

                // TODO: make it time + simtime()
                EV << "At time: " << simTime()
                   << " Node: " << 0 // it's sender //need to be changed
                   << " sent frame with seq_num= " << Sn
                   << " property: " << property
                   << " and payload= " << thePayload
                   << " and trailer= " << parity
                   << ", Modified bit number " << modified
                   << ", Lost " << loss
                   << ", Duplicate " << duplicate // not handled yet
                   << ", Delay " << delay
                   << endl;
                if (time > 0.001)
                    sendDelayed(sendMsg, time, "portOut");

                // take out of condition??
                if (Sn + 1 < Sl && Sn + 1 < msgs.size() && tag != 'D')
                {
                    scheduleAt(simTime() + (double)getParentModule()->par("PT"),
                               new cMessage(("S" + std::to_string(Sn + 1)).c_str()));

                    property = msgs[Sn + 1].first;
                    if (property == 2 or property == 3 or property == 10 or property == 11)
                        scheduleAt(simTime() + (double)getParentModule()->par("PT") + (double)getParentModule()->par("DD"),
                                   new cMessage(("D" + std::to_string(Sn + 1)).c_str()));
                }
                if (tag != 'D')
                {
                    cMessage *timeoutMsg = new cMessage(("T" + std::to_string(Sn)).c_str());
                    scheduleAt(simTime() + (double)getParentModule()->par("PT") + (int)getParentModule()->par("TO"),
                               timeoutMsg);
                    timeouts[Sn] = timeoutMsg;
                }
            }
        }
        else
        {
            CustomizedMsg_Base *receivedMsg = check_and_cast<CustomizedMsg_Base *>(msg);
            EV << "At time: " << simTime()
               << " frame type: " << receivedMsg->getFrame_type()
               << " sequence number: " << receivedMsg->getN_ack_value() << endl;

            // update ack array
            if (receivedMsg->getFrame_type() == 1) // ack
            {
                int recived_Sn = receivedMsg->getN_ack_value();
                acks[recived_Sn - Sf] = 1;
                if (timeouts[recived_Sn])
                    cancelEvent(timeouts[recived_Sn]);
                int shift = applyShift(acks);
                if (shift && Sn + 1 == Sl && Sn + 1 < msgs.size())
                {
                    scheduleAt(simTime() + (double)getParentModule()->par("PT"),
                               new cMessage(("S" + std::to_string(Sn + 1)).c_str()));

                    int property = msgs[Sn + 1].first;
                    if (property == 2 or property == 3 or property == 10 or property == 11)
                        scheduleAt(simTime() + (double)getParentModule()->par("PT") + (double)getParentModule()->par("DD"),
                                   new cMessage(("S" + std::to_string(Sn + 1)).c_str()));
                }
                Sl += shift;
                Sf += shift;
            }
            // n-ack
            //        else if (receivedMsg->getFrame_type() == 2)
            //        {
            // re-send from this frame until window size
            //            int recived_Sn = receivedMsg->getN_ack_value();
            //            if (timeouts[recived_Sn])
            //                cancelEvent(timeouts[recived_Sn]);
            //            scheduleAt(simTime() + (double)getParentModule()->par("PT"),
            //            new cMessage(("T" + std::to_string(receivedMsg->getN_ack_value())).c_str()));
            //        }
            // schedule ( like Timeout but only with PT)
        }
    }
}

char *Sender::framing(std::string msg, char flag, char escape)
{
    char *updated_msg = new char[3 + msg.size() * 2];
    updated_msg[0] = flag;
    int j = 1;
    for (int i = 0; i < msg.size(); i++)
    { // get character at position i
        if (msg.at(i) == flag or msg.at(i) == escape)
        {
            updated_msg[j] = escape;
            j++;
        }
        updated_msg[j] = msg.at(i);
        j++;
    }
    //    add flag at the end of the msg
    updated_msg[j] = flag;
    j++;
    updated_msg[j] = '\0';
    return updated_msg;
}

char Sender::addParity(char *frame)
{
    std::bitset<8> parity(frame[0]); // fill the parity with first character
    int Size = 0;
    while (frame[Size] != '\0')
        Size++;
    for (int i = 1; i < Size; i++)
    {                                      // get character at position i // or frame.size()
        std::bitset<8> charBits(frame[i]); // turn char to bits
        parity ^= charBits;                // xor all characters to get the parity
    }
    return (char)parity.to_ulong(); // convert the parity bits to be 1 char
}

void Sender::readFile(std::string filename)
{
    std::ifstream input(filename);
    std::string errors_str, msg, line;
    while (input)
    {
        getline(input, line);
        if (line.size() >= 4)
        {
            errors_str = line.substr(0, 4);
            std::bitset<4> errors_bin(errors_str);
            int errors = errors_bin.to_ullong();
            msg = "";
            if (line.size() >= 6)
                msg = line.substr(5, line.size() - 5);
            msgs.push_back(std::make_pair(errors, msg));
        }
    }
}

int Sender::applyShift(std::vector<bool> &ack)
{
    int s = 0;
    while (s < ack.size() && ack[s])
        s++;

    std::vector<bool> new_ack(ack.size(), false);
    for (int i = 0; i < ack.size() - s; i++)
        new_ack[i] = ack[s + i];
    ack = new_ack;

    return s;
}

char Sender::checkParity(char *frame)
{
    std::bitset<8> parity(frame[0]); // fill the parity with first character
    int Size = 0;
    while (frame[Size] != '\0')
        Size++;
    for (int i = 1; i < Size; i++)
    {                                      // get character at position i // or frame.size()
        std::bitset<8> charBits(frame[i]); // turn char to bits
        parity ^= charBits;                // xor all characters to get the parity
    }
    return (char)parity.to_ulong(); // convert the parity bits to be 1 char
}
