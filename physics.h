#ifndef PHYSICS_H
#define PHYSICS_H

#include "rwvalue.h"
#include "events.h"

/* Manages objects and moves them about
 */
void do_physics(rwvalue< phys::event >& e, rwvalue< cam::event >& scene);

#endif // PHYSICS_H
