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



//
//
//package test_project;
//
//@license(LGPL);
////
//// TODO documentation
////
//network Network
//{
//    parameters:
//        int WS;
//        int TO;
//        double PT;
//        double TD;
//        double ED;
//        double DD;
//        double LP;
//    submodules:
//        coordinator: Coordinator {
//            @display("p=174,175");
//        }
//        node0: Node {
//            @display("p=275,92");
//        }
//        node1: Node {
//            @display("p=65,92");
//        }
//    connections:
//        node0.out --> node1.in_node;
//        node1.out --> node0.in_node;
//        coordinator.out_node0 --> node0.in_coordinator;
//        coordinator.out_node1 --> node1.in_coordinator;
//}
//
//





package test_project;

network Net
{
    @display("bgb=765,269");
    submodules:
        Sender: SimpleNode {
            @display("p=90,79");
        }
        Reciever: SimpleNode {
            @display("p=451,85");
        }
    connections:
        Sender.out --> Reciever.in;
        Reciever.out --> Sender.in;
}
