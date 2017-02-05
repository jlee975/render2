#include "clock.h"

Clock::Clock() : time(0)
{

}

bool Clock::exec_inner(event_type e)
{
	switch (e)
	{
	case DONE_RENDER:
	{
		const done_render_event& u = get< DONE_RENDER >();

		const double t1 = u.time + 1. / 64;

		if ( t1 > 10 )
		{
			return false;
		}

		notify(in_place_type<update_time_event>, t1);
	}
		break;
	default:
		break;
	}

	return true;
}

void Clock::init()
{
	notify(in_place_type<update_time_event>, 0);
}
