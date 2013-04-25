#!/usr/bin/env python

import urllib
import sys
import time

def getHtml(url):
    if not url:
        url = 'http://www.google.com'

    ret = "again"
    while ret == "again":
        try:
            page = urllib.urlopen(url)
            ret = "ok"
        except Exception as e:
            print e
            time.sleep(2)
            ret = "again"
    html = page.read()
    page.close()
    return html

if __name__ == "__main__":
    if len(sys.argv) > 1:
        if sys.argv[1] == '-h':
            print sys.argv[0], '<url>  #example: http://www.xxxx.com'
            sys.exit(1)
        else:
            url = sys.argv[1]
    else:
        url = ''
    html = getHtml(url)
    print html

