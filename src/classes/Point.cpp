/*
 * Point.cpp
 *
 *  Created on: 01/04/2015
 *      Author: MateusMendelson
 */

#include "Point.h"

Point::Point() {
	x = 0;
	y = 0;
	direction = true;
}

Point::Point(float x_0, float y_0) {
	setPoint(x_0, y_0);
	direction = true;
}

void Point::setPoint(float x_0, float y_0) {
	x = x_0;
	y = y_0;
}

float Point::getDistanceFrom(Point p) {
	return sqrt((x - p.x)*(x - p.x) + (y - p.y)*(y - p.y));
}

void Point::output() {
	std::cout << "x: " << this->x << "; y: " << this->y << "; magnitude: " << this->getMagnitude() << std::endl;
}
