#include "render.h"

#include <iostream>

#include "physics.h"

void Render::exec(Physics& physics, Camera& camera)
{
	for ( double t = 0; t < 10; t += 1. / 64 )
	{
		const update_time_event x = { t };

		physics.emplace(x);

		events.wait();
		event& e = events.front();

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
		}

		events.pop();

		// std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}
