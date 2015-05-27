/*
 * Timer.h
 *
 *  Created on: 14/05/2015
 *      Author: MateusMendelson
 */

#ifndef SRC_CLASSES_TIMER_H_
#define SRC_CLASSES_TIMER_H_

class Timer {
public:
	Timer() { this->time = 0; }
	~Timer() {};

	void Update(float dt) { time += dt; }
	void Restart() { time = 0; }
	float Get() { return time; }

private:
	float time;
};

#endif /* SRC_CLASSES_TIMER_H_ */
