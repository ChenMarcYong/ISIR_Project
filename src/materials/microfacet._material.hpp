#ifndef __RT_ISICG_MICROFACET_MATERIAL__
#define __RT_ISICG_MICROFACET_MATERIAL__

#include "base_material.hpp"

#include "brdfs/cookTorance_brdf.hpp"
#include "brdfs/phong_brdf.hpp"
#include "brdfs/lambert_brdf.hpp"
#include "brdfs/orenNayar_brdf.hpp"

namespace RT_ISICG
{
	class MicrofacetMaterial : public BaseMaterial
	{
	  public:
		MicrofacetMaterial( const std::string & p_name,
							const Vec3f &		p_diffuse,
							const float			p_teta,
							const float			p_metalness )
			: BaseMaterial( p_name ), _OrenNayarbrdf( p_diffuse, p_teta ), _CookTorrancebrdf( p_diffuse, p_teta ),
			  _metalness( p_metalness ) {};

		virtual ~MicrofacetMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			return ( 1 - _metalness ) * _OrenNayarbrdf.evaluate(p_hitRecord._normal, -p_ray.getDirection(), p_lightSample._direction) + _metalness * _CookTorrancebrdf.evaluate(p_hitRecord._normal, -p_ray.getDirection(), p_lightSample._direction); // (1 - _metalness) * diffus + _metalness * specular
		}

		inline const Vec3f & getFlatColor() const override { return _OrenNayarbrdf.getKd(); }

	  protected:
		OrenNayarBRDF _OrenNayarbrdf;
		CookTorranceBRDF _CookTorrancebrdf;
		float _metalness;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_MICROFACET_MATERIAL__
