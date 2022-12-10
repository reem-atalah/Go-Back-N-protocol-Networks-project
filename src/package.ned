package project;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    parameters:
        int WS = default(5);
        int TO = default(10);
        double PT = default(0.5);
        int TD = default(1);
        int ED = default(4);
        double DD = default(0.1);
//    @display("bgb=570,327");
    submodules:
        sender: Sender {
            @display("p=201,150");
        }
        hub: Hub {
            @display("p=345,124");
        }
    connections:
        sender.portOut --> hub.portIn;
        hub.portOut --> sender.portIn;
}

