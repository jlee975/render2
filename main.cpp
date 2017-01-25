#include <iostream>

#include <thread>

#include "physics.h"
#include "camera.h"
#include "render.h"

int main()
{
	Render  render;
	Camera  camera(render);
	Physics physics(camera);

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

	render.exec(physics);
	camera.quit();
	physics.quit();
	camera_thread.join();
	physics_thread.join();

	return 0;
}
