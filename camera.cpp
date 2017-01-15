#include "camera.h"

void do_camera(rwvalue< cam::event >& events, rwvalue< double >& render)
{
	cam::event e;

	while (true) {
		events.wait(e);

		switch (e.type)
		{
		case cam::UPDATE_TIME:
			render.set(e.d);
			break;
		case cam::QUIT:
			return;
		}
	}
}

