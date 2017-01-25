#include <iostream>

#include <thread>

#include "physics.h"
#include "camera.h"

int main()
{
	event_queue render;
	Camera camera(render);
	Physics physics(camera);

	std::thread physics_thread(&Physics::exec, &physics);
	std::thread camera_thread(&Camera::exec, &camera);

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			const create_object_event e = { { 0, { i, j, 0 }, { 1, 0, 0 } } };

			physics.emplace(e);
		}
	}

	for (double t = 0; t < 10; t += 1./64)
	{
		const update_time_event x = { t };

		physics.emplace(x);

		render.wait();
		event& e = render.front();
		switch (e.type())
		{
		case event::RENDER:
		{
			render_event& u = e.get_render();

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
	camera.emplace(q);
	physics.emplace(q);
	camera_thread.join();
	physics_thread.join();

	return 0;
}
