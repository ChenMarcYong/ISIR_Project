
#ifndef __RT_ISICG_SPHERE_LIGHT__
#define __RT_ISICG_SPHERE_LIGHT__

#include "base_light.hpp"
#include "utils/random.hpp"

namespace RT_ISICG
{
	class SphereLight : public BaseLight
	{
	  public:
		SphereLight()		 = delete;
		virtual ~SphereLight() = default;

		SphereLight( const Vec3f & p_centre, const float p_rayon, const Vec3f & p_color, const float p_power )
			: BaseLight( p_color, p_power, true ), _centre( p_centre ), _rayon( p_rayon )
		{
			_area = 4.f * PIf * _rayon * _rayon;
		}

		inline const Vec3f & getCenter() const { return _centre; }
		inline const float	 getRadius() const { return _rayon; }
		inline const float	 getArea() const { return _area; }

		virtual LightSample sample( const Vec3f & p_point ) const override
		{
			// LightSample(const Vec3f & p_direction, const float p_distance, const Vec3f & p_radiance, const float
			// p_pdf )
			Vec3f randomPoint = _centre + randomPointOnSphere() * _rayon;
			Vec3f direction	  = glm::normalize( randomPoint - p_point );
			float distance	  = glm::distance( p_point, randomPoint );

			Vec3f normal = glm::normalize( _centre - randomPoint );
			float cosTetaI = glm::dot( direction, normal );


			float pdf = distance * distance / (abs(cosTetaI) * _area);	//

			Vec3f radiance = _color * _power / pdf;
			return LightSample( direction, distance, radiance, pdf );
		}

		Vec3f randomPointOnSphere() const
		{
			float u = randomFloat();	// on génère 2 floats entre 0 et 1.
			float v = randomFloat();

			float theta = 2.f * PIf * u;		// Conversion de u et v en coordonnées sphériques
			float phi	= acos( 2.f * v - 1.f );

			float x = cos( theta ) * sin( phi );	// coordonnées cartésiennes, merci les formules de fig
			float y = sin( theta ) * sin( phi );
			float z = cos( phi );

			return Vec3f( x, y, z );
		}

	  protected:
		Vec3f _centre = VEC3F_ZERO;
		float _area		= 0.f;
		float _rayon;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_BASE_LIGHT__
