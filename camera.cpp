#include "camera.h"

void do_camera(rwqueue< event >& events, rwqueue< event >& render)
{
	event e;

	while (true) {
		events.wait(e);

		switch (e.type)
		{
		case UPDATE_POSITIONS:
			render.emplace(std::move(e));
			break;
		case QUIT:
			return;
		}
	}
}

