#ifndef WORKER_H
#define WORKER_H

#include "event_queue.h"

class Worker
{
public:
	virtual ~Worker() {}

	void exec();

	template< typename... Args >
	void emplace(Args&& ... args)
	{
		events.emplace(std::forward< Args >(args) ...);
	}

	void quit();

private:
	virtual bool exec_inner(event&);

	event_queue        events;
};

#endif // WORKER_H
