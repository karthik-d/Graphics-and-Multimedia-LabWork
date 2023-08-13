# UCS1712: Graphics and Multimedia - Lab Work

Programs, documentation, and output snapshots of implemented and designed experiments for the laboratory coursework in **UCS1712: Graphics and Multimedia Lab**, [SSN College of Engineering](https://www.ssn.edu.in/college-of-engineering/cse-faculty/), Chennai, India.

[Link to Compiled Documentation of Experiments](./Compiled-Record-Work.pdf)

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
    
5. [2D Transformations in C++ using OpenGL](./Ex5-2DTransformations)
    - Perform 2D transformations, namely *translation*, *rotation*, *scaling*, *shearing*, and *reflection*.
    - Demonstrate all use-cases for the said transformations.
    - Use matrix operations and homogeneous coordinates to perform the transformations.
    - [Outputs](./Ex5-2DTransformations/Outputs)
    - [Report](./Ex5-2DTransformations/Report.pdf) 
    <br><br>
    
6. [2D Composite Transformations and Windowing in C++ using OpenGL](./Ex6-2DCompositeTransformations)
    - Perform a combination of two transformations from *translation*, *rotation*, *scaling*, *shearing*, and *reflection*.
    - Demonstrate all use-cases for the said transformations.
    - Use matrix operations and homogeneous coordinates to perform the transformations.
    - Transform an object from *World* coordinate system to a user-defined *Viewport* coordinate system.
    - [Outputs](./Ex6-2DCompositeTransformations/Outputs)
    - [Report](./Ex6-2DCompositeTransformations/Report.pdf) 
    <br><br>

7. [Cohen Sutherland Line Clipping in C++ using OpenGL](./Ex7-CohenSutherland)
    - Perform line clipping using the Cohen Sutherland algorithm, for given line endpoints and viewing window bounds.
    - Demonstrate all use-cases for line clipping.
    - Indicate the intersection coordinates for clipped lines.
    - Transform an object from *World* coordinate system to a user-defined *Viewport* coordinate system.
    - [Outputs](./Ex7-CohenSutherland/Outputs)
    - [Report](./Ex7-CohenSutherland/Report.pdf) 
    <br><br>
    
8. [3D Transformations in C++ using OpenGL](./Ex8-3DTransformations)
    - Perform 2D transformations, namely *translation*, *rotation*, and *scaling*.
    - Demonstrate all use-cases for the said transformations.
    - Use matrix operations and homogeneous coordinates to perform the transformations.
    - [Outputs](./Ex8-3DTransformations/Outputs)
    - [Report](./Ex8-3DTransformations/Report.pdf) 
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
