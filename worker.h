#ifndef WORKER_H
#define WORKER_H

#include <map>
#include "event_queue.h"

class Worker
{
public:
	virtual ~Worker() {}

	void exec();

	template< typename T >
	void push(T&& arg)
	{
		events.push(std::forward< T >(arg));
	}

	void quit();

	static void connect(Worker*, Worker*, event_type);
protected:
	/// @todo Template
	void notify(update_positions_event&& e)
	{
		auto range = observers.equal_range(UPDATE_POSITIONS);
		for (auto it = range.first; it != range.second; ++it)
		{
			/// @todo If only one match, move the object
			it->second->push(e);
		}
	}

	void notify(update_time_event&& e)
	{
		auto range = observers.equal_range(UPDATE_TIME);
		for (auto it = range.first; it != range.second; ++it)
		{
			/// @todo If only one match, move the object
			it->second->push(e);
		}
	}

	void notify(render_event&& e)
	{
		auto range = observers.equal_range(RENDER);
		for (auto it = range.first; it != range.second; ++it)
		{
			/// @todo If only one match, move the object
			it->second->push(e);
		}
	}

	template< typename T >
	T& get()
	{
		return events.front< T>();
	}

	template< typename T >
	const T& get() const
	{
		return events.front< T>();
	}
private:
	virtual bool exec_inner(event_type);

	event_queue        events;

	std::multimap< event_type, Worker* > observers;
};

#endif // WORKER_H
