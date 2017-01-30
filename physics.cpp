#include "physics.h"

#include <vector>

bool Physics::exec_inner(event_type e)
{
	switch ( e )
	{
	case UPDATE_TIME:
	{
		update_time_event&     u     = get< UPDATE_TIME >();
		std::vector< point > v;

		for ( std::size_t i = 0, n = objects.size(); i < n; ++i )
		{
			v.push_back(objects[i].pos + ( u.time - objects[i].time ) * objects[i].vel);
		}

		notify(in_place_type< update_positions_event >, u.time, std::move(v));
	}
	break;
	case QUIT:
		return false;

	case CREATE_OBJECT:
	{
		create_object_event& u = get< CREATE_OBJECT >();
		objects.push_back(u.o);
	}
	break;
	default:
		break;
	} // switch

	return true;
}
