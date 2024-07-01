#include "Polygon.h"

float Point::GetX() const{
	return _x;
}

float Point::GetY() const{
	return _x;
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
		return Point(first._x + (second._x - first._x) / 2,
			(second._y - first._y) / 2);
	}
}

Point Point::GetReflectedPoint(const Axis& axis) const
{
	// ѕолучаем координаты первой и второй точек оси
	float x1 = axis.getFirst().GetX();
	float y1 = axis.getFirst().GetY();
	float x2 = axis.getSecond().GetX();
	float y2 = axis.getSecond().GetY();

	// ¬ычисл€ем угол наклона пр€мой
	float dx = x2 - x1;
	float dy = y2 - y1;
	float angle = atan2(dy, dx);

	// ѕеремещаем точку и ось так, чтобы перва€ точка оси была в начале координат
	float translated_x = _x - x1;
	float translated_y = _y - y1;

	// ѕоворачиваем точку на -angle, чтобы ось совпала с осью x
	float cos_angle = cos(-angle);
	float sin_angle = sin(-angle);
	float rotated_x = translated_x * cos_angle - translated_y * sin_angle;
	float rotated_y = translated_x * sin_angle + translated_y * cos_angle;

	// ќтражаем точку относительно оси x
	float reflected_x = rotated_x;
	float reflected_y = -rotated_y;

	// ѕоворачиваем точку обратно на angle
	float final_x = reflected_x * cos(angle) - reflected_y * sin(angle);
	float final_y = reflected_x * sin(angle) + reflected_y * cos(angle);

	// ѕеремещаем точку обратно
	final_x += x1;
	final_y += y1;

	return Point(final_x, final_y);
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