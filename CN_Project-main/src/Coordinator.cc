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

#include "Coordinator.h"
#include<fstream>
#include "CoordinatorMsg_m.h"
Define_Module(Coordinator);

void Coordinator::initialize()
{
    std::string tempVar;
    std::ifstream myFile("coordinator.txt");
    while(getline(myFile, tempVar)){
        int nodeNum = atoi(tempVar.c_str());
        int startingTime = atoi(tempVar.c_str()+1);
        // TODO create custom message for coordinator
        CoordinatorMsg_Base* msg = new CoordinatorMsg_Base("coordinator");
        msg->setStartTime(startingTime);
        msg->setStartingNode(nodeNum);
        if(nodeNum==0){
            send(msg, "out_node0");
        }
        else{
            send(msg, "out_node1");
        }
    }
    myFile.close();
}

void Coordinator::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}
