#include "render.h"

#include <iostream>

#include "physics.h"

Render::Render() : time(0)
{

}

bool Render::exec_inner()
{
	switch ( get_event_type())
	{
	case RENDER:
	{
		render_event& u = get< render_event >();

		for ( std::size_t i = 0, n = u.posns.size(); i < n; ++i )
		{
			std::cout << u.posns[i].at< 0 >() << "," << u.posns[i].at< 1 >() << "," << u.posns[i].at< 2 >() << "\n";
		}

		const double t1 = u.time + 1./64;
		if (t1 > 10)
			return false;

		notify(update_time_event{t1});
	}
	break;
	default:
		break;
	}

	return true;
}