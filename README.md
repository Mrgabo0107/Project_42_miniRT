# **_MiniRT_**

This is a graphic project from the 42 school in Paris, done in pairs, aimed at modeling images following the raytracing protocol. These images must represent a scene from a defined angle and contain simple geometric objects, each with its own lighting system. The project is written in C and uses a simple graphics library called MiniLibX, developed by the school for educational purposes.

The goal is to render geometric objects based on certain mathematical characteristics that define them (position, direction vector, etc.) and the conditions that will determine the correct representation of their color in scenarios with one or multiple light sources of any possible color.

Although the mandatory part of the project required rendering only planes, spheres, and cylinders, managing their interiors and intersections while allowing modifications to aspects such as radius, height, or direction of the objects, as well as managing shadows and ambient light with a single light source, we have implemented several bonuses. These include rendering cones and triangles, which allows for the importation of Blender objects (with a considerable computational cost). Textures and bump mapping have also been implemented on surfaces, along with Phong specular reflection, mirror reflection, and the option to create checkerboard surfaces, allowing the selection of two colors to use and multiple lights of any color possible, along with other interesting features.

# Installation:

This project is designed to run on Linux and compiles correctly with GCC v11.4.0. It may be necessary to install certain dependencies for MiniLibX; you can find the documentation here: [MiniLibX Getting Started](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html). 

To proceed, simply clone the repository, run the `make` command in the terminal, and then use:
```bash
./minirt <scenes>
```

You can use the default scenes located in the /scenes folder of the repository or any scenes that the user wishes to implement.

# Usage:

The scenes to be rendered must be stored in files with a `.rt` extension. Each element declaration in the scene must be separated by a newline, and each scene must include the following elements:

- **Ambient Light (A)**: Defines the general brightness of the scene.
- **At least one Light Source (L)**: Provides specific lighting to objects.
- **Camera (C)**: Defines the viewpoint to render the scene from.

This setup creates an empty scene where you can add objects to render. The syntax for declaring these elements is as follows:

### Ambient Light (A):
```
A <intensity> <R,G,B>
```
- `<intensity>`: A value between 0 and 1 that defines the light intensity.
- `<R,G,B>`: RGB color values (red, green, blue) as integers ranging from 0 to 255.

### Light Source (L):
```
L <position> <intensity> <R,G,B>
```
- `<position>`: The x, y, z coordinates of the light source.
- `<intensity>`: A value between 0 and 1 defining light intensity.
- `<R,G,B>`: RGB color values as integers ranging from 0 to 255.

### Camera (C):
```
C <position> <view direction> <FOV>
```
- `<position>`: The x, y, z coordinates of the camera.
- `<view direction>`: A vector defining the direction the camera is facing, with values between -1 and 1.
- `<FOV>`: The field of view angle, a value between 0 and 180 degrees.

## Objects

You can add various objects to the scene using the following syntax:

### Plane(pl):
```
pl <point on the plane> <normal vector> <R,G,B>
```
- `<point>`: A reference coordinate defining the plane.
- `<normal vector>`: The vector normal to the plane.
- `<R,G,B>`: RGB color values for the plane.

### Sphere(sp):
```
sp <center coordinates> <radius> <R,G,B>
```
- `<center coordinates>`: The x, y, z coordinates of the sphere's center.
- `<radius>`: The sphere’s radius.
- `<R,G,B>`: RGB color values for the sphere.

### Cylinder(cy):
```
cy <center coordinates> <orientation> <radius> <height> <R,G,B>
```
- `<center coordinates>`: The x, y, z coordinates of the cylinder's center.
- `<orientation>`: The orientation vector of the cylinder.
- `<radius>`: The radius of the cylinder's base.
- `<height>`: The cylinder's height.
- `<R,G,B>`: RGB color values for the cylinder.

