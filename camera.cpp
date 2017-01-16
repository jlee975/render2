#include "camera.h"

void do_camera(rwqueue< event >& events, rwqueue< double >& render)
{
	event e;

	while (true) {
		events.wait(e);

		switch (e.type)
		{
		case UPDATE_TIME:
			render.set(e.d);
			break;
		case QUIT:
			return;
		}
	}
}

