#ifndef PHYSICS_H
#define PHYSICS_H

#include "rwvalue.h"

namespace phys
{
enum event_type { NOEVENT, UPDATE_TIME, QUIT };

struct event
{
	event() : type(NOEVENT){ }
	explicit event(event_type t) : type(t) { }
	event(event_type t, double x) : type(t), d(x) { }

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
