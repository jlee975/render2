#include "camera.h"

void do_camera(event_queue& events, event_queue& render)
{
	event e;

	while (true) {
		events.wait(e);

		switch (e.type)
		{
		case event::UPDATE_POSITIONS:
			render.emplace(std::move(e));
			break;
		case event::QUIT:
			return;
		}
	}
}

