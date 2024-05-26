#ifndef __RT_ISICG_IMPLICIT_TORE__
#define __RT_ISICG_IMPLICIT_TORE__

#include "base_object.hpp"
#include "objects/implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitTore : public ImplicitSurface
	{
	  public:
		ImplicitTore()			  = delete;
		virtual ~ImplicitTore() = default;

		ImplicitTore( const std::string & p_name, const Vec3f & p_centre, float p_majorRayon, float p_minorRayon )
			: ImplicitSurface( p_name ), _centre( p_centre ), _majorRayon( p_majorRayon ), _minorRayon( p_minorRayon )
		{
		}


		virtual float _sdf( const Vec3f & p_point ) const override 
		{

			//
			float distance = glm::length( Vec2f( p_point - _centre ));	// distance entre point et le rayon du tore

			Vec2f q = Vec2f( distance - _majorRayon, ( p_point - _centre ).z );	
			return glm::length( q ) - _minorRayon;

		}

	  private:
		const Vec3f _centre;
		const float _majorRayon;
		const float _minorRayon;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_TORE__
