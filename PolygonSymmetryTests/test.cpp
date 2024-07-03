#include "gtest/gtest.h"
#include "..//PolygonSymmetry/Polygon.h"

TEST(PointTest, ConstructorTest) {
	Point point = Point(1.0f, 1.0f);

	EXPECT_TRUE(point.GetX() == 1.0f && point.GetY() == 1.0f);
}

TEST(PointTest, GetMiddlePointTest) {
	Point point = Point(1.0f, 1.0f);

	Point point2 = Point(1.0f, 3.0f);

	Point test = Point::GetMiddlePoint(point, point2);

	Point test2 = Point::GetMiddlePoint(point, test);

	Point test3 = Point::GetMiddlePoint(point, test2);

	EXPECT_EQ(test, Point(1.0f, 2.0f));
	EXPECT_EQ(test2, Point(1.0f, 1.5f));
	EXPECT_EQ(test3, Point(1.0f, 1.25f));
}

TEST(PointTest, GetReflectedPointParallelAxisTest) {

	Point point = Point(1.0f, 0.5f);

	Axis axis = Axis(Point(0.0f, 0.0f), Point(0.0f, 1.0f));
	Axis axis2 = Axis(Point(0.5f, 1.0f), Point(1.5f, 1.0f));

	Point reflected = point.GetReflectedPoint(axis);
	Point reflected2 = point.GetReflectedPoint(axis2);

	EXPECT_EQ(reflected, Point(-1.0f, 0.5f));
	EXPECT_EQ(reflected2, Point(1.0f, 1.5f));

}

TEST(PointTest, GetReflectedPointRegularAxisTest) {

	Point point = Point(1.0f, 0.0f);

	Axis axis = Axis(Point(0.0f, 0.0f), Point(1.0f, 1.0f));

	Point reflected = point.GetReflectedPoint(axis);

	EXPECT_EQ(reflected, Point(0.0f, 1.0f));
}

TEST(AxisTest, ConstructorTest) {

	Axis axis = Axis(Point(0.0f, 0.0f), Point(1.0f, 1.0f));
	EXPECT_EQ(axis.getFirst(), Point(0.0f, 0.0f));
	EXPECT_EQ(axis.getSecond(), Point(1.0f, 1.0f));
}

TEST(PolygonTest, ConstructorTest) {
	std::vector<Point> points = { Point(0.0f, 1.0f) };

	Polygon polygon = Polygon(points);

	points.push_back(Point(1.0f, 1.0f));
	points.push_back(Point(1.0f, 1.0f));

	EXPECT_EQ(polygon.GetSize(), 1);

	polygon = Polygon(points);
	
	EXPECT_EQ(polygon.GetSize(), 3);
}


TEST(PolygonTest, FindSymmetryAxesSquareTest) {
	std::vector<Point> points = std::vector<Point>(
		{
			Point(0.0f, 0.0f), Point(0.0f, 1.0f),
			Point(1.0f, 1.0f), Point(1.0f, 0.0f),
		});


	Polygon polygon = Polygon(points);

	std::vector<Axis> result = polygon.FindAxesOfSymmetry();

	EXPECT_TRUE(std::find(result.begin(), result.end(), 
		Axis(Point(0.0f, 0.0f), Point(1.0f, 1.0f))) != result.end());

	EXPECT_TRUE(std::find(result.begin(), result.end(),
		Axis(Point(0.0f, 1.0f), Point(1.0f, 0.0f))) != result.end());

	EXPECT_TRUE(std::find(result.begin(), result.end(),
		Axis(Point(0.5f, 1.0f), Point(0.5f, 0.0f))) != result.end());

	EXPECT_TRUE(std::find(result.begin(), result.end(),
		Axis(Point(0.0f, 0.5f), Point(1.0f, 0.5f))) != result.end());

}

TEST(PolygonTest, FindSymmetryAxesRombTest) {
	std::vector<Point> points = std::vector<Point>(
		{
			Point(0.0f, 0.0f), Point(2.0f, 1.0f),
			Point(0.0f, 3.0f), Point(-2.0f, 1.0f),
		});


	Polygon polygon = Polygon(points);

	std::vector<Axis> result = polygon.FindAxesOfSymmetry();

	EXPECT_TRUE(std::find(result.begin(), result.end(),
		Axis(Point(0.0f, 0.0f), Point(0.0f, 3.0f))) != result.end());


}


TEST(PolygonTest, FindSymmetryAxesFiveTest) {
	std::vector<Point> points = std::vector<Point>(
		{
			Point(0.0f, 1.0f), Point(1.0f, 0.0f),
			Point(2.0f, 0.0f), Point(3.0f, 1.0f),
			Point(1.5f, 2.0f)
		});


	Polygon polygon = Polygon(points);

	std::vector<Axis> result = polygon.FindAxesOfSymmetry();

	EXPECT_TRUE(std::find(result.begin(), result.end(),
		Axis(Point(1.5f, 0.0f), Point(1.5f, 2.0f))) != result.end());
}


TEST(PolygonTest, FindSymmetryAxesNonSymmetricTest) {
	std::vector<Point> points = std::vector<Point>(
		{
			Point(0.1f, 1.0f), Point(-1.0f, 0.0f),
			Point(0.0f, -1.0f), Point(1.0f, -0.5f),
			Point(2.0f, 1.0f)
		});


	Polygon polygon = Polygon(points);

	std::vector<Axis> result = polygon.FindAxesOfSymmetry();

	EXPECT_EQ(result, std::vector<Axis>());
}