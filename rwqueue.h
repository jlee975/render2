#ifndef RWQUEUE_H
#define RWQUEUE_H

#include <mutex>
#include <condition_variable>

// A single-produce, single-consumer queue
/// @todo Make lock-free
/// @todo Different mutex for head and tail
template< typename T >
class rwqueue
{
public:
	typedef T value_type;

	rwqueue() : head(nullptr), tail(nullptr) { }

	rwqueue(const rwqueue&) = delete;
	rwqueue(rwqueue&&) = delete;
	rwqueue& operator=(const rwqueue&) = delete;
	rwqueue& operator=(rwqueue&&) = delete;

	~rwqueue()
	{
		std::unique_lock< std::mutex > lk(mut);
		item* t = head;
		while (t != nullptr)
		{
			item* next = t->next;
			delete t;
			t = next;
		}
	}

	template< typename U >
	void push(U&& x)
	{
		append(new item(std::forward< U >(x)));
	}

	template< typename... Args >
	void emplace(Args&&... args)
	{
		append(new item(std::forward< Args >(args)...));
	}

	/// @todo Don't think we need to lock if head is not null
	void wait()
	{
		std::unique_lock< std::mutex > lk(mut);
		while (head == nullptr)
		{
			cv.wait(lk);
		}
	}

	T& front()
	{
		return head->value;
	}

	const T& front() const
	{
		return head->value;
	}

	void pop()
	{
		item* t = nullptr;
		{
			std::unique_lock< std::mutex > lk(mut);
			if (head != nullptr)
			{
				t = head;
				if (t->next != nullptr)
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

private:
	struct item
	{
		template< typename... Args >
		item(Args&&... args) : next(nullptr), value(std::forward< Args >(args)...)
		{
		}

		item* next;
		T value;
	};

	void append(item* p)
	{
		std::unique_lock< std::mutex > lk(mut);

		if (tail)
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

	std::mutex mut;
	std::condition_variable cv;

	item* head;
	item* tail;
};

#endif // RWVALUE_H
