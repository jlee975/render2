#ifndef CAMERA_H
#define CAMERA_H

#include "worker.h"

class Render;

class Camera : public Worker
{
public:
private:
	bool exec_inner(event_type);
};

#endif // CAMERA_H
