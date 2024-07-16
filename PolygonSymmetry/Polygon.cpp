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
	const Point& second) {

	// Add half the difference between the points to the first point
	return Point(first._x + (second._x - first._x) / 2.0f,
		first._y + (second._y - first._y) / 2.0f);
}

Point Point::GetReflectedPoint(const Axis& axis) const {
	// If points coincide, the axis is bad
	if (axis.getFirst() == axis.getSecond()) {
		throw std::invalid_argument("Bad Axis");
	}

	float x1 = axis.getFirst().GetX();
	float y1 = axis.getFirst().GetY();
	float x2 = axis.getSecond().GetX();
	float y2 = axis.getSecond().GetY();

	/*
	We use a projection onto a straight line, 
	from where we find the reflected point. 
	More details - https://github.com/draksal1/Polygon-Symmetry
	*/

	float dx = x2 - x1;
	float dy = y2 - y1;


	float a = (dx * dx - dy * dy) / (dx * dx + dy * dy);
	float b = 2 * dx * dy / (dx * dx + dy * dy);

	float x = a * (_x - x1) + b * (_y - y1) + x1;
	float y = b * (_x - x1) - a * (_y - y1) + y1;

	return Point(x, y);
}

bool Point::operator==(const Point& other) const {
	return _x == other._x && _y == other._y;
}


bool Axis::operator==(const Axis& other) const{
	return (_first == other._first) && (_second == other._second);
}


std::vector<Axis> Polygon::FindAxesOfSymmetry() const {

	/*
		Here we go through all the points of the polygon and check the axes of symmetry, and then,

		if the number of vertices is even, then we check the axis passing through this point and through me + (_size / 2), 
		as well as through the middle point between this and the next and the middle point between me + (_size / 2) and the next.
		This is necessary in order to check only those axes whose number of points on each side is equal.

		If there are an odd number of vertices, then we check the axis passing between this point and the average between I + (_size / 2) and the next, 
		as well as the axis passing through the middle point between this and the next and the next for me + (_size / 2).

		Read more with illustrations in README.md
	*/

	if (_vertices.size() < 3) {
		throw std::invalid_argument("Bad polygon");
	}

	std::vector<Axis> result = std::vector<Axis>();

	Axis temp = Axis();
	Point pointFirst;
	Point pointFirstPlusHalf;
	Point pointSecond;
	Point pointSecondPlusHalf;

	int j;

	for (int i = 0; i < _size - 1; i++) {

		j = i + (_size / 2);

		if (j >= _size)
		{
			break;
		}

		pointFirst = _vertices[i];
		pointFirstPlusHalf = Point::GetMiddlePoint(pointFirst, _vertices[i + 1]);



		if (_vertices.size() % 2 == 0) {
			pointSecond = _vertices[i + (_size / 2)];

			if (j == _size - 1) {
				pointSecondPlusHalf = Point::GetMiddlePoint(pointSecond, _vertices[0]);
			}
			else {
				pointSecondPlusHalf = Point::GetMiddlePoint(pointSecond, _vertices[j + 1]);
			}
		}
		else {
			if (j == _size - 1) {
				pointSecond = Point::GetMiddlePoint(_vertices[i + (_size / 2)], _vertices[0]);
				pointSecondPlusHalf = _vertices[0];
			}
			else {
				pointSecond = Point::GetMiddlePoint(_vertices[i + (_size / 2)], _vertices[j + 1]);
				pointSecondPlusHalf = _vertices[j + 1];
			}
		}


		temp = Axis(pointFirst, pointSecond);

		if (IsSymmetryAxis(temp)) {
			result.push_back(temp);
		}


		temp = Axis(pointFirstPlusHalf, pointSecondPlusHalf);

		if (IsSymmetryAxis(temp)) {
			result.push_back(temp);
		}

	}
	return result;
}

bool Polygon::IsSymmetryAxis(const Axis& axis) const{

	// If points coincide, the axis is bad
	if (axis.getFirst() == axis.getSecond()) {
		throw std::invalid_argument("Bad Axis");
	}


	std::vector<Point> reflectedVertices;

	// We just reflect every point 
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

size_t Polygon::GetSize() const{
	return _size;}