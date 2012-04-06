#!/bin/bash

svn status --no-ignore | grep '^[?I]' | awk '{print "rm -rf", $2}' 
