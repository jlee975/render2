#include <iostream>

#include <thread>

#include "physics.h"
#include "camera.h"

int main()
{
	rwvalue< phys::event > pevents;
	rwvalue< double > scene;
	rwvalue< double > render;

	std::thread physics(do_physics, std::ref(pevents), std::ref(scene));
	std::thread camera(do_camera, std::ref(scene), std::ref(render));

	for (double t = 0; t < 10; t += 1./60)
	{
		phys::event e = { phys::UPDATE_TIME };
		e.d = t;
		pevents.set(e);

		double x;
		render.wait(x);
		std::cout << x << std::endl;
//		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	scene.set(-1);
	{
		phys::event e = { phys::QUIT };
		pevents.set(e);
	}
	camera.join();
	physics.join();

	return 0;
}
