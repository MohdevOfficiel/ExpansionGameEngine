#pragma once

#ifndef _EXP_GAME_H__
#define _EXP_GAME_H__

#ifdef EXPANSIONGAMEENGINECORE_EXPORTS
#define EXPGE_API __declspec(dllexport)
#else
#define EXPGE_API __declspec(dllimport)
#endif

#ifdef _DEBUG
#define RENDER_DBG true
#else
#define RENDER_DBG false
#endif

#include <iostream>
#include <string>
#include <vector>

#include <thread>
#include <mutex>

#include <RaindropRenderer.h>
#include <RD_Mesh.h>
#include <RD_PointLight.h>
#include <RD_Texture.h>

#include <BD_StructMan.h>
#include <BD_MatRW.h>

#include <PhysicaSound.h>
#include <PS_Listener.h>

#include <vec3.h>

//Forward Declaration
class EXP_Actor;
class EXP_Camera;
class EXP_SoundEmitter;
class EXP_RigidBody;
class EXP_PhysicsHandler;

class EXPGE_API EXP_Game
{
public:
	EXP_Game(BD_Resolution res, BD_GameInfo gameinfo, vec3f refreshColor);
	~EXP_Game();
	
	BD_GameInfo GetGameInfo();

	//For internal usage only
	void RegisterMesh(RD_Mesh*);
	void RegisterPointLight(RD_PointLight*);
	void RegisterCamera(EXP_Camera*);

	//Rendering
	RaindropRenderer* GetRenderer();
	vec3f GetRefreshColor();
	std::vector<RD_Mesh*> GetStaticMeshes();
	BD_MatDef GetDefaultMaterial();
	BD_MatDef FetchMaterialFromFile(std::string fileref);

	void MainLoop();
	
	//Sounds
	void UpdateSound();
	PSound* GetSoundEngine();
	void RegisterSoundEmitter(EXP_SoundEmitter*);
	void PlaySimpleSound(std::string ref, float gain);
	void PlaySound3D(std::string ref, vec3f pos, float gain);

	std::string GetFilePathByRef(std::string ref);

	//Physics
	void UpdatePhysics();
	EXP_PhysicsHandler* GetPhysicsHandler();

private:
	void InitGame(BD_Resolution winRes, vec3f refreshColor, BD_GameInfo gameinfo);
	void InitPhysicaSound();
	void InitGui();
	void InitPhysics();

	RaindropRenderer* m_rndr;

	PSound* m_soundEngine;

	BD_Resolution m_res;
	BD_GameInfo m_gameinfo;

	vec3f m_refreshColor;
	std::string m_gameName;

	BD_MatDef m_def_mat;

	EXP_Camera* m_currentCamera;
	PS_Listener* m_listener;

	//Physics
	EXP_PhysicsHandler* m_physicsHandler;

	//Renderables
	std::vector<RD_Mesh*> m_staticMeshes;
	std::vector<RD_PointLight*> m_points_light;
};

#endif //_EXP_GAME_H__