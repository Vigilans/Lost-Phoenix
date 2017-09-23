#pragma once
#include <math.h>

/// <summary>
/// 数学二维向量模板类。
/// </summary>
template <typename _Ty>
struct basic_vector2D
{
	using value_type_t = _Ty;
	using reference_t = _Ty&;

	_Ty x;
	_Ty y;
	
	/// <summary>
	/// 根据分量构造向量。
	/// </summary>
	/// <param name="_x"> (可选) x方向分量。默认为0。 </param>
	/// <param name="_y"> (Optional) y方向分量。默认为0。 </param>
	basic_vector2D(_Ty _x = _Ty(), _Ty _y = _Ty()) : x(_x), y(_y) {}
	
	/// <summary>
	/// 根据两个向量a,b构建一个从a指向b的单位方向向量。
	/// </summary>
	/// <param name="a"> 起点向量。 </param>
	/// <param name="b"> 终点向量。 </param>
	basic_vector2D(const basic_vector2D& a, const basic_vector2D& b) { *this = (b - a).unit( ); }

	void set(_Ty _x, _Ty _y)
	{
		x = _x;
		y = _y;
	}

	double length() { return sqrt(x * x + y * y); }
	
	/// <summary>
	/// 获取当前向量的方向单位向量。
	/// </summary>
	/// <returns>
	/// 一个单位向量，方向与当前向量相同。
	/// </returns>
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
	
	/// <summary>
	/// 根据与x轴的偏角构造一个单位向量。
	/// </summary>
	/// <param name="degree"> 与x轴正向的夹角。为角度制。 </param>
	/// <returns>
	/// 一个单位向量，与x轴正向夹角为参数偏角。
	/// </returns>
	static basic_vector2D<double> unitByDegree(double degree)
	{
		constexpr double PI = 3.1415926535897932384626;
		double radian = degree * 180 / PI;
		return { cos(radian), sin(radian) };
	}
};

using Vector2D = basic_vector2D<double>;