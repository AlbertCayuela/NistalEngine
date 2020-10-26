#ifndef __GOCOMPONENT_H__
#define __GOCOMPONENT_H__

#include "GameObject.h"

class GOComponent 
{

public:

	GOComponent();
	~GOComponent();

	virtual void Update(float dt);
	virtual bool Enable();
	virtual bool Disable();

public:

	GOCOMPONENT_TYPE type;
	bool active = true;
	GameObject* parent;

};

#endif
