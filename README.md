# Ft_malcolm

[![fr](https://img.shields.io/badge/Langue-fr-blue)](README.fr.md)

<!-- $$\color{darkgreen}{{\Huge \mathbf {125/100 ✅}}}$$ -->

## The goal

Develops a Man In Middle attack who intercept ARP packet.

The program must wait an ARP Request send on the broadcast and response an ARP packet with spoofed MAC address.

**This program need to use raw socket to intercept ARP Packet so you must have root right !**

## Requirement

First of all you need to setup 2 Virtual Machine who are both connected on the same network (NAT network or Host-Only).

To test the program, I recommend to install an old linux version (Debian 7) on the victim VM, otherwise, the Linux kernel may correct the ARP Table after a while.

## Execution

This project contain a `Makefile`.
It compile each file in `src/` directory and it produce a executable.
The executable must be executed as follow :
````sh
sudo ./ft_malcolm source_ip source_mac target_ip target_mac [interface]
````

$\color{red}{\large {\mathbf {⚠⚠\ You\ need\ to\ have\ root\ right\ to\ run\ the\ program\ ⚠⚠}}}$

**Step by Step guide :**
1. Launch 2 Virtual Machine & check their IP Adresse
2. On the victim VM, erase the arp table of the second VM (where the program while be launch)
````sh
arp -d ip_address
````
3. Start the program on the second virtual machine, **source** is VM where you launch `ft_malcolm` & **target** is the victim VM
4. See the result with `arp` command ont the victim VM

**Useful command to see arp packet trafic :**
````sh
sudo tcpdump -i [interface_name] arp
````

## Bonuses

**This project have few bonuses :**
- The program handle the DNS resolution
You can put either IP addresses (`172.30.78.23`) or DNS addresses (`vbox.user`) of the Virtual Machine.
- You can add, at the end of command for launch the program, the name of the network interface where you want to listen and send the ARP Packet (`eth0`).
If you doesn't put the interface, the program auto select the default interface.