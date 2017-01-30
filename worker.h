#ifndef WORKER_H
#define WORKER_H

#include <map>
#include "event_queue.h"

/// @todo Think about supporting multiple observers on a signal
class Worker
{
public:
	Worker();

	virtual ~Worker()
	{
	}

	void exec();

	template< event_type T >
	void push(event< T >&& arg)
	{
		events.push(std::move(arg));
	}

	template< event_type T >
	void push(const event< T >& arg)
	{
		events.push(arg);
	}

	template< event_type T, typename... Args >
	void emplace(in_place_type_t<event<T>>, Args... args)
	{
		events.emplace(in_place_type<event<T>>, std::forward<Args>(args)...);
	}

	void quit();

	static void connect(Worker*, Worker*, event_type);
protected:
	/// @todo Could support an emplace version
	template< event_type T >
	void notify(event< T >&& e)
	{
		if (Worker* w = observers[T])
		{
			w->push(std::move(e));
		}
	}

	template< event_type T, typename... Args >
	void notify(in_place_type_t<event<T>>, Args... args)
	{
		if (Worker* w = observers[T])
		{
			w->emplace(in_place_type<event<T>>, std::forward<Args>(args)...);
		}
	}

	template< event_type T >
	event< T >& get()
	{
		return events.front< T >();
	}

	template< event_type T >
	const event< T >& get() const
	{
		return events.front< T >();
	}

private:
	virtual bool exec_inner(event_type);

	event_queue events;

	std::array< Worker*, NUMBER_OF_EVENT_TYPES > observers;
};

#endif // WORKER_H
