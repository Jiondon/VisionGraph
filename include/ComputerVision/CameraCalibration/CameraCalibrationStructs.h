//
// Adaptive Vision Library 4.10.0.61766
// This file is a part of Adaptive Vision Library, version 4.10
// Copyright (C) 2018 Future Processing Sp. z o. o.
//
// This file should not be included directly in your program.
// Please, include the main header file of the library instead.
//

#ifndef _CAMERACALIBRATIONSTRUCTS_H
#define _CAMERACALIBRATIONSTRUCTS_H

#include "ATL/AtlTypes.h"

namespace avl
{
	struct LensDistortion
	{
		float	k1;
		float	k2;
		float	p1;
		float	p2;
		float	k3;
		float	k4;
		float	k5;
		float	k6;
		float	s1;
		float	s2;
		float	s3;
		float	s4;

		explicit LensDistortion
		(
			float k1_ = 0.0f,
			float k2_ = 0.0f,
			float p1_ = 0.0f,
			float p2_ = 0.0f,
			float k3_ = 0.0f,
			float k4_ = 0.0f,
			float k5_ = 0.0f,
			float k6_ = 0.0f,
			float s1_ = 0.0f,
			float s2_ = 0.0f,
			float s3_ = 0.0f,
			float s4_ = 0.0f 
		) :
			 k1(k1_),
			 k2(k2_),
			 p1(p1_),
			 p2(p2_),
			 k3(k3_),
			 k4(k4_),
			 k5(k5_),
			 k6(k6_),
			 s1(s1_),
			 s2(s2_),
			 s3(s3_),
			 s4(s4_) 
		{}

		float K1() const	{ return k1;	};
		float K2() const	{ return k2;	};
		float P1() const	{ return p1;	};
		float P2() const	{ return p2;	};
		float K3() const	{ return k3;	};
		float K4() const	{ return k4;	};
		float K5() const	{ return k5;	};
		float K6() const	{ return k6;	};
		float S1() const	{ return s1;	};
		float S2() const	{ return s2;	};
		float S3() const	{ return s3;	};
		float S4() const	{ return s4;	};

		bool operator == ( const avl::LensDistortion& rhs ) const
		{
			return k1 == rhs.k1 && 
			k2 == rhs.k2 && 
			p1 == rhs.p1 && 
			p2 == rhs.p2 && 
			k3 == rhs.k3 && 
			k4 == rhs.k4 && 
			k5 == rhs.k5 && 
			k6 == rhs.k6 && 
			s1 == rhs.s1 && 
			s2 == rhs.s2 && 
			s3 == rhs.s3 && 
			s4 == rhs.s4;
		}

		bool operator != ( const avl::LensDistortion& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

	struct Position3D
	{
		float	x;
		float	y;
		float	z;
		float	phi;
		float	theta;
		float	psi;

		explicit Position3D
		(
			float x_ = 0.0f,
			float y_ = 0.0f,
			float z_ = 0.0f,
			float phi_ = 0.0f,
			float theta_ = 0.0f,
			float psi_ = 0.0f 
		) :
			 x(x_),
			 y(y_),
			 z(z_),
			 phi(phi_),
			 theta(theta_),
			 psi(psi_) 
		{}

		float X() const		{ return x;		};
		float Y() const		{ return y;		};
		float Z() const		{ return z;		};
		float Phi() const	{ return phi;	};
		float Theta() const	{ return theta;	};
		float Psi() const	{ return psi;	};

		bool operator == ( const avl::Position3D& rhs ) const
		{
			return x == rhs.x && 
			y == rhs.y && 
			z == rhs.z && 
			phi == rhs.phi && 
			theta == rhs.theta && 
			psi == rhs.psi;
		}

		bool operator != ( const avl::Position3D& rhs ) const
		{
			return !(operator==(rhs));
		}

	};

} //namespace avl


#endif

