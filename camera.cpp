#include "camera.h"

#include "render.h"

bool Camera::exec_inner()
{
	switch ( get_event_type())
	{
	case UPDATE_POSITIONS:
	{
		update_positions_event& up = get< update_positions_event >();
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
