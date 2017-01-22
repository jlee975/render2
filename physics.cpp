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
		switch (e.type)
		{
		case event::UPDATE_TIME:
		{
			const double t = e.u.d;
			std::vector< point > posns;
			for (std::size_t i = 0, n = objects.size(); i < n; ++i)
			{
				posns.push_back(objects[i].pos + (t - objects[i].time) * objects[i].vel);
			}
			scene.emplace(event::UPDATE_POSITIONS, std::move(posns));
		}
			break;
		case event::QUIT:
			run = false;
			break;
		case event::CREATE_OBJECT:
			objects.push_back(e.u.o);
			break;
		}
		pevents.pop();
	}
}
