#ifndef RWQUEUE_H
#define RWQUEUE_H

#include <mutex>
#include <condition_variable>
#include <list>

// A single-produce, single-consumer queue
/// @todo Make lock-free
/// @todo Don't copy out the value. Once wait returns, simply access the value,
/// then call pop (front) when done
template< typename T >
class rwqueue
{
public:
	rwqueue() { }

	template< typename U >
	void set(U&& x)
	{
		std::unique_lock< std::mutex > lk(mut);

		values.push_back(std::forward< U >(x));
		lk.unlock();
		cv.notify_one();
	}

	template< typename... Args >
	void emplace(Args&&... args)
	{
		std::unique_lock< std::mutex > lk(mut);

		values.emplace_back(std::forward< Args >(args)...);
		lk.unlock();
		cv.notify_one();
	}

	void wait(T& dest)
	{
		std::unique_lock< std::mutex > lk(mut);
		while (values.empty())
		{
			cv.wait(lk);
		}
		dest = std::move(values.front());
		values.pop_front();
	}

private:
	std::mutex mut;
	std::condition_variable cv;

	std::list< T > values;
};

#endif // RWVALUE_H
