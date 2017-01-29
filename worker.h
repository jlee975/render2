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
		const std::vector< Worker* >& v = observers[T];

		const std::size_t n = v.size();

		for (std::size_t i = 0; i + 1 < n; ++i)
		{
			v[i]->push(e);
		}
		v[n-1]->push(std::move(e));
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

	std::array< std::vector< Worker* >, NUMBER_OF_EVENT_TYPES > observers;
};

#endif // WORKER_H
