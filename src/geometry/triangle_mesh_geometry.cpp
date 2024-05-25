#include "triangle_mesh_geometry.hpp"
#include "objects/triangle_mesh.hpp"

namespace RT_ISICG
{
	TriangleMeshGeometry::TriangleMeshGeometry( const unsigned int p_v0,
												const unsigned int p_v1,
												const unsigned int p_v2,
												MeshTriangle *	   p_refMesh )
		: _v0( p_v0 ), _v1( p_v1 ), _v2( p_v2 ), _refMesh( p_refMesh )
	{
		_faceNormal = glm::normalize( glm::cross( _refMesh->_vertices[ p_v1 ] - _refMesh->_vertices[ p_v0 ],
												  _refMesh->_vertices[ p_v2 ] - _refMesh->_vertices[ p_v0 ] ) );
	}

	bool TriangleMeshGeometry::intersect( const Ray & p_ray, float & p_t, float & p_u, float & p_v ) const // on rajoute les attribut p_u et p_v pour pouvoir interpoler les normales par la suite
	{
		const Vec3f & origin	 = p_ray.getOrigin();
		const Vec3f & direction	 = p_ray.getDirection();
		const Vec3f & v0 = _refMesh->_vertices[ _v0 ];
		const Vec3f & v1 = _refMesh->_vertices[ _v1 ];
		const Vec3f & v2 = _refMesh->_vertices[ _v2 ];

		constexpr float epsilon = std::numeric_limits<float>::epsilon();

		Vec3f edge1, edge2;
		edge1 = v1 - v0;
		edge2 = v2 - v0;

		Vec3f rayEdge2 = cross( direction, edge2 );
		float det	   = dot( edge1, rayEdge2 );

		if ( det > -epsilon && det < epsilon ) return false;

		float invDet = 1.f / det;
		Vec3f s		 = origin - v0;
		p_u		 = invDet * dot( s, rayEdge2 );

		if ( p_u < 0.f || p_u > 1.f ) return false;

		Vec3f sCrossEdge1 = cross( s, edge1 );
		p_v				  = invDet * dot( direction, sCrossEdge1 );

		if ( p_v < 0.f || p_u + p_v > 1.f ) return false;

		float t = invDet * dot( edge2, sCrossEdge1 );

		if ( t > epsilon )	//intersection
		{
			p_t = t;
			return true;
		}

		else	// pas d'intersection
		{
			p_t = -1.f;
			return false;
		}
	}


	//MeshTriangle * TriangleMeshGeometry::getRefMesh() { return _refMesh; }


	Vec3f TriangleMeshGeometry::NormalInterpolation( const float & p_u, const float & p_v ) const
	{ 
		Vec3f & n0 = _refMesh->_normals[ _v0 ];
		Vec3f & n1 = _refMesh->_normals[ _v1 ];
		Vec3f & n2 = _refMesh->_normals[ _v2 ];
		
		Vec3f normalInterpolated = normalize( ( 1 - p_u - p_v ) * n0 + p_u * n1 + p_v * n2 );
		return normalInterpolated;
	}

	const Vec3f & TriangleMeshGeometry::getSommet(int id ) const
	{ 
		return _refMesh->_vertices[ _v[ id ] ]; 
	};


	const Vec3f TriangleMeshGeometry::getCentre()
	{
		return Vec3f(( _refMesh->_vertices[ _v0 ] + _refMesh->_vertices[ _v1 ] + _refMesh->_vertices[ _v2 ] ) / 3.f); 
	};

} // namespace RT_ISICG