### Cone(co):
```
co <vertex position> <direction> <angle> <height> <R,G,B>
```
- `<vertex position>`: The x, y, z coordinates of the cone's vertex.
- `<direction>`: The vector direction of the cone's point.
- `<angle>`: The cone's opening angle.
- `<height>`: The cone's height.
- `<R,G,B>`: RGB color values for the cone.

### Triangle(tr):
```
tr <first point> <second point> <third point> <R,G,B>
```
- `<first point>`: The x, y, z coordinates of the first vertex.
- `<second point>`: The x, y, z coordinates of the second vertex.
- `<third point>`: The x, y, z coordinates of the third vertex.
- `<R,G,B>`: RGB color values for the triangle.

**Note:** In this version, triangles will remain unmodifiable during execution.

## Example of a Basic Scene:

```
A 1 0,0,25
C 12,0,0 -1,0,0 90
L 4,0,3 0.7 255,255,255

pl 0,0,0 0,0,1 0,255,255
cy 0,0,0 0,0,1 1 2 255,100,100
sp 0,-4,0 3 100,100,100
co 0,4,0 0,0,1 35 3 2,200,4
tr 1,5,5 0,6,4 -1,8,3 255,0,0
```
The parser accepts spaces and tabs between object data. Lines can also be commented out using the `#` symbol, preventing them from being read and rendered.

## Controls

In miniRT, you can select an object in the scene by clicking on it. This allows you to modify its position, orientation, and properties (with exceptions for lights, which will be explained in their dedicated section). To deselect an object, simply click outside any object, and the selection will return to the camera, which is the default selected object.

### General Commands:

- **ESC**: Closes the program.
- **ENTER**: Resets the scene to its initial values.
- **Z**: Saves the current scene to a `scene.rt` file in the root directory.
- **X**: Takes a screenshot of the current scene.
- **DEL**: Deselects an object when the background is not visible, returning the selection to the camera.

### Camera Controls:

- **W**: Move forward.
- **S**: Move backward.
- **A**: Move left.
- **D**: Move right.
- **E**: Move up.
- **Q**: Move down.

To change the viewing direction, use the arrow keys:

- **Up Arrow**: Rotate view upward.
- **Down Arrow**: Rotate view downward.
- **Left Arrow**: Rotate view left.
- **Right Arrow**: Rotate view right.

### Object Controls:

When selecting a plane, sphere, cylinder, or cone, you can modify their position and rotation relative to the camera axes using the following commands:

#### Position:
- **6 (Numpad)**: Move right.
- **4 (Numpad)**: Move left.
- **2 (Numpad)**: Move down.
- **8 (Numpad)**: Move up.
- **7 (Numpad)**: Move backward.
- **1 (Numpad)**: Move forward.

#### Rotation:
- **X Axis**:
  - **J**: Rotate clockwise.
  - **K**: Rotate counterclockwise.
- **Y Axis**:
  - **O**: Rotate clockwise.
  - **I**: Rotate counterclockwise.
- **Z Axis**:
  - **M**: Rotate clockwise.
  - **N**: Rotate counterclockwise.

### Lights:
Press **L** to select a light. If multiple lights are present, press **L** until the desired light is selected. Use the same position controls as for other objects. Press **+** or **-** to adjust the light's intensity.

### Specular Property (Not Available in Triangles)

Specular light in ray tracing simulates the bright reflections produced when a surface reflects a light source directly towards the observer's eye. This is what creates the bright spots of light that make objects appear shiny or polished.

_Key Parameters:_

*Intensity (base):* This defines how strong the specular reflection is, controlling the brightness of reflections on the surface. A higher value makes the object appear brighter.

*Exponent:* This controls the sharpness or size of the reflection. A high exponent results in small, sharp reflections, simulating a very polished surface, while a low exponent creates more diffuse reflections, simulating rough surfaces.

To apply specular light to an object, simply add the following line under the object's declaration:
```
spec <intensity> <exponent>
```
- `<intensity>`: from 0 to 1
- `<exponent>`: from 1 to 1000

### Checkered Surfaces (Not Available in Triangles)

