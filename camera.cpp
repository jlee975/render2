#include "camera.h"

#include "render.h"

Camera::Camera(Render& render_) : render(render_)
{

}

void Camera::exec()
{
	bool run = true;
	while (run)
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
		render_event re = { std::move(e.get_update_positions().posns) };
		render.emplace(re);
	}
	break;
	case event::QUIT:
		return false;
	default:
		break;
	}

	return true;
}
