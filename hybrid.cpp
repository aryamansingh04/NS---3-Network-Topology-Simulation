#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/csma-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/mobility-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main () {

  // 1. Create nodes
  NodeContainer bus;
  bus.Create (8);

  NodeContainer hub;
  hub.Create (1);

  NodeContainer star;
  star.Create (6);

  // 2. Install Internet stack
  InternetStackHelper internet;
  internet.Install (bus);
  internet.Install (hub);
  internet.Install (star);

  // 3. BUS (CSMA)
  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

  NetDeviceContainer busDevices = csma.Install (bus);

  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  ipv4.Assign (busDevices);

  // 4. HUB ↔ BUS (Point-to-Point)
  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

  for (uint32_t i = 0; i < bus.GetN (); i++) {
    NetDeviceContainer dev =
      p2p.Install (NodeContainer (hub.Get (0), bus.Get (i)));
    ipv4.NewNetwork ();
    ipv4.Assign (dev);
  }

  // 5. HUB ↔ STAR (Point-to-Point)
  for (uint32_t i = 0; i < star.GetN (); i++) {
    NetDeviceContainer dev =
      p2p.Install (NodeContainer (hub.Get (0), star.Get (i)));
    ipv4.NewNetwork ();
    ipv4.Assign (dev);
  }

  // 6. Mobility (CRITICAL for NetAnim)
  MobilityHelper mobility;
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");

  Ptr<ListPositionAllocator> pos =
    CreateObject<ListPositionAllocator> ();

  // Bus node positions
  for (uint32_t i = 0; i < bus.GetN (); i++)
    pos->Add (Vector (60*i, 200, 0));

  // Hub position
  pos->Add (Vector (240, 350, 0));

  // Star node positions
  for (uint32_t i = 0; i < star.GetN (); i++)
    pos->Add (Vector (240 + 180*cos(2*M_PI*i/star.GetN()),
                      350 + 180*sin(2*M_PI*i/star.GetN()),
                      0));

  mobility.SetPositionAllocator (pos);
  mobility.Install (NodeContainer (bus, hub, star));

  // 7. NetAnim output
  AnimationInterface anim ("hybrid_15.xml");

  // 8. Run simulation
  Simulator::Stop (Seconds (10));
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
