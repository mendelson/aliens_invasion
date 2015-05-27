/*
 * Rect.h
 *
 *  Created on: 01/04/2015
 *      Author: MateusMendelson
 */

#ifndef SRC_CLASSES_RECT_H_
#define SRC_CLASSES_RECT_H_

#include "Point.h"

class Rect {
public:
	Rect();
	Rect(float x_0, float y_0, float w_0, float h_0);

	// Set new values for all rectangle's properties
	void setRect(float x_0, float y_0, float w_0, float h_0);

	// Set the rectangle to have its center at (x, y)
	void setCenterAt(float x_0, float y_0);

	// Add a point to the rectangle (used to move the rectangle)
	void addPoint(Point);

	// Get the coordinates of the rectangle's center
	Point getCenter();

	// Get the coordinates of the rectangle's center (just to fit the code that was given for the collisions)
	Point GetCenter() const { return Point(point.x + ((float) w / 2), point.y + ((float) h / 2)); }

	// Get the distance from a rectangle's center to the center of the current rectangle
	float getDistanceFrom(Rect);

	// Check if a point is inside a rectangle
	bool IsInside(Point);

	// Check if a point is inside a rectangle
	bool IsInside(float, float);

	Point point;
	float w;
	float h;
};

#endif /* SRC_CLASSES_RECT_H_ */
