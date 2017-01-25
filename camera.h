#ifndef CAMERA_H
#define CAMERA_H

#include "event_queue.h"

class Camera
{
public:
	explicit Camera(event_queue& render_);
	void exec();

	template< typename... Args >
	void emplace(Args&&... args)
	{
		events.emplace(std::forward< Args >(args)...);
	}
private:
	event_queue events;
	event_queue& render;
};

#endif // CAMERA_H
