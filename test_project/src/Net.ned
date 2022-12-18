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
