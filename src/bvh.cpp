#include "bvh.hpp"
#include "geometry/triangle_mesh_geometry.hpp"
#include "utils/chrono.hpp"
#include <functional>
#include <algorithm>
#include <iostream>

namespace RT_ISICG
{
	void BVH::build( std::vector<TriangleMeshGeometry> * p_triangles )
	{
		std::cout << "Building BVH..." << std::endl;
		if ( p_triangles == nullptr || p_triangles->empty() )
		{
			throw std::exception( "BVH::build() error: no triangle provided" );
		}
		_triangles = p_triangles;

		Chrono chr;
		chr.start();

		/// TODO
		_root = new BVHNode();	

		_buildRec( _root, 0, p_triangles->size(), 1 );


		chr.stop();

		std::cout << "[DONE]: " << chr.elapsedTime() << "s" << std::endl;
	}

	bool BVH::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		/// TODO


		

		return _intersectRec( _root, p_ray, p_tMin, p_tMax, p_hitRecord ); 
	}

	bool BVH::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		/// TODO
		return _intersectAnyRec( _root, p_ray, p_tMin, p_tMax ); 
	}

	void BVH::_buildRec( BVHNode *			p_node,
						 const unsigned int p_firstTriangleId,
						 const unsigned int p_lastTriangleId,
						 const unsigned int p_depth )
	{
		/// TODO




		// On définit l'aabb du noeuds avec tous les TriangleMeshGeometry contenu dans le noeuds
		for ( int i = p_firstTriangleId; i < p_lastTriangleId; i++ ) // On va récupérer tous les sommets de chaque TriangleMeshGeometry
		{
			// on recupère le triangleMeshGeometry à l'indice i.
			p_node->_aabb.extend(( *_triangles )[ i ].getSommet( 0 ) ); // on ajoute les 3 sommets du triangle à notre aabb.
			p_node->_aabb.extend( ( *_triangles )[ i ].getSommet( 1 ) );
			p_node->_aabb.extend( ( *_triangles )[ i ].getSommet( 2 ) );
		}
		p_node->_firstTriangleId = p_firstTriangleId;
		p_node->_lastTriangleId	 = p_lastTriangleId;

		if ( p_depth >= _maxDepth || _maxTrianglesPerLeaf >= p_lastTriangleId - p_firstTriangleId ) return; // critère pour devenir une feuille, soit on a atteint la profondeur maximal de l'arbre soit on un nombre de triangles insuffisant dans le noeud pour le diviser.


		Vec3f middle = p_node->_aabb.centroid();
		int axe = p_node->_aabb.largestAxis(); // on prend l'axe le plus grand.

		std::function<bool( TriangleMeshGeometry )> split;
		split = [ middle, axe ]( TriangleMeshGeometry triangle ) -> bool	// création d'une fonction de partitionnement qui retourne un booléen en fonction de la position du centre du triangle par rapport au centrôide de l'aabb, return true si elle est inférieur et false sinon.
		{ return triangle.getCentre()[axe] < middle[ axe ]; };

		std::vector<TriangleMeshGeometry>::iterator itMiddle = std::partition(		// On partitionne à l'aide d'un iterateur qui va réorganiser notre liste de triangles en deux listes, la première avec tous les triangles qui sont inférieurs au centrôide de l'aabb et l'autre avec tous ceux qui sont supérieur, itMiddle retourne l'indice du premier triangles compris dans la 2e liste. 
			_triangles->begin() + p_firstTriangleId,
			_triangles->begin() + p_lastTriangleId, 
			split );

		int id = std::distance( _triangles->begin(), itMiddle );


		// on initialise les deux noeuds enfants.



		p_node->_left  = new BVHNode();
		p_node->_right = new BVHNode();

		_buildRec( p_node->_left, p_firstTriangleId, id, p_depth + 1 );
		_buildRec( p_node->_right, id, p_lastTriangleId, p_depth + 1 );



		// on partitionne les triangles selon l'axe le plus grand












	}

	bool BVH::_intersectRec( const BVHNode * p_node,
							 const Ray &	 p_ray,
							 const float	 p_tMin,
							 const float	 p_tMax,
							 HitRecord &	 p_hitRecord ) const
	{
		/// TODO

		if ( !p_node->_aabb.intersect( p_ray, p_tMin, p_tMax ) )
			return false; // on vérifie d'abord s'il intersecte l'aabb du noeud

		// dans la feuille

		if ( p_node->isLeaf() )
		{
			bool isIntersection = false;

			for ( int i = p_node->_firstTriangleId; i < p_node->_lastTriangleId; i++ ) // On va tester pour chaque triangles du noeud s'il y a une intersection avec le rayon
			{
				float t, u, v;
				float tClosest = 0;
				bool  first	   = true;
				if ( _triangles->at( i ).intersect(
						 p_ray, t, u, v ) ) // On vérifie si il y a une intersection à l'indice i.
				{
					if ( t >= p_tMin && t <= p_tMax ) // on fait attention que t est comprise dans la bonne distance.
					{
						if ( p_hitRecord._object == nullptr
							 || t < p_hitRecord._distance ) // soit c'est la première intersection, soit on trouve une
															// intersection plus proche.
						{
							p_hitRecord._point	  = p_ray.pointAtT( t );
							p_hitRecord._normal	  = _triangles->at( i ).NormalInterpolation( u, v );
							p_hitRecord._distance = t;
							p_hitRecord._object	  = reinterpret_cast<BaseObject *>( _triangles->at( i ).getRefMesh() );
							p_hitRecord.faceNormal( p_ray.getDirection() );

							isIntersection = true;
						}
					}
				}
			}
			return isIntersection;
		}

		else  // tant que nous sommes pas sur une feuille on continue de parcourir le bvh.
		{
			if ( p_node->_left != nullptr )_intersectRec(p_node->_left, p_ray,	p_tMin,	p_tMax,	p_hitRecord ); // on vérifie que les enfants gauche et droit ne sont pas nul avant de parcourir.
			if ( p_node->_right != nullptr ) _intersectRec( p_node->_right, p_ray, p_tMin, p_tMax, p_hitRecord );
		}

		return false;
	}


	bool BVH::_intersectAnyRec( const BVHNode * p_node,
								const Ray &		p_ray,
								const float		p_tMin,
								const float		p_tMax ) const
	{
		/// TODO

		if ( !p_node->_aabb.intersect( p_ray, p_tMin, p_tMax ) ) return false;	// on vérifie d'abord s'il intersecte l'aabb du noeud

		if ( p_node != nullptr )
		{
			if ( !p_node->isLeaf() ) // tant que nous sommes pas sur une feuille on continue de parcourir le bvh.
			{
				if ( p_node->_left != nullptr )
					if(_intersectAnyRec(
						p_node->_left,
						p_ray,
						p_tMin,
						p_tMax)) return true; // on vérifie que les enfants gauche et droit ne sont pas nul avant de parcourir.

				

				if ( p_node->_right != nullptr ) if(_intersectAnyRec( p_node->_right, p_ray, p_tMin, p_tMax)) return true ;
			}

			// dans la feuille

			for ( int i = p_node->_firstTriangleId; i < p_node->_lastTriangleId; i++ ) // On va tester pour chaque triangles du noeud s'il y a une intersection avec le rayon
			{
				float t, u, v;
				if ( _triangles->at( i ).intersect(
						 p_ray, t, u, v ) ) // On vérifie si il y a une intersection à l'indice i.
				{
					if ( t >= p_tMin && t <= p_tMax ) // on fait attention que t est comprise dans la bonne distance.
					{
						return true;
					}
				}

				
			}
		}
		return false;
	}
} // namespace RT_ISICG
