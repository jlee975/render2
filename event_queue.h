#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "rwqueue.h"
#include "events.h"

// A queue of "events" with a single consumer thread
typedef rwqueue< event > event_queue;

#endif // EVENTQUEUE_H
