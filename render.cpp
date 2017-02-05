#include "render.h"

#include <iostream>

#include "physics.h"

bool Render::exec_inner(event_type e)
{
	switch ( e )
	{
	case RENDER:
	{
		render_event& u = get< RENDER >();

		for ( std::size_t i = 0, n = u.posns.size(); i < n; ++i )
		{
			std::cout << u.posns[i].at< 0 >() << "," << u.posns[i].at< 1 >() << "," << u.posns[i].at< 2 >() << "\n";
		}

		notify(in_place_type< done_render_event >, u.time);

	}
	break;
	case QUIT:
		return false;
	default:
		break;
	} // switch

	return true;
}
