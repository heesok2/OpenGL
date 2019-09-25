#pragma once

#include "WBFModuleData.hpp"
#include "DataBox.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CModuleBox : public CWBFModuleData<CDataBox>
{
public:
	CModuleBox(DTYPE dbType);
	virtual ~CModuleBox();


};

#include "HeaderPost.h"

