#pragma once

#include "CMatrix.h"
#include "CPowerMath.h"


#include "CxbHvdcGrid.h"
#include "CxbResult.h"
#include "CxbOrder.h"

#include "CPowerProfile.h"


class CxbProfile : public CPowerProfile
{
public:
	//struct_xbBranchData * pxbBranchData;

public:
	//
	virtual ~CxbProfile();

	virtual void Init();
	virtual void Clear();

protected:
	virtual void doInit();
	virtual void doClear();
	
public:
	virtual void InitMatrix();

	virtual void ReSetData();

protected:
	virtual void doInitMatrix();
	virtual void doInitData();

public:
	int Flag_DCFOver;

	/**
	 * ���㹤��ָ��
	 */
	CxbOrder* pxbOrder;

	/**
	 * г������
	 */
	int hOrder=1;

	/**
	 * ϵͳƵ��
	 */
	double xbFreq=50;

	//����
	CMatrix * Ymatrix;
	CMatrix * Ivect;
	CMatrix * Uvect;
	
public:
	int StaDim();
	virtual double Omega();

	virtual void Solve();

	void UpdateYLine(int * pNode, CMatrix vY);

	virtual void UpdateI0(int iNode, double vIr, double vIm);

	virtual void UpdateI(int iNode, int jNode, double vIr, double vIm);


};

