#ifndef PHYSICS_H
#define PHYSICS_H

#include "rwvalue.h"

namespace phys
{
enum event_type { UPDATE_TIME, QUIT };

struct event
{
	event_type type;

	union
	{
		double d;
	};
};
}

/* Manages objects and moves them about
 */
void do_physics(rwvalue< phys::event >& e, rwvalue< double >& scene);

#endif // PHYSICS_H
