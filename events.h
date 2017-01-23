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
	event(const event& e) { copy(e); }

	/// @todo Implement
	event(event&& e) { move(std::move(e)); }

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

	event& operator=(const event& e)
	{
		destroy();
		copy(e);

		return *this;
	}

	/// @todo Implement
	event& operator=(event&& e)
	{
		destroy();
		move(std::move(e));
		return *this;
	}

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

	// Precondition: type_ == NOEVENT and u has nothing in it
	void copy(const event& e)
	{
		switch(e.type_)
		{
		case NOEVENT:
			break;
		case UPDATE_TIME:
			new (&u.update_time) update_time_event(e.u.update_time);
			break;
		case UPDATE_POSITIONS:
			new (&u.update_positions) update_positions_event(e.u.update_positions);
			break;
		case QUIT:
			new (&u.quit) quit_event(e.u.quit);
			break;
		case CREATE_OBJECT:
			new (&u.create_object) create_object_event(e.u.create_object);
			break;
		}

		type_ = e.type_;
	}

	void move(event&& e)
	{
		switch(e.type_)
		{
		case NOEVENT:
			break;
		case UPDATE_TIME:
			new (&u.update_time) update_time_event(std::move(e.u.update_time));
			e.u.update_time.~update_time_event();
			break;
		case UPDATE_POSITIONS:
			new (&u.update_positions) update_positions_event(std::move(e.u.update_positions));
			e.u.update_positions.~update_positions_event();
			break;
		case QUIT:
			new (&u.quit) quit_event(std::move(e.u.quit));
			e.u.quit.~quit_event();
			break;
		case CREATE_OBJECT:
			new (&u.create_object) create_object_event(std::move(e.u.create_object));
			e.u.create_object.~create_object_event();
			break;
		}

		type_ = e.type_;
		e.type_ = NOEVENT;
	}

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
