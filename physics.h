#ifndef PHYSICS_H
#define PHYSICS_H

#include "worker.h"

class Physics : public Worker
{
public:
	Physics() = default;
private:
	bool exec_inner(event_type);

	std::vector< obj > objects;
};

#endif // PHYSICS_H
