#!/usr/bin/env python
# coding=utf8

env = Environment(CFLAGS='-Wall -pedantic-errors -std=c99 -Wfatal-errors')
env.ParseConfig('pkg-config --cflags --libs gtk+-2.0')
env.Program('clock_widget.c')
