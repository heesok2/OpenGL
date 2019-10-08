#pragma once

#ifndef DEFINE_DICT
#define DEFINE_DICT

#include "DataBaseDefine.h"

#define D_DEFAULT_HASH_NUM 10000
#define D_HASH_INDEX(key, hash_size) ((key) % (hash_size))

template <class ENTITY_DATA>
class CEntityDictionary
{
public:
	typedef struct tagEntity
	{
		TEntityParam Param;
		ENTITY_DATA Data;

		// Linked List
		tagEntity* lPrev;
		tagEntity* lNext;

		// Hashmap List
		tagEntity* hPrev;
		tagEntity* hNext;

	} TEntity, *LPEntity;

public:
	CEntityDictionary(long lHashNum = D_DEFAULT_HASH_NUM) : m_dbMaxKey(0),
		m_lLinkedNum(0), m_pHead(nullptr), m_pTail(nullptr),
		m_lHashNum(lHashNum), m_pHashmap(nullptr)
	{
		if (m_lHashNum < D_DEFAULT_HASH_NUM) m_lHashNum = D_DEFAULT_HASH_NUM;

		m_pHashmap = new LPEntity[m_lHashNum];
		memset(m_pHashmap, 0, sizeof(LPEntity)*m_lHashNum);
	}

	~CEntityDictionary()
	{
		DeleteAll();

		DeleteHashAll();
	}

public:
	void Clear()
	{
		DeleteAll();

		// Hashmap 은 그대로 둔다.
	}

	BOOL IsEmpty()
	{
		return m_lLinkedNum == 0;
	}

	long GetSize()
	{
		return m_lLinkedNum;
	}

	DKEY GetNewKey() { return m_dbMaxKey + 1; }

	DITER Find(DKEY dbKey)
	{
		if (!KEY_IS_VALID(dbKey))
		{
			ASSERT(g_warning);
			return (DITER)nullptr;
		}

		auto hidx = D_HASH_INDEX(dbKey, m_lHashNum);
		auto pEntity = m_pHashmap[hidx];
		while (pEntity != nullptr)
		{
			if (pEntity->Data.GetKey() == dbKey)
				return (DITER)pEntity;

			pEntity = pEntity->hNext;
		}

		return (DITER)nullptr;
	}

	DITER InsertNU(const ENTITY_DATA& data)
	{
		auto dbKey = data.GetKey();
		auto itr = Find(dbKey);
		if (ITR_IS_VALID(itr))
		{
			ASSERT(g_warning);
			return (DITER)nullptr;
		}

		auto pEntity = new TEntity();
		pEntity->Data = data;

		InsertData(pEntity);
		InsertHash(pEntity);

		SetMaxKey(dbKey);

		return (DITER)pEntity;
	}

	BOOL SetAtNU(DITER itr, const ENTITY_DATA& data)
	{
		auto dbKey = data.GetKey();
		auto itrFind = Find(dbKey);

		if (!ITR_IS_VALID(itrFind) || itrFind != itr)
		{
			ASSERT(g_warning);
			return FALSE;
		}

		auto pEntity = (TEntity*)itr;

		RemoveHash(pEntity);
		pEntity->Data = data;
		InsertHash(pEntity);

		SetMaxKey(dbKey);

		return TRUE;
	}

	BOOL Remove(DITER itr)
	{
		if (!ITR_IS_VALID(itr))
		{
			ASSERT(g_warning);
			return FALSE;
		}

		auto pEntity = (TEntity*)itr;

		RemoveHash(pEntity);
		RemoveData(pEntity);

		return TRUE;
	}

	const ENTITY_DATA& GetAtNU(DITER itr) const
	{
		return ((LPEntity)itr)->Data;
	}

	long GetList(std::vector<DITER>& lstIter)
	{
		auto pEntity = m_pHead;
		while (pEntity != nullptr)
		{
			lstIter.push_back((DITER)pEntity);
			pEntity = pEntity->lNext;
		}

		return (long)lstIter.size();
	}

	long GetListData(std::vector<ENTITY_DATA>& lstData)
	{
		auto pEntity = m_pHead;
		while (pEntity != nullptr)
		{
			lstData.push_back(pEntity->Data);
			pEntity = pEntity->lNext;
		}

		return (long)lstData.size();
	}

protected:
	void DeleteAll()
	{
		memset(m_pHashmap, 0, sizeof(LPEntity)*m_lHashNum);

		auto pEntity = m_pHead;
		auto pNext = m_pHead;
		while (pEntity != nullptr)
		{
			pNext = pEntity->lNext;
			_SAFE_DELETE(pEntity);
			pEntity = pNext;
		}

		m_lLinkedNum = 0;
		m_pHead = nullptr;
		m_pTail = nullptr;

		m_dbMaxKey = 0;
	}

	void DeleteHashAll()
	{
		_SAFE_DELETE_ARRAY(m_pHashmap);
		m_lHashNum = 0;
	}

	void InsertData(TEntity* pEntity)
	{
		if (m_pHead == nullptr)
		{
			pEntity->lPrev = nullptr;
			pEntity->lNext = nullptr;

			m_pHead = m_pTail = pEntity;
		}
		else
		{
			pEntity->lPrev = m_pTail;
			pEntity->lNext = nullptr;

			if (m_pTail != nullptr)
				m_pTail->lNext = pEntity;

			m_pTail = pEntity;
		}

		m_lLinkedNum++;
	}

	void RemoveData(TEntity* pEntity)
	{
		if (pEntity->lPrev) pEntity->lPrev->lNext = pEntity->lNext;
		else m_pHead = pEntity->lNext;

		if (pEntity->lNext) pEntity->lNext->lPrev = pEntity->lPrev;
		else m_pTail = pEntity->lPrev;

		_SAFE_DELETE(pEntity);

		m_lLinkedNum--;
	}

	void InsertHash(TEntity* pEntity)
	{
		auto dbKey = pEntity->Data.GetKey();

		auto hidx = D_HASH_INDEX(dbKey, m_lHashNum);
		auto pHmap = m_pHashmap[hidx];

		pEntity->hPrev = nullptr;
		pEntity->hNext = pHmap;
		if (pHmap != nullptr)
			pHmap->hPrev = pEntity;

		m_pHashmap[hidx] = pEntity;
	}

	void RemoveHash(TEntity* pEntity)
	{
		auto dbKey = pEntity->Data.GetKey();

		long hidx = D_HASH_INDEX(dbKey, m_lHashNum);
		auto pHash = m_pHashmap[hidx];

		if (pHash->hPrev == nullptr)
			m_pHashmap[hidx] = pHash->hNext;
		else
			pHash->hPrev->hNext = pHash->hNext;

		if (pHash->hNext != nullptr)
			pHash->hNext->hPrev = pHash->hPrev;
	}

	void SetMaxKey(DKEY dbKey)
	{
		if (m_lLinkedNum == 0)
		{
			m_dbMaxKey = dbKey;
		}
		else
		{
			m_dbMaxKey = dbKey < m_dbMaxKey ? m_dbMaxKey : dbKey;
		}
	}

protected:
	DKEY m_dbMaxKey;

	long m_lLinkedNum;
	LPEntity m_pHead;
	LPEntity m_pTail;

	long m_lHashNum;
	LPEntity* m_pHashmap;
};

#endif // !DEFINE_DICT

