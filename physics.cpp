#include "physics.h"

#include <vector>

#include "camera.h"

Physics::Physics(Camera& camera_) : camera(camera_)
{

}

void Physics::exec()
{
	for (bool run = true; run; )
	{
		// Read time, push new positions,etc to cameras
		events.wait();

		event& e = events.front();
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

			camera.emplace(std::move(uppos));
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
		events.pop();
	}
}

