#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/mobility-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main () {

  NodeContainer nodes;
  nodes.Create (15);

  InternetStackHelper internet;
  internet.Install (nodes);

  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");

  auto link = [&](int a, int b) {
    NetDeviceContainer dev = p2p.Install (NodeContainer (nodes.Get(a), nodes.Get(b)));
    ipv4.Assign (dev);
    ipv4.NewNetwork ();
  };

  link(0,1); link(0,2);
  link(1,3); link(1,4);
  link(2,5); link(2,6);
  link(3,7); link(3,8);
  link(4,9); link(4,10);
  link(5,11); link(5,12);
  link(6,13); link(6,14);

  MobilityHelper mobility;
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");

  Ptr<ListPositionAllocator> pos = CreateObject<ListPositionAllocator> ();
  for (uint32_t i = 0; i < 15; i++)
    pos->Add (Vector (100*(i%4), 120*(i/4), 0));

  mobility.SetPositionAllocator (pos);
  mobility.Install (nodes);

  AnimationInterface anim ("tree_15.xml");

  Simulator::Stop (Seconds (10));
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
