//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRY_H
#define AVL_GEOMETRY_H

#include "ATL/Error.h"
#include "ATL/AtlString.h"
#include <cmath>

namespace avl
{
	struct Point2D
	{
		Point2D()
			: x(0), y(0)
		{}
		Point2D( float x, float y )
			: x(x), y(y)
		{}
		Point2D ( int x, int y )
			: x((float)x), y((float)y)
		{}
		Point2D ( float x, int y )
			: x(x), y((float)y)
		{}
		Point2D ( int x, float y )
			: x((float)x), y(y)
		{}

		float x;
		float y;

		float X( void ) const	{ return x; }
		float Y( void ) const	{ return y; }

		bool operator < ( const Point2D& rhs ) const
		{
			return y != rhs.y ? y < rhs.y : x < rhs.x;
		}
		bool operator > ( const Point2D& rhs ) const
		{
			return y != rhs.y ? y > rhs.y : x > rhs.x;
		}
		bool operator == ( const Point2D& rhs ) const
		{
			return x == rhs.x && y == rhs.y;
		}
		bool operator != ( const Point2D& rhs ) const
		{
			return !(operator==(rhs));
		}
	};

	struct Line2D
	{
		Line2D() : a(0), b(0), c(0) {}
		Line2D( float A, float B, float C ) : a(A), b(B), c(C)
		{
			normaliseLine();
		}

		float a;
		float b;
		float c;

		float A( void ) const	{ return a;	}
		float B( void ) const	{ return b;	}
		float C( void ) const	{ return c;	}

		bool operator == ( const avl::Line2D& rhs) const
		{
			return a == rhs.a && b == rhs.b && c == rhs.c;
		}

		bool operator != ( const avl::Line2D& rhs) const
		{
			return !(operator==(rhs));
		}

	private:
		void normaliseLine()
		{
			float nrml = std::sqrt(a * a + b * b);
			if (nrml > 0.0f)
			{
				a /= nrml;
				b /= nrml;
				c /= nrml;
			}

			const bool isAlmostZero = (std::fabs(a) < 1e-3f);
			if ((isAlmostZero && b < 0.0f) || (!isAlmostZero && a < 0.0f))
			{
				a = -a;
				b = -b;
				c = -c;
			}
		}
	};

	struct Segment2D
	{
		Segment2D()
			: point1(), point2()
		{}
		Segment2D( const Point2D& point1_, const Point2D& point2_ )
			: point1(point1_), point2(point2_)
		{}
		Segment2D( float x1, float y1, float x2, float y2 )
			: point1(x1, y1), point2(x2, y2)
		{}
		
		Point2D point1;
		Point2D point2;

		Point2D Point1( void ) const	{ return point1;	}
		Point2D Point2( void ) const	{ return point2;	}
		float X1( void ) const		{ return point1.x;	}
		float Y1( void ) const		{ return point1.y;	}
		float X2( void ) const		{ return point2.x;	}
		float Y2( void ) const		{ return point2.y;	}

		bool operator == ( const Segment2D& rhs ) const
		{
			return point1 == rhs.point1 && point2 == rhs.point2;
		}
		bool operator != ( const Segment2D& rhs ) const
		{
			return !(operator==(rhs));
		}

		float Length() const
		{
			const float deltaX = X2() - X1();
			const float deltaY = Y2() - Y1();
			return std::sqrt( deltaX * deltaX + deltaY * deltaY );
		}
	};

	struct Circle2D
	{
		Circle2D()
			: center(), radius(0)
		{}
		Circle2D( const Point2D& center_, float radius_ )
			: center(center_), radius(radius_)
		{}
		Circle2D( float x, float y, float radius_ )
			: center(x, y), radius(radius_)
		{}
		Circle2D( int x, int y, int radius_ )
			: center((float)x, (float)y), radius((float)radius_)
		{}
		
		Point2D center;
		float radius;
		
		float Radius( void ) const		{ return radius;			}
		Point2D Center( void ) const		{ return center;			}
		float X( void ) const			{ return center.x;			}
		float Y( void ) const			{ return center.y;			}

		bool operator == ( const avl::Circle2D& rhs ) const
		{
			return center == rhs.center && radius == rhs.radius;
		}

