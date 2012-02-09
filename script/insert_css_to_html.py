#!/usr/bin/env python

# 
# filename: insert_css_to_html.py
# author: AireadFan (fgh1987168@gmail.com)
#
# version 0.1
# Copyright 2012 
#
# This script is designed for Beautify my blog. It can insert the attribute in
# external css file to the html. After do that, you can browsing your article
# with the same style in your blog and without other side effect.
#
#

import sys
import re

def get_css_format_string(css_name):
    # open css file, read content_css
    file_css = open(css_name)
    content_css = file_css.read()
    file_css.close()

    # delete comment, change " to '
    p_delete_comment = re.compile('/\*.*?\*/', re.DOTALL)
    content_css = p_delete_comment.sub('', content_css)
    content_css_ = content_css.replace('\"', '\'');

    return content_css

def get_dict(content_css):
    # write dict file
    content_dict = content_css.replace('\n', '');
    content_dict = content_dict.replace('}', '}\n\n')
    file_dict = open("dict.tmp", 'w')
    file_dict.write(content_dict)
    file_dict.close()

    # get dict
    dict = {}
    file_dict = open("dict.tmp", 'r')
    p_get_dict = re.compile('(.*){(.*)}')

    for line in file_dict.readlines():
        match = p_get_dict.match(line);
        if match != None:
            dict[match.group(1).strip()] = match.group(2)

    file_dict.close()
    return dict

def html_insert_css(content_html, dict):
    for key in dict.keys():
        if key.find('.') < 0:   # not find .
            tag = '<' + key + '>'
            tag = tag.lower()
#            print tag
            tag_style = '<' + key.lower() + ' style="' + dict[key] + '">'
#           print tag_style
            content_html = content_html.replace(tag, tag_style);
        else:
            tag_class_list = key.split('.')
            tag = '<' + tag_class_list[0] + ' class="' + tag_class_list[1] + '">'
            tag = tag.lower()
#            print tag
            tag_style = '<' + tag_class_list[0].lower() + ' style="' + dict[key] + '">'
#            print tag_style
            content_html = content_html.replace(tag, tag_style);

    return content_html

def get_base_name(path):
    return path.split('/')[-1]

def produce_html(html_name, dict):
    # insert sytle to html
    file_html = open(html_name, 'r')
    content_html = file_html.read()
    file_html.close()

    content_html_changed = html_insert_css(content_html, dict)

    produce_html_name = "blog_" + get_base_name(html_name)
    file_html_changed = open(produce_html_name, 'w')
    file_html_changed.write(content_html_changed)
    file_html_changed.close()

def main():
    if len(sys.argv) < 3:
        print "usage: %s <html name> <css name>" % sys.argv[0]
        sys.exit(1)

    html_name = sys.argv[1]
    css_name = sys.argv[2]

    content_css = get_css_format_string(css_name)
    dict = get_dict(content_css)
    produce_html(html_name, dict)

main()
