#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "rwqueue.h"
#include "events.h"

typedef rwqueue< event > event_queue;

#endif // EVENTQUEUE_H
