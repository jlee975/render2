#include "worker.h"

void Worker::exec()
{
	bool run = true;

	while ( run )
	{
		// Read time, push new positions,etc to cameras
		events.wait();

		run = exec_inner(events.type());

		events.pop();
	}
}

void Worker::quit()
{
	events.push(quit_event{}
	);
}

void Worker::connect(
	Worker*    sender,
	Worker*    observer,
	event_type type
)
{
	sender->observers.at(type).push_back(observer);
}

bool Worker::exec_inner(event_type)
{
	return false;
}
