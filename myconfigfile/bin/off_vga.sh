#!/bin/sh

echo IGD > /sys/kernel/debug/vgaswitcheroo/switch
echo OFF > /sys/kernel/debug/vgaswitcheroo/switch
cat /sys/kernel/debug/vgaswitcheroo/switch
