#include "physics.h"

void do_physics(rwvalue< event >& pevents, rwvalue< event >& scene)
{
	event e;

	while (true) {
		// Read time, push new positions,etc to cameras
		pevents.wait(e);

		switch (e.type)
		{
		case UPDATE_TIME:
			scene.emplace(UPDATE_TIME, e.d);
			break;
		case QUIT:
			return;
		}
	}
}
