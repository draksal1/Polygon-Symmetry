#include "Polygon.h"

float Point::GetX() const{
	return _x;
}

float Point::GetY() const{
	return _y;
}


const Point& Axis::getFirst() const {
	return _first;
}

const Point& Axis::getSecond() const {
	return _second;
}

Point Point::GetMiddlePoint(const Point& first,
	const Point& second)
{
	{
		return Point(first._x + (second._x - first._x) / 2.0f,
			first._y + (second._y - first._y) / 2.0f);
	}
}

Point Point::GetReflectedPoint(const Axis& axis) const
{
	float x1 = axis.getFirst().GetX();
	float y1 = axis.getFirst().GetY();
	float x2 = axis.getSecond().GetX();
	float y2 = axis.getSecond().GetY();

	float dx = x2 - x1;
	float dy = y2 - y1;

	float a = (dx * dx - dy * dy) / (dx * dx + dy * dy);
	float b = 2 * dx * dy / (dx * dx + dy * dy);

	float x = a * (_x - x1) + b * (_y - y1) + x1;
	float y = b * (_x - x1) - a * (_y - y1) + y1;

	return Point(x, y);
}

bool Point::operator==(const Point& other) const
{
	return _x == other._x && _y == other._y;
}


std::vector<Axis> Polygon::FindAxesOfSymmetry() const
{
	std::vector<Axis> result = std::vector<Axis>();

	Axis temp = Axis();
	Point pointFirst;
	Point pointFirstPlusHalf;
	Point pointSecond;
	Point pointSecondPlusHalf;

	for (int i = 0; i < _size; i++)
	{
		for (int j = i + 1; j < _size; j++) 
		{
			pointFirst = _vertices[i];
			pointFirstPlusHalf = Point::GetMiddlePoint(pointFirst, _vertices[i + 1]);
			pointSecond = _vertices[j];

			if (j == _size - 1)
			{
				pointSecondPlusHalf = Point::GetMiddlePoint(pointSecond, _vertices[0]);
			}
			else
			{
				pointSecondPlusHalf = Point::GetMiddlePoint(pointSecond, _vertices[j + 1]);
			}

			for (auto& firstIter : { pointFirst, pointFirstPlusHalf })
			{
				for (auto& secondIter : { pointSecond, pointSecondPlusHalf })
				{
					temp = Axis(firstIter, secondIter);
					if (IsSymmetryAxis(temp))
					{
						result.push_back(temp);
					}
				}
			}
		}
	}
	return result;
}

bool Axis::operator==(const Axis& other) const
{
	return (_first == other._first) && (_second == other._second);
}

bool Polygon::IsSymmetryAxis(const Axis& axis) const
{
	std::vector<Point> reflectedVertices;
	for (const auto& p : _vertices) {
		reflectedVertices.push_back(p.GetReflectedPoint(axis));
	}
	// Sort both sets of vertices to check for equality
	auto comp = [](const Point& p1, const Point& p2) {
		return p1.GetX() < p2.GetX() || (p1.GetX() == p2.GetX() && p1.GetY() < p2.GetY());
		};
	std::sort(reflectedVertices.begin(), reflectedVertices.end(), comp);
	std::vector<Point> sortedVertices = _vertices;
	std::sort(sortedVertices.begin(), sortedVertices.end(), comp);
	return reflectedVertices == sortedVertices;
}

size_t Polygon::GetSize() {
	return _size;}