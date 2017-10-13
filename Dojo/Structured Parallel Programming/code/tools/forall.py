#!/usr/bin/python
import os
import subprocess
import sys

# Grab all but first argument.  These will be passed on to make.
target = "";
for a in sys.argv[1:]:
    target += a + " ";

for root, dirs, files in os.walk("src"):
    if 'Makefile' in set(files):
        subprocess.call("(cd "+root+";make "+target+")",shell=True)

