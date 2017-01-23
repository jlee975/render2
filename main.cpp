#include <iostream>

#include <thread>

#include "physics.h"
#include "camera.h"

int main()
{
	event_queue pevents;
	event_queue scene;
	event_queue render;

	std::thread physics(do_physics, std::ref(pevents), std::ref(scene));
	std::thread camera(do_camera, std::ref(scene), std::ref(render));

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			const create_object_event e = { { 0, { i, j, 0 }, { 1, 0, 0 } } };

			pevents.emplace(e);
		}
	}

	for (double t = 0; t < 10; t += 1./60)
	{
		const update_time_event x = { t };

		pevents.emplace(x);

		render.wait();
		event& e = render.front();
		switch (e.type())
		{
		case event::UPDATE_POSITIONS:
		{
			update_positions_event& u = e.get_update_positions();

			for (std::size_t i = 0, n = u.posns.size(); i < n; ++i)
			{
				std::cout << u.posns[i].at<0>() << "," << u.posns[i].at<1>() << "," << u.posns[i].at<2>() << std::endl;
			}
		}
			break;
		}
		render.pop();

//		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	quit_event q = { };
	scene.emplace(q);
	pevents.emplace(q);
	camera.join();
	physics.join();

	return 0;
}
