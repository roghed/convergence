# Description

A simple C++ program which utilizes an OpenGL shader to visualize the convergence of the fixed-point iteration numerical method.

## Fixed-point iteration root-finding method

Given any function $f(x)$ one can prove that the recursive formula:
$$x_{n+1}=x_n + \alpha f(x_n)$$
will converge for some values of the parameter $\alpha$ and initial values of $x_0$ on the roots of function $f(x)$.

This program tries to visualize, which pairs of the above parameters: $\alpha$ and $x_0$ give rise to the convergence on the solution.

## Main window

### Example screens

| ![example1.jpg](https://github.com/roghed/convergence/blob/master/doc/screens/example1.jpg) | 
|:--:| 
| $$f(x) = e^x - \frac{1}{x}$$ |

| ![example2.jpg](https://github.com/roghed/convergence/blob/master/doc/screens/example2.jpg) |
|:--:|
| $$f(x) = \sin(e^x)$$ |

| ![example3.jpg](https://github.com/roghed/convergence/blob/master/doc/screens/example3.jpg) |
|:--:|
| $$f(x) = x^2 \sin(x)$$ |

| ![example4.jpg](https://github.com/roghed/convergence/blob/master/doc/screens/example4.jpg) |
|:--:|
| $$f(x) = x\cos(x) - x\sin(x)$$ |

### Explanation

In the main window of the application a graph of $\alpha$ to $x_0$ is shown. Black areas represent values of the parameters for which the method *does not* converge, while white areas represent points for which the method *does* converge. Points which are close to the solution are rendered grey, and the brightness represents how close the value is to the actual root.

### Controls

- zoom in/out with mouse wheel
- click and drag to move the view

## Function input window

The secondary window is meant to input the function $f(x)$. Any function that can be compiled by the OpenGL compiler is a valid function. The input from this window is inserted directly into the shader code.

# How to build

## Prerequisites

- C++17 compliant compiler 
- CMake (>= 3.24)
- SFML library, along with System, Window and Graphics components (>= 2.5)
- Boost library; system, filesystem, math and dll components needed (>= 1.74)

Make sure both libraries are located in a directory, where CMake can find them.

## Build instructions

Obtain source code by downloading one of the release archives or by cloning directly from this repo, unpack, then run following commands from inside the directory:
```
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
cmake --build build
```
This will build the binaries into the `build` directory, inside the source tree.

# Third party licenses

## ExprTk

This program uses the [C++ Mathematical Expression Toolkit Library](https://github.com/ArashPartow/exprtk):

File: [exprtk.hpp](third_party/include/exprtk.hpp)

Author: Arash Partow (1999-2023)
URL: https://www.partow.net/programming/exprtk/index.html 

Copyright notice:
Free  use  of  the  C++  Mathematical  Expression  Toolkit  Library is
permitted under the guidelines and in accordance with the most current
version of the MIT License.

https://www.opensource.org/licenses/MIT

## Ubuntu font

This program uses the UbuntuMono-Regular font which is distributed under the UBUNTU FONT LICENSE Version 1.0.

For more information see the [Ubuntu Font License.txt](https://github.com/roghed/convergence/blob/master/Ubuntu%20Font%20License.txt) file provided with the project.

## FreeType

Portions of this software are copyright © 2006 The FreeType Project (www.freetype.org). 
All rights reserved.
