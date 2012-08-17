#!/bin/sh

route del default;
route add default gw 192.168.1.245;
route -n;
