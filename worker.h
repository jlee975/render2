#ifndef WORKER_H
#define WORKER_H

#include <map>
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

	static void connect(Worker*, Worker*, event::event_type);
protected:
	/// @todo Template
	void notify(update_positions_event&& e)
	{
		auto range = observers.equal_range(event::UPDATE_POSITIONS);
		for (auto it = range.first; it != range.second; ++it)
		{
			/// @todo If only one match, move the object
			it->second->emplace(e);
		}
	}

	void notify(update_time_event&& e)
	{
		auto range = observers.equal_range(event::UPDATE_TIME);
		for (auto it = range.first; it != range.second; ++it)
		{
			/// @todo If only one match, move the object
			it->second->emplace(e);
		}
	}

	void notify(render_event&& e)
	{
		auto range = observers.equal_range(event::RENDER);
		for (auto it = range.first; it != range.second; ++it)
		{
			/// @todo If only one match, move the object
			it->second->emplace(e);
		}
	}

private:
	virtual bool exec_inner(event&);

	event_queue        events;

	std::multimap< event::event_type, Worker* > observers;
};

#endif // WORKER_H
