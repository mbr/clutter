env = Environment(tools = ['default', 'vala', 'archive'], toolpath = ['scons-tools'])

env.ParseConfig('pkg-config --cflags --libs gtk+-2.0')
env['CFLAGS'] += ['-I/usr/include/librsvg-2']
env['LIBS'] += ['-lrsvg-2']

env['VALACPACKAGES'] = ['gtk+-2.0','librsvg-2.0','posix']

vala_files = env.Glob('*.vala')
vala_files_c = env.Vala(vala_files)

compile = env.Program('clutter_desktop_clock', vala_files_c)

Default(compile)

env['ARCHIVE_PREFIX'] = 'clutter-desktop-clock'
Alias('release', env.Archive('dist/clutter-desktop-clock.tar.bz2', ['clutter_desktop_clock'] + env.Glob('theme/*.svg')))
