#pragma once

#include "C3pDevGrid.h"
#include "C3pResult.h"
#include "C3pSolves.h"


class C3pSolveMvc
{
protected:
	C3pDevGrid * p3pHvdc;
	C3pProfile* p3pProfile;
	C3pResult* p3pResult;
	C3pSolves * p3pSolves;

public:
	virtual ~C3pSolveMvc();

	virtual void Init();
	virtual void Init(C3pDevGrid* vGrid);

	virtual void Clear();
	virtual void InitOrder();

public:
	virtual void Test(int vGNDType);
	virtual void Run();
protected:

	virtual void doNewSolves(int vGNDType);

protected:
	int StaCount();
	double hMax();
	double Frequence();

	//
	void doInitRun();

	virtual void doRecordResult();

	virtual void doRun();

	void doSort3p();
	void doStationSort();

	void doRun_Ground(string vFlag);
	void doRun_Rd(string vFlag);
	void doRun_Ud(string vFlag);
	void doRun_UdCustom();
	void doRun_Uac(string vFlag);
	void doRun_UacSwap(string vFlag, int vIndex, int vStaCount);
	void doRun_Pd();

};
