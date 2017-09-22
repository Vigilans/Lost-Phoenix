#pragma once
#include <math.h>

template <typename _Ty>
struct basic_vector2D
{
	using value_type_t = _Ty;
	using reference_t = _Ty&;

	_Ty x;
	_Ty y;

	// ���ݷ�����������
	basic_vector2D(_Ty _x = _Ty(), _Ty _y = _Ty()) : x(_x), y(_y) {}
	
	// ������������a,b����һ����aָ��b�ĵ�λ��������
	basic_vector2D(const basic_vector2D& a, const basic_vector2D& b) { *this = (b - a).unit( ); }

	void set(_Ty _x, _Ty _y)
	{
		x = _x;
		y = _y;
	}

	double length() { return sqrt(x * x + y * y); }

	basic_vector2D unit()
	{
		double l = length();
		if (l > 0)
			return (*this) / l;
		else
			return basic_vector2D( );
	}

	bool operator==(const basic_vector2D& v2) { return x == v2.x && y == v2.y; }
	bool operator!=(const basic_vector2D& v2) { return x != v2.x || y != v2.y; }

	basic_vector2D operator+(const basic_vector2D& v2) const { return basic_vector2D(x + v2.x, y + v2.y); }
	basic_vector2D operator-(const basic_vector2D& v2) const { return basic_vector2D(x - v2.x, y - v2.y); }
	basic_vector2D operator*(_Ty scalar) { return basic_vector2D(x * scalar, y * scalar); }
	basic_vector2D operator/(_Ty scalar) { return basic_vector2D(x / scalar, y / scalar); }

	friend basic_vector2D& operator+=(basic_vector2D& v1, const basic_vector2D& v2)
	{
		v1.x += v2.x;
		v1.y += v2.y;

		return v1;
	}
	friend basic_vector2D& operator-=(basic_vector2D& v1, const basic_vector2D& v2)
	{
		v1.x -= v2.x;
		v1.y -= v2.y;

		return v1;
	}
	
	basic_vector2D& operator*=(_Ty scalar)
	{
		x *= scalar;
		y *= scalar;

		return *this;
	}
	basic_vector2D& operator/=(_Ty scalar)
	{
		x /= scalar;
		y /= scalar;

		return *this;
	}

	static basic_vector2D<double> unitByDegree(double degree)
	{
		constexpr double PI = 3.1415926535897932384626;
		double radian = degree * 180 / PI;
		return { cos(radian), sin(radian) };
	}
};

using Vector2D = basic_vector2D<double>;