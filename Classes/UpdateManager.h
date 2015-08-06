#pragma once
#include "Singleton.h"
#include <list>
#include <memory>

using namespace std;

class IUpdate;

class UpdateManager :
	public Singleton<UpdateManager>
{
public:
	void Insert(shared_ptr<IUpdate> update);
	void Delete(shared_ptr<IUpdate> update);
	void Updating();
	void Release();

private:
	list<shared_ptr<IUpdate>> m_arrUpdate;
};

