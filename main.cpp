#include <iostream>

#include <thread>

#include "physics.h"
#include "camera.h"
#include "render.h"

int main()
{
	Render  render;
	Camera  camera;
	Physics physics;

	Worker::connect(&physics, &camera, event::UPDATE_POSITIONS);
	Worker::connect(&camera, &render, event::RENDER);
	Worker::connect(&render, &physics, event::UPDATE_TIME);

	std::thread physics_thread(&Physics::exec, &physics);
	std::thread camera_thread(&Camera::exec, &camera);

	for ( int i = 0; i < 10; ++i )
	{
		for ( int j = 0; j < 10; ++j )
		{
			const create_object_event e = { { 0, { i, j, 0 }, { 1, 0, 0 } } };

			physics.emplace(e);
		}
	}

	physics.emplace(update_time_event{0});

	render.exec();
	camera.quit();
	physics.quit();
	camera_thread.join();
	physics_thread.join();

	return 0;
}
