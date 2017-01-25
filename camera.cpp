#include "camera.h"

Camera::Camera(event_queue& render_) : render(render_)
{

}

void Camera::exec()
{
	for (bool run = true; run; )
	{
		events.wait();

		event& e = events.front();
		switch (e.type())
		{
		case event::UPDATE_POSITIONS:
		{
			render_event re = { std::move(e.get_update_positions().posns) };
			render.emplace(re);
		}
			break;
		case event::QUIT:
			run = false;
			break;
		}

		events.pop();
	}
}


