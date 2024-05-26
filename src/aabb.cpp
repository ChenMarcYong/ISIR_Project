#include "aabb.hpp"

namespace RT_ISICG
{
	bool AABB::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		/// TODO
		const Vec3f & origin	= p_ray.getOrigin();
		const Vec3f & direction = p_ray.getDirection();

		// il faut regarder pour chaque composante x, y et z s'il sont dans l'aabb.

		float tminX = ( _min.x - origin.x ) / direction.x;
		float tmaxX = ( _max.x - origin.x ) / direction.x;

		float tmin = glm::min( tminX, tmaxX );
		float tmax = glm::max( tminX, tmaxX );

		if ( tmin > tmax ) return false;

		float tminY = ( _min.y - origin.y ) / direction.y;
		float tmaxY = ( _max.y - origin.y ) / direction.y;

		tmin = glm::max( tmin, glm::min( tminY, tmaxY ) );
		tmax = glm::min( tmax, glm::max( tminY, tmaxY ) );

		if ( tmin > tmax ) return false;

		float tminZ = ( _min.z - origin.z ) / direction.z;
		float tmaxZ = ( _max.z - origin.z ) / direction.z;

		tmin = glm::max( tmin, glm::min( tminZ, tmaxZ ) );
		tmax = glm::min( tmax, glm::max( tminZ, tmaxZ ) );



		return tmax >= tmin && tmax >= 0;
	}
} // namespace RT_ISICG
