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

#include "node.h"
#include <bitset>
#include <vector>

Define_Module(Node);

void Node::initialize()
{
    // TODO - Generated method body



    if(strcmp(getName(), "sender") == 0)
    {


        std::string mes = "0000 begin";                        //from the end user



            std::string errorType;
            for (int i = 0 ; i <=3; i++)
            {
                errorType += mes[i];
            }



            std::bitset<8> parity(0);


            std::string SENTBITS;







            for(int i = 5 ; i < mes.size(); i++)
            {
                parity = parity ^ std::bitset<8>(mes[i]);
                std::bitset<8> bitss (mes[i]);

                SENTBITS += bitss.to_string();
                EV<<mes[i]<<" is converted to "<<bitss.to_string()<<endl;

                EV<<"message of bits is now "<<SENTBITS<<endl;
            }
            SENTBITS+=parity.to_string();

            std::cout<<"string: "<<mes<<" will be sent as: "<<SENTBITS<<endl;
            EV<<"message of bits is now "<<SENTBITS<<endl;
            EV<<"I am "<< getName()<<endl;




        cMessage * msg = new cMessage(SENTBITS.c_str());
        send(msg, "out");

        cMessage * timeOutmsg = new cMessage("TimeOut");
        scheduleAt(simTime() + par("Timeout"),timeOutmsg);
    }
}

