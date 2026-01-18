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
  p2p.SetChannelAttribute ("Delay", StringValue ("1ms"));

  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");

  for (uint32_t i = 0; i < 15; i++) {
    NetDeviceContainer dev =
      p2p.Install (NodeContainer (nodes.Get(i), nodes.Get((i+1)%15)));
    ipv4.Assign (dev);
    ipv4.NewNetwork ();
  }

  MobilityHelper mobility;
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");

  Ptr<ListPositionAllocator> pos = CreateObject<ListPositionAllocator> ();
  for (uint32_t i = 0; i < 15; i++) {
    pos->Add (Vector (400 + 250*cos(2*M_PI*i/15),
                      300 + 250*sin(2*M_PI*i/15), 0));
  }

  mobility.SetPositionAllocator (pos);
  mobility.Install (nodes);

  AnimationInterface anim ("ring_15.xml");

  Simulator::Stop (Seconds (10));
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
