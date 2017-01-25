#ifndef PHYSICS_H
#define PHYSICS_H

#include "event_queue.h"

class Camera;

class Physics
{
public:
	explicit Physics(Camera& camera_);
	void exec();

	template< typename... Args >
	void emplace(Args&&... args)
	{
		events.emplace(std::forward< Args >(args)...);
	}
private:
	event_queue events;
	Camera& camera;
	std::vector< obj > objects;
};

#endif // PHYSICS_H
