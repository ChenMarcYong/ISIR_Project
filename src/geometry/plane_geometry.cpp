#include "plane_geometry.hpp"

namespace RT_ISICG
{
	bool PlaneGeometry::intersect( const Ray & p_ray, float & p_t ) const
	{
		float angle = glm::dot( this->getNormale(), p_ray.getDirection() );
		// Si le plan et le rayon ne sont pas parallèles
		if ( angle != 0.f )
		{ // Attention à la comparaison avec 0
			Vec3f po = this->getPoint() - p_ray.getOrigin();
			p_t		 = glm::dot( po, this->getNormale() ) / angle;
			return true; 
		}	
		// Sinon, pas d’intersection
		return false;
	}

} // namespace RT_ISICG
