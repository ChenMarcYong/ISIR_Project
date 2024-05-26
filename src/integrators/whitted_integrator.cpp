#include "integrators/whitted_integrator.hpp"
namespace RT_ISICG
{
	Vec3f WhittedIntegrator::Li( const Scene & p_scene,
										const Ray &	  p_ray,
										const float	  p_tMin,
										const float	  p_tMax ) const
	{ return trace(p_scene, p_ray, p_tMin, p_tMax, true);
	}



	Vec3f WhittedIntegrator::trace( const Scene & p_scene,
									const Ray &	  p_ray,
									const float	  p_tMin,
									const float	  p_tMax, 
									bool		  p_isNotInObject ) const 
	{ 
		if ( p_ray._nbBounces >= maxBounces ) return BLACK;		// d�passe le nombre de rebonds maximum.

		HitRecord hitRecord;

		if ( p_scene.intersect(p_ray, p_tMin, p_tMax, hitRecord))	// si une intersection avec un objet de la sc�ne
		{
			if ( hitRecord._object->getMaterial()->isMirror() ) // si le mat�riau intersect� est un mirroir.
			{
				Vec3f reflected = glm::reflect( p_ray.getDirection(), hitRecord._normal );
				Ray	*reflectedRay = new Ray( Vec3f(hitRecord._point), glm::normalize(reflected) );
				reflectedRay->_nbBounces = p_ray._nbBounces + 1;
				reflectedRay->offset( hitRecord._normal );
				return trace(
					p_scene, *reflectedRay, p_tMin, p_tMax, p_isNotInObject ); // r�cursion avec le rayon r�flechie.
			}

			else if ( hitRecord._object->getMaterial()->isTransparent() ) 
			{ 
				

				Vec3f reflected			 = glm::reflect( p_ray.getDirection(), hitRecord._normal );
				Ray * reflectedRay		 = new Ray( Vec3f( hitRecord._point ), glm::normalize( reflected ) );
				reflectedRay->_nbBounces = p_ray._nbBounces + 1;
				reflectedRay->offset( hitRecord._normal );
				Vec3f reflex = trace(p_scene, *reflectedRay, p_tMin, p_tMax, p_isNotInObject ); // r�cursion avec le rayon r�flechie.


				float ior = hitRecord._object->getMaterial()->getIor();

				float n1, n2;		// lois de Snell-Descartes

				if ( p_isNotInObject )	// si p_isNotInObject est faux cela siginifie que l'on ai � l'ext�rieur du milieu.
				{ 
					n1 = 1.f;		// n1 sera �gale � l'indice de r�fraction dans l'air
					n2 = ior;		// n2 sera �gale � l'indice de r�fraction dans un milieu transparent 1.3
				}
				else				// on inverse dans le cas contraire
				{ 
					n1 = ior;
					n2 = 1.f;
				}
				float CosTetaI = glm::dot( -p_ray.getDirection(), hitRecord._normal );	// equation de Fresnel
				float SinTetaI = glm::sin( glm::acos( CosTetaI ) );
				if ( SinTetaI > 1.f ) return reflex; // r�flexion totale
				// n1 sin(Oi) = n2 sin(Ot)	
				// -> n1 * sqrt(1 - cos�(Oi)) =  n2 * sqrt(1 - cos�(Ot))	
				// -> cos�(Ot) = (n1� * cos�(Oi) - (n1� -n2�)) / n2� 
				// -> cos(Ot) = sqrt(1 - (n1 / n2)� * ( 1 - cos�(Oi))

				float CosTetaT = glm::sqrt( 1.f - ( n1 / n2 ) * ( n1 / n2 ) * (1.f - CosTetaI * CosTetaI) );	
				float Rs = pow( abs((n1 * CosTetaI - n2 * CosTetaT) / (n1 * CosTetaI + n2 * CosTetaT)), 2);	// doc wikip�dia (37, 38)

				float Rp = pow( abs((n2 * CosTetaT - n1 * CosTetaI) / (n2 * CosTetaT + n1 * CosTetaI)), 2);

				float kr = 0.5f * (Rs + Rp);

				if ( kr > 1.f ) return reflex; // r�flexion totale

				
				Vec3f refracted			 = glm::refract( p_ray.getDirection(), hitRecord._normal, n1 / n2 );
				Ray * refractedRay = new Ray( Vec3f( hitRecord._point ), glm::normalize( refracted ) );
				refractedRay->_nbBounces = p_ray._nbBounces + 1;
				refractedRay->offset(- hitRecord._normal );
				Vec3f refract = trace( p_scene, *refractedRay, p_tMin, p_tMax, !p_isNotInObject );
				return reflex * kr + refract * ( 1.f - kr );
			}

			else 
			{ 
				return _directLighting( p_scene, p_ray, p_tMin, p_tMax, hitRecord );
			}
		}
	}
	






} // namespace RT_ISICG
