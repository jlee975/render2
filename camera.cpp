#include "camera.h"

void do_camera(event_queue& events, event_queue& render)
{
	for (bool run = true; run; )
	{
		events.wait();

		event& e = events.front();
		switch (e.type())
		{
		case event::UPDATE_POSITIONS:
			/// @todo Move the event with a splice-like function
			render.emplace(e.get_update_positions());
			break;
		case event::QUIT:
			run = false;
			break;
		}

		events.pop();
	}
}

