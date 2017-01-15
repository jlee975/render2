#include "camera.h"

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

