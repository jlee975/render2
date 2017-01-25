#ifndef RENDER_H
#define RENDER_H

#include "event_queue.h"
class Physics;
class Camera;

class Render
{
public:
	template< typename... Args >
	void emplace(Args&& ... args)
	{
		events.emplace(std::forward< Args >(args) ...);
	}

	void exec(Physics& physics);
private:
	bool exec_inner(event&);

	event_queue events;
};


#endif // RENDER_H
