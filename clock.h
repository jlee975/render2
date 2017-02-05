#ifndef CLOCK_H
#define CLOCK_H

#include "worker.h"


class Clock : public Worker
{
public:
	Clock();
private:
	bool exec_inner(event_type);
	void init();

	double time;
};

#endif // CLOCK_H
