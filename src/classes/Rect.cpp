/*
 * Rect.cpp
 *
 *  Created on: 01/04/2015
 *      Author: MateusMendelson
 */

#include "Rect.h"

Rect::Rect() : point() {
	w = 0;
	h = 0;
}

Rect::Rect(float x_0, float y_0, float w_0, float h_0) : point(x_0, y_0) {
	w = w_0;
	h = h_0;
}

void Rect::setRect(float x_0, float y_0, float w_0, float h_0) {
	point.setPoint(x_0, y_0);
	w = w_0;
	h = h_0;
}

void Rect::setCenterAt(float x_0, float y_0) {
	this->point.setPoint(x_0 - ((float) w / 2), y_0 - ((float) h / 2));
}

void Rect::addPoint(Point p) {
	point = point + p;
}

Point Rect::getCenter() {
	Point p(point.x + ((float) w / 2), point.y + ((float) h / 2));

	return p;
}

float Rect::getDistanceFrom(Rect r) {
	Point myCenter = this->getCenter();

	return myCenter.getDistanceFrom(r.getCenter());
}

bool Rect::IsInside(Point p) {
	if (p.x >= point.x && p.x <= (point.x + w) && p.y >= point.y
			&& p.y <= (point.y + h)) {
		return true;
	}

	return false;
}

bool Rect::IsInside(float x, float y) {
	Point p(x, y);

	return IsInside(p);
}
