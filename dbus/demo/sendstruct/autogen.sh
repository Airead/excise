#!/bin/bash 

dbus-binding-tool --mode=glib-server --prefix=sendstruct \
		dbus_general.xml > general_stub.h

dbus-binding-tool --mode=glib-client --prefix=sendstruct \
		dbus_general.xml > general_proxy.h
