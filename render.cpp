#include "render.h"

#include <iostream>

#include "physics.h"

void Render::exec(Physics& physics)
{
	for ( double t = 0; t < 10; t += 1. / 64 )
	{
		const update_time_event x = { t };

		physics.emplace(x);

		events.wait();
		exec_inner(events.front());

		events.pop();
	}
}

bool Render::exec_inner(event& e)
{
	switch ( e.type())
	{
	case event::RENDER:
	{
		render_event& u = e.get_render();

		for ( std::size_t i = 0, n = u.posns.size(); i < n; ++i )
		{
			std::cout << u.posns[i].at< 0 >() << "," << u.posns[i].at< 1 >() << "," << u.posns[i].at< 2 >() << std::endl;
		}
	}
	break;
	default:
		break;
	}

	return true;
}
