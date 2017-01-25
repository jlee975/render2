#include "render.h"

#include <iostream>

#include "physics.h"

void Render::exec(Physics& physics)
{
	double t = 0;
	physics.emplace(update_time_event{t});

	bool run = true;

	while (run)
	{
		events.wait();

		/// @todo Better predicition
		t += 1./64;
		physics.emplace(update_time_event{t});

		run = exec_inner(events.front());

		if (t > 10)
			run = false;

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
			std::cout << u.posns[i].at< 0 >() << "," << u.posns[i].at< 1 >() << "," << u.posns[i].at< 2 >() << "\n";
		}
	}
	break;
	default:
		break;
	}

	return true;
}
