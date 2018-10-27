//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef AVL_GEOMETRY3D_H
#define AVL_GEOMETRY3D_H

#include "Geometry/Geometry.h"
#include "ATL/Array.hxx"
#include "AVLCommon/MatrixTypes.h"
#include <cmath>

namespace avl
{

	struct Point3D
	{
		Point3D()
			: x(0), y(0), z(0)
		{}
		Point3D( float x, float y, float z )
			: x(x), y(y), z(z)
		{}
		Point3D( int x, int y, int z )
			: x((float)x), y((float)y), z((float)z)
		{}
		explicit Point3D( Point2D p)
			: x(p.x), y(p.y), z(0)
		{}
		explicit Point3D( const atl::Array<float>& a )
			: x(a[0]), y(a[1]), z(a[2])
		{}

		float x;
		float y;
		float z;

		float X( void ) const	{ return x; }
		float Y( void ) const	{ return y; }
		float Z( void ) const	{ return z; }

		bool operator < ( const Point3D& rhs ) const
		{
			return (z != rhs.z) ? z < rhs.z : ((y != rhs.y) ? y < rhs.y : x < rhs.x);
		}
		bool operator > ( const Point3D& rhs ) const
		{
			return (z != rhs.z) ? z > rhs.z : ((y != rhs.y) ? y > rhs.y : x > rhs.x);
		}
		bool operator == ( const Point3D& rhs ) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z;
		}
		bool operator != ( const Point3D& rhs ) const
		{
			return !(operator==(rhs));
		}
	};

	struct Vector3D
	{
		Vector3D()
			: deltaX(0), deltaY(0), deltaZ(0)
		{}
		Vector3D( float x, float y, float z )
			: deltaX(x), deltaY(y), deltaZ(z)
		{}
		Vector3D( int x, int y, int z )
			: deltaX((float)x), deltaY((float)y), deltaZ((float)z)
		{}
		Vector3D( Point3D from, Point3D to)
			: deltaX(to.x-from.x), deltaY(to.y - from.y), deltaZ(to.z - from.z)
		{}
		explicit Vector3D( const atl::Array<float>& a )
			: deltaX(a[0]), deltaY(a[1]), deltaZ(a[2])
		{}

		float deltaX;
		float deltaY;
		float deltaZ;

		float DeltaX( void ) const	{ return deltaX; }
		float DeltaY( void ) const	{ return deltaY; }
		float DeltaZ( void ) const	{ return deltaZ; }

		bool operator == ( const Vector3D& rhs ) const
		{
			return deltaX == rhs.deltaX && deltaY == rhs.deltaY && deltaZ == rhs.deltaZ;
		}

		bool operator != ( const Vector3D& rhs ) const
		{
			return !(operator==(rhs));
		}

		Vector3D operator - () const
		{
			return Vector3D( -deltaX, -deltaY, -deltaZ );
		}

		float Length() const
		{
			return std::sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
		}

		atl::Array<float> toArray() const
		{
			atl::Array<float> result;
			result.PushBack(deltaX);
			result.PushBack(deltaY);
			result.PushBack(deltaZ);
			return result;
		}
	};


#ifndef CODE_REGION_POINT3D_VECTOR3D_OPERATORS
	inline Point3D operator+(const Point3D& p, const Vector3D& v)
	{
		return Point3D(p.x + v.deltaX, p.y + v.deltaY, p.z + v.deltaZ);
	}
	inline Point3D operator-(const Point3D& p, const Vector3D& v)
	{
		return Point3D(p.x - v.deltaX, p.y - v.deltaY, p.z - v.deltaZ);
	}
	inline Vector3D operator-(const Point3D& a, const Point3D& b)
	{
		return Vector3D(a.x - b.x, a.y - b.y, a.z - b.z);
	}
	inline Vector3D operator*(const Vector3D& v, float a)
	{
		return Vector3D(v.deltaX*a, v.deltaY*a, v.deltaZ*a);
	}
	inline Vector3D operator*(float a, const Vector3D& v)
	{
		return Vector3D(v.deltaX*a, v.deltaY*a, v.deltaZ*a);
	}
	inline Vector3D operator-(const Vector3D& a, const Vector3D& b)
	{
		return Vector3D(a.deltaX - b.deltaX, a.deltaY - b.deltaY, a.deltaZ - b.deltaZ);
	}
	inline Vector3D operator+(const Vector3D& a, const Vector3D& b)
	{
		return Vector3D(a.deltaX + b.deltaX, a.deltaY + b.deltaY, a.deltaZ + b.deltaZ);
	}
	inline Vector3D operator*(const Matrix& m, const Vector3D& v)
	{
		if ( m.RowCount() != 3 || m.ColCount() != 3 )
			throw atl::DomainError("Wrong matrix size in Matrix*Vector3D multiply");
		return Vector3D(
			m[0][0] * v.deltaX + m[0][1] * v.deltaY + m[0][2] * v.deltaZ,
			m[1][0] * v.deltaX + m[1][1] * v.deltaY + m[1][2] * v.deltaZ,
			m[2][0] * v.deltaX + m[2][1] * v.deltaY + m[2][2] * v.deltaZ
		);
	}
	inline Matrix crossProductMatrix(const Vector3D& v)
	{
		Matrix m(3, 3, 0.0f);
		m[0][1] = -v.deltaZ;
		m[1][0] =  v.deltaZ;
		m[0][2] =  v.deltaY;
		m[2][0] = -v.deltaY;
		m[1][2] = -v.deltaX;
		m[2][1] =  v.deltaX;
		return m;
	}
	inline Vector3D crossProduct(const Vector3D &A, const Vector3D &B)
	{
		return Vector3D(
			A.deltaY*B.deltaZ - A.deltaZ*B.deltaY,
			A.deltaZ*B.deltaX - A.deltaX*B.deltaZ,
			A.deltaX*B.deltaY - A.deltaY*B.deltaX
		);
	}
	inline float dotProduct(const Vector3D &A, const Vector3D &B)
	{
		return A.deltaX*B.deltaX + A.deltaY*B.deltaY + A.deltaZ * B.deltaZ;
	}
	inline Matrix outerProduct(const Vector3D &A, const Vector3D &B)
	{
		Matrix result(3, 3);
		result[0][0] = A.deltaX * B.deltaX;
		result[0][1] = A.deltaX * B.deltaY;
		result[0][2] = A.deltaX * B.deltaZ;
		result[1][0] = A.deltaY * B.deltaX;
		result[1][1] = A.deltaY * B.deltaY;
		result[1][2] = A.deltaY * B.deltaZ;
		result[2][0] = A.deltaZ * B.deltaX;
		result[2][1] = A.deltaZ * B.deltaY;
		result[2][2] = A.deltaZ * B.deltaZ;
		return result;
	}
