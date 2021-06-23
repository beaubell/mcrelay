# Building
## Fedora Linux
### Preparing for Development
`sudo dnf group install "C Development Tools and Libraries"`

`sudo dnf install cmake boost-devel dpkg`

### Building
```
#From source dir
mkdir build
cd build
cmake ../
make

#Make RPM Package
cpack -G RPM

#Make Debian Package
cpack -G DEB
```

# Installing
## RPM Based distro (Fedora/Redhat/Centos)
`sudo dnf install ./mcrelay-*.rpm`

# Running
## Setting Up
Create a file in `/etc/mcrelay` with the filename format like `mcrelay@whateveryouwant` (ex. `mcrelay@COTSAtoMTOC1`) and contents like
```
LISTEN_ADDRESS=0.0.0.0
MULTICAST_ADDRESS=239.2.3.1
MULTICAST_PORT=6969
LISTEN_PORT=10000
REMOTE_UDP_ADDRESS=192.168.1.20
REMOTE_UDP_PORT=10000
```

Each Multicast to Unicast pair requires a separate configuration file and operates like a separate service.

## Starting MCRelay service
using systemctl, start the service using the filename that you used in the setup phase.

Ex. `sudo systemctl start mcrelay@COTSAtoMTOC1`

Use `enable` to have the service start on boot.
Ex. `sudo systemctl enable mcrelay@COTSAtoMTOC1`

# Troubleshooting
Check

- Connectivity between the local and destination networks
- Firewall settings
- Port forwarding setttings at your NAT/firewall
- Routes for multicast (multicast will use route tables to determine the default in/out interface)
