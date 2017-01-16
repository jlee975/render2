#ifndef CAMERA_H
#define CAMERA_H

#include "rwqueue.h"
#include "events.h"

void do_camera(rwqueue< event >& scene, rwqueue< double >& render);

#endif // CAMERA_H
