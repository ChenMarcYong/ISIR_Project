#include "implicit_surface.hpp"

namespace RT_ISICG
{
	bool ImplicitSurface::intersect( const Ray & p_ray,
									 const float p_tMin,
									 const float p_tMax,
									 HitRecord & p_hitRecord ) const
	{
		/// TODO


		// début, on commence à p_tMin
		float t			  = p_tMin;
		
		float distance = _sdf( p_ray.getOrigin() + t * p_ray.getDirection() ); // retourne la distance entre la surface et le point

		while ( distance  > _minDistance )	// tant que le rayon de la sphere est plus grand que notre epsilon on continue d'itérer
		{
			distance = _sdf( p_ray.getOrigin() + t * p_ray.getDirection() );																				// a chaque boucle on calcule une nouvelle sphere avec la méthode _sdf qui nous donne la distance entre le point à une distance t et la surface
			t += distance;	// on incrémente la distance du rayon.

			if ( t > p_tMax ) return false;	// si notre distance est plus grande que la distance maximun nous retournons faux
			
		}

		p_hitRecord._distance = t;
		p_hitRecord._object	  = this;
		p_hitRecord._point	  = Vec3f( p_ray.getOrigin() + t * p_ray.getDirection() );
		p_hitRecord._normal	  = _evaluateNormal( p_ray.getOrigin() + t * p_ray.getDirection() );
		p_hitRecord.faceNormal( p_ray.getDirection() );

		return true;


	}

	bool ImplicitSurface::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		/// TODO

		float t = p_tMin;

		float distance
			= _sdf( p_ray.getOrigin() + t * p_ray.getDirection() ); // retourne la distance entre la surface et le point

		while ( distance
				> _minDistance ) // tant que le rayon de la sphere est plus grand que notre epsilon on continue d'itérer
		{
			distance = _sdf(
				p_ray.getOrigin()
				+ t * p_ray.getDirection() ); // a chaque boucle on calcule une nouvelle sphere avec la méthode _sdf qui
											  // nous donne la distance entre le point à une distance t et la surface
			t += distance; // on incrémente la distance du rayon.

			if ( t > p_tMax )
				return false; // si notre distance est plus grande que la distance maximun nous retournons faux
		}

		return true;



	}
} // namespace RT_ISICG
