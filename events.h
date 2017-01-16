#ifndef EVENTS_H
#define EVENTS_H

enum event_type { NOEVENT, UPDATE_TIME, QUIT };

struct event
{
	event() : type(NOEVENT){ }
	explicit event(event_type t) : type(t) { }
	event(event_type t, double x) : type(t), d(x) { }

	event_type type;

	union
	{
		double d;
	};
};

#endif // EVENTS_H
