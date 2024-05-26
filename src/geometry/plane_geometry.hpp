#ifndef __RT_ISICG_PLANE_GEOMETRY__
#define __RT_ISICG_PLANE_GEOMETRY__

#include "base_geometry.hpp"

namespace RT_ISICG
{
	class PlaneGeometry : public BaseGeometry
	{
	  public:
		PlaneGeometry()			  = delete;
		virtual ~PlaneGeometry() = default;

		PlaneGeometry( const Vec3f & p_point, const Vec3f & p_normale ) : _point( p_point ), _normale( p_normale ) {}

		inline const Vec3f & getPoint() const { return _point; }
		inline const Vec3f & getNormale() const { return _normale; }

		bool intersect( const Ray & p_ray, float & p_t ) const;

		inline Vec3f computeNormal( const Vec3f & p_point ) const
		{
			/// TODO !
			return glm::normalize( _normale );
			// return Vec3f( 1.f );
		}

	  private:
		Vec3f _point = VEC3F_ZERO;
		Vec3f _normale = VEC3F_ZERO;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_PLANE_GEOMETRY__
