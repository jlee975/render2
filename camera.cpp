#include "camera.h"

#include "render.h"

bool Camera::exec_inner(event& e)
{
	switch ( e.type())
	{
	case event::UPDATE_POSITIONS:
	{
		update_positions_event& up = e.get_update_positions();
		notify(render_event{ up.time, std::move(up.posns) });
	}
	break;
	case event::QUIT:
		return false;

	default:
		break;
	}

	return true;
}
