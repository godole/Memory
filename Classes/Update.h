#pragma once
#include "UpdateManager.h"

class IUpdate
{
public :
	IUpdate()
	{
	}
	virtual void Update() = 0;
};
