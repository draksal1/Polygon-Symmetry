#pragma once

#include <vector>
#include <stdexcept>
#include <algorithm>

class Axis;

class Point
{
private:
	float _x;
	float _y;

public:
	Point() = default;

	Point(float x, float y)
		: _x(x), _y(y) {};

	Point GetReflectedPoint(const Axis& axis) const;

	float GetX() const;

	float GetY() const;

	static Point GetMiddlePoint(const Point& first,
		const Point& second);
};


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
};


class Polygon
{
private:
	std::vector<Point> _vertices;

	int _size;

	bool IsSymmetryAxis(const Axis& axis) const;

public:
	Polygon(const std::vector<Point>& vertices)
		: _vertices(vertices), _size(vertices.size()) {};

	std::vector<Axis> FindAxesOfSymmetry() const;
};
