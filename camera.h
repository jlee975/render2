#ifndef CAMERA_H
#define CAMERA_H

#include "worker.h"

class Render;

class Camera : public Worker
{
public:
	explicit Camera(Render& render_);

private:
	bool exec_inner(event&);

	Render&     render;
};

#endif // CAMERA_H
