#include "sphere_geometry.hpp"

namespace RT_ISICG
{
	bool SphereGeometry::intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const
	{
		/// TODO !

		Vec3f oc = p_ray.getOrigin() - this->getCenter();
		float b = 2 * glm::dot( oc, p_ray.getDirection() );
		float c = glm::dot( oc, oc ) - this->getRadius() * this->getRadius();
		float delta = b * b - 4 * c;

		if ( delta > 0 ) 
		{ 
			
			float t1 = ( -b - sqrt( delta ) ) / 2;
			float t2	 = ( -b + sqrt( delta ) ) / 2;

			p_t1 = std::min( t1, t2 );
			p_t2 = std::max( t1, t2 );
			
			// * glm::dot(-p_ray.getDirection(), hitRecord._normal);

			return true;
		} 

		p_t1 = -1.f;
		p_t2 = -1.f;

		return false;
	}

} // namespace RT_ISICG
