#!/usr/bin/env python
# coding=utf8

env = Environment(CFLAGS='-Wall -pedantic-errors -std=c99 -Wfatal-errors -DG_DEBUG')
env.ParseConfig('pkg-config --cflags --libs gtk+-2.0')

util = env.Object('util.c')

# widgets:
widgets = []
widgets.append(env.Object('clutterdesktopwidget.c'))

env.Program(['clock_widget.c', util] + widgets)
