#include "physics.h"

#include <vector>

void do_physics(event_queue& pevents, event_queue& scene)
{
	std::vector< obj > objects;

	for (bool run = true; run; )
	{
		// Read time, push new positions,etc to cameras
		pevents.wait();

		event& e = pevents.front();
		switch (e.type())
		{
		case event::UPDATE_TIME:
		{
			update_time_event& u = e.get_update_time();
			update_positions_event uppos;
			for (std::size_t i = 0, n = objects.size(); i < n; ++i)
			{
				uppos.posns.push_back(objects[i].pos + (u.time - objects[i].time) * objects[i].vel);
			}

			scene.emplace(std::move(uppos));
		}
			break;
		case event::QUIT:
			run = false;
			break;
		case event::CREATE_OBJECT:
		{
			create_object_event& u = e.get_create_object();
			objects.push_back(u.o);
		}
			break;
		}
		pevents.pop();
	}
}
