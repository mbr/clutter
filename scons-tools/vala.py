"""SCons.Tool.vala

Tool-specific initialization for Vala toolchain.

There normally shouldn't be any need to import this module directly.
It will usually be imported through the generic SCons.Tool.Tool()
selection method.

"""

#
# Copyright (c) 2010 The SCons Foundation
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
# KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
# LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

#  Author : Russel Winder <russel@russel.org.uk>
#  Date : 2010-05-06 19:06+01:00

#  Uses some code ideas originally from http://www.scons.org/wiki/ValaBuilder as at 2010-05-06 19:20+01:00

import SCons

def generate ( env ) :
    env['VALAC'] = env.Detect ( 'valac' ) or 'valac'
    env['VALACFLAGS'] = SCons.Util.CLVar ( '' )
    env['VALACPACKAGES'] = SCons.Util.CLVar ( '' )
    env['VALACPACKAGEPREFIX'] = '--pkg='
    env['_VALACPACKAGES'] = '${ _defines ( VALACPACKAGEPREFIX , VALACPACKAGES , None , __env__ ) }'
    env['VALACPACKAGEPATHS'] = SCons.Util.CLVar ( '' )
    env['VALACPACKAGEPATHPREFIX'] = '--vapidir='
    env['_VALACPACKAGEPATHS'] = '${ _defines ( VALACPACKAGEPATHPREFIX , VALACPACKAGEPATHS , None , __env__ ) }'
    baseCommandString = '-d $TARGET.dir $VALACFLAGS $_VALACPACKAGEPATHS $_VALACPACKAGES $SOURCES'
    valaProgramAction = SCons.Action.Action ( '$VALAC ' + baseCommandString , '$VALAPROGRAMCOMSTR' )
    valaProgramBuilder = SCons.Builder.Builder (
        action = valaProgramAction ,
        src_suffix = '.vala' ,
        suffix = ''
        )    
    valaCAction = SCons.Action.Action ( '$VALAC -C ' + baseCommandString , '$VALACCOMSTR' )
    def valaCEmitter ( target , source , env ) :
        target = [ ]
        for src in source :
            target.append ( src.target_from_source ( '' , '.c' ) )
            env.SideEffect ( src.target_from_source ( '' , '.h' ) , src )
        return target, source
    valaCBuilder = SCons.Builder.Builder(
        action = valaCAction ,
        emitter = valaCEmitter ,
        multi = 1,
        src_suffix = '.vala',
        suffix = '.c'
        )
    env.Append ( BUILDERS = {
        'ValaProgram' : valaProgramBuilder ,
        'Vala' : valaCBuilder
        } )

def exists ( env ) :
    return env.Detect ( [ "valac" ] )
