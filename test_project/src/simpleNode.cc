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

#include "simpleNode.h"

Define_Module(SimpleNode);

void SimpleNode::initialize()
{
    // TODO - Generated method body

    if(strcmp(getName(), "Sender") == 0)
    {
        cMessage* msg = new cMessage("beign");
        send(msg, "out");
    }
}

void SimpleNode::handleMessage(cMessage *msg)
{
    // TODO - Generated method body

    if(strcmp(msg->getName(), "ack") == 0)
    {
        cMessage* fetch = new cMessage("fetch");
        scheduleAt(simTime()+1, fetch);
        //cancelAndDelete(msg);
    }


    else if(msg->isSelfMessage() and (strcmp(msg->getName(), "fetch") == 0))
    {
        cMessage* payload = new cMessage("Hello i am a payload");
        scheduleAt(simTime()+1, payload);
        //cancelAndDelete(msg);
    }


    else if(msg->isSelfMessage()  and (strcmp(getName(), "Sender") == 0)) //and (strcmp(msg->getName(), "fetch")!= 0)
    {
        cMessage* msgtoSend = new cMessage(msg->getName());
        send(msgtoSend, "out");
        //cancelAndDelete(msg);
    }




    else if((strcmp(msg->getName(), "fetch") != 0) and (strcmp(msg->getName(), "ack") != 0) and (strcmp(msg->getName(), "ackfetch") != 0))         //meaning any payload
    {
        EV<<"Iam here"<<endl;
        cMessage* ackmsg = new cMessage("ackfetch");
        scheduleAt(simTime()+1, ackmsg);                                                                //wait tt ack
        //cancelAndDelete(msg);
    }

    else if(msg->isSelfMessage() and (strcmp(msg->getName(), "ackfetch")== 0) and (strcmp(getName(), "Reciever") == 0))       //meaning to send the ack
    {
        EV<<"then I am here"<<endl;
        cMessage* acktoSend = new cMessage("ack");
        send(acktoSend, "out");                                                         //send the ack
        //cancelAndDelete(msg);
    }

    //cancelAndDelete(msg);
}
