#include "worker.h"

void Worker::exec()
{
	bool run = true;

	while ( run )
	{
		// Read time, push new positions,etc to cameras
		events.wait();

		run = exec_inner();

		events.pop();
	}
}


void Worker::quit()
{
	events.push(quit_event{});
}

void Worker::connect(Worker* sender, Worker* observer, event_type type)
{
	sender->observers.emplace(type, observer);
}

event_type Worker::get_event_type() const
{
	return events.type();
}

bool Worker::exec_inner()
{
	return false;
}
