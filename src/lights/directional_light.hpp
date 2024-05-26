
#ifndef __RT_ISICG_DIRECTIONAL_LIGHT__
#define __RT_ISICG_DIRECTIONAL_LIGHT__

#include "base_light.hpp"

namespace RT_ISICG
{
	class DirectionalLight : public BaseLight
	{
	  public:
		DirectionalLight( const Vec3f & direction, const Vec3f & color, const float power )
			: BaseLight( color, power, false ), _direction( glm::normalize( direction ) )
		{
		}

		virtual LightSample sample( const Vec3f & p_point ) const override
		{
			Vec3f direction = _direction;
			float distance = std::numeric_limits<float>::infinity();
			float pdf = std::numeric_limits<float>::infinity();
			Vec3f radiance = getFlatColor() * getPower();
			return LightSample( direction, distance, radiance, pdf );
		}

	  protected:
		Vec3f _direction;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_DIRECTIONAL_LIGHT__