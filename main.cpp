#include <iostream>

#include <thread>
#include <mutex>
#include <condition_variable>

#include "rwvalue.h"

// one thread writes, another thread reads
/* Manages objects and moves them about
 */
void do_physics(rwvalue< double >& clock, rwvalue< double >& scene)
{
	while (true) {
		// Read time, push new positions,etc to cameras
		double time;
		clock.wait(time);
		if (time < 0)
			break;
		scene.set(time);
	}
}

void do_camera(rwvalue< double >& scene, rwvalue< double >& render)
{
	while (true) {
		double x;
		scene.wait(x);
		if (x < 0)
			break;
		render.set(x);
	}
}

int main()
{
	rwvalue< double > clock;
	rwvalue< double > scene;
	rwvalue< double > render;

	std::thread physics(do_physics, std::ref(clock), std::ref(scene));
	std::thread camera(do_camera, std::ref(scene), std::ref(render));

	for (double t = 0; t < 10; t += 1./60)
	{
		clock.set(t);

		double x;
		render.wait(x);
		std::cout << x << std::endl;
//		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	scene.set(-1);
	clock.set(-1);
	camera.join();
	physics.join();

	return 0;
}
