#include "physics.h"

#include <vector>

#include "camera.h"

Physics::Physics(Camera& camera_) : camera(camera_)
{

}

bool Physics::exec_inner(event& e)
{
	switch ( e.type())
	{
	case event::UPDATE_TIME:
	{
		update_time_event&     u = e.get_update_time();
		update_positions_event uppos = { u.time, { } };

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
