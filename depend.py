## INFO ########################################################################
##                                                                            ##
##                                  pycasso                                   ##
##                                  =======                                   ##
##                                                                            ##
##    Cross-platform, hardware accelerated, constraint based GUI framework    ##
##                       Version: 0.5.02.035 (20140911)                       ##
##                                                                            ##
##                              File: depend.py                               ##
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

# Import Python modules
from sys import argv
from re import findall
from os.path import join

#------------------------------------------------------------------------------#
# Module level constants
INCLUDE = r'\n\s*#include\s+"(.+)"\s*\n'


#------------------------------------------------------------------------------#
# Tiny utility to make scanned path muliplatform
formatpath = lambda path: join(*path.split('/'))

#------------------------------------------------------------------------------#
def get_depends(path, include_paths, dependency_list):
    # TODO: collect all headers and arrange them like this:
    #
    #       some.o: dir/header1 dir/dir/header2
    #       dir/header1: dir/header1.h
    #       dir/dir/header2: dir/dir/header2.h
    #
    for include_path in include_paths:
        file_path = join(include_path, path)
        try:
            with open(file_path, encoding='utf-8') as file:
                if (not file_path.endswith('.c') and
                    file_path not in dependency_list):
                        dependency_list.append(file_path)
                for include in findall(INCLUDE, file.read()):
                    include = include.replace('../', '')
                    get_depends(include, include_paths, dependency_list)
        except FileNotFoundError:
            continue


#------------------------------------------------------------------------------#
if __name__ == '__main__':

    # Initialise values
    src = []
    inc = ['']
    out = 'depend.d'
    dep = ['# DO NOT DELETE\n']

    # Process input arguments
    for arg in argv[1:]:
        if arg.startswith('-I'):
            inc.append(arg[2:])
        elif arg.endswith('.c'):
            src.append(arg)
        else:
            out = arg

    # Make paths cross-platform
    src = map(formatpath, src)
    inc = map(formatpath, inc)

    # Process files for dependencies
    # and build dependency tree
    for path in src:
        headers = []
        get_depends(path, inc, headers)
        if headers:
            dep.append('{}: {}'.format(path[:-2] + '.o', ' '.join(headers)))

    # Write dependencies to file
    with open(out, 'w') as file:
        file.write('\n'.join(dep))
