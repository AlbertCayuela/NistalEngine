#ifndef __GOCOMPONENT_H__
#define __GOCOMPONENT_H__

#include "GameObject.h"

class GameObject;
enum GOCOMPONENT_TYPE;

class GOComponent 
{

public:

	GOComponent(GameObject* game_object);
	~GOComponent();

	virtual void Update(float dt);
	virtual bool Enable();
	virtual bool Disable();

public:

	GOCOMPONENT_TYPE type;
	bool active = true;
	GameObject* parent = nullptr;

};

#endif
