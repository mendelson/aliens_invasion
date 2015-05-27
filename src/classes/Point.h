/*
 * Point.h
 *
 *  Created on: 01/04/2015
 *      Author: MateusMendelson
 */

#ifndef SRC_CLASSES_POINT_H_
#define SRC_CLASSES_POINT_H_

#include <cmath>
#include <iostream>

class Point {
public:
	Point();
	Point(float, float);

	// Set new values for all point's properties
	void setPoint(float, float);

	// Get the distance from a point to the current point
	float getDistanceFrom(Point);

	// Get inclination of a straight line composed by the current point and another point (radians)
	float getAngleOfInclination(Point p) { return atan((p.y - y)/(p.x - x)); }

	// Overload sum operator
	Point operator+(const Point& rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}

	// Overload subtraction operator
	Point operator-(const Point& rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}

	// Overload multiplication operator (scalar product)
	Point operator*(const float& scalar) const {
		return Point(x*scalar, y*scalar);
	}

	// Output
	void output();

	// Get inclination relative to de x-axis (radians)
	double getInclinationX() { return atan2(y, x); };

	// Get magnitude
	float getMagnitude() { return sqrt(x*x + y*y); }

	// Negate the vector
	void negate() { x = -x; y = -y; }

	float x;
	float y;
	bool direction; // true: positive; false: negative (used only to make things easier for Penguins class)
};

#endif /* SRC_CLASSES_POINT_H_ */
