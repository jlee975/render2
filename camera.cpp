#include "camera.h"

void do_camera(event_queue& events, event_queue& render)
{
	for (bool run = true; run; )
	{
		events.wait();

		event& e = events.front();
		switch (e.type)
		{
		case event::UPDATE_POSITIONS:
			render.emplace(std::move(e));
			break;
		case event::QUIT:
			run = false;
			break;
		}

		events.pop();
	}
}

