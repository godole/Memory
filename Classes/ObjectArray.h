#pragma once
#include <memory>
#include <vector>

using namespace std;

template <class Object>

class CObjectArray
{
public :
	void InsertObject(shared_ptr<Object> a_pObj)
	{
		m_arrObject.push_back(a_pObj);
		m_nSize++;
	}

	void RemoveObject(Object* a_pObj)
	{
		for (auto itr = m_arrObject.begin(); itr != m_arrObject.end(); itr++)
		{
			if ((*itr) == a_pObj)
			{
				m_arrObject.erase(itr);
				m_nSize--;
				break;
			}
		}
	}

	vector<shared_ptr<Object>> getObjectArray()
	{
		return m_arrObject;
	}

	shared_ptr<Object>	getObjectAt(int i)
	{
		return m_arrObject[i];
	}

	int	getSize()
	{
		return m_nSize;
	}

public :
	CObjectArray()
	{
		m_nSize = 0;
	}
	~CObjectArray(){};

private :
	vector<shared_ptr<Object>>	m_arrObject;

	int			m_nSize;
};