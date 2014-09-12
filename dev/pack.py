#!/usr/bin/env python3
## INFO ########################################################################
##                                                                            ##
##                                  pycasso                                   ##
##                                  =======                                   ##
##                                                                            ##
##    Cross-platform, hardware accelerated, constraint based GUI framework    ##
##                       Version: 0.5.02.035 (20140911)                       ##
##                                                                            ##
##                             File: dev/pack.py                              ##
##                                                                            ##
##  For more information about the project, visit <http://www.pycasso.org>.   ##
##                       Copyright (C) 2014 Peter Varo                        ##
##                                                                            ##
##  This program is free software: you can redistribute it and/or modify it   ##
##   under the terms of the GNU General Public License as published by the    ##
##       Free Software Foundation, either version 3 of the License, or        ##
##                    (at your option) any later version.                     ##
##                                                                            ##
##    This program is distributed in the hope that it will be useful, but     ##
##         WITHOUT ANY WARRANTY; without even the implied warranty of         ##
##            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            ##
##            See the GNU General Public License for more details.            ##
##                                                                            ##
##     You should have received a copy of the GNU General Public License      ##
##     along with this program, most likely a file in the root directory,     ##
##        called 'LICENSE'. If not, see <http://www.gnu.org/licenses>.        ##
##                                                                            ##
######################################################################## INFO ##

# Import python modules
from os.path import join
from collections import OrderedDict

# Import cutils modules
from cutils.cres import pack

#------------------------------------------------------------------------------#
FOLDER_VS = join('shaders', 'vertex')
FOLDER_FS = join('shaders', 'fragment')

# Define properties of resources/shader.h
shaders = {'output': join('resources', 'shaders.h'),
           'header': '/* INFO **\n** INFO */\n\n',
           'guard' : '_PYCASSO_RESOURCES_SHADERS_26875033728857023_',
           'array_by_enum': 'SHADER_SOURCES',
           'inputs': OrderedDict([
                # Vertex shaders
                ('MAIN_VS'        , join(FOLDER_VS, 'main.vs')),
                ('QUAD_COLOR_VS'  , join(FOLDER_VS, 'quad_color.vs')),
                ('QUAD_TEXTURE_VS', join(FOLDER_VS, 'quad_texture.vs')),
                ('SYS_GRID_VS'    , join(FOLDER_VS, 'sys_grid.vs')),
                # Fragment shaders
                ('MAIN_FS'                   , join(FOLDER_FS, 'main.fs')),
                ('SHAPE_CIRCLE_FS'           , join(FOLDER_FS, 'shape_circle.fs')),
                ('SHAPE_RECTANGLE_FS'        , join(FOLDER_FS, 'shape_rectangle.fs')),
                ('SHAPE_ROUNDED_RECTANGLE_FS', join(FOLDER_FS, 'shape_rounded_rectangle.fs')),
                ('FILL_SOLID_COLOR_FS'       , join(FOLDER_FS, 'fill_solid_color.fs')),
                ('FILL_TEXTURE_FS'           , join(FOLDER_FS, 'fill_texture.fs')),
                ('FILL_LINEAR_GRADIENT_FS'   , join(FOLDER_FS, 'fill_linear_gradient.fs')),
                ('FILL_RADIAL_GRADIENT_FS'   , join(FOLDER_FS, 'fill_radial_gradient.fs')),
                ('FILL_CONICAL_GRADIENT_FS'  , join(FOLDER_FS, 'fill_conical_gradient.fs'))])}

# Pack resources
pack(shaders)
