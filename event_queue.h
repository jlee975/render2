#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <vector>
#include <mutex>
#include <condition_variable>

#include "config.h"

enum event_type
{
	UPDATE_TIME,
	UPDATE_POSITIONS,
	QUIT,
	CREATE_OBJECT,
	RENDER,
	NUMBER_OF_EVENT_TYPES
};

template< event_type E >
struct event;

template< >
struct event< UPDATE_TIME >
{
	double time;
};

using update_time_event = event< UPDATE_TIME >;

template< >
struct event< CREATE_OBJECT >
{
	obj o;
};

using create_object_event = event< CREATE_OBJECT >;

template< >
struct event< UPDATE_POSITIONS >
{
	double time;
	std::vector< point > posns;
};
using update_positions_event = event< UPDATE_POSITIONS >;

template< >
struct event< QUIT >
{
};

using quit_event = event< QUIT >;

template< >
struct event< RENDER >
{
	double time;
	std::vector< point > posns;
};

using render_event = event< RENDER >;

// A queue of "events" with a single consumer thread
/// @todo Make lock-free
/// @todo Different mutex for head and tail
/// @todo Ring buffer to avoid news
class event_queue
{
public:
	event_queue() : head(nullptr), tail(nullptr)
	{
	}

	event_queue(const event_queue&)            = delete;
	event_queue(event_queue&&)                 = delete;
	event_queue& operator=(const event_queue&) = delete;
	event_queue& operator=(event_queue&&)      = delete;

	~event_queue()
	{
		std::unique_lock< std::mutex > lk(mut);
		item*                          t = head;

		while ( t != nullptr )
		{
			item* next = t->next;
			delete t;
			t = next;
		}
	}

	template< event_type T >
	void push(event< T >&& x)
	{
		append(new itemt< T >(std::move(x)));
	}

	template< event_type T >
	void push(const event< T >& x)
	{
		append(new itemt< T >(x));
	}

	/// @todo Don't think we need to lock if head is not null
	void wait()
	{
		std::unique_lock< std::mutex > lk(mut);

		while ( head == nullptr )
		{
			cv.wait(lk);
		}
	}

	template< event_type T >
	event< T >& front()
	{
		return static_cast< itemt< T >* >( head )->value;
	}

	template< event_type T >
	const event< T >& front() const
	{
		return static_cast< itemt< T >* >( head )->value;
	}

	void pop()
	{
		item* t = nullptr;
		{
			std::unique_lock< std::mutex > lk(mut);

			if ( head != nullptr )
			{
				t = head;

				if ( t->next != nullptr )
				{
					head = t->next;
				}
				else
				{
					head = nullptr;
					tail = nullptr;
				}
			}
		}

		delete t;
	}

	event_type type() const
	{
		return head->type;
	}

private:
	struct item
	{
		explicit item(event_type t) : type(t), next(nullptr)
		{
		}

		virtual ~item()
		{
		}

		event_type type;
		item* next;
	};

	template< event_type T >
	struct itemt : item
	{
		itemt(event< T > x) : item(T), value(x)
		{
		}

		event< T > value;
	};

	void append(item* p)
	{
		std::unique_lock< std::mutex > lk(mut);

		if ( tail )
		{
			tail->next = p;
		}
		else
		{
			head = p;
		}

		tail = p;
		lk.unlock();
		cv.notify_one();
	}

	std::mutex              mut;
	std::condition_variable cv;

	item* head;
	item* tail;
};

#endif // EVENTQUEUE_H
