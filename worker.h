#ifndef WORKER_H
#define WORKER_H

#include <map>
#include "event_queue.h"

class Worker
{
public:
	virtual ~Worker() {}

	void exec();

	template< event_type T >
	void push(event<T>&& arg)
	{
		events.push(std::move(arg));
	}

	template< event_type T >
	void push(const event<T>& arg)
	{
		events.push(arg);
	}

	void quit();

	static void connect(Worker*, Worker*, event_type);
protected:
	template< event_type T >
	void notify(event<T>&& e)
	{
		auto range = observers.equal_range(T);
		for (auto it = range.first; it != range.second; ++it)
		{
			/// @todo If only one match, move the object
			it->second->push(e);
		}
	}

	template< event_type T >
	event<T>& get()
	{
		return events.front< T>();
	}

	template< event_type T >
	const event<T>& get() const
	{
		return events.front< T>();
	}
private:
	virtual bool exec_inner(event_type);

	event_queue        events;

	std::multimap< event_type, Worker* > observers;
};

#endif // WORKER_H
