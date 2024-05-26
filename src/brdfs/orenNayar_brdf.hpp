#ifndef __RT_ISICG_BRDF_ORENNAYAR__
#define __RT_ISICG_BRDF_ORENNAYAR__

#include "defines.hpp"

namespace RT_ISICG
{
	class OrenNayarBRDF
	{
	  public:
		OrenNayarBRDF( const Vec3f & p_kd, const float sigma ) : _kd( p_kd ) 
		{
			_A = 1.f - 0.5f * ( sigma * sigma ) / ( sigma * sigma  + 0.33f);
			_B = 0.45f * ( sigma * sigma ) / ( sigma * sigma  + 0.09f);
		};

		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate( const Vec3f & SurfaceNormal,
							   const Vec3f & ObservationDirection,
							   const Vec3f &	 IncidenceDirection )
			const // à partir de la normale à la surface et des directions d’observation et d’incidence
		{
			
			float tetaObser = glm::dot( SurfaceNormal, ObservationDirection );	// angle formé entre les vecteurs de la surface normale et de la direction d'observation.
			float tetaInc	= glm::dot( SurfaceNormal, IncidenceDirection );	// angle formé entre les vecteurs de la surface normale et de la direction d'incidence.

			float tetaObserInv = glm::acos( tetaObser );
			float tetaIncInv   = glm::acos( tetaInc );

			float Alpha = glm::max( tetaObserInv, tetaIncInv );
			float Beta = glm::min( tetaObserInv, tetaIncInv );

			float phi_i = std::atan2( IncidenceDirection.y, IncidenceDirection.x );	
			float phi_o = std::atan2( ObservationDirection.y, ObservationDirection.x );

			float cosPhi = glm::cos( phi_i - phi_o );

			return _kd * INV_PIf * ( _A + ( _B * glm::max( 0.f, cosPhi ) * glm::sin( Alpha ) * glm::tan( Beta ) ) ); 
		}

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f _kd = WHITE;


		float _A; 
		float _B;


	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_ORENNAYAR__
