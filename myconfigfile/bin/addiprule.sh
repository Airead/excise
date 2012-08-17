#!/bin/sh

sudo ip rule add to 61.135.169.125 lookup bai
sudo ip rule add to 61.135.169.105 lookup bai
sudo ip route add default via 192.168.1.245 table bai
sudo ip route add 192.168.1.0/24 dev eth0 table bai
sudo ip route show table bai

