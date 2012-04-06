#!/bin/bash

echo nameserver 192.168.0.1 > /tmp/resolv.conf
sudo cp /tmp/resolv.conf /etc
sudo ifconfig eth0 up
sudo ifconfig eth0 192.168.0.166 netmask 255.255.255.0
sudo route add default gw 192.168.0.1
