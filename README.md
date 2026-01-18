# NS-3 Network Topology Simulation

A comprehensive NS-3 simulation project demonstrating various network topologies including Bus, Mesh, Ring, Star, Tree, and Hybrid topologies. This project provides implementations for creating and visualizing different network topologies using NS-3 and NetAnim.

## 📋 Overview

This project contains NS-3 simulation scripts for creating and analyzing different network topologies. Each topology demonstrates unique characteristics and is suitable for understanding network architecture, connectivity patterns, and performance analysis.

## 🔗 Topologies Implemented

### 1. **Bus Topology** (`bus.cpp`)
- Creates 15 nodes connected via CSMA bus
- Uses CSMA helper with 100 Mbps data rate
- IP addresses assigned from 10.1.1.0/24 subnet
- Nodes arranged linearly (50 units apart)

### 2. **Mesh Topology** (`mesh.cpp`)
- Creates 15 nodes in a fully connected mesh
- Each node connects to all other nodes
- Uses Point-to-Point links with 10 Mbps data rate
- Nodes positioned in a 5x3 grid pattern

### 3. **Ring Topology** (`ring.cpp`)
- Creates 15 nodes in a circular ring
- Each node connects to its two neighbors
- Last node connects back to first node (closed ring)
- Uses Point-to-Point links with 5 Mbps data rate and 1ms delay
- Nodes positioned in a circle using cosine/sine calculations

### 4. **Star Topology** (`star.cpp`)
- Creates 15 nodes with one central hub (node 0)
- All other nodes connect to the hub
- Point-to-Point links with 5 Mbps data rate and 2ms delay
- Hub at center with spokes arranged in a star pattern

### 5. **Tree Topology** (`tree.cpp`)
- Creates 15 nodes in a hierarchical tree structure
- Parent-child relationships following tree structure
- Point-to-Point links with 5 Mbps data rate and 2ms delay
- Nodes arranged in a grid pattern based on tree levels

### 6. **Hybrid Topology** (`hybrid.cpp`)
- Combines Bus, Hub, and Star topologies
- 8 nodes in CSMA bus segment
- 1 central hub node
- 6 nodes in star configuration
- Demonstrates mixed topology design

## 📦 Requirements

* **NS-3**: Network Simulator 3 (version 3.30 or later recommended)
* **NetAnim**: For visualizing the network topologies
* **C++ Compiler**: GCC or Clang with C++11 support
* **Build System**: Waf (included with NS-3)

## 🚀 Installation

### 1. Install NS-3
```bash
# Download NS-3 from https://www.nsnam.org/
# Extract and build NS-3
cd ns-3.xx
./waf configure
./waf build
```

### 2. Enable Required Modules
Ensure the following NS-3 modules are enabled:
* `core-module`
* `network-module`
* `internet-module`
* `point-to-point-module`
* `csma-module`
* `mobility-module`
* `netanim-module`

### 3. Install NetAnim (optional, for visualization)
```bash
# NetAnim is typically included with NS-3
# Or download from: https://www.nsnam.org/wiki/NetAnim
```

## 💻 Usage

### Compiling the Simulations

Each topology can be compiled and run independently:

```bash
# Compile bus topology
g++ -o bus bus.cpp `pkg-config --cflags --libs ns3-dev`

# Compile mesh topology
g++ -o mesh mesh.cpp `pkg-config --cflags --libs ns3-dev`

# Compile ring topology
g++ -o ring ring.cpp `pkg-config --cflags --libs ns3-dev`

# Compile star topology
g++ -o star star.cpp `pkg-config --cflags --libs ns3-dev`

# Compile tree topology
g++ -o tree tree.cpp `pkg-config --cflags --libs ns3-dev`

# Compile hybrid topology
g++ -o hybrid hybrid.cpp `pkg-config --cflags --libs ns3-dev`
```

### Running the Simulations

