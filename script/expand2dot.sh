#!/bin/bash

EXPANDS=`find . -name "*.expand" | xargs`

egypt $EXPANDS
