#pragma once

#include <vector>

class Point
{
private:
	float _x;
	float _y;

public:
	Point(float x, float y);

	Point Reflect(const Axis& axis);

	float getX();

	float getY();
};


class Axis
{
private:
	Point _first;
	Point _second;

public:
	Axis(const Point& first, const Point& second);

	Point getFirst();

	Point getSecond();
};


class Polygon
{
private:
	std::vector<Point> _vertices;

	bool IsSymmetryAxis(const Axis& axis);

public:
	Polygon(const std::vector<Point>& vertices);
	
	std::vector<Axis> FindAxesOfSymmetry();
};
