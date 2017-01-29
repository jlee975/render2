#include "camera.h"

#include "render.h"

bool Camera::exec_inner(event_type e)
{
	switch ( e )
	{
	case UPDATE_POSITIONS:
	{
		update_positions_event& up = get< UPDATE_POSITIONS >();
		notify(render_event{ up.time, std::move(up.posns) });
	}
	break;
	case QUIT:
		return false;

	default:
		break;
	}

	return true;
}
