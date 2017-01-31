#include "worker.h"

Worker::Worker() :observers{nullptr}
{

}

void Worker::exec()
{
	bool run = true;

	while ( run )
	{
		// Read time, push new positions,etc to cameras
		events.wait();

		run = exec_inner(events.type());

		/// @todo Recycle any vectors etc that might be in the event
		events.pop();
	}
}

void Worker::quit()
{
	events.push(quit_event{});
}

void Worker::connect(
	Worker*    sender,
	Worker*    observer,
	event_type type
)
{
	if (sender->observers.at(type))
		throw std::logic_error("Observer already set");

	sender->observers[type] = observer;
}

bool Worker::exec_inner(event_type)
{
	return false;
}
