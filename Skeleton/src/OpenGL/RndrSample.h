#pragma once

#include "IRndrBase.h"

class CRndrSample : public IRndrBase
{
public:
	CRndrSample();
	virtual ~CRndrSample();

public:
	virtual bool Run() override;

private:
	static void MyDisplay();

};

