#ifndef RENDER_H
#define RENDER_H

#include "worker.h"

class Render : public Worker
{
public:
	Render();
private:
	bool exec_inner(event&);

	double time;
};


#endif // RENDER_H
