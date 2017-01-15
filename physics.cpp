#include "physics.h"

void do_physics(rwvalue< phys::event >& pevents, rwvalue< cam::event >& scene)
{
	phys::event e;

	while (true) {
		// Read time, push new positions,etc to cameras
		pevents.wait(e);

		switch (e.type)
		{
		case phys::UPDATE_TIME:
			scene.emplace(cam::UPDATE_TIME, e.d);
			break;
		case phys::QUIT:
			return;
		}
	}
}
