#ifndef EVENTS_H
#define EVENTS_H

#include <vector>

#include "config.h"

struct update_time_event
{
	double time;
};
struct create_object_event
{
	obj o;
};
struct update_positions_event
{
	std::vector< point > posns;
};
struct quit_event
{
};

class event
{
public:
	enum event_type {
		NOEVENT,
		UPDATE_TIME,
		UPDATE_POSITIONS,
		QUIT,
		CREATE_OBJECT
	};

	event() : type_(NOEVENT){ }
	event(const event&) = delete;
	event(event&&) = delete;

	explicit event(update_time_event e) : type_(UPDATE_TIME)
	{
		new (&u.update_time) update_time_event(std::move(e));
	}

	explicit event(create_object_event e) : type_(CREATE_OBJECT)
	{
		new (&u.create_object) create_object_event(std::move(e));
	}

	explicit event(update_positions_event e) : type_(UPDATE_POSITIONS)
	{
		new (&u.update_positions) update_positions_event(std::move(e));
	}

	explicit event(quit_event e) : type_(QUIT)
	{
		new (&u.quit) quit_event(std::move(e));
	}

	~event()
	{
		destroy();
	}

	event& operator=(const event&) = delete;
	event& operator=(event&&) = delete;

	event_type type() const
	{
		return type_;
	}

	update_positions_event& update_positions()
	{
		return u.update_positions;
	}

	update_time_event& update_time()
	{
		return u.update_time;
	}

	create_object_event& create_object()
	{
		return u.create_object;
	}

private:
	union storage
	{
		storage() { }
		~storage() { }
		update_time_event update_time;
		create_object_event create_object;
		update_positions_event update_positions;
		quit_event quit;
	};

	void destroy()
	{
		switch(type_)
		{
		case NOEVENT:
			break;
		case UPDATE_TIME:
			u.update_time.~update_time_event();
			break;
		case UPDATE_POSITIONS:
			u.update_positions.~update_positions_event();
			break;
		case QUIT:
			u.quit.~quit_event();
			break;
		case CREATE_OBJECT:
			u.create_object.~create_object_event();
			break;
		}
		type_ = NOEVENT;
	}

	event_type type_;

	storage u;

};

#endif // EVENTS_H
