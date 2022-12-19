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

#ifndef __TERMPROJECT_NODE_H_
#define __TERMPROJECT_NODE_H_

#include <omnetpp.h>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Node : public cSimpleModule
{
  protected:
    bool isSender = false;
    int nodeNumber = 0;
    std::vector<std::string> messageErrors;
    std::vector<std::string> messages;
    int currentMsgToSend = 0;

    // time of start sending
    int startingTime = 0;

    // global parameters
    int WS; // window size
    int TO; // time out
    double PT; // processing time
    double TD; // transmission time
    double ED; // error delay
    double DD; // duplication delay
    double LP; // loss probability

    // window parameters
    // Sender: window first and last indexes of the vector above
    int SF = 0;
    int SL = 0;
    // Receiver: window index
    int R = 0;

    // timed out message index
    int timedoutMsgIndex = -1;

    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif
