#ifndef __RT_ISICG_IMPLICIT_SPHERE__
#define __RT_ISICG_IMPLICIT_SPHERE__

#include "base_object.hpp"
#include "objects/implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitSphere : public ImplicitSurface
	{
	  public:
		ImplicitSphere() = delete;
		virtual ~ImplicitSphere() = default;

		ImplicitSphere( const std::string & p_name, const Vec3f & p_centre, const float & p_rayon )
			: ImplicitSurface( p_name ), _centre( p_centre ), _rayon( p_rayon )
		{
		}

		virtual float _sdf( const Vec3f & p_point ) const override { return glm::length( p_point - _centre ) - _rayon; }

	  private:
		const Vec3f _centre;
		const float _rayon;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_SPHERE__
