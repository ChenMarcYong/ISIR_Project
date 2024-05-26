#ifndef __RT_ISICG_PLASTIC_MATERIAL__
#define __RT_ISICG_PLASTIC_MATERIAL__

#include "base_material.hpp"
#include "brdfs/phong_brdf.hpp"
#include "brdfs/lambert_brdf.hpp"

namespace RT_ISICG
{
	class PlasticMaterial : public BaseMaterial
	{
	  public:
		PlasticMaterial( const std::string & p_name, const Vec3f & p_diffuse, const Vec3f & p_reflec, const float p_shininess )
			: BaseMaterial( p_name ), _LambertBrdf( p_diffuse ), _PhongBrdf( p_diffuse, p_reflec, p_shininess ) 
		{
		}
		virtual ~PlasticMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{



			return _LambertBrdf.evaluate() * 0.7f + _PhongBrdf.evaluate(p_hitRecord._normal, - p_ray.getDirection(), p_lightSample._direction) * 0.3f;
		}

		inline const Vec3f & getFlatColor() const override { return _LambertBrdf.getKd(); }

	  protected:
		LambertBRDF _LambertBrdf;
		PhongBRDF	_PhongBrdf;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_PLASTIC_MATERIAL__
