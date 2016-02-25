#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glm.hpp>

using namespace glm;

struct Quaternion
{
    // member variables
	float w;
	vec3 v;

    // constructors
	Quaternion():w(1) {}
	Quaternion( float w, const vec3 &v ):w(w),v(v) {}

    // operator overloads
	Quaternion operator-()const
	{
		return Quaternion( w,-v );
	}
	Quaternion operator+( const Quaternion &q )const
	{
		return Quaternion( w+q.w,v+q.v );
	}
	Quaternion operator-( const Quaternion &q )const
	{
		return Quaternion( w-q.w,v-q.v );
	}

//	Quaternion operator*( const Quaternion &q )const
//	{
////		return Quaternion( w*q.w-v.dot(q.v),q.v.cross(v)+q.v*w+v*q.w );
//		return Quaternion( w*q.w - dot() v.dot(q.v) ,q.v.cross(v)+q.v*w+v*q.w );
//	}
//	Vector operator*( const Vector &q )const{
//		return (*this * Quat(0,q) * -*this).v;
//	}
//	Quat operator*( float q )const{
//		return Quat( w*q,v*q );
//	}
//	Quat operator/( float q )const{
//		return Quat( w/q,v/q );
//	}
//	float dot( const Quat &q )const{
//		return v.x*q.v.x+v.y*q.v.y+v.z*q.v.z+w*q.w;
//	}
//	float length()const{
//		return sqrtf( w*w+v.x*v.x+v.y*v.y+v.z*v.z );
//	}
//	void normalize(){
//		*this=*this/length();
//	}
//	Quat normalized()const{
//		return *this/length();
//	}
//	Quat slerpTo( const Quat &q,float a )const{
//		Quat t=q;
//		float d=dot(q),b=1-a;
//		if( d<0 ){ t.w=-t.w;t.v=-t.v;d=-d; }
//		if( d<1-EPSILON ){
//			float om=acosf( d );
//			float si=sinf( om );
//			a=sinf( a*om )/si;
//			b=sinf( b*om )/si;
//		}
//		return *this*b + t*a;
//	}
//	Vector i()const{
//		float xz=v.x*v.z,wy=w*v.y;
//		float xy=v.x*v.y,wz=w*v.z;
//		float yy=v.y*v.y,zz=v.z*v.z;
//		return Vector( 1-2*(yy+zz),2*(xy-wz),2*(xz+wy) );
//	}
//	Vector j()const{
//		float yz=v.y*v.z,wx=w*v.x;
//		float xy=v.x*v.y,wz=w*v.z;
//		float xx=v.x*v.x,zz=v.z*v.z;
//		return Vector( 2*(xy+wz),1-2*(xx+zz),2*(yz-wx) );
//	}
//	Vector k()const{
//		float xz=v.x*v.z,wy=w*v.y;
//		float yz=v.y*v.z,wx=w*v.x;
//		float xx=v.x*v.x,yy=v.y*v.y;
//		return Vector( 2*(xz-wy),2*(yz+wx),1-2*(xx+yy) );
//	}
};

#endif // GEOMETRY_H
