#pragma once

#include "gbHead_3pType.h"

#include "CPowerCalculate.h"
#include "C3pProfile.h"


class C3pCalculate : public CPowerCalculate
{
protected:
	C3pProfile * p3pProfile;

	int Index3p;

public:
	void Init(CPowerProfile* vProfile) override;
	void Init(CDevBase * vDev) override;


public:

	virtual void Sort3p(ValveMap& vValMap);
	virtual void Prepare();
};


typedef vector<C3pCalculate*> p3pCalVector;