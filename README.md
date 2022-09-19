# UCS1712-GraphicsAndMultimedia-LabWork

Programs, reports, documentation and screenshots implemented and designed for the laboratory coursework in UCS1712: Graphics and Multimedia Lab 

## Exercises

1. [Study of Basic Output Primitives in C++ using OpenGL](./Ex1-Primitives)
    - Generate all primitive shapes
    - Draw a black-white checkboard of given dimensions
    - Draw a house using primitives
    - [Outputs](./Ex1-Primitives/Outputs/)
    - [Report](./Ex1-Primitives/Report.pdf) 
    <br><br>

2. [DDA Line Drawing Algorithm in C++ using OpenGL](./Ex2-DDALineDrawing)
    - Generate a line for given start and end points using the DDA algorithm
    - [Outputs](./Ex2-DDALineDrawing/Outputs/)
    - [Report](./Ex2-DDALineDrawing/Report.pdf)
    <br><br>

3. [Bresenham’s Line Drawing Algorithm in C++ using OpenGL](./Ex3-BresenhamLineDrawing)
    - Generate a line for given start and end points using Bresenham's algorithm  
    - [Outputs](./Ex3-BresenhamLineDrawing/Outputs)
    - [Report](./Ex3-BresenhamLineDrawing/Report.pdf) 
    <br><br>

4. [Midpoint Circle Drawing Algorithm in C++ using OpenGL](./Ex4-MidpointCircleDrawing)
    - Plot a circle, given its center and radius, using the midpoint algorithm
    - Draw a simple figure using lines and circles
    - [Outputs](./Ex4-MidpointCircleDrawing/Outputs)
    - [Report](./Ex4-MidpointCircleDrawing/Report.pdf) 
    <br><br>


## Installation and Runtime

### GNU Systems

- `apt` packages required:
    - freeglut3-dev
    - mesa-common-dev


- Compilation command:
    ```
    gcc -o <bin-name> <prog-name> -lGL -lGLU -lglut
    ```

- [Reference](http://www.cse.iitm.ac.in/~vplab/courses/CG/opengl_start.html)
