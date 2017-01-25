#include "physics.h"

#include <vector>

#include "camera.h"

Physics::Physics(Camera& camera_) : camera(camera_)
{

}

void Physics::exec()
{
	bool run = true;
	while (run)
	{
		// Read time, push new positions,etc to cameras
		events.wait();

		run = exec_inner(events.front());

		events.pop();
	}
}

bool Physics::exec_inner(event & e)
{
	switch ( e.type())
	{
	case event::UPDATE_TIME:
	{
		update_time_event&     u = e.get_update_time();
		update_positions_event uppos;

		for ( std::size_t i = 0, n = objects.size(); i < n; ++i )
		{
			uppos.posns.push_back(objects[i].pos + ( u.time - objects[i].time ) * objects[i].vel);
		}

		camera.emplace(std::move(uppos));
	}
	break;
	case event::QUIT:
		return false;
	case event::CREATE_OBJECT:
	{
		create_object_event& u = e.get_create_object();
		objects.push_back(u.o);
	}
	break;
	default:
		break;
	} // switch

	return true;
}
