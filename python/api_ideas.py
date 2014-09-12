# Hierarchy of Pycasso's basic units:
#
#
#        { Window }
#
#          ^
#          |
#
#        { Region }
#
#          ^
#          |
#
#        { Geometry + Constraint + Geometry
#          Geometry + Constraint + Layout
#          Layout   + Constraint + Layout }
#
#          ^
#          |
#
#        { Geometry }
#
#
# Window: set of regions
# Region: single layout
# Layout: visually unrepresentable object
# Geometry: visually represantable object
# Constraint: relationship defined between layouts and geometries


class Window:

    @property
    def title(self):
        return self._title
    @title.setter
    def title(self, value):
        self._title = value

    @property
    def x(self):
        return self._x
    @x.setter
    def x(self, value):
        self._x = value

    @property
    def y(self):
        return self._y
    @y.setter
    def y(self, value):
        self._y = value

    @property
    def position(self):
        return self.x, self.y
    @position.setter
    def position(self, values):
        self.x, self.y = value

    @property
    def width(self):
        return self._width
    @width.setter
    def width(self, value):
        self._width = value

    @property
    def height(self):
        return self._height
    @height.setter
    def height(self, value):
        self._height = value

    @property
    def dimension(self):
        return self.width, self.height
    @dimension.setter
    def dimension(self, values):
        self.width, self.height = values

    @property
    def basecolor(self):
        return self._basecolor
    @basecolor.setter
    def basecolor(self, value):
        self._basecolor = value


    def __init__(self,
                 title  = 'Pycasso <version>',
                 x = pycasso.constants.CENTER,
                 y = pycasso.constants.CENTER,
                 width  = 512,
                 height = 512,
                 basecolor = pycasso.color.rgb(0, 0, 0)):
        # Set values
        self.title = title
        self.position = x, y
        self.dimension = width, height
        self.basecolor = basecolor

    def add_region(self, region):
        pass

    def run(self):
        while True:
            for region in self.region:
                if region.changed:
                    region.draw()
            self.wait_events()

class Region:

    def close(self):
        self.parent.remove_region(self)

    def draw(self):
        pass

#------------------------------------------------------------------------------#
# EXAMPLE

# Import modules
import pycasso
from pycasso.constants import *

# Setup window
window = pycasso.Window()
window.title = 'My first Pycasso App'
window.position = CENTER, CENTER
window.dimension = 1024, 768

# Create main region
region = pycasso.Region(x=0, y=0, width=FILL, height=FILL)
window.add_region(region)

# Create region layout
region.layout = pycasso.Layout()

# Create geometry
rectangle = pycasso.geometry.Rectangle()
circle    = pycasso.geometry.Circle()

region.layout.add_object(rectangle)
region.layout.add_object(circle)

# Create constraints
rectangle.x == circle.x                                       #<-- anonym consts
rectangle.y == rectangle.y

layout.const.dim1 = rectangle.width  == circle.width * 2      #<-- named consts
layout.const.dim2 = rectangle.height == circle.height * 1.5

# Initial values
rectangle.position = CENTER, CENTER
circle.bring_top()

# Add event
@window.on_mouse_move
def on_mouse_move(x, y, dx, dy):
    rectangle.position = x, y

@window.on_mouse_left_drag
def on_mouse_left_drag(x, y, dx, dy):
    rectangle.width  += dx
    rectangle.height += dy

space_key_flag = True
@window.on_space_pressed
def on_space_pressed():
    # Change constraits
    if space_key_flag:
        layout.const.dim1 = circle.width  == rectangle.width * 2
        layout.const.dim2 = circle.height == rectangle.height * 1.5
    else:
        layout.const.dim1 = rectangle.width  == circle.width * 2
        layout.const.dim2 = rectangle.height == circle.height * 1.5
    # Rebuild
    region.layout.build()
    # Toogle
    space_key_flag = not space_key_flag

# Build constraints
region.layout.build()
# Enter event loop
window.run()
