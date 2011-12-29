#!/usr/bin/python
# 
# connman-client
# 

import gtk
import dbus

CONNMAN_BUS = "org.moblin.connman"
CONNMAN_INTERFACE_MANAGER = "org.moblin.connman.Manager"
CONNMAN_INTERFACE_SERVICE = "org.moblin.connman.Service"
MAIN_WINDOW_WIDTH = 300
MAIN_WINDOW_HIGHTH = 300

# main frame
class ConnClient(gtk.Window):
    def __init__(self):
        super(ConnClient, self).__init__()
        
        # set main window style
        self.set_title("Connman-client")
        self.set_size_request(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HIGHTH)
        self.set_position(gtk.WIN_POS_CENTER)
        self.connect("destroy", gtk.main_quit)

        self.show_all()

def get_manager_properties():
    bus = dbus.SystemBus()
    obj = bus.get_object(CONNMAN_BUS, "/")
    ifa = dbus.Interface(obj, CONNMAN_INTERFACE_MANAGER)
    return ifa.GetProperties()

def get_connman_services():
    manager_properties = get_manager_properties()
    services_raw = manager_properties['Services']
    return services_raw

def get_service_properties():
    list_service_properties = [];
    bus = dbus.SystemBus()

    service_objs = get_connman_services()
    for dbusobj in service_objs:
        obj = bus.get_object(CONNMAN_BUS, str(dbusobj))
        ifa = dbus.Interface(obj, CONNMAN_INTERFACE_SERVICE)
        list_service_properties.append(ifa.GetProperties())
    
    return list_service_properties

def test():
    manager_properties = get_manager_properties()
    print "manager_properties: \n"
    print manager_properties
    print "=" * 33 + "\n"

    connman_services = get_connman_services()
    print "connman_services: \n"
    for service in connman_services:
        print service
    print "=" * 33 + "\n"

    service_properties = get_service_properties()
    print "service_properties: \n"
    print service_properties
    print "=" * 33 + "\n"


test()

ConnClient()
gtk.main()
