gtkenv = Environment()

gtkenv.Tool('vala', toolpath=['scons-tools'])

gtkenv['VALACPACKAGES'] = ['gtk+-2.0']
gtkenv.ParseConfig('pkg-config --cflags --libs gtk+-2.0')

widget_vala = ['ClutterDesktopWidget.vala']
widget_c = gtkenv.Vala(widget_vala)
widget_o = gtkenv.Object(widget_c)
