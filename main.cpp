/// @todo Store faces as (edge index, opposite vertex index). Full description
/// of triangle in two values.
#include <iostream>

#include <thread>

#include "physics.h"
#include "camera.h"
#include "render.h"
#include "clock.h"

int main()
{
	Clock clock;
	Render  render;
	Camera  camera;
	Physics physics;


	Worker::connect(&clock, &physics, UPDATE_TIME);
	Worker::connect(&physics, &camera, UPDATE_POSITIONS);
	Worker::connect(&camera, &render, RENDER);
	Worker::connect(&render, &clock, DONE_RENDER);

	std::thread physics_thread(&Physics::exec, &physics);
	std::thread camera_thread(&Camera::exec, &camera);
	std::thread render_thread(&Render::exec, &render);

	for ( int i = 0; i < 10; ++i )
	{
		for ( int j = 0; j < 10; ++j )
		{
			const create_object_event e = { { 0, { i, j, 0 }, { 1, 0, 0 } } };

			physics.push(e);
		}
	}

	clock.exec();
	render.quit();
	camera.quit();
	physics.quit();
	render_thread.join();
	camera_thread.join();
	physics_thread.join();

	return 0;
}
