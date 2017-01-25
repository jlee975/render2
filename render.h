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

	void exec(Physics& physics, Camera& camera);

private:
	event_queue events;
};


#endif // RENDER_H
