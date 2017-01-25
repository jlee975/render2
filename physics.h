#ifndef PHYSICS_H
#define PHYSICS_H

#include "worker.h"

class Camera;

class Physics : public Worker
{
public:
	explicit Physics(Camera& camera_);

private:
	bool exec_inner(event&);

	Camera&            camera;
	std::vector< obj > objects;
};

#endif // PHYSICS_H