This option is the default configuration that can be modified on objects by pressing + or - to increase or decrease the number of squares on the surface. If another option is selected for modification, simply press the letter **C** to return to modifying this property.

To declare an object that appears checkered in the scene upon initializing the program, use the following line under the object's declaration:
```
check <RGB> <density>
```
- `<RGB>`: This defines the second color used in the checkerboard pattern and is mandatory to specify it if declared in the .rt file. However, if the surface is set to be checkerboard-patterned during program execution without specifying a color, the program will automatically calculate the inverse color by subtracting each RGB channel value from 255 (i.e., 255 - color value).
- `<density>`: It is the number of squares in a given area in the checkerboard pattern, and it is the property that is modified with + and - during execution.

### Mirror (Not Available in Triangles)

This option allows objects to exhibit mirror-like reflections. To give this property to an object, simply add the following line under the object's declaration:
```
mir <reflection index>
```
- `<reflection index>`: between 0 and 1, where 1 represents a perfect mirror and 0 means no reflection.

### Bump Mapping (Not Available in Triangles)

A bump map in ray tracing is a technique used to simulate surface detail or roughness on an object without modifying its actual geometry. It uses a height map (a grayscale texture) to alter how light interacts with the surface, creating the illusion of bumps and indentations.

Instead of changing the object's structure, the bump map modifies the surface normals at each point, affecting how light bounces off those areas. This gives the impression that the surface has detailed textures like wrinkles, cracks, or patterns without increasing the polygon count, thus maintaining performance.

To use a texture as a bump map, add the following line under the object's declaration:
```
bump <path to .xpm image>
```
This raytracer interprets any grayscale .xpm image to use as a bump map. Note that the projection used on spheres is equirectangular, while projections made on other objects are basic but can still be useful.

The implementation of a bump map is independent of color; it can even be used over textures or checkered patterns. If you wish to stop using the bump map at any point during execution, simply press **B** to deactivate it, and press **B** again to reactivate it.

### Textures (Not Available in Triangles)
This raytracer allows you to project any .xpm image onto the objects in the scene, similar to bump mapping. The equirectangular projection used on spheres creates realistic environments, enhancing the visual quality. On flat surfaces, the texture will repeat indefinitely, while on other shapes, we implement projections that creatively deform the image, resulting in visually interesting effects.

To project a texture onto the surface of an object, add the following line under the object's declaration:
```
tex <path to .xpm image>
```
It is important to note that choosing a texture will override any existing color settings (such as checkered patterns or colors defined in the .rt file).

If at any point you wish to stop projecting the texture onto an object, simply press **T**, and it will revert to its original color or color pattern. You can reactivate the texture by pressing **T** again.

## Example of a fairly complete scene:
```
A		1.0		0,0,25
C		12.0,0.0,0.0		-1.0,0.0,0.0		90
L		15,0.0,3.0		0.70000		255,255,255

pl		0.0,0.0,-7.0		0.0,0.0,1.0		0,255,255
mir 0.0
spec 0.30000 16.0
check 255,0,0 1.0

sp		0.0,-4.0,0.0		3.0		100,100,100
spec 1.0 100.0
check 155,155,155 0.0
mir 0.0
tex textures_and_bumpmap/emoji1.xpm

cy		7,0.0,0.0		0.0,0.0,1.0		1.0		2.0		255,100,100
mir 0.0
check 0,155,155 0.0
bump textures_and_bumpmap/brick_bump.xpm
spec 0.30000 16.0

tr		1.0,5.0,5.0		0.0,6.0,4.0		-1.0,8.0,3.0		255,0,0
check 0,255,255 0.0
spec 0.30000 16.0
mir 0.0

co		0.0,4.0,0.0		0.0,0.0,1.0		35.0		3.0		2,200,4
mir 1.0
spec 0.30000 16.0
check 8,8,8 2.0
```

As you can see the order of declaration for spec, check, mir, tex, or bump in the lines following an object does not have a specified order and can be separated by several line breaks; the important thing is that they are on different lines.


