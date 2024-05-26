#ifndef __RT_ISICG_IMPLICIT_FRACTALE_MANDELBUB__
#define __RT_ISICG_IMPLICIT_FRACTALE_MANDELBUB__

#include "base_object.hpp"
#include "objects/implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitMandelbulb : public ImplicitSurface
	{
	  public:
		ImplicitMandelbulb()		  = delete;
		virtual ~ImplicitMandelbulb() = default;

		ImplicitMandelbulb( const std::string & p_name, const int p_nbIteration, const float p_power )
			: ImplicitSurface( p_name ), _nbIteration( p_nbIteration ), _power( p_power )
		{
		}

		virtual float _sdf( const Vec3f & p_point ) const override
		{
			Vec3f z	 = p_point;
			float dr = 1.f;
			float r	 = 0.f;

			for ( int i = 0; i < _nbIteration; i++ )
			{
				r = glm::length( z );
				if ( r > 2.f ) break;

				float theta = acos( z.z / r );
				float phi	= atan2( z.y, z.x );

				dr = pow( r, _power - 1.f ) * _power * dr + 1.0f;

				float zr = pow( r, _power );
				theta	 = theta * _power;
				phi		 = phi * _power;

				z = zr * Vec3f( sin( theta ) * cos( phi ), sin( phi ) * sin( theta ), cos( theta ) ) + p_point;
			}

			return 0.5f * log( r ) * r / dr;
		}

	  private:
		const int	_nbIteration;
		const float _power;

	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_FRACTALE_MANDELBUB__
