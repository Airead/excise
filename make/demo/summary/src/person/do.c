/**
 * @file do.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/11/30 15:03:44
 */

#include "do.h"
#include "lib.h"

void do_done(void)
{
    lib_print("  - XO_OX is a backgammon (https://github.com/Airead/XO_OX)\n"
              "  - digit-box is digital photo frame (https://github.com/Airead/digit-box)\n"
              "  - sword-bsp, bare compiled for ARM and simple shell environment (https://github.com/Airead/sword-bsp)\n"
              "  - some exercise during learning (https://github.com/Airead/excise)\n"
              "  - Webpad network module, it is designed to let the js code can control the wireless network devices. (Code can not release)\n"
              "  - linux network module (God said not to say)\n"
              "  - language: C, shell, python\n");
}
void do_studied(void)
{

    lib_print("  - language: C, shell, python\n"
              "  - version control tools: git, svn\n"
              "  - tcp/ip protocol\n"
              "  - nginx web sever or proxy\n"
              "  - some knowledge about linux kernel module\n"
              "  - How Linux Network Stack Works(ipv4)\n"
              "  - politic routing and iptables\n"
              "  - netfilter\n"
              "  - D-Bus\n"
              "  - litte knowledge about django, irc protocol\n");
}
void do_can(void)
{
    lib_print("  - develop high-performance web servers\n"
              "  - writing about the netfilter linux kernel module\n"
              "  - other projects related to linux c\n");
}
void do_need(void)
{
    lib_print("  - solid basic knowledge about computer\n"
              "  - more proficient in C language\n"
              "  - more familiar with the netfilter\n"
              "  - more familiar with linux kernel\n");
}
