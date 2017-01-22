#ifndef CONFIG_H
#define CONFIG_H

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


#endif // CONFIG_H
