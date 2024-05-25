#include "direct_lighting_integrator.hpp"

namespace RT_ISICG
{
	Vec3f DirectLightingIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		HitRecord hitRecord;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			return _directLighting( p_scene, p_ray, p_tMin, p_tMax, hitRecord );
		}
		else { return _backgroundColor; }
	}

	Vec3f DirectLightingIntegrator::_directLighting( const Scene & p_scene,
													 const Ray & p_ray,
													 const float   p_tMin,
													 const float   p_tMax,
													 const HitRecord hitRecord ) const
	{
		Vec3f li = VEC3F_ZERO;

		for ( BaseLight * baseLight : p_scene.getLights() ) 
		{
			if ( baseLight->getIsSurface() ) 
			{ 
				Vec3f liTemp = VEC3F_ZERO;
				for ( int i = 0; i < _nbLightSamples; i++ ) 
				{
					LightSample lightSample = baseLight->sample( hitRecord._point );
					float		angle		= glm::max( glm::dot( lightSample._direction, hitRecord._normal ), 0.f );
					Ray			ray			= Ray( hitRecord._point, lightSample._direction );
					ray.offset( hitRecord._normal );
					if ( !p_scene.intersectAny( ray, p_tMin, lightSample._distance ) )
						liTemp += hitRecord._object->getMaterial()->shade(p_ray, hitRecord,  lightSample)  * lightSample._radiance * angle;							// hitRecord._object->getMaterial()->getFlatColor()
				}
				li += liTemp / (float)_nbLightSamples;
			}
			else 
			{
				LightSample lightSample = baseLight->sample( hitRecord._point );
				float		angle		= glm::max( glm::dot( lightSample._direction, hitRecord._normal ), 0.f );
				Ray			ray			= Ray( hitRecord._point, lightSample._direction );
				ray.offset( hitRecord._normal );
				if ( !p_scene.intersectAny( ray, p_tMin, lightSample._distance ) )
					li +=  hitRecord._object->getMaterial()->shade(p_ray, hitRecord,  lightSample)                                     //hitRecord._object->getMaterial()->getFlatColor()
						  * lightSample._radiance * angle;
			}

			
		}
		return li;	
	}
} // namespace RT_ISICG