```bash
# Run bus topology
./bus

# Run mesh topology
./mesh

# Run ring topology
./ring

# Run star topology
./star

# Run tree topology
./tree

# Run hybrid topology
./hybrid
```

### Using NS-3 Waf Build System

If integrated into NS-3's build system:

```bash
# Copy files to ns-3 scratch directory
cp *.cpp /path/to/ns-3/scratch/

# Build and run
cd /path/to/ns-3
./waf --run bus
./waf --run mesh
./waf --run ring
./waf --run star
./waf --run tree
./waf --run hybrid
```

## 📁 Project Structure

```
NS-3-Network-Topology-Simulation/
├── README.md                    # This file
├── bus.cpp                      # Bus topology implementation
├── bus_15.xml                   # Bus topology visualization file (generated)
├── bus.png                      # Bus topology diagram
├── mesh.cpp                     # Mesh topology implementation
├── mesh_15.xml                  # Mesh topology visualization file (generated)
├── mesh.png                     # Mesh topology diagram
├── ring.cpp                     # Ring topology implementation
├── ring.png                     # Ring topology diagram
├── star.cpp                     # Star topology implementation
├── star_15.xml                  # Star topology visualization file (generated)
├── star.png                     # Star topology diagram
├── tree.cpp                     # Tree topology implementation
├── tree_15.xml                  # Tree topology visualization file (generated)
├── tree.png                     # Tree topology diagram
├── hybrid.cpp                   # Hybrid topology implementation
├── hybrid_15.xml                # Hybrid topology visualization file (generated)
└── hybrid.png                   # Hybrid topology diagram
```

## 📊 Visualization

After running each simulation, an XML file is generated that can be opened in NetAnim:

1. **Open NetAnim**
2. **Load XML file**: File → Open → Select the generated `.xml` file
3. **View Animation**: The network topology will be displayed with nodes and links

### Generated Visualization Files:

* `bus_15.xml` - Bus topology visualization
* `mesh_15.xml` - Mesh topology visualization
* `ring_15.xml` - Ring topology visualization (generated when run)
* `star_15.xml` - Star topology visualization
* `tree_15.xml` - Tree topology visualization
* `hybrid_15.xml` - Hybrid topology visualization

## ⚙️ Configuration

### Modifying Node Count

Edit the `nodes.Create(N)` line in each file to change the number of nodes.

### Adjusting Data Rates

Modify the `SetDeviceAttribute("DataRate", ...)` line:

```cpp
p2p.SetDeviceAttribute("DataRate", StringValue("10Mbps"));  // Change value here
```

### Changing Node Positions

Modify the position calculations in the `ListPositionAllocator` section:

```cpp
pos->Add(Vector(x, y, 0));  // Adjust x, y coordinates
```

### IP Address Configuration

Modify the IP address base in each file:

```cpp
ipv4.SetBase("10.1.1.0", "255.255.255.0");  // Change network address
```

## 📚 Additional Resources

* [NS-3 Documentation](https://www.nsnam.org/documentation/)
* [NetAnim User Guide](https://www.nsnam.org/wiki/NetAnim)
* [NS-3 Tutorial](https://www.nsnam.org/docs/tutorial/html/)

## 📝 Notes

* XML files are generated automatically when simulations run
* All simulations use constant position mobility models (static nodes)
* The bus topology uses CSMA while others use Point-to-Point links
* The hybrid topology demonstrates a combination of multiple topology types
* All simulations run for 10 seconds by default

## 🤝 Contributing

Feel free to extend this project by:

* Adding more topologies (mesh-star, hierarchical star, etc.)
* Implementing dynamic routing protocols
* Adding traffic generation and analysis
* Creating comparison metrics between topologies
* Adding performance analysis tools

## 📄 License

This project is provided for educational purposes. Please refer to NS-3's licensing terms for commercial use.

---

**Author**: Network Simulation Project  
**Purpose**: Educational demonstration of network topologies in NS-3  
**Last Updated**: 2025