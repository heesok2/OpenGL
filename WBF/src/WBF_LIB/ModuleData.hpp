#pragma once

#ifndef MODULEDATA_DEF
#define MODULEDATA_DEF

#include "ModuleBase.h"
#include "EntityDictionary.hpp"

template <class TD>
class CModuleData : public CModuleBase
{
public:
	CModuleData(CPackage * pPackage, DTYPE _dbType) 
		: CModuleBase(pPackage), dbType(_dbType) {}
	virtual ~CModuleData() {}

public:
	virtual DTYPE GetDataType() { return dbType; }

public: // Data 
	virtual void Clear() 
	{ 
		m_Dictionary.Clear(); 
	}

	virtual BOOL Empty()
	{
		return m_Dictionary.IsEmpty();
	}

	virtual BOOL Exist(DKEY key)
	{
		auto itr = m_Dictionary.Find(key);
		return ITR_IS_VALID(itr);
	}

	virtual DITER Find(DKEY key)
	{
		return m_Dictionary.Find(key);
	}

	virtual BOOL Find(DKEY key, TD& data)
	{
		auto itr = m_Dictionary.Find(key);
		if (!ITR_IS_VALID(itr)) return FALSE;

		data = m_Dictionary.GetAtNU(itr);
		return TRUE;
	}

	virtual DITER InsertNU(const TD& data)
	{
		return m_Dictionary.InsertNU(data);
	}

	virtual BOOL SetAtNU(DITER itr, const TD& data)
	{
		return m_Dictionary.SetAtNU(itr, data);
	}

	virtual BOOL Remove(DITER itr)
	{
		return m_Dictionary.Remove(itr);
	}

	virtual const TD& GetAtNU(DITER itr) const
	{
		return m_Dictionary.GetAtNU(itr);
	}

	virtual long GetIterList(std::vector<DITER>& lstIter)
	{
		return m_Dictionary.GetList(lstIter);
	}

	virtual long GetDataList(std::vector<TD>& lstData)
	{
		return m_Dictionary.GetListData(lstData);
	}

	virtual DKEY GetNewKey()
	{
		return m_Dictionary.GetNewKey();
	}

public:
	virtual DITER GetDefaultData()
	{
		ASSERT(g_warning);
		return (DITER)nullptr;
	}

	virtual void SetDefaultData() 
	{
		ASSERT(g_warning);
	}

protected:
	DTYPE dbType;
	CEntityDictionary<TD> m_Dictionary;
};

#endif // !MODULEDATA_DEF

