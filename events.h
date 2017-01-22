#ifndef EVENTS_H
#define EVENTS_H

#include <vector>

struct point
{
	double x;
	double y;
	double z;
};

inline point operator+(const point& l, const point& r)
{
	return { l.x + r.x, l.y + r.y, l.z + r.z };
}

inline point operator*(double s, const point& p)
{
	return { p.x * s, p.y * s, p.z * s };
}

struct obj
{
	double time;
	point pos;
	point vel;
};

struct event
{
	enum event_type {
		NOEVENT,
		UPDATE_TIME,
		UPDATE_POSITIONS,
		QUIT,
		CREATE_OBJECT
	};

	event() : type(NOEVENT){ }
	event(const event& e) : type(e.type) { copy(e); }
	explicit event(event_type t) : type(t) { }
	event(event_type t, double x) : type(t), u(x) {
	}
	event(event_type t, const obj& o) : type(t), u(o) {
	}
	event(event_type t, std::vector< point >&& posns) : type(t), u(std::move(posns))
	{
	}

	~event()
	{
		destroy();
	}

	event& operator=(const event& e)
	{
		destroy();
		type = e.type;
		copy(e);

		return *this;
	}

	void copy(const event& e)
	{
		switch(e.type)
		{
		case NOEVENT:
			break;
		case UPDATE_TIME:
			u.d = e.u.d;
			break;
		case UPDATE_POSITIONS:
			new (&u.posns)std::vector< point >(e.u.posns);
			break;
		case QUIT:
			break;
		case CREATE_OBJECT:
			u.o = e.u.o;
			break;
		}

	}

	void destroy()
	{
		switch(type)
		{
		case UPDATE_POSITIONS:
			u.posns.~vector();
			break;
		}
	}

	event_type type;

	union storage
	{
		storage() { }
		storage(double x) : d(x) { }
		storage(const obj& o_) : o(o_) { }
		storage(std::vector< point >&& posns_) : posns(posns_) { }

		~storage() { }

		double d;
		obj o;
		std::vector< point > posns;
	};

	storage u;

};

#endif // EVENTS_H
