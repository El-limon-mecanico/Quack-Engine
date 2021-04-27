#include "BulletQuack.h"
#include "BtOgre.h"
#include <assert.h>

using namespace BtOgre;

std::unique_ptr<BulletQuack>  BulletQuack::instance_;

// AQUI FALTA MANEJO DE ERRORES Y EXCEPCIONES
bool BulletQuack::Init() {
	assert(instance_.get() == nullptr);
	instance_.reset(new BulletQuack());
	return instance_.get();
}

BulletQuack* BulletQuack::Instance()
{
	assert(instance_.get() != nullptr);
	return instance_.get();
}


void BulletQuack::init() {

	world_ = new DynamicsWorld(Ogre::Vector3(0, -100, 0));

	////Bullet initialisation.
	//mCollisionConfig.reset(new btDefaultCollisionConfiguration());
	//mDispatcher.reset(new btCollisionDispatcher(mCollisionConfig.get()));
	//mSolver.reset(new btSequentialImpulseConstraintSolver());
	//mBroadphase.reset(new btDbvtBroadphase());

	//mBtWorld = new btDiscreteDynamicsWorld(mDispatcher.get(), mBroadphase.get(), mSolver.get(), mCollisionConfig.get());
	//mBtWorld->setGravity(btVector3(0, -10, 0));
	//mBtWorld->setInternalTickCallback(onTick);
}

//void BulletQuack::onTick(btDynamicsWorld* world, float timeStep)
//{
//	int numManifolds = world->getDispatcher()->getNumManifolds();
//	auto manifolds = world->getDispatcher()->getInternalManifoldPointer();
//	for (int i = 0; i < numManifolds; i++) {
//		btPersistentManifold* manifold = manifolds[i];
//
//		for (int j = 0; j < manifold->getNumContacts(); j++)
//		{
//			const btManifoldPoint& mp = manifold->getContactPoint(j);
//			auto body0 = static_cast<EntityCollisionListener*>(manifold->getBody0()->getUserPointer());
//			auto body1 = static_cast<EntityCollisionListener*>(manifold->getBody1()->getUserPointer());
//			if (body0->listener)
//				body0->listener->contact(body1->listener, mp);
//			if (body1->listener)
//				body1->listener->contact(body0->listener, mp);
//		}
//	}
//}

void BulletQuack::stepPhysics(double deltaTime)
{
	world_->getBtWorld()->stepSimulation(deltaTime);
	//mBtWorld->stepSimulation(deltaTime);
}

btRigidBody* BulletQuack::addRigidBody(Ogre::Entity* e, CollisionListener* listener, float mass, BtOgre::ColliderType col)
{

	return world_->addRigidBody(mass, e, col, listener);

	//auto node = e->getParentSceneNode();
	//RigidBodyState* state = new RigidBodyState(node);

	//btCollisionShape* cs = NULL;
	//switch (col)
	//{
	//case CT_BOX:
	//	cs = createBoxCollider(e);
	//	break;
	//case CT_SPHERE:
	//	cs = createSphereCollider(e);
	//	break;
	//case CT_TRIMESH:
	//	cs = StaticMeshToShapeConverter(e).createTrimesh();
	//	break;
	//case CT_HULL:
	//	cs = StaticMeshToShapeConverter(e).createConvex();
	//	break;
	//}

	//btVector3 inertia(0, 0, 0);
	//if (mass != 0) // mass = 0 -> static
	//	cs->calculateLocalInertia(mass, inertia);

	//auto rb = new btRigidBody(mass, state, cs, inertia);
	//mBtWorld->addRigidBody(rb);
	//rb->setUserPointer(new EntityCollisionListener{ e, listener });

	//// transfer ownership to node
	//auto bodyWrapper = std::make_shared<RigidBody>(rb, mBtWorld);
	//node->getUserObjectBindings().setUserAny("BtRigidBody", bodyWrapper);

	//return rb;
}
