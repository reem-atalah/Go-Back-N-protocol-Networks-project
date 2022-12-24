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

package project;

//
// TODO auto-generated module
//
simple Sender
{
    parameters:

        int N=10; // number of messages
//      int timer[]; //timer for each message
        double interval= exponential(2.0);


     gates:
        input  fromCoordinator @loose;
        input  fromNode @loose;
        output toNode @loose;
        // input portIn @loose;
        // output portOut @loose;
}
