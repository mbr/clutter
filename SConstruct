env = Environment(tools = ['default', 'vala', 'disttar'], toolpath = ['scons-tools'])
env['DISTTAR_FORMAT'] = 'bz2'

env.ParseConfig('pkg-config --cflags --libs gtk+-2.0')
env['CFLAGS'] += ['-I/usr/include/librsvg-2']
env['LIBS'] += ['-lrsvg-2']

env['VALACPACKAGES'] = ['gtk+-2.0','librsvg-2.0','posix']

vala_files = env.Glob('*.vala')
vala_files_c = env.Vala(vala_files)

compile = env.Program('clutter_desktop_clock', vala_files_c)

Default(compile)

env.Alias("release",
         AlwaysBuild(env.DistTar('dist/clutter_desktop_clock-binary', ['README', 'clutter_desktop_cloc', env.Dir('theme')]))
)
