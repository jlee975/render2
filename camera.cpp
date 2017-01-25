#include "camera.h"

#include "render.h"

Camera::Camera(Render& render_) : render(render_)
{

}

void Camera::exec()
{
	bool run = true;

	while ( run )
	{
		events.wait();

		run = exec_inner(events.front());

		events.pop();
	}
}

bool Camera::exec_inner(event& e)
{
	switch ( e.type())
	{
	case event::UPDATE_POSITIONS:
	{
		update_positions_event& up = e.get_update_positions();
		render_event re = { up.time, std::move(up.posns) };
		render.emplace(std::move(re));
	}
	break;
	case event::QUIT:
		return false;

	default:
		break;
	}

	return true;
}
