#ifndef RWVALUE_H
#define RWVALUE_H

#include <mutex>
#include <condition_variable>

// one thread writes to, one thread reads from
// value can only be read once
template< typename T >
class rwvalue
{
public:
	rwvalue() : isset(false) { }

	template< typename U >
	void set(U&& x)
	{
		std::unique_lock< std::mutex > lk(mut);
		value = std::forward< U >(x);
		isset = true;
		lk.unlock();
		cv.notify_one();
	}

	void wait(T& dest)
	{
		std::unique_lock< std::mutex > lk(mut);
		while (!isset)
		{
			cv.wait(lk);
		}
		dest = std::move(value);
		isset = false;
	}

private:
	std::mutex mut;
	std::condition_variable cv;

	bool isset;
	T value;
};

#endif // RWVALUE_H
