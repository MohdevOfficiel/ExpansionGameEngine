#pragma once

#ifndef EXP_RIGID_BODY_H__
#define EXP_RIGID_BODY_H__

#ifdef _WIN32

#ifdef EXPANSIONGAMEENGINECORE_EXPORTS
#define EXPGE_API __declspec(dllexport)
#else
#define EXPGE_API __declspec(dllimport)
#endif

#else

#define EXPGE_API

#endif //_WIN32

#include <iostream>

#include <vec3.h>
#include <BD_Reader.h>

#include "EXP_Game.h"

#include <PxPhysicsAPI.h>

//Forward Declaration
class EXP_PhysicsHandler;

struct EXPGE_API EXP_PhysicsMaterial {
	float StaticFriction = 0.0f;
	float DynamicFriction = 0.1f;
	float Restitution = 0.0f;
};

class EXPGE_API EXP_RigidBody
{
public:
	EXP_RigidBody(EXP_Game* game, vec3f pos, vec3f rot, vec3f scale, float mass, bool kinematic = false, EXP_PhysicsMaterial mat = {});
	virtual ~EXP_RigidBody();

	physx::PxRigidActor* GetBody();
	vec3f GetWorldPosition();

	void AddMovementInput(vec3f direction, float scale);
	void FreezeRotationAxis(bool X, bool Y, bool Z);
	void FreezePositionAxis(bool X, bool Y, bool Z);
	vec3f GetLinearVelocity();

	virtual void ConstructShape();

protected:
	vec3f m_pos, m_rot, m_scale;
	physx::PxRigidDynamic* m_body;
	physx::PxRigidStatic* m_body_static; //UGLYYYYYYY

	EXP_PhysicsMaterial m_mat;

	float m_mass;
	bool m_isKinematic;

	EXP_Game* m_game;
};

class EXPGE_API EXP_RB_Box : public EXP_RigidBody {
public:
	EXP_RB_Box(EXP_Game* game, vec3f pos, vec3f rot, vec3f scale, float mass, bool kinematic = false, EXP_PhysicsMaterial mat = {});
};

class EXPGE_API EXP_RB_Sphere : public EXP_RigidBody {
public:
	EXP_RB_Sphere(EXP_Game* game, vec3f pos, vec3f rot, float radius, float mass, bool kinematic = false, EXP_PhysicsMaterial mat = {});

	virtual void ConstructShape() override;

private:
	float m_radius;
};

class EXPGE_API EXP_RB_Capsule : public EXP_RigidBody {
public:
	EXP_RB_Capsule(EXP_Game* game, vec3f pos, vec3f rot, float radius, float height, float mass, bool kinematic = false, EXP_PhysicsMaterial mat = {});

	virtual void ConstructShape() override;

private:
	float m_radius;
	float m_height;
};

class EXPGE_API EXP_RB_Mesh : public EXP_RigidBody {
public:
	EXP_RB_Mesh(EXP_Game* game, vec3f pos, vec3f rot, vec3f scale, std::string meshref, float mass, EXP_PhysicsMaterial mat = {});

	virtual void ConstructShape() override;

private:
	std::vector<physx::PxVec3> m_verticies;
	std::vector<int32_t> m_indicies;
};

class EXPGE_API EXP_CharacterController {
public:
	EXP_CharacterController() {
		m_controller = nullptr;
	};

	virtual ~EXP_CharacterController() {}

	virtual void AddMovementInput(vec3f dir) = 0;
	virtual vec3f GetWorldPosition() = 0;

	virtual void ConstructController() = 0;

protected:
	physx::PxController* m_controller;
	physx::PxControllerFilters m_filters;
};

class EXPGE_API EXP_CharControllerCapsule : public EXP_CharacterController {
public:
	EXP_CharControllerCapsule(EXP_Game* game, vec3f pos, float height, float radius, float mass, EXP_PhysicsMaterial mat = {});
	virtual ~EXP_CharControllerCapsule();

	virtual vec3f GetWorldPosition();
	virtual void AddMovementInput(vec3f dir);

	virtual void ConstructController() override;

private:
	EXP_Game* m_game;
	float m_height, m_radius;
	
	vec3f m_pos;
	EXP_PhysicsMaterial m_mat;
};

#endif //EXP_RIGID_BODY_H__