#endif // CODE_REGION_POINT3D_VECTOR3D_OPERATORS

	struct Segment3D
	{
		Segment3D()
			: point1(), point2()
		{}
		Segment3D( const Point3D& point1_, const Point3D& point2_ )
			: point1(point1_), point2(point2_)
		{}
		Segment3D( float x1, float y1, float z1, float x2, float y2, float z2 )
			: point1(x1, y1, z1), point2(x2, y2, z2)
		{}

		Point3D point1;
		Point3D point2;

		Point3D Point1( void ) const	{ return point1;	}
		Point3D Point2( void ) const	{ return point2;	}
		float X1( void ) const		{ return point1.x;	}
		float Y1( void ) const		{ return point1.y;	}
		float Z1( void ) const		{ return point1.z;  }
		float X2( void ) const		{ return point2.x;	}
		float Y2( void ) const		{ return point2.y;	}
		float Z2( void ) const		{ return point2.z;  }

		bool operator == ( const Segment3D& rhs ) const
		{
			return point1 == rhs.point1 && point2 == rhs.point2;
		}
		bool operator != ( const Segment3D& rhs ) const
		{
			return !(operator==(rhs));
		}


		float Length() const
		{
			const float deltaX = X2() - X1();
			const float deltaY = Y2() - Y1();
			const float deltaZ = Z2() - Z1();
			return std::sqrt( deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ );
		}
	};

	struct Line3D
	{
		Line3D() : x(0), y(0), z(0), deltaX(0), deltaY(0), deltaZ(0) {}
		Line3D( float x_, float y_, float z_, float deltaX_, float deltaY_, float deltaZ_ )
			: x(x_), y(y_), z(z_), deltaX(deltaX_), deltaY(deltaY_), deltaZ(deltaZ_)
		{
			normaliseLine3D();
		}
		Line3D( const Point3D& point_, const Vector3D& delta_ )
			: x(point_.x), y(point_.y), z(point_.z), deltaX(delta_.deltaX), deltaY(delta_.deltaY), deltaZ(delta_.deltaZ)
		{
			normaliseLine3D();
		}

		float x;
		float y;
		float z;
		float deltaX;
		float deltaY;
		float deltaZ;

		float X( void ) const			{ return x;			}
		float Y( void ) const			{ return y;			}
		float Z( void ) const			{ return z;			}
		float DeltaX( void ) const		{ return deltaX;	}
		float DeltaY( void ) const		{ return deltaY;	}
		float DeltaZ( void ) const		{ return deltaZ;	}

		Point3D Point( void ) const		{ return Point3D(x, y, z);				}
		Vector3D Delta( void ) const	{ return Vector3D(deltaX, deltaY, deltaZ);	}

		bool operator == (const avl::Line3D& rhs) const
		{
			return Point() == rhs.Point() && Delta() == rhs.Delta();
		}

		bool operator != (const avl::Line3D& rhs) const
		{
			return !(operator==(rhs));
		}

	private:
		void normaliseLine3D()
		{
			float nrml = std::sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
			if (nrml > 0.0f)
			{
				deltaX /= nrml;
				deltaY /= nrml;
				deltaZ /= nrml;
			}

			const bool isAlmostZeroDeltaX = (std::fabs(deltaX) < 1e-3f);
			const bool isAlmostZeroDeltaY = (std::fabs(deltaY) < 1e-3f);
			if ((!isAlmostZeroDeltaX && deltaX < 0.0f) || (isAlmostZeroDeltaX && !isAlmostZeroDeltaY && deltaY < 0.0f) || (isAlmostZeroDeltaX && isAlmostZeroDeltaY && deltaZ < 0.0f))
			{
				deltaX = -deltaX;
				deltaY = -deltaY;
				deltaZ = -deltaZ;
			}

			float t = 0.0f;
			if (!isAlmostZeroDeltaX)
			{
				t = -x / deltaX;
			}
			else if (!isAlmostZeroDeltaY)
			{
				t = -y / deltaY;
			}
			else
			{
				t = -z / deltaZ;
			}

			x += t * deltaX;
			y += t * deltaY;
			z += t * deltaZ;
		}
	};

	struct Plane3D
	{
		Plane3D() : a(0), b(0), c(0), d(0) {}
		Plane3D( float A, float B, float C, float D ) : a(A), b(B), c(C), d(D)
		{
			normalisePlane();
		}

		float a;
		float b;
		float c;
		float d;

		float A( void ) const	{ return a;	}
		float B( void ) const	{ return b;	}
		float C( void ) const	{ return c;	}
		float D( void ) const	{ return d; }

		bool operator == ( const avl::Plane3D& rhs) const
		{
			return a == rhs.a && b == rhs.b && c == rhs.c && d == rhs.d;
		}

		bool operator != ( const avl::Plane3D& rhs) const
		{
			return !(operator==(rhs));
		}

	private:
		void normalisePlane()
		{
			float nrml = std::sqrt(a * a + b * b + c * c);
			if (nrml > 0.0f)
			{
				a /= nrml;
				b /= nrml;
				c /= nrml;
				d /= nrml;
			}

			const bool isAlmostZeroC = (std::fabs(c) < 1e-3f);
			const bool isAlmostZeroB = (std::fabs(b) < 1e-3f);
			if ((!isAlmostZeroC && c < 0.0f) || (isAlmostZeroC && !isAlmostZeroB && b < 0.0f) || (isAlmostZeroC && isAlmostZeroB && a < 0.0f))
			{
				a = -a;
				b = -b;
				c = -c;
				d = -d;
			}
		}
	};

	struct Circle3D
	{
		Circle3D()
			: center(), plane(), radius(0)
		{}
		Circle3D( const Point3D& center_, const Plane3D& plane_, float radius_ )
			: center(center_), plane(plane_), radius(radius_)
		{
			normaliseCircle3DPlane();
		}

		Point3D center;
		Plane3D plane;
		float radius;

		float Radius( void ) const		{ return radius;			}
		Plane3D Plane( void ) const			{ return plane;				}
		Point3D Center( void ) const		{ return center;			}
		float X( void ) const			{ return center.x;			}
		float Y( void ) const			{ return center.y;			}
		float Z( void ) const			{ return center.z;			}

		bool operator == ( const avl::Circle3D& rhs ) const
		{
			return center == rhs.center && plane == rhs.plane && radius == rhs.radius;
		}

		bool operator != ( const avl::Circle3D& rhs ) const
		{
			return !(operator==(rhs));
		}

	private:
		void normaliseCircle3DPlane()
		{
			plane.d = -(plane.a * center.x + plane.b * center.y + plane.c * center.z);
		}
	};

	struct Box3D
	{
		float x;
		float y;
		float z;
		float xLength;
		float yLength;
		float zLength;

		Box3D() : x(0), y(0), z(0), xLength(0), yLength(0), zLength(0) {}
		Box3D(float x_, float y_, float z_, float xLength_, float yLength_, float zLength_)
			: x(x_), y(y_), z(z_), xLength(xLength_), yLength(yLength_), zLength(zLength_)
		{
			if (xLength < 0 || yLength < 0 || zLength < 0)
			{
				throw atl::DomainError( "Negative dimension of Box3D." );
			}
		}

		float X( void ) const			{ return x;			}
		float Y( void ) const			{ return y;			}
		float Z( void ) const			{ return z;			}
		float XLength( void ) const		{ return xLength;	}
		float YLength( void ) const		{ return yLength;	}
		float ZLength( void ) const		{ return zLength;	}

		bool operator == (const Box3D& rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z &&
				   xLength == rhs.xLength && yLength == rhs.yLength && zLength == rhs.zLength;
		}

		bool operator != (const Box3D& rhs) const
		{
			return !(operator==(rhs));
		}

	};


	struct Sphere3D
	{
		Sphere3D()
			: center(), radius(0)
		{}
		Sphere3D( const Point3D& center_, float radius_ )
			: center(center_), radius(radius_)
		{}

		Point3D center;
		float radius;

		float Radius( void ) const		{ return radius;			}
		Point3D Center( void ) const		{ return center;			}
		float X( void ) const			{ return center.x;			}
		float Y( void ) const			{ return center.y;			}
		float Z( void ) const			{ return center.z;			}

		bool operator == ( const avl::Sphere3D& rhs ) const
		{
			return center == rhs.center && radius == rhs.radius;
		}

		bool operator != ( const avl::Sphere3D& rhs ) const
		{
			return !(operator==(rhs));
		}
	};

}

#endif
