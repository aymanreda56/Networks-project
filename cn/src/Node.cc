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

#include "Node.h"
#include "CoordinatorMsg_m.h"
#include "NodeMsg_m.h"
#include <fstream>
#include <bitset>
#include<sstream>
Define_Module(Node);

void Node::initialize()
{
    // TODO - Generated method body
    // TODO initial parameters in .ini and package.ned or node.ned????
    this->WS = getParentModule()->par("WS");//.intValue();
    this->TO = getParentModule()->par("TO");//.intValue();
    this->PT = getParentModule()->par("PT");//.doubleValue();
    this->TD = getParentModule()->par("TD");//.doubleValue();
    this->ED = getParentModule()->par("ED");//.doubleValue();
    this->DD = getParentModule()->par("DD");//.doubleValue();
    this->LP = getParentModule()->par("LP");//.doubleValue();
    this->logFile.open("D:\\omnetpp-6.0.1\\samples\\cn\\src\\log_"+std::string(getName())+".txt", std::ios_base::app);


//    std::stringstream ss;
//    ss<<"hello i am testing the log file"<<endl;
//
//    EV<<ss.str();
//    this->logFile<<ss.str();
}

void Node::handleMessage(cMessage *msg)
{
    std::stringstream ss;

    // TODO - Generated method body
    ss << "handle message from " << getName()<<" SF: "<< this->SF<<" SL: "<<this->SL<<" cur = "<<this->currentMsgToSend<<endl;
    EV<<ss.str();
    ss = std::stringstream();

    // if the message is from the coordinator
    if(dynamic_cast<CoordinatorMsg_Base*>(msg)!=nullptr){
        CoordinatorMsg_Base* coordinator_msg = check_and_cast<CoordinatorMsg_Base*>(msg);
        this->isSender = true;
        this->startingTime = coordinator_msg->getStartTime();

        this->nodeNumber = coordinator_msg->getStartingNode();
        // Read file and store it in vector
        std::string fileName = this->nodeNumber==0?"D:\\omnetpp-6.0.1\\samples\\cn\\src\\input0.txt":"D:\\omnetpp-6.0.1\\samples\\cn\\src\\input1.txt";
        std::ifstream inputFile(fileName);
        std::string line = "";
        while(getline(inputFile, line)){
            std::string msgType = line.substr(0, 4); //0011 for example
            std::string msgStr = line.substr(5, line.size() - 5); // rest of the line
            this->messageErrors.push_back(msgType);
            this->messages.push_back(msgStr);
        }

        cMessage* new_msg = new cMessage("considerNext"); // consider
        // TODO: time in seconds??
        scheduleAt(simTime()+this->startingTime, new_msg);

        // window parameters
        this->SF = 0; // first pointer in the window
        this->SL = WS - 1; // last pointer in the window
        return;
    }
    // sender
    if(isSender){
        // possible self-messages names:
        // considerNext: gets a message from vector, applies framing, error to it and schedule sending it after delay
        //, send: send to other node and increment currentMsgToSend
        //, timeout: start re-sending messages from SF
        //, ACK/NACK
        // TODO create custom message for these types??
        // TODO cast instead of checking on name
        if(std::string(msg->getName())=="considerNext"){
            int cur = this->currentMsgToSend;
            if(cur>=messages.size() || cur > this->SL){
//                EV<<"Current message index is wrong(> #messages"<<endl;
                return;
            }
            std::string currentMessage = this->messages[cur];
            std::string errors = this->messageErrors[cur];

            ss << "At time "
                    <<simTime()// - this->startingTime
                    <<getName()
                    <<" Introduced channel error with code "
                    << errors <<endl;
            EV<<ss.str();
//            this->logFile.open("D:\\omnetpp-6.0.1\\samples\\cn\\src\\log_"+std::string(getName())+".txt", std::ios_base::app);
            this->logFile<<ss.str();
            ss = std::stringstream();
            NodeMsg* new_msg = new NodeMsg("send");
            std::string msg_payload = "";

            // **TODO MAKE THEM SEPERATE FIELDS IN THE MESSAGE INSTEAD OF IN THE STRING ***********/
            // Header = Seq_Num
            // TODO should it be cyclic??
            new_msg->setSeq_num(cur);

            // Starting Flag
            msg_payload+='$';

            // Payload & Parity byte
            std::bitset<8> parityByte(0);
            for(int i = 0; i < currentMessage.size(); i++){
                parityByte^=std::bitset<8>(currentMessage[i]);
                if(currentMessage[i] == '$' || currentMessage[i] == '/'){
                    msg_payload+='/';
                    parityByte^=std::bitset<8>('/');
                }
                msg_payload+=currentMessage[i];
            }
            // Finishing Flag
            msg_payload+='$';


            // Parity Byte
            new_msg->setParityByte(char(parityByte.to_ulong()));

            // Frame type = Data = 0
            new_msg->setMessageType(0);

            // Ack/Nack Number = 0??? (DATA)
            new_msg->setAck_num(0);

            // Calculate Exact time to send the message and schedule it to be sent

            auto sendingTime = simTime();
            sendingTime+=this->PT;
            sendingTime+=this->TD;

            // TODO add error delay, duplicate & duplication delay, etc.
            bool isLost = false;
            bool isDuplicated = false;
            bool isDelayed = false;
            int modifiedBitNumber = -1;
            if(this->currentMsgToSend!=this->timedoutMsgIndex){
                // errors+delays: update sendingTime, msg_payload
                // seems like loss should be in =="send"
                // if message is lost:
                if(errors[1] == '1'){
                    isLost = true;
                }
 //               else{
                    // delay error
                    if(errors[3] == '1'){
                        sendingTime+=this->ED;
                        isDelayed = true;
                    }
                    // modification
                    if(errors[0] == '1')
                    {
//                        EV<<"before mod: "<<msg_payload<<endl;
                        int locationOfError_bits = uniform(0, msg_payload.size()*8);
                        modifiedBitNumber = locationOfError_bits;
//                        EV<<"i will modify this bit: "<<locationOfError_bits<<endl;
                        int locationOfError_char = int(locationOfError_bits/8);
//                        EV<<"i will modify this index: "<<locationOfError_char<<endl;
                        char errchar = msg_payload[locationOfError_char];
//                        EV<<"i will modify this char: "<<errchar<<endl;
                        std::bitset <8> charinBits (errchar);
                        std::string charincharbits = charinBits.to_string();
                        int locationOfError = (locationOfError_bits%8);
//                        EV<<charinBits.to_string()[locationOfError]<<endl;
                        if(charinBits.to_string()[locationOfError] == '1')
                        {
                            charincharbits[locationOfError] = '0';
                        }
                        else
                        {
//                            EV<<"hello lol ol o"<<endl;
                            charincharbits[locationOfError] = '1';
                        }
//                        EV<<charincharbits[locationOfError]<<endl;
                        std::bitset<8> charinbitsafter (charincharbits);

                        msg_payload[locationOfError_char] = (char)charinbitsafter.to_ulong();
//                        EV<<"after mod: "<<msg_payload<<endl;
//                        cMessage* payloadmsg = new cMessage(payload.c_str());
//                        scheduleAt(simTime()+par("tt").intValue(), payloadmsg);

                    }
                    if(errors[2] == '1'){
                        isDuplicated = true;
                    }

 //               }
            }
            else{
                this->timedoutMsgIndex = -1; // reset
            }
            new_msg->setPayload(msg_payload.c_str());
            ss <<"At time "
                    <<simTime() + this->PT
                    <<" "<<getName()
                    <<" sent frame with seq_num="
                    <<new_msg->getSeq_num() % this->WS
                    <<" and payload= "
                    <<new_msg->getPayload()
                    <<" and trailer = "
                    <<std::bitset<8>(new_msg->getParityByte())
                    <<", Modified " << modifiedBitNumber
                    <<", lost " << (isLost?"Yes":"No")
                    <<", Duplicate " << (isDuplicated?"1":"0")
                    <<", Delay "<<(isDelayed?this->ED:0)
                    <<endl;
            EV<<ss.str();
//            this->logFile.open("D:\\omnetpp-6.0.1\\samples\\cn\\src\\log_"+std::string(getName())+".txt", std::ios_base::app);
            this->logFile<<ss.str();
            ss = std::stringstream();

            if(!isLost){
                // "send"

                scheduleAt(sendingTime, new_msg);
                if(isDuplicated){
                    scheduleAt(sendingTime+this->DD, new_msg->dup());
                    ss <<"At time "
                            // TODO Not good
                            <<simTime()+this->DD  + this->PT
                            <<" "<<getName()
                            <<" sent frame with seq_num="
                            <<new_msg->getSeq_num() % this->WS
                            <<" and payload= "
                            <<new_msg->getPayload()
                            <<" and trailer = "
                            <<std::bitset<8>(new_msg->getParityByte())
                            <<", Modified " << modifiedBitNumber
                            <<", lost " << (isLost?"Yes":"No")
                            <<", Duplicate 2 "
                            <<", Delay "<<(isDelayed?this->ED:0)
                            <<endl;
                    EV<<ss.str();
//                    this->logFile.open("D:\\omnetpp-6.0.1\\samples\\cn\\src\\log_"+std::string(getName())+".txt", std::ios_base::app);
                    this->logFile<<ss.str();
                    ss = std::stringstream();
                }
            }

            // start timer for timeout
            NodeMsg* new_msg_for_timeout = new_msg->dup();
            new_msg_for_timeout->setName("timeout");
            // todo simTime() instead of sending time?
            scheduleAt(simTime()+this->PT+this->TO, new_msg_for_timeout);

            this->currentMsgToSend++;
            // TODO Should we do the window in a for loop instead of this????
            if(this->currentMsgToSend<=SL && this->currentMsgToSend < this->messages.size()){
                // self message to consider next message
                cMessage* new_msg_2 = new cMessage("considerNext");

                scheduleAt(simTime()+this->PT, new_msg_2);
            }


        }
        // after the delay
        else if(std::string(msg->getName())=="send"){

            NodeMsg*new_msg = check_and_cast<NodeMsg*>(msg);
            send(new_msg, "out");

        }
        else if(std::string(msg->getName())=="timeout"){
            NodeMsg*new_msg = check_and_cast<NodeMsg*>(msg);

            // XXXXX How to send all again except for the corrupted one: send it without error? XXX
            // if it is in window and received timeout: reschedule it
            int badMsgIndex = new_msg->getSeq_num();
            if(this->timeoutHappened){
                return;
            }
            if(badMsgIndex>=this->SF){
                this->timeoutHappened = true;
                ss<<"Time out event at time "
                        <<simTime()
                        <<", at "<<getName()
                        <<" for frame with seq_num="
                        <<badMsgIndex % this->WS<<endl;

                EV<<ss.str();
//                this->logFile.open("D:\\omnetpp-6.0.1\\samples\\cn\\src\\log_"+std::string(getName())+".txt", std::ios_base::app);
                this->logFile<<ss.str();
                ss = std::stringstream();

                cMessage*resendMsg = new cMessage("considerNext");
                this->timedoutMsgIndex = badMsgIndex;
                this->currentMsgToSend = SF;
                scheduleAt(simTime(), resendMsg);
            }
        }
        // came from receiver should check ack from msg->msgType
        else if(std::string(msg->getName())=="ack"){
            NodeMsg*new_msg = check_and_cast<NodeMsg*>(msg);
            ss << "Sender received ack with acknum = "<<new_msg->getAck_num() << " and curmsgtosend = "<<this->currentMsgToSend<<endl;
            EV<<ss.str();
//            this->logFile.open("D:\\omnetpp-6.0.1\\samples\\cn\\src\\log_"+std::string(getName())+".txt", std::ios_base::app);
            this->logFile<<ss.str();
            ss = std::stringstream();

//            if(new_msg->getAck_num()==this->currentMsgToSend+1){
            // XXXXX what if ack not in order?? XXXX
            if(new_msg->getAck_num()==this->SF+1){
                this->SF++;
                if(SL+1<this->messages.size()){
                    this->SL++;
                }
                this->timeoutHappened = false;
//                this->currentMsgToSend++;
                scheduleAt(simTime(), new cMessage("considerNext"));
            }

        }
    }
    // receiver
    else{
        NodeMsg* received_msg = check_and_cast<NodeMsg*>(msg);
        // after PT: start sending
        bool isLost = false;
        if(std::string(received_msg->getName())=="ack"){
            // Probability of ack LOSS
            double prob = uniform(0, 1);

            if(prob <= this->LP)
            {
                isLost = true;
            }
            else{
                sendDelayed(received_msg, this->TD, "out");
            }
            ss <<"At time "
                    <<simTime()<<' '
                    <<getName()<<' '
                    <<"Sending Ack with number "
                    << received_msg->getAck_num() % this->WS
                    <<", loss = "<<(isLost?"Yes":"No")<<endl;
            EV<<ss.str();
//            this->logFile.open("D:\\omnetpp-6.0.1\\samples\\cn\\src\\log_"+std::string(getName())+".txt", std::ios_base::app);
            this->logFile<<ss.str();
            ss = std::stringstream();

            return;
        }


       // bool errorExists = false;
        // check for error and send nack and return

        std::string checkrecMes = std::string(received_msg->getPayload());
        std::bitset<8> recParity(0);
        for (int i = 0 ; i < checkrecMes.size(); i++)
        {
            recParity = recParity^std::bitset<8>(checkrecMes[i]);
        }

        if(received_msg->getParityByte() != recParity.to_ulong())             //detected errors
        {
//            ss <<"At time "
//                           <<simTime()
//                           <<" "<<getName()
//                           <<" received frame with seq_num="
//                           <<received_msg->getSeq_num() % this->WS
//                           <<" and payload= "
//                           <<received_msg->getPayload()
//                           <<" and trailer = "
//                           <<std::bitset<8>(received_msg->getParityByte())
//                           // TODO : how to do the following???
//                           // maybe will need to make error delay and loss and TD here and use sendDelayed?
//                           <<", Modified 1 "
//                           <<", lost ? "
//                           <<", Duplicate ? "
//                           <<", Delay ?"<<endl;
//            EV<<ss.str();
////            this->logFile.open("D:\\omnetpp-6.0.1\\samples\\cn\\src\\log_"+std::string(getName())+".txt", std::ios_base::app);
//            this->logFile<<ss.str();
//            ss = std::stringstream();
            NodeMsg* new_msg = new NodeMsg("nack");
            new_msg->setAck_num(this->R); // TODO is this true?
            new_msg->setMessageType(2); // ack



            double prob = uniform(0, 1);
            if(prob <= this->LP)
            {
                isLost = true;
            }
            else{
                sendDelayed(new_msg, this->PT+this->TD, "out");
            }



            ss <<"At time "
            <<simTime() + this->PT<<' '
            <<getName()<<' '
            <<"Sending Nack with number "
            << received_msg->getAck_num() % this->WS
            <<", loss = "<<(isLost?"Yes":"No")<<endl;
            EV<<ss.str();
//            this->logFile.open("D:\\omnetpp-6.0.1\\samples\\cn\\src\\log_"+std::string(getName())+".txt", std::ios_base::app);
            this->logFile<<ss.str();

            ss = std::stringstream();

            return;
                       //scheduleAt(simTime()+(this->PT), new_msg);

        }

//        ss <<"At time "
//                <<simTime()
//                <<" "<<getName()
//                <<" received frame with seq_num="
//                <<received_msg->getSeq_num() % this->WS
//                <<" and payload= "
//                <<received_msg->getPayload()
//                <<" and trailer = "
//                <<std::bitset<8>(received_msg->getParityByte())
//                // TODO : how to do the following???
//                // maybe will need to make error delay and loss and TD here and use sendDelayed?
//                <<", Modified -1 "
//                <<", lost ? "
//                <<", Duplicate ? "
//                <<", Delay ?"<<endl;
//        EV<<ss.str();
////        this->logFile.open("D:\\omnetpp-6.0.1\\samples\\cn\\src\\log_"+std::string(getName())+".txt", std::ios_base::app);
//        this->logFile<<ss.str();
//        ss = std::stringstream();

        // send ack
        if(received_msg->getSeq_num()==this->R){
            NodeMsg* new_msg = new NodeMsg("ack");

            this->R++;
            new_msg->setAck_num(this->R); // TODO is this true?
            new_msg->setMessageType(1); // ack
            scheduleAt(simTime()+(this->PT), new_msg);
        }

    }

}
