#ifndef __RT_ISICG_BRDF_COOKTORRANCE__
#define __RT_ISICG_BRDF_COOKTORRANCE__

#include "defines.hpp"



namespace RT_ISICG
{
	class CookTorranceBRDF
	{
	  public:
		CookTorranceBRDF( const Vec3f & p_kd, const float p_teta  ) : _kd( p_kd ), _teta(p_teta) {};

		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate( const Vec3f & SurfaceNormal,
							   const Vec3f & ObservationDirection,
							   const Vec3f & IncidenceDirection ) const 
		{

			Vec3f h = glm::normalize( ObservationDirection + IncidenceDirection );	// demi vecteur h.


			float D, G; 
			Vec3f F;
			
			

			
			float tetaObser = glm::dot( SurfaceNormal, ObservationDirection );
			float tetaInc	= glm::dot( SurfaceNormal, IncidenceDirection );

			D = calculateD( h, SurfaceNormal ); // distribution de Trowbridge-Reitz
		
			G = Calculateg1( glm::dot( SurfaceNormal, ObservationDirection ) ) * Calculateg1( glm::dot( SurfaceNormal, IncidenceDirection ) );	// modèle de Smith

			F = Calculatef(ObservationDirection, h);



			return D *  F * G / 4.f * tetaObser * tetaInc; 
		}

		inline const Vec3f & getKd() const { return _kd; }


		float calculateD( const Vec3f & p_h, const Vec3f & p_SurfaceNormal ) const
		{
			float alpha = _teta * _teta; // alpha = teta² 
			float cosnh = glm::dot( p_SurfaceNormal, p_h );
			return ( alpha * alpha ) / ( PIf * pow( cosnh * cosnh * ( alpha * alpha - 1.f ) + 1.f, 2 ) );

		}

		inline float Calculateg1( const float p_x ) const

		{ 
			float k = ( _teta + 1.f ) * ( _teta + 1.f ) / 8.f;
			return p_x / ( p_x * ( 1.f - k ) + k );
		}

		inline Vec3f Calculatef( const Vec3f & p_ObservationDirection, const Vec3f & p_h ) const //, const Vec3f & p_f0
		{ 
			return _kd + ( 1.f - _kd ) * float(pow( 1.f - ( glm::dot( p_h, p_ObservationDirection ) ), 5 ));
		}

	  private:
		Vec3f _kd = WHITE;
		float _teta;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_COOKTORRANCE__
