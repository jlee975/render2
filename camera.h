#ifndef CAMERA_H
#define CAMERA_H

#include "event_queue.h"

class Render;

class Camera
{
public:
	explicit Camera(Render& render_);
	void exec();

	template< typename... Args >
	void emplace(Args&& ... args)
	{
		events.emplace(std::forward< Args >(args) ...);
	}

	void quit()
	{
		events.emplace(quit_event{});
	}

private:
	bool exec_inner(event&);

	event_queue  events;
	Render& render;
};

#endif // CAMERA_H
