#pragma once

class IRndrBase
{
public:
	IRndrBase();
	virtual ~IRndrBase();

public:
	virtual bool Run() = 0;
};

