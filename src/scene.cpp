#include "scene.hpp"


#include "objects/sphere.hpp"
#include "objects/triangle_mesh.hpp"
#include "objects/Plane.hpp"
#include "objects/implicit_sphere.hpp"
#include "objects/implicit_tore.hpp"
#include "objects/implict_fractale_mandelbub.hpp"
#include "objects/implicit_cube.hpp"

#include "lights/point_light.hpp"
#include "lights/quad_light.hpp"

#include "materials/color_material.hpp"
#include "materials/lambert_material.hpp"
#include "materials/matte_material.hpp"
#include "materials/plastic_material.hpp"
#include "materials/microfacet._material.hpp"
#include "materials/mirror_material.hpp"
#include "materials/transparent_material.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace RT_ISICG
{
	Scene::Scene() { _addMaterial( new ColorMaterial( "default", WHITE ) ); }

	Scene::~Scene()
	{
		for ( const ObjectMapPair & object : _objectMap )
		{
			delete object.second;
		}
		for ( const MaterialMapPair & material : _materialMap )
		{
			delete material.second;
		}
		for ( const BaseLight * light : _lightList )
		{
			delete light;
		}
	}

	void Scene::initTp1()
	{
		// Add objects.
		_addObject( new Sphere( "Sphere1", Vec3f( 0.f, 0.f, 3.f ), 1.f ) );

		// Add materials.
		_addMaterial( new ColorMaterial( "Blue", BLUE ) );

		// Link objects and materials.
		_attachMaterialToObject( "Blue", "Sphere1" );
	}

	void Scene::initTp2() 
	{  
		

				// Add objects.
		_addObject( new Sphere( "Sphere1", Vec3f( 0.f, 0.f, 3.f ), 1.f ) );
		_addObject( new Plane( "Plane1", Vec3f( 0.f, -2.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );

		// Add materials.
		_addMaterial( new ColorMaterial( "Blue", BLUE ) );
		_addMaterial( new ColorMaterial( "Red", RED ) );

		// Link objects and materials.
		_attachMaterialToObject( "Blue", "Sphere1" );
		_attachMaterialToObject( "Red", "Plane1" );

		_addLight( new PointLight( WHITE, 100.f, Vec3f( 1.f, 10.f, 1.f ) ) );
		
	}

	void Scene::initTp3()
	{
		// Add objects.
		_addObject( new Sphere( "Sphere1", Vec3f( 0.f, 0.f, 3.f ), 1.f ) );
		_addObject( new Plane( "Plane1", Vec3f( 0.f, -2.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );

		// Add materials.
		_addMaterial( new ColorMaterial( "Blue", BLUE ) );
		_addMaterial( new ColorMaterial( "Red", RED ) );

		// Link objects and materials.
		_attachMaterialToObject( "Blue", "Sphere1" );
		_attachMaterialToObject( "Red", "Plane1" );
		
		_addLight( new QuadLight( Vec3f( 1.f, 10.f, 2.f ), Vec3f( -2.f, 0.f, 0.f ), Vec3f( 0.f, 0.f, 2.f ), WHITE, 40.f ));
	}

	void Scene::initTp4()
	{
		// ================================================================
		// Add materials .
		// ================================================================
		_addMaterial( new ColorMaterial( " RedColor ", RED ) );
		_addMaterial( new ColorMaterial( " GreenColor ", GREEN ) );
		_addMaterial( new ColorMaterial( " BlueColor ", BLUE ) );
		_addMaterial( new ColorMaterial( " GreyColor ", GREY ) );
		_addMaterial( new ColorMaterial( " MagentaColor ", MAGENTA ) );
		_addMaterial( new ColorMaterial( " YellowColor ", YELLOW ) );
		_addMaterial( new ColorMaterial( " CyanColor ", CYAN ) );
		// ================================================================
		// Add objects .
		// ================================================================
		// OBJ.


		//loadFileTriangleMesh( "UVsphere", "data/Objet/uvsphere.obj" );
		//_attachMaterialToObject( " CyanColor ", "UVsphere_defaultobject" );
		loadFileTriangleMesh( "Bunny", "data/Objet/Bunny.obj" );
		_attachMaterialToObject( " CyanColor ", "Bunny_defaultobject" );
		//loadFileTriangleMesh( "Conf", "data/Objet/conference/conference.obj" );


		// Pseudo Cornell box made with infinite planes .
		 _addObject( new Plane( " PlaneGround ", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		_attachMaterialToObject( " GreyColor ", " PlaneGround " );
		_addObject( new Plane( " PlaneLeft ", Vec3f( 5.f, 0.f, 0.f ), Vec3f( -1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( " RedColor ", " PlaneLeft " );
		_addObject( new Plane( " PlaneCeiling ", Vec3f( 0.f, 7.f, 0.f ), Vec3f( 0.f, -1.f, 0.f ) ) );
		_attachMaterialToObject( " GreenColor ", " PlaneCeiling " );
		_addObject( new Plane( " PlaneRight ", Vec3f( -5.f, 0.f, 0.f ), Vec3f( 1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( " BlueColor ", " PlaneRight " );
		_addObject( new Plane( " PlaneFront ", Vec3f( 0.f, 0.f, 10.f ), Vec3f( 0.f, 0.f, -1.f ) ) );
		_attachMaterialToObject( " MagentaColor ", " PlaneFront " );
		_addObject( new Plane( " PlaneRear ", Vec3f( 0.f, 0.f, -10.f ), Vec3f( 0.f , 0.f, 1.f ) ) );
		_attachMaterialToObject( " YellowColor ", " PlaneRear " );
		// ================================================================
		// Add lights .
		// ================================================================
		_addLight( new PointLight( WHITE, 100.f, Vec3f( 0.f, 3.f, -5.f ) ) );

	}

	void Scene::initTp5()
	{
		// ================================================================
		// Add materials .
		// ================================================================
		_addMaterial( new ColorMaterial( " Red ", RED ) );

		_addMaterial( new LambertMaterial( "GreyL", GREY ) );
		_addMaterial( new MatteMaterial( "GreyM", GREY, 1.f) );
		_addMaterial( new ColorMaterial( "GreyC", GREY ) );
		_addMaterial( new PlasticMaterial( "GreyP", GREY, GREY, 128.f ) );
		_addMaterial( new PlasticMaterial( "RedP", RED, RED, 128.f ) );
		_addMaterial( new MicrofacetMaterial( "GoldMicro", Vec3f( 1.f, 0.85f, 0.57f ), 0.3f, 0.5f ) );
		// ================================================================
		// Add objects .
		// ================================================================
		// OBJ.

		_addObject( new Plane( " PlaneGround ", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		_attachMaterialToObject( "RedP", " PlaneGround " );
		_addObject( new Sphere( "Sphere", Vec3f( 0.f, 0.f, 3.f ), 1.f) );
		_attachMaterialToObject( "GoldMicro", "Sphere" );

		 //loadFileTriangleMesh( "Bunny", "data/Objet/Bunny.obj" );
		//_attachMaterialToObject( "GoldMicro", "Bunny_defaultobject" );


		
		// ================================================================
		// Add lights .
		// ================================================================
		//_addLight( new PointLight( WHITE, 100.f, Vec3f( 0.f, 5.f, -5.f ) ) );		// golden bunny
		_addLight( new PointLight( WHITE, 60.f, Vec3f( 0.f, 0.f, -2.f ) ) );
		//_addLight(new QuadLight( Vec3f( 1.f, 10.f, 2.f ), Vec3f( -2.f, 0.f, 0.f ), Vec3f( 0.f, 0.f, 2.f ), WHITE, 40.f ) );
	}


	void Scene::initTp6()
	{
		// ================================================================
		// Add materials .
		// ================================================================
		_addMaterial( new MatteMaterial( " WhiteMatte ", WHITE, 0.6f ) );
		_addMaterial( new MatteMaterial( " RedMatte ", RED, 0.6f ) );
		_addMaterial( new MatteMaterial( " GreenMatte ", GREEN, 0.6f ) );
		_addMaterial( new MatteMaterial( " BlueMatte ", BLUE, 0.6f ) );
		_addMaterial( new MatteMaterial( " GreyMatte ", GREY, 0.6f ) );
		_addMaterial( new MatteMaterial( " MagentaMatte ", MAGENTA, 0.6f ) );

		_addMaterial( new MirrorMaterial( "Mirror" ) );
		_addMaterial( new TransparentMaterial( "Transaprent" ) );

		_addMaterial( new MicrofacetMaterial( "GoldMicro", Vec3f( 1.f, 0.85f, 0.57f ), 0.3f, 0.5f ) );
		// ================================================================
		// Add objects .
		// ================================================================
		// Spheres .
		_addObject( new Sphere( " Sphere1 ", Vec3f( -2.f, 0.f, 3.f ), 1.5f ) );
		_attachMaterialToObject( "Mirror", " Sphere1 " );
		_addObject( new Sphere( " Sphere2 ", Vec3f( 2.f, 0.f, 3.f ), 1.5f ) );
		_attachMaterialToObject( "Transaprent", " Sphere2 " );
		// Pseudo Cornell box made with infinite planes .
		_addObject( new Plane( " PlaneGround ", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		_attachMaterialToObject( " GreyMatte ", " PlaneGround " );
		_addObject( new Plane( " PlaneLeft ", Vec3f( 5.f, 0.f, 0.f ), Vec3f( -1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( "Mirror", " PlaneLeft " );
		_addObject( new Plane( " PlaneCeiling ", Vec3f( 0.f, 7.f, 0.f ), Vec3f( 0.f, -1.f, 0.f ) ) );
		_attachMaterialToObject( "Mirror", " PlaneCeiling " );
		_addObject( new Plane( " PlaneRight ", Vec3f( -5.f,0.f, 0.f ), Vec3f( 1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( "GoldMicro", " PlaneRight " );
		_addObject( new Plane( " PlaneFront ", Vec3f( 0.f, 0.f, 10.f ), Vec3f( 0.f, 0.f, -1.f ) ) );
		_attachMaterialToObject( "Mirror", " PlaneFront " );
		// ================================================================
		// Add lights .
		// ================================================================
		_addLight( new PointLight( WHITE, 100.f, Vec3f( 0.f, 5.f, 0.f ) ) );
		//_addLight ( new QuadLight ( Vec3f ( 1.f, 5.f, -2.f ), Vec3f ( -2.f, 0.f, 0.f ) , Vec3f ( 0.f, 1.f, 2.f ) , WHITE , 40.f ) );

	}

		void Scene::initTp7()
	{
		// ================================================================
		// Add materials .
		// ================================================================
		_addMaterial( new ColorMaterial( " Red ", RED ) );

		_addMaterial( new LambertMaterial( "GreyL", GREY ) );
		_addMaterial( new MatteMaterial( "GreyM", GREY, 1.f ) );
		_addMaterial( new ColorMaterial( "GreyC", GREY ) );
		_addMaterial( new PlasticMaterial( "GreyP", GREY, GREY, 128.f ) );
		_addMaterial( new PlasticMaterial( "RedP", RED, RED, 128.f ) );
		_addMaterial( new MicrofacetMaterial( "GoldMicro", Vec3f( 1.f, 0.85f, 0.57f ), 0.3f, 0.5f ) );
		// ================================================================
		// Add objects .
		// ================================================================
		// OBJ.

		_addObject( new Plane( " PlaneGround ", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		_attachMaterialToObject( "RedP", " PlaneGround " );
		//_addObject( new Sphere( "Sphere", Vec3f( 0.f, 0.f, 3.f ), 1.f ) );
		//_attachMaterialToObject( "GoldMicro", "Sphere" );

		_addObject( new ImplicitSphere( "implicitSphere", Vec3f( 0.f, 0.f, 3.f ), 1.f ) );
		_attachMaterialToObject( "GoldMicro", "implicitSphere" );
		// loadFileTriangleMesh( "Bunny", "data/Objet/Bunny.obj" );
		//_attachMaterialToObject( "GoldMicro", "Bunny_defaultobject" );

		// ================================================================
		// Add lights .
		// ================================================================
		//_addLight( new PointLight( WHITE, 100.f, Vec3f( 0.f, 5.f, -5.f ) ) );		// golden bunny
		_addLight( new PointLight( WHITE, 60.f, Vec3f( 0.f, 0.f, -2.f ) ) );
		//_addLight(new QuadLight( Vec3f( 1.f, 10.f, 2.f ), Vec3f( -2.f, 0.f, 0.f ), Vec3f( 0.f, 0.f, 2.f ), WHITE, 40.f));
		//) );
	}

		void Scene::MagnifiqueImageLaPlusBelle()
	{
		// ================================================================
		// Add materials .
		// ================================================================
		_addMaterial( new ColorMaterial( " Red ", RED ) );

		_addMaterial( new LambertMaterial( "GreyL", GREY ) );
		_addMaterial( new MatteMaterial( "GreyM", GREY, 1.f ) );
		_addMaterial( new ColorMaterial( "GreyC", GREY ) );
		_addMaterial( new PlasticMaterial( "GreyP", GREY, GREY, 128.f ) );
		_addMaterial( new PlasticMaterial( "RedP", RED, RED, 128.f ) );
		_addMaterial( new MicrofacetMaterial( "GoldMicro", Vec3f( 1.f, 0.85f, 0.57f ), 0.3f, 0.5f ) );
		_addMaterial( new MirrorMaterial( "Mirror" ) );
		_addMaterial( new TransparentMaterial( "Transaprent" ) );

		// ================================================================
		// Add objects .
		// ================================================================
		// OBJ.

		_addObject( new Plane( "PlaneGround", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		_addObject( new Plane( "PlaneCeiling", Vec3f( 0.f, 7.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		_addObject( new Plane( "PlaneFront", Vec3f( 0.f, 0.f, 10.f ), Vec3f( 0.f, 0.f, -1.f ) ) );


		//loadFileTriangleMesh( "Bunny", "data/Objet/Bunny.obj" );
		//_attachMaterialToObject( "Transaprent", "Bunny_defaultobject" );

		_attachMaterialToObject( "GreyL", "PlaneGround" );
		_attachMaterialToObject( "GreyL", "PlaneCeiling" );
		_attachMaterialToObject( "GreyL", "PlaneFront" );

		_addObject( new Sphere( "Sphere", Vec3f( 0.f, 0.f, 3.f ), 1.f ) );
		_attachMaterialToObject( "Transaprent", "Sphere" );

		//_addObject( new ImplicitSphere( "implicitSphere", Vec3f( 0.f, 0.f, 5.f ), 1.f ) );
		//_attachMaterialToObject( "GoldMicro", "implicitSphere" );
		// loadFileTriangleMesh( "Bunny", "data/Objet/Bunny.obj" );
		//_attachMaterialToObject( "GoldMicro", "Bunny_defaultobject" );

		// ================================================================
		// Add lights .
		// ================================================================
		//_addLight( new PointLight( WHITE, 100.f, Vec3f( 0.f, 5.f, -5.f ) ) );		// golden bunny
		//_addLight( new PointLight( WHITE, 60.f, Vec3f( 0.f, 0.f, -2.f ) ) );
		//_addLight( new PointLight( WHITE, 100.f, Vec3f( 0.f, 5.f, 0.f ) ) );

		_addLight(new QuadLight( Vec3f( 0.f, 5.f, 0.f ), Vec3f( -2.f, 0.f, 0.f ), Vec3f( 0.f, 0.f, 2.f ), WHITE, 40.f));;
	}



		void Scene::Projet_tore()
	{
		_addMaterial( new ColorMaterial( "Red", RED ) );
		_addMaterial( new ColorMaterial( "GreyColor", GREY ) );


		_addObject( new Plane( "PlaneGround", Vec3f( 0.f, -3.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		_addObject( new ImplicitTore( "Tore", Vec3f( 0.f, 0.f, 3.f ), 3.f, 1.f));

		_attachMaterialToObject( "GreyColor", "PlaneGround" );
		_attachMaterialToObject( "Red", "Tore" );

		_addLight(new QuadLight( Vec3f( 0.f, 5.f, 0.f ), Vec3f( -2.f, 0.f, 0.f ), Vec3f( 0.f, 0.f, 2.f ), WHITE, 40.f ) );
		;
	}

		void Scene::Projet_fractale()
	{
		_addMaterial( new ColorMaterial( "Red", RED ) );
		_addMaterial( new ColorMaterial( "GreyColor", GREY ) );
		_addMaterial( new MicrofacetMaterial( "GoldMicro", Vec3f( 1.f, 0.85f, 0.57f ), 0.3f, 0.5f ) );
		_addMaterial( new MicrofacetMaterial( "ArgentMicro", Vec3f( 0.753f, 0.753f, 0.753f ), 0.3f, 0.1f ) );



		//_addObject( new Plane( "PlaneGround", Vec3f( 0.f, -5.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ) ) );
		//_addObject( new ImplicitTore( "Tore", Vec3f( 0.f, 1.f, 3.f ), 5.f, 3.f ) );

		_addObject( new ImplicitMandelbulb( "Mandelbub",  8, 16.0f ));
		//_addObject( new ImplicitCube( "Cube", Vec3f( 0.f, 0.f, 3.f ), 4.f ) );
		//_attachMaterialToObject( "Red", "Cube" );
		//_attachMaterialToObject( "GreyColor", "PlaneGround" );
		//_attachMaterialToObject( "ArgentMicro", "Tore" );

		//_addLight(new QuadLight( Vec3f( 0.f, 5.f, 0.f ), Vec3f( -2.f, 0.f, 0.f ), Vec3f( 0.f, 0.f, 2.f ), WHITE, 40.f ) );
		_addLight( new PointLight( WHITE, 60.f, Vec3f( 0.f, 2.f, -5.f ) ) );

		;
	}

	void Scene::loadFileTriangleMesh( const std::string & p_name, const std::string & p_path )
	{
		std::cout << "Loading: " << p_path << std::endl;
		Assimp::Importer importer;

		// Read scene and triangulate meshes
		const aiScene * const scene
			= importer.ReadFile( p_path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_GenUVCoords );

		if ( scene == nullptr ) { throw std::runtime_error( "Fail to load file: " + p_path ); }

		unsigned int cptTriangles = 0;
		unsigned int cptVertices  = 0;

		for ( unsigned int m = 0; m < scene->mNumMeshes; ++m )
		{
			const aiMesh * const mesh = scene->mMeshes[ m ];
			if ( mesh == nullptr ) { throw std::runtime_error( "Fail to load file: " + p_path + ": mesh is null" ); }

			const std::string meshName = p_name + "_" + std::string( mesh->mName.C_Str() );
			std::cout << "-- Load mesh " << m + 1 << "/" << scene->mNumMeshes << ": " << meshName << std::endl;

			cptTriangles += mesh->mNumFaces;
			cptVertices += mesh->mNumVertices;

			const bool hasUV = mesh->HasTextureCoords( 0 );

			MeshTriangle * triMesh = new MeshTriangle( meshName );
			// Vertices before faces otherwise face normals cannot be computed.
			for ( unsigned int v = 0; v < mesh->mNumVertices; ++v )
			{
				triMesh->addVertex( mesh->mVertices[ v ].x, mesh->mVertices[ v ].y, mesh->mVertices[ v ].z );
				triMesh->addNormal( mesh->mNormals[ v ].x, mesh->mNormals[ v ].y, mesh->mNormals[ v ].z );
				if ( hasUV ) triMesh->addUV( mesh->mTextureCoords[ 0 ][ v ].x, mesh->mTextureCoords[ 0 ][ v ].y );
			}
			for ( unsigned int f = 0; f < mesh->mNumFaces; ++f )
			{
				const aiFace & face = mesh->mFaces[ f ];
				triMesh->addTriangle( face.mIndices[ 0 ], face.mIndices[ 1 ], face.mIndices[ 2 ] );
			}

			_addObject( triMesh );
			// cr�ation de la bvh.
			triMesh->createBVH();


			const aiMaterial * const mtl = scene->mMaterials[ mesh->mMaterialIndex ];
			if ( mtl == nullptr )
			{
				std::cerr << "Material undefined," << meshName << " assigned to default material" << std::endl;
			}
			else
			{
				Vec3f kd = WHITE;
				Vec3f ks = BLACK;
				float s	 = 0.f;

				aiColor3D aiKd;
				if ( mtl->Get( AI_MATKEY_COLOR_DIFFUSE, aiKd ) == AI_SUCCESS ) kd = Vec3f( aiKd.r, aiKd.g, aiKd.b );
				aiColor3D aiKs;
				if ( mtl->Get( AI_MATKEY_COLOR_SPECULAR, aiKs ) == AI_SUCCESS ) ks = Vec3f( aiKs.r, aiKs.g, aiKs.b );
				float aiS = 0.f;
				if ( mtl->Get( AI_MATKEY_SHININESS, aiS ) == AI_SUCCESS ) s = aiS;
				aiString mtlName;
				mtl->Get( AI_MATKEY_NAME, mtlName );

				/*_addMaterial( new ColorMaterial( std::string( mtlName.C_Str() ), kd ) );
				_attachMaterialToObject( mtlName.C_Str(), meshName );*/
			}

			std::cout << "-- [DONE] " << triMesh->getNbTriangles() << " triangles, " << triMesh->getNbVertices()
					  << " vertices." << std::endl;
		}
		std::cout << "[DONE] " << scene->mNumMeshes << " meshes, " << cptTriangles << " triangles, " << cptVertices
				  << " vertices." << std::endl;


		


	}

	bool Scene::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		float tMax = p_tMax;
		bool  hit  = false;
		for ( const ObjectMapPair & object : _objectMap )
		{
			if ( object.second->intersect( p_ray, p_tMin, tMax, p_hitRecord ) )
			{
				tMax = p_hitRecord._distance; // update tMax to conserve the nearest hit
				hit	 = true;
			}
		}
		return hit;
	}

	bool Scene::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		for ( const ObjectMapPair & object : _objectMap )
		{
			if ( object.second->intersectAny( p_ray, p_tMin, p_tMax ) ) { return true; }
		}
		return false;
	}

	void Scene::_addObject( BaseObject * p_object )
	{
		const std::string & name = p_object->getName();
		if ( _objectMap.find( name ) != _objectMap.end() )
		{
			std::cout << "[Scene::addObject] Object \'" << name << "\' already exists" << std::endl;
			delete p_object;
		}
		else
		{
			_objectMap[ name ] = p_object;
			_objectMap[ name ]->setMaterial( _materialMap[ "default" ] );
		}
	}

	void Scene::_addMaterial( BaseMaterial * p_material )
	{
		const std::string & name = p_material->getName();
		if ( _materialMap.find( name ) != _materialMap.end() )
		{
			std::cout << "[Scene::_addMaterial] Material \'" << name << "\' already exists" << std::endl;
			delete p_material;
		}
		else
		{
			std::cout << "Material \'" << name << "\' added." << std::endl;
			_materialMap[ name ] = p_material;
		}
	}

	void Scene::_addLight( BaseLight * p_light ) { _lightList.emplace_back( p_light ); }

	void Scene::_attachMaterialToObject( const std::string & p_materialName, const std::string & p_objectName )
	{
		if ( _objectMap.find( p_objectName ) == _objectMap.end() )
		{
			std::cout << "[Scene::attachMaterialToObject] Object \'" << p_objectName << "\' does not exist"
					  << std::endl;
		}
		else if ( _materialMap.find( p_materialName ) == _materialMap.end() )
		{
			std::cout << "[Scene::attachMaterialToObject] Material \'" << p_materialName << "\' does not exist, "
					  << "object \'" << p_objectName << "\' keeps its material \'"
					  << _objectMap[ p_objectName ]->getMaterial()->getName() << "\'" << std::endl;
		}
		else
		{
			_objectMap[ p_objectName ]->setMaterial( _materialMap[ p_materialName ] );
		}
	}

} // namespace RT_ISICG