		bool operator != ( const avl::Circle2D& rhs ) const
		{
			return !(operator==(rhs));
		}
	};

	struct Arc2D
	{
		Point2D center;
		float radius;
		float startAngle;
		float sweepAngle;

		Arc2D()
			: center(), radius(0), startAngle(0), sweepAngle(0)
		{}

		Arc2D(float x, float y, float radius_, float startAngle_, float sweepAngle_)
			: center(x, y), radius(radius_), startAngle(startAngle_), sweepAngle(sweepAngle_)
		{}

		Arc2D(const Point2D center_, float radius_, float startAngle_, float sweepAngle_)
			: center(center_), radius(radius_), startAngle(startAngle_), sweepAngle(sweepAngle_)
		{}

		Point2D Center() const				{ return center;					}
		float Radius( void ) const		{ return radius;					}
		float StartAngle( void ) const	{ return startAngle;				}
		float SweepAngle( void ) const	{ return sweepAngle;				}
		float X( void ) const			{ return center.x;					}
		float Y( void ) const			{ return center.y;					}
		Circle2D GetCircle() const			{ return Circle2D(center, radius);	}

		bool operator == ( const Arc2D& rhs ) const
		{
			return center == rhs.center && radius == rhs.radius && startAngle == rhs.startAngle && sweepAngle == rhs.sweepAngle;
		}

		bool operator != ( const Arc2D& rhs ) const
		{
			return !(operator==(rhs));
		}
	};

	inline void NormalizeAngle(float& ioAngle)
	{
		if (ioAngle < 0.0f)
		{
			int k = (int)std::ceil(-ioAngle / 360.0f);
			ioAngle += k * 360.0f;
		}
		else
		{
			int k = (int)std::floor(ioAngle / 360.0f);
			ioAngle -= k * 360.0f;
		}
	}

	struct Rectangle2D
	{
		Rectangle2D()
			: origin(), angle(0)
		{
			SetDimensions(0, 0);
		}
		Rectangle2D( const Point2D& origin_, float angle_, float width_, float height_ )
			: origin(origin_), angle(angle_)
		{
			SetDimensions(width_, height_);
			NormalizeAngle(angle);
		}
		Rectangle2D( float x, float y, float angle_, float width_, float height_ )
			: origin(x, y), angle(angle_)
		{
			SetDimensions(width_, height_);
			NormalizeAngle(angle);
		}
		
		Point2D origin;
		float angle;
		float width;
		float height;

		Point2D Origin( void ) const	{ return origin;	}
		float Angle( void ) const	{ return angle;		}
		float Width( void ) const	{ return width;		}
		float Height( void ) const	{ return height;	}
		float X( void ) const		{ return origin.x;	}
		float Y( void ) const		{ return origin.y;	}

		bool operator == ( const Rectangle2D& rhs ) const
		{
			return origin == rhs.origin && angle == rhs.angle && width == rhs.width && height == rhs.height;
		}
		bool operator != ( const Rectangle2D& rhs ) const
		{
			return !(operator==(rhs));
		}

	private:
		void SetDimensions(const float inWidth, const float inHeight)
		{
			if (inWidth < 0.0f)
			{
				throw atl::DomainError( "Negative width of Rectangle2D." );
			}
			if (inHeight < 0.0f)
			{
				throw atl::DomainError( "Negative height of Rectangle2D." );
			}

			width = inWidth;
			height = inHeight;
		}
	};

	struct Vector2D
	{
		Vector2D()
			: deltaX(0), deltaY(0)
		{}
		Vector2D( float x, float y )
			: deltaX(x), deltaY(y)
		{}
		Vector2D( Point2D from, Point2D to) 
			: deltaX(to.x-from.x), deltaY(to.y - from.y)
		{}

		float deltaX;
		float deltaY;

		float DeltaX( void ) const	{ return deltaX;	}
		float DeltaY( void ) const	{ return deltaY;	}

		bool operator == ( const Vector2D& rhs ) const
		{
			return deltaX == rhs.deltaX && deltaY == rhs.deltaY;
		}

		bool operator != ( const Vector2D& rhs ) const
		{
			return !(operator==(rhs));
		}

		Vector2D operator - () const
		{
			return Vector2D( -deltaX, -deltaY );
		}

