#pragma once

#ifndef MODULEDATA_DEF
#define MODULEDATA_DEF

#include <map>
#include <vector>

#include "ModuleBase.h"

template <class TD>
class CModuleData : public CModuleBase
{
public:
	CModuleData(CPackage * pPackage, DTYPE _dbType) 
		: CModuleBase(pPackage), dbType(_dbType) {}
	virtual ~CModuleData() {}

public:
	virtual void Clear() { m_mData.clear(); }
	virtual DKEY GetNewKey()
	{
		if (Empty()) return 1;

		auto itr = m_mData.rbegin();
		return itr->first + 1;
	}
	virtual DTYPE GetDataType() { return dbType; }

public: // Data 
	virtual BOOL Empty()
	{
		return m_mData.empty();
	}

	virtual BOOL Exist(DKEY key)
	{
		auto itr = m_mData.find(key);
		return itr != m_mData.end();
	}

	virtual BOOL Find(DKEY key, TD& data)
	{
		auto itr = m_mData.find(key);
		if (itr != m_mData.end())
			data = itr->second;

		return itr != m_mData.end();
	}

	virtual long GetDataList(std::vector<TD>& lstData)
	{
		auto szData = m_mData.size();
		if (szData > 0)
		{
			lstData.resize(szData);

			auto lCount = 0;
			auto itr = m_mData.begin();
			while (itr != m_mData.end())
			{
				lstData[lCount++] = itr->second;
				itr++;
			}
		}

		return static_cast<long>(szData);
	}

	virtual BOOL Insert(const TD& data)
	{
		if (Exist(data.GetKey()))
		{
			ASSERT(g_warning);
			return FALSE;
		}

		m_mData[data.GetKey()] = data;

		return TRUE;
	}

	virtual BOOL SetAt(DKEY key, const TD& data)
	{
		if (!Erase(key)) return FALSE;
		if (!Insert(data)) return FALSE;

		return TRUE;
	}

	virtual BOOL Erase(DKEY key)
	{
		auto itr = m_mData.find(key);
		if (itr == m_mData.end())
		{
			ASSERT(g_warning);
			return FALSE;
		}

		m_mData.erase(itr);

		return TRUE;
	}

public: 
	virtual void SetDefaultData() 
	{
		ASSERT(g_warning);
	}

protected:
	DTYPE dbType;
	std::map<DKEY, TD> m_mData;
};

#endif // !MODULEDATA_DEF

