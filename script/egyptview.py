#!/usr/bin/python
#
# author Airead Fan <fgh1987168@gmail.com>
# date 2012/07
# GPL
# 

import sys
import re
import sets
import os

dot_file_content = []
result_set = sets.Set()

def help_print():
    print ""
    print "usags: <operate> <func_name> <a|b> # a for after (calling), b for before (called)"
    print "    example"
    print "       add main"
    print "       add main a"
    print "       del main b"
# rl for result add
# direct: 'a' for after, 'b' for before, 'c' for all
def rl_add(func_name, direct):
    global dot_file_content
    global result_set

    if direct == 'a':
        s = func_name + '" -> '  # s for search string
    elif direct == 'b':
        s = ' -> "' + func_name
    elif direct == 'c':
        s = func_name
    else:
        help_print()
        return False

    for l in dot_file_content:
        rc = l.find(s)
        if rc >= 0:
            result_set.add(l)
    return True

def rl_del(func_name, direct):
    global result_set
    tmp_sets = sets.Set()

    if direct == 'a':
        s = func_name + '" -> '  # s for search string
    elif direct == 'b':
        s = ' -> "' + func_name
    elif direct == 'c':
        s = func_name
    else:
        help_print()
        return False

    for l in result_set:
        rc = l.find(s)
        if rc < 0:
            tmp_sets.add(l)
    result_set = tmp_sets
    return True

def rl_display_all():
    global dot_file_content
    global result_set

    s = ' -> '

    for l in dot_file_content:
        rc = l.find(s)
        if rc >= 0:
            result_set.add(l)
    return True

def cmd_exec(operate, func_name, direct):
    result = False
    if operate == "add":
        result = rl_add(func_name, direct)
    elif operate == "del":
        result = rl_del(func_name, direct)
    elif operate == "all":
        result = rl_display_all()
    else:
        help_print()

    return result

def cmd_parse(cmds):
    direct = ""
    cmd = cmds.split();
    n = len(cmd)
    if n < 1:
        return False
    elif n < 2:
        operate = cmd[0]        
        func_name = None
    elif n < 3:
        operate = cmd[0]
        func_name = cmd[1]
        direct = 'c'
    else:
        operate = cmd[0]
        func_name = cmd[1]
        direct = cmd[2]

    rc = cmd_exec(operate, func_name, direct)
    return rc
        
    
def main():
    global dot_file_content
    global result_set

    tmp_dot = '/tmp/egypt_view.dot'
    tmp_svg = '/tmp/egypt_view.svg'

    if len(sys.argv) < 2:
        print "usage:", sys.argv[0], "<dot file>"
        sys.exit(1)
    
    dot_file_name = sys.argv[1]
    
    dot_file = open(dot_file_name)
    dot_file_content = dot_file.readlines();
    cmds = ""
    
    while cmds != "exit":
        cmds = raw_input("view > ")
        rc = cmd_parse(cmds)
        if rc != False:
#            print result_set
            of = open(tmp_dot, 'w') # of for output file
            of.write("digraph callgraph {\n")
            of.writelines(result_set)
            of.write("}\n")
            of.close()
            shell_cmd = "cat " + tmp_dot + " | dot -Tsvg -Grankdir=LR >" + tmp_svg
            os.system(shell_cmd)
            shell_cmd = "google-chrome " + tmp_svg
            os.system(shell_cmd)
main()
