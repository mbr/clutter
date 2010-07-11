env = Environment()
env.ParseConfig('pkg-config --cflags --libs gtk+-2.0')
env['CFLAGS'] += ['-I/usr/include/librsvg-2']
env['LIBS'] += ['-lrsvg-2']

env.Tool('vala', toolpath=['scons-tools'])
env['VALACPACKAGES'] = ['gtk+-2.0','librsvg-2.0']

vala_files = env.Glob('*.vala')
vala_files_c = env.Vala(vala_files)

env.Program('main_test', vala_files_c)
