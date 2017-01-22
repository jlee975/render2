#include "physics.h"

#include <vector>

void do_physics(rwqueue< event >& pevents, rwqueue< event >& scene)
{
	event e;

	std::vector< obj > objects;

	while (true) {
		// Read time, push new positions,etc to cameras
		pevents.wait(e);

		switch (e.type)
		{
		case UPDATE_TIME:
		{
			const double t = e.u.d;
			std::vector< point > posns;
			for (std::size_t i = 0, n = objects.size(); i < n; ++i)
			{
				posns.push_back(objects[i].pos + (t - objects[i].time) * objects[i].vel);
			}
			scene.emplace(UPDATE_POSITIONS, std::move(posns));
		}
			break;
		case QUIT:
			return;
		case CREATE_OBJECT:
			objects.push_back(e.u.o);
			break;
		}
	}
}
