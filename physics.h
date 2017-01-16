#ifndef PHYSICS_H
#define PHYSICS_H

#include "rwqueue.h"
#include "events.h"

/* Manages objects and moves them about
 */
void do_physics(rwqueue< event >& e, rwqueue< event >& scene);

#endif // PHYSICS_H
