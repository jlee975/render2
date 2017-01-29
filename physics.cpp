#include "physics.h"

#include <vector>

bool Physics::exec_inner(event_type e)
{
	switch ( e)
	{
	case UPDATE_TIME:
	{
		update_time_event&     u = get< update_time_event >();
		update_positions_event uppos = { u.time, { } };

		for ( std::size_t i = 0, n = objects.size(); i < n; ++i )
		{
			uppos.posns.push_back(objects[i].pos + ( u.time - objects[i].time ) * objects[i].vel);
		}

		notify(std::move(uppos));
	}
	break;
	case QUIT:
		return false;

	case CREATE_OBJECT:
	{
		create_object_event& u = get<create_object_event >();
		objects.push_back(u.o);
	}
	break;
	default:
		break;
	} // switch

	return true;
}
