#!/usr/bin/env python3
## INFO ########################################################################
##                                                                            ##
##                                  pycasso                                   ##
##                                  =======                                   ##
##                                                                            ##
##    Cross-platform, hardware accelerated, constraint based GUI framework    ##
##                       Version: 0.5.02.035 (20140911)                       ##
##                                                                            ##
##                             File: dev/proj.py                              ##
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

# Import cutils modules
from cutils.cver import version
# from cutils.cdoc import document
from cutils.ccom import collect, EXCEPTIONS
from cutils.clic import header

# Module level constants
OVERWRITE=0

#------------------------------------------------------------------------------#
# Increase version number
version(infolder='.',
        sub_max=9,
        rev_max=99,
        build_max=999)

# Add C specific extensions to exceptions
exceptions = EXCEPTIONS + ('.o' '.a', '.lib', '.so', '.dll', '.dylib')

# Collect special comments
collect('.', exceptions=exceptions, overwrite=OVERWRITE)

# Generate license headers
header('.', exceptions=exceptions, overwrite=OVERWRITE)

# Feedback
print('pycasso: project is up to date', end='\n'*2)