void Node::handleMessage(cMessage *msg)
{
    // TODO - Generated method body




    if(msg->isSelfMessage() && strcmp(msg->getName(), "TimeOut") == 0)          //if(msg->isSelfMessage() && strcmp(msg->getName(),"TO")==0)
    {
        //ack is lost in the way
        EV<<"ACK IS LOST and TIMEOUT"<<endl;
        std::cout<<"Iam here when ack is lost"<<endl;
        cancelAndDelete(msg);
    }


    if(strcmp(msg->getName(), "ack")==0)
    {
        std::cout<<"Iam here when i am sending another mesage"<<endl;
        cancelAndDelete(msg);
        cMessage * TTmes = new cMessage("Fetch");
        scheduleAt(simTime()+par("TT"), TTmes);
        cancelAndDelete(msg);
    }







    if( (strcmp(msg->getName(), "Fetch" )==0) && strcmp(getName(), "sender") == 0 )     //else if( (strcmp(msg->getName(), "ack" )==0 || strcmp(msg->getName(), "dummymsg") ==0) && strcmp(getName(), "sender") == 0 )
    {

        //EV<<"message is sent successfully and recieved the ack"<<endl;



        std::string mes1 = "0000 Hello";                        //from the end user
        std::string mes2 = "0001 HelloDElayed";                        //from the end user
        //std::string mes3 = "1000 Hellomodified";                        //from the end user
        std::string mes4 = "0100 Hello";                        //from the end user
        std::string mes5 = "0010 HelloDUP";                        //from the end user
        std::string mes6 = "0000 Hello FINAL";                        //from the end user

        std::vector<std::string> vector_of_messages;
        vector_of_messages.push_back(mes1);
        vector_of_messages.push_back(mes2);
        //vector_of_messages.push_back(mes3);
        vector_of_messages.push_back(mes4);
        vector_of_messages.push_back(mes5);
        vector_of_messages.push_back(mes6);

        std::string mes = vector_of_messages[CurrentMessageNumber];                             //I WANT A GLOBAL VARIABLE
        CurrentMessageNumber++;
        EV<<"ITERATION "<<CurrentMessageNumber<<endl;
        //std::string mes = "0000 hello";


        std::string errorType;
        for (int i = 0 ; i <=3; i++)
        {
            errorType += mes[i];
        }



        std::bitset<8> parity(0);
        std::vector<std::string> stringmessage;

        std::string SENTBITS;

        for(int i = 5 ; i < mes.size(); i++)
            {
                parity = parity ^ std::bitset<8>(mes[i]);
                std::bitset<8> bitss (mes[i]);
                stringmessage.push_back(bitss.to_string());
                SENTBITS += bitss.to_string();
                EV<<mes[i]<<" is converted to "<<bitss.to_string()<<endl;

                EV<<"message of bits is now "<<SENTBITS<<endl;
            }
         SENTBITS+=parity.to_string();




        if(errorType[1] == '1')
        {
            //delay some tt and dont send
            cMessage * dummymsg = new cMessage("Fetch");
            scheduleAt(simTime()+ par("TT"), dummymsg);
        }
        else
        {
            if(errorType[3] == '1')               //modification
            {
                int errorLocation = uniform(0, (mes.size() - 5)* 8 + 8);
                int errorprob = uniform(0,2);
                if(errorprob == 1)
                {
                    SENTBITS[errorLocation] = int(!(bool(SENTBITS[errorLocation])));
                    EV<<"I am sender, the sent message is modified to "<<SENTBITS<<endl;
                }

                cMessage * msg = new cMessage(SENTBITS.c_str());
                send(msg, "out");
                cMessage * timeOutmsg = new cMessage("TimeOut");
                scheduleAt(simTime() + par("Timeout"),timeOutmsg);


            }
            if(errorType[2] == '1')                             //duplication
            {

                cMessage * msg = new cMessage(SENTBITS.c_str());
                send(msg, "out");
                cMessage * timeOutmsg = new cMessage("TimeOut");
                scheduleAt(simTime() + par("Timeout"),timeOutmsg);


            }
            if(errorType[3] == '1')                             //delay
            {
                //delay 5sec then send, do it with scheduleAt()
                cMessage * msg = new cMessage(SENTBITS.c_str());
                cMessage * timeOutmsg = new cMessage("TimeOut");
                //scheduleAt(simTime()+par("Delay"), msg);
                send(msg, "out");
                scheduleAt(simTime() + par("Timeout"),timeOutmsg);
            }
            if(errorType== "0000")
            {
                cMessage * timeOutmsg = new cMessage("TimeOut");
                cMessage * msg = new cMessage(SENTBITS.c_str());
                //scheduleAt(simTime()+par("TT"), msg);
                send(msg, "out");
                scheduleAt(simTime() + par("Timeout"),timeOutmsg);
            }
        }
        //cancelAndDelete(msg);






    }




    //reciever code
    else
    {
        std::string temp;
        std::string paritytemp;
        bool corruptionflag = false;
        std::bitset<8> paritybits(0);
        std::string finalMsg;


        //for (int i = 0 ; i < std::strlen(msg->getName()); i++)
        //{
        //    std::bitset<8> tempbits (msg->getName()[i]);
        //    finalMsg += (char)tempbits.to_ulong();

        //}

        //EV<<"After decoding: "<<std::string(recvec.data(), recvec.size())<<endl;



        for (int i = 0 ; i <= std::strlen(msg->getName()); i++)
        {
            if(std::strlen(msg->getName()) - i > 8)
            {
                temp += msg->getName()[i];
                //get payload
                if(i%8 == 7)
                {
                    EV<<"decoding a char"<<endl;
                    std::bitset<8> str8bits (temp);
                    EV<<"current i is "<<i<<endl;
                    EV<<str8bits.to_ulong()<<endl;
                    finalMsg+=(char)str8bits.to_ulong();
                    temp.clear();
                }
            }

            //if(i != std::strlen(msg->getName())) temp += msg->getName()[i];


            //get the last 8 bits
            else
            {
                paritytemp += msg->getName()[i];
            }


        }

        std::bitset<8> parity(paritytemp);


        //loop on the entire message to check parity
        for(int i = 0 ; i < finalMsg.size(); i++)
        {
            paritybits = paritybits ^ std::bitset<8>(finalMsg[i]);
        }



        //std::bitset<8> paritycheck(paritybits ^ parity);


        if(std::bitset<8>(paritybits ^ parity).to_ulong() != 0)
        {
            corruptionflag = true;
            EV<<"!!! Message is corrupted "<<"I recieved a message of : "<<msg->getName()<<endl;
            EV<<"After decoding: '"<<finalMsg<<"'"<<endl;
        }

        else
        {
            EV<<"CORRECT I recieved a message of : "<<msg->getName()<<endl;
            EV<<"After decoding: '"<<finalMsg<<"'"<<endl;
        }


        int acklossprop = 0;//uniform(0, 2);
        if(acklossprop == 0)
        {
            cMessage *ackmsg = new cMessage("ack");
            send(ackmsg, "out");
        }
        else
        {
            //wait for some tt and dont send
        }


    }
    cancelAndDelete (msg);

}


