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

#ifndef __PROJECT_SENDER_H_
#define __PROJECT_SENDER_H_

#include <omnetpp.h>
#include <bitset>
#include <vector>
#include <fstream>
#include <unordered_map>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Sender : public cSimpleModule
{
public:
    std::vector<std::pair<int, std::string>> msgs;
    std::vector<bool> acks;
    std::unordered_map<int, std::pair<cMessage *, cMessage *>> timeouts;
    char * framing(std::string msg, char flag, char escape);
    char addParity(char * frame);
    void readFile(std::string filename);
    int applyShift(std::vector<bool>& ack);
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;


};

#endif
