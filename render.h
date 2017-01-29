#ifndef RENDER_H
#define RENDER_H

#include "worker.h"

class Render : public Worker
{
public:
	Render();
private:
	bool exec_inner();

	double time;
};


#endif // RENDER_H
