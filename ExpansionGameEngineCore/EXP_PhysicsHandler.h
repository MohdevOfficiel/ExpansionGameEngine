#pragma once

#ifndef _EXP_PHYSICS_HANDLER_H__
#define _EXP_PHYSICS_HANDLER_H__

#ifdef EXPANSIONGAMEENGINECORE_EXPORTS
#define EXPGE_API __declspec(dllexport)
#else
#define EXPGE_API __declspec(dllimport)
#endif

#include <iostream>

#include <vec3.h>

#include <bullet/btBulletDynamicsCommon.h>

#include "EXP_RigidBody.h"

class EXPGE_API EXP_PhysicsHandler
{
public:
	EXP_PhysicsHandler(vec3f gravity, int maxFramerate);
	~EXP_PhysicsHandler();

	void UpdateWorld();
	void InitWorld();

	void RegisterRigidBody(EXP_RigidBody*);

private:
	btDiscreteDynamicsWorld* m_dWorld;

	vec3f m_gravity;
	
	int m_maxFramerate;
	float m_updtTime;
};

#endif //_EXP_PHYSICS_HANDLER_H__