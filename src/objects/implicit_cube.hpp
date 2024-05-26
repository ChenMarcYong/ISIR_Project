#ifndef __RT_ISICG_IMPLICIT_CUBE__
#define __RT_ISICG_IMPLICIT_CUBE__

#include "base_object.hpp"
#include "objects/implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitCube : public ImplicitSurface
	{
	  public:
		ImplicitCube()			  = delete;
		virtual ~ImplicitCube() = default;

		ImplicitCube( const std::string & p_name, const Vec3f & p_centre, const float & p_taille)
			: ImplicitSurface( p_name ), _centre( p_centre ), _taille( p_taille )
		{
		}

		virtual float _sdf( const Vec3f & p_point ) const override
		{
			Vec3f distance				  = glm::abs( p_point - _centre ) - ( _taille / 2.0f );		// calcule de la distance entre le point et le centre du cube
			float insideDistance  = glm::min( glm::max( distance.x, glm::max( distance.y, distance.z ) ), 0.f );	
			float outsideDistance = glm::length( glm::max( distance, 0.f ) );
			return insideDistance + outsideDistance;
		}

	  private:
		const Vec3f _centre;
		const float _taille;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_CUBE__
