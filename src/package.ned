package project;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    parameters:
        int WS = default(4);
        int TO = default(10);
        double PT = default(0.5);
        int TD = default(1);
        int ED = default(4);
        double DD = default(0.1);
        double LP = default(0.1);
//    @display("bgb=570,327");
    submodules:
        sender[2]: Sender {
            @display("p=201,150");
        }
        hub: Hub {
            @display("p=345,124");
        }
    connections:
        // sender is the NODE
        // hub is the coordinaor
        // sender.portOut --> hub.portIn;
        hub.portOut++ --> sender[0].fromCoordinator;
        hub.portOut++ --> sender[1].fromCoordinator;
        sender[0].toNode --> sender[1].fromNode;
        sender[1].toNode --> sender[0].fromNode;
}

