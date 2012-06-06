#!/bin/bash  
alias ifconfig="/sbin/ifconfig"  
eth=eth0  
while true; do  
RXpre=$(ifconfig ${eth} | grep bytes | awk '{print $2}'| awk -F":" '{print $2}')  
TXpre=$(ifconfig ${eth} | grep bytes | awk '{print $6}' | awk -F":" '{print $2}')  
sleep 1  
RXnext=$(ifconfig ${eth} | grep bytes | awk '{print $2}'| awk -F":" '{print $2}')  
TXnext=$(ifconfig ${eth} | grep bytes | awk '{print $6}' | awk -F":" '{print $2}')  
echo RX ----- TX  
echo "$((($($RXnext-$RXpre)/1024)/1024))MB/s $((($($TXnext-$TXpre)/1024/1024)))MB/s"  
done
