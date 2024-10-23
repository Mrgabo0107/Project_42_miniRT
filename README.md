# **MiniRT**

This is a graphic project from the 42 school in Paris, done in pairs, aimed at modeling images following the raytracing protocol. These images must represent a scene from a defined angle and contain simple geometric objects, each with its own lighting system. The project is written in C and uses a simple graphics library called MiniLibX, developed by the school for educational purposes.

The goal is to render geometric objects based on certain mathematical characteristics that define them (position, direction vector, etc.) and the conditions that will determine the correct representation of their color in scenarios with one or multiple light sources of any possible color.

Although the mandatory part of the project required rendering only planes, spheres, and cylinders, managing their interiors and intersections while allowing modifications to aspects such as radius, height, or direction of the objects, as well as managing shadows and ambient light with a single light source, we have implemented several bonuses. These include rendering cones and triangles, which allows for the importation of Blender objects (with a considerable computational cost). Textures and bump mapping have also been implemented on surfaces, along with Phong specular reflection, mirror reflection, and the option to create checkerboard surfaces, allowing the selection of two colors to use and multiple lights of any color possible, along with other interesting features.

## **Installation:**

This project is designed to run on Linux and compiles correctly with GCC v11.4.0. It may be necessary to install certain dependencies for MiniLibX; you can find the documentation here: [MiniLibX Getting Started](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html). 

To proceed, simply clone the repository, run the `make` command in the terminal, and then use:
```bash
./minirt <scenes>

You can use the default scenes located in the /scenes folder of the repository or any scenes that the user wishes to implement.

## **Usage:**

