#include "UpdateManager.h"
#include "Update.h"


void UpdateManager::Insert(shared_ptr<IUpdate> update)
{
	m_arrUpdate.push_back(update);
}

void UpdateManager::Delete(shared_ptr<IUpdate> update)
{
	m_arrUpdate.remove(update);
}

void UpdateManager::Updating()
{
	for (auto itr = m_arrUpdate.begin(); itr != m_arrUpdate.end(); itr++)
	{
		itr->get()->Update();
	}
}

void UpdateManager::Release()
{
	m_arrUpdate.clear();
}