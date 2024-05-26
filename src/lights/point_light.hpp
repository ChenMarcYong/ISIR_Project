
#ifndef __RT_ISICG_POINT_LIGHT__
#define __RT_ISICG_POINT_LIGHT__

#include "base_light.hpp"

namespace RT_ISICG
{
	class PointLight : public BaseLight
	{
	  public:

		PointLight()		  = delete;
		virtual ~PointLight() = default;

		PointLight( const Vec3f & p_color, const float p_power, const Vec3f & p_position )
			: BaseLight( p_color, p_power, false ), _position( p_position ) {}
		

		inline const Vec3f & getPosition() const { return _position; }

		virtual LightSample sample( const Vec3f & p_point ) const override
		{
			//LightSample(const Vec3f & p_direction, const float p_distance, const Vec3f & p_radiance, const float p_pdf )

			Vec3f direction = glm::normalize( this->getPosition() - p_point );
			float distance	= glm::distance( this->getPosition(), p_point );
			Vec3f radiance	= this->getFlatColor() * this->getPower() * (float)(1.f / glm::pow(distance, 2));
			return LightSample( direction, distance, radiance, 1.f );

		}

	  protected:
		Vec3f _position = VEC3F_ZERO;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_BASE_LIGHT__
