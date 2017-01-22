#include "camera.h"

void do_camera(event_queue& events, event_queue& render)
{
	while (true) {
		events.wait();

		event& e = events.front();
		switch (e.type)
		{
		case event::UPDATE_POSITIONS:
			render.emplace(std::move(e));
			break;
		case event::QUIT:
			return;
		}

		events.pop();
	}
}

