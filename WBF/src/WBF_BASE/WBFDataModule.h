#pragma once

#include "WBFDataDefine.h"
#include "HeaderPre.h"
namespace db
{
	class CWBFData;
	template <class type>
	class __MY_EXT_CLASS__ CWBFDataModule<type>
	{
	public:
		CWBFDataModule();
		virtual ~CWBFDataModule();

	public:
		virtual DTYPE GetDataType() = 0;

	public: // Data 
		virtual BOOL Exist(DKEY key) = 0;
		virtual BOOL LookUp(DKEY key, CWBFData* data) = 0;
		virtual BOOL Add(CWBFData* data) = 0;
		virtual BOOL Delete(DKEY key) = 0;
		virtual BOOL Modify(DKEY key, CWBFData* data) = 0;

	};
}
#include "HeaderPost.h"