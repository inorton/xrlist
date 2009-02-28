#!/usr/bin/python

import os
import sys

def print_cmd_line(s, target, src, env):
  cmd = Split(s)
  sys.stdout.write(" ... %s %s  %s\n" % ( cmd[0], cmd[1], " ".join([str(x) for x in target]) )) 
  # Save real cmd to log file
  open(env['CMD_LOGFILE'], 'a').write("%s\n"%s);

env=Environment()
env['PRINT_CMD_LINE_FUNC'] = print_cmd_line
env['CMD_LOGFILE'] = 'build-log.txt'


optimize = '-O2'
cflags   = '';

if os.environ.has_key("DEBUG"):
  optimize = ' -O0 -g '

cflags      = cflags + optimize + ' -Werror -Wall -fno-stack-protector '


xrlist_sources = Split("""xrlist.c""")

env.Library('xrlist',xrlist_sources,CFLAGS=cflags)

SConscript(['tests/SConscript'],exports='env')

