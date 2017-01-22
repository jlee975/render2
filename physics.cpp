#include "physics.h"

#include <vector>

void do_physics(event_queue& pevents, event_queue& scene)
{
	event e;

	std::vector< obj > objects;

	while (true) {
		// Read time, push new positions,etc to cameras
		pevents.wait(e);

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
			return;
		case event::CREATE_OBJECT:
			objects.push_back(e.u.o);
			break;
		}
	}
}
