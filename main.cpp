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
			obj t = { 0, { i, j, 0 }, { 1, 0, 0 } };

			pevents.emplace(event::CREATE_OBJECT, t);
		}
	}

	for (double t = 0; t < 10; t += 1./60)
	{
		pevents.emplace(event::UPDATE_TIME, t);

		event e;
		render.wait(e);
		switch (e.type)
		{
		case event::UPDATE_POSITIONS:
			for (std::size_t i = 0, n = e.u.posns.size(); i < n; ++i)
			{
				std::cout << e.u.posns[i].at<0>() << "," << e.u.posns[i].at<1>() << "," << e.u.posns[i].at<2>() << std::endl;
			}
			break;
		}

//		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	scene.emplace(event::QUIT);
	pevents.emplace(event::QUIT);
	camera.join();
	physics.join();

	return 0;
}
