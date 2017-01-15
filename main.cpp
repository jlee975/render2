#include <iostream>

#include <thread>

#include "physics.h"
#include "camera.h"

int main()
{
	rwvalue< phys::event > pevents;
	rwvalue< cam::event > scene;
	rwvalue< double > render;

	std::thread physics(do_physics, std::ref(pevents), std::ref(scene));
	std::thread camera(do_camera, std::ref(scene), std::ref(render));

	for (double t = 0; t < 10; t += 1./60)
	{
		pevents.emplace(phys::UPDATE_TIME, t);

		double x;
		render.wait(x);
		std::cout << x << std::endl;
//		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	scene.emplace(cam::QUIT);
	pevents.emplace(phys::QUIT);
	camera.join();
	physics.join();

	return 0;
}
