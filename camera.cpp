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
		{
			render_event re = { std::move(e.get_update_positions().posns) };
			render.emplace(re);
		}
			break;
		case event::QUIT:
			run = false;
			break;
		}

		events.pop();
	}
}

