# Polygon-Symmetry
Finding the axes of symmetry of a convex polygon

<h3>Description:</h3>
A convex polygon (closed polyline) is given in 2D by the list of nodes’ coordinates.
Implement an algorithm that searches all axes of symmetry for this polygon or reports that
the polygon is non-symmetric.

<h3>Interface:</h3>

The interface is implemented as a console application

Input:
In the command line of which you need to enter the name of the file in which the points in the format lie:

x y

x y

Output:
The axes are output to the console as pairs of points:

x1 y1 - x2 y2

<h3>Stack:</h3>

- ⇒ С++ Standart ISO 20
- ⇒ Google Tests

<h3>Algorithm:</h3>

Here we go through all the points of the polygon and check the axes of symmetry, and then,

1. If the number of vertices is even, then we check the axis passing through this point and through me + (_size / 2), as well as through the middle point between this and the next and the middle point between me + (_size / 2) and the next.This is necessary in order to check only those axes whose number of points on each side is equal.
  
  Example for green point:
  
  <img src="/Pictures/Square.png" width="300" height="300">

2. If there are an odd number of vertices, then we check the axis passing between this point and the average between I + (_size / 2) and the next, as well as the axis passing through the middle point between this and the next and the next for me + (_size / 2).

  Example for green point:
  
  <img src="/Pictures/Pentagon.png" width="300" height="300">

For each obtained line we check whether this line is a symmetry axis for the given polygon. For this purpose, we create a new list of vertices, where we put the reflected vertices of the original polygon. Then we sorit both arrays and check for equality.

To reflect the point, we applied the deduced formulas for the projection of a point onto a line. 

![](Pictures/article.jpg)

<h3>Tests:</h3>

Tests implemented using the Google Tests framework
