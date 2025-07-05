# Ft_malcolm

[![en](https://img.shields.io/badge/Langue-en-red)](README.md)

<!-- $$\color{darkgreen}{{\Huge \mathbf {125/100 ✅}}}$$ -->

## L'Objectif

Developper une virus de type "Man in the Middle"  qui intercepter les paquets ARP.

Le programme doit attendre qu'une requête ARP soit envoyer sur le réseaux et repondre avec un packet ARP avec une fausse adresse MAC.

**Ce programme utilse des socket brute pour intercepter les paquets ARP donc vous devez avec voir les droits administrateur**

## Exigence

Tout d'abord, vous devez avoir 2 Machine Virtuelle qui sont connecter sur le meme reseaux (NAT ou Host-Only).

Pour tester le programme, je recommande d'installer, sur la VM victime, une veille version de linux (Debian 7), sinon le noyau Linux risque de corriger automatiquement la table ARP au bout d'un certain temps.

## Execution

Ce projet contient un `Makefile`.
Il compile chaque ficheir dans le dossier et produit un executable.
Le programme doit être executé comme suit :
````sh
sudo ./ft_malcolm source_ip source_mac target_ip target_mac [interface]
````

$\color{red}{\large {\mathbf {⚠⚠\ Vous\ devez\ avoir\ les\ droits\ administrateur\ pour\ executer\ le\ programme\ ⚠⚠}}}$

**Guide pas à pas :**
1. Démarrez les 2 Machines Virtuelle et noter leurs adresse IP
2. Sur la VM victime, effacer la table ARP de la seconde VM (d'où le programme sera lancé)
````sh
arp -d ip_address
````
3. Lancez le programme sur les 2ème VM, **source** est les VM d'où `ft_malcolm` est lancé & **target** est la VM victim.
4. Verifiez le résultat avec le commande `arp` sur la VM victime

**Commande pratique pour le trafic des paquets ARP :**
````sh
sudo tcpdump -i [interface_name] arp
````

## Bonus

**Ce projet contient quelque Bonus :**
- Le programme gère la resolution DNS.
Vous pouvez mettre soit les adresses IP (`172.30.78.23`) ou les adresses DNS (`vbox.user`) de la Machine Virtuelle.
- A la fin de la commande pour lancer le programme, vous pouvez ajouter le nom de l'interface réseaux où vous voulez écouter et envoyer les paquets ARP (`eth0`).
Si aucune interface est préciser, alors le pogramme choisie automatiquement l'interface par défault.

**This project have few bonuses :**
- The program also handle the DNS resolution.
You can put either ip addresses  or DNS addresses of the Virtual Machine .
- You can add at the end of the program, the name of the network interface where you want to listen and send the ARP Packet (`eth0`)
If you doesn't put the interface, the program auto select the default interface