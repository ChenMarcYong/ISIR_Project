#ifndef __RT_ISICG_WITTED_INTEGRATOR__
#define __RT_ISICG_WITTED_INTEGRATOR__

#include "direct_lighting_integrator.hpp"

namespace RT_ISICG
{
	class WhittedIntegrator : public DirectLightingIntegrator
	{
	  public:
		WhittedIntegrator() : DirectLightingIntegrator() {}
		virtual ~WhittedIntegrator() = default;

		const IntegratorType getType() const override { return IntegratorType::WHITTED; }

		// Return incoming luminance.
		Vec3f Li( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;
		Vec3f trace( const Scene & p_scene,
					 const Ray &   p_ray,
					 const float   p_tMin,
					 const float   p_tMax,
					 bool		   p_isNotIn ) const;

	  private:

		int	  _nbLightSamples = 1;
		int	  maxBounces	  = 5;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_WITTED_INTEGRATOR__
