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
	RENDER
};

struct update_time_event
{
	static const event_type type = UPDATE_TIME;
	double time;
};

struct create_object_event
{
	static const event_type type = CREATE_OBJECT;
	obj o;
};

struct update_positions_event
{
	static const event_type type = UPDATE_POSITIONS;
	double time;
	std::vector< point > posns;
};

struct quit_event
{
	static const event_type type = QUIT;
};

struct render_event
{
	static const event_type type = RENDER;
	double time;
	std::vector< point > posns;
};

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

	template< typename T >
	void push(T&& x)
	{
		append(new itemt<std::decay_t<T>>(std::forward< T >(x)));
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

	template< typename T >
	std::decay_t< T> & front()
	{
		return static_cast< itemt<std::decay_t<T>>* >(head)->value;
	}

	template< typename T >
	const std::decay_t<T>& front() const
	{
		return static_cast< itemt<std::decay_t<T>>* >(head)->value;
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
		explicit item(event_type t) : type(t), next(nullptr) { }
		virtual ~item() { }

		event_type type;
		item* next;
	};

	template< typename T >
	struct itemt : item
	{
		itemt(T x) : item(T::type), value(x) { }
		T value;
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