		float Length() const
		{
			return std::sqrt(deltaX * deltaX + deltaY * deltaY);
		}
	};

#ifndef CODE_REGION_POINT2D_VECTOR2D_OPERATORS
	inline float crossProduct(const Vector2D &A, const Vector2D &B)
	{
		return A.deltaX * B.deltaY - A.deltaY * B.deltaX;
	}

	inline float dotProduct(const Vector2D &A, const Vector2D &B)
	{
		return A.deltaX * B.deltaX + A.deltaY * B.deltaY;
	}

	inline Point2D operator+(const Point2D& p, const Vector2D& v)
	{
		return Point2D(p.x + v.deltaX, p.y + v.deltaY);
	}
	inline Point2D operator-(const Point2D& p, const Vector2D& v)
	{
		return Point2D(p.x - v.deltaX, p.y - v.deltaY);
	}

	inline Vector2D operator-(const Point2D& a, const Point2D& b)
	{
		return Vector2D(a.x - b.x, a.y - b.y);
	}
	inline Vector2D operator*(const Vector2D& v, float a)
	{
		return Vector2D(v.deltaX*a, v.deltaY*a);
	}
	inline Vector2D operator*(float a, const Vector2D& v)
	{
		return Vector2D(v.deltaX*a, v.deltaY*a);
	}
	inline Vector2D operator-(const Vector2D& a, const Vector2D& b)
	{
		return Vector2D(a.deltaX - b.deltaX, a.deltaY - b.deltaY);
	}
	inline Vector2D operator+(const Vector2D& a, const Vector2D& b)
	{
		return Vector2D(a.deltaX + b.deltaX, a.deltaY + b.deltaY);
	}
#endif // CODE_REGION_POINT2D_VECTOR2D_OPERATORS

	struct CoordinateSystem2D
	{
		CoordinateSystem2D()
			: origin(), angle(0), scale(1.0f)
		{
		}
		CoordinateSystem2D( const Point2D& origin_, float angle_, float scale_ = 1.0f )
			: origin(origin_), angle(angle_)
		{
			SetScale(scale_);
			NormalizeAngle(angle);
		}
		CoordinateSystem2D( const Vector2D& delta, float angle_, float scale_ = 1.0f )
			: origin(delta.deltaX, delta.deltaY), angle(angle_)
		{
			SetScale(scale_);
			NormalizeAngle(angle);
		}
		CoordinateSystem2D( float x_, float y_, float angle_, float scale_ = 1.0f )
			: origin(x_, y_), angle(angle_)
		{
			SetScale(scale_);
			NormalizeAngle(angle);
		}
		
		Point2D origin;
		float angle;
		float scale;

		Point2D Origin( void ) const	{ return origin;	}
		float Angle( void ) const	{ return angle;		}
		float Scale( void ) const	{ return scale;		}
		float X( void ) const		{ return origin.x;	}
		float Y( void ) const		{ return origin.y;	}

		bool operator == ( const CoordinateSystem2D& rhs ) const
		{
			return origin == rhs.origin && angle == rhs.angle && scale == rhs.scale;
		}
		bool operator != ( const CoordinateSystem2D& rhs ) const
		{
			return !(operator==(rhs));
		}

	private:
		void SetScale(const float inScale)
		{
			if (inScale <= 0.0f)
			{
				throw atl::DomainError( "Not positive scale of CoordinateSystem2D." );
			}
			scale = inScale;
		}
	};


	struct StringLabel
	{
		atl::String text;
		Point2D position;

		StringLabel()
		{}

#ifdef HAS_CPP0X

		StringLabel(atl::String text, const Point2D& p)
		: text(std::move(text))
		, position(p)
		{}

#else

		StringLabel(const atl::String& text, const Point2D& p)
		: text(text)
		, position(p)
		{}

#endif

		const atl::String& Text() const
		{
			return text;
		}

		const Point2D& Position() const
		{
			return position;
		}

		operator const atl::String& () const
		{
			return text;
		}

		bool operator == (const StringLabel& other) const
		{
			return other.text == text && other.position == position;
		}

		bool operator != (const StringLabel& other) const
		{
			return other.text != text || other.position != position;
		}
	};
}

#endif
