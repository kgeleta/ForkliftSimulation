#pragma once

class Point3D
{
private:
	float x;
	float y;
	float z;
public:

	Point3D(float x, float y, float z) : x(x), y(y), z(z) {}

	float get_x() const
	{
		return x;
	}

	void set_x(float x)
	{
		this->x = x;
	}

	float get_y() const
	{
		return y;
	}

	void set_y(float y)
	{
		this->y = y;
	}

	float get_z() const
	{
		return z;
	}

	void set_z(float z)
	{
		this->z = z;
	}
};
