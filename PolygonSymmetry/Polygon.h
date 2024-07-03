#pragma once

#include <vector>
#include <stdexcept>
#include <algorithm>

class Axis;


// Class representing a point in 2D space.
class Point
{
private:
	float _x;
	float _y;

public:
	Point() = default;

	Point(float x, float y)
		: _x(x), _y(y) {};

	// Function returns the reflected point about a given axis.
	Point GetReflectedPoint(const Axis& axis) const;

	float GetX() const;

	float GetY() const;

	//  Function returns the middle point between two points.
	static Point GetMiddlePoint(const Point& first,
		const Point& second);

	bool operator==(const Point& other) const;
};


// Class representing a axis of symmetry.
class Axis
{
private:
	Point _first;
	Point _second;

public:
	Axis() = default;

	Axis(const Point& first, const Point& second)
		: _first(first), _second(second) {};

	const Point& getFirst() const;

	const Point& getSecond() const;

	bool operator==(const Axis& other) const;
};


// Class representing a polygon by ordered list of points.
class Polygon
{
private:
	std::vector<Point> _vertices;

	size_t _size;

	// Checks whether the given axis is the axis of symmetry of the polygon.
	bool IsSymmetryAxis(const Axis& axis) const;

public:
	Polygon(const std::vector<Point>& vertices)
		: _vertices(vertices), _size(vertices.size()) {};

	// Returns the list of axes of symmetry of the polygon.
	std::vector<Axis> FindAxesOfSymmetry() const;

	size_t GetSize();
};
