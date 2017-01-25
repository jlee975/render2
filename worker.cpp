#include "worker.h"

void Worker::exec()
{
	bool run = true;

	while ( run )
	{
		// Read time, push new positions,etc to cameras
		events.wait();

		run = exec_inner(events.front());

		events.pop();
	}
}


void Worker::quit()
{
	events.emplace(quit_event{});
}

void Worker::connect(Worker* sender, Worker* observer, event::event_type type)
{
	sender->observers.emplace(type, observer);
}

bool Worker::exec_inner(event &)
{
	return false;
}
