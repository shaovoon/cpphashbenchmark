/*
CGifStatic class to display GIF in static control version 1.0.0

Copyright (c) 2008 Wong Shao Voon

The Code Project Open License (CPOL)
http://www.codeproject.com/info/cpol10.aspx
*/

#pragma once
#include "PaintGraph.h"

// CGraphStatic
class CGraphStatic : public CStatic
{
	DECLARE_DYNAMIC(CGraphStatic)

	PaintGraph* m_pGraph;

public:
	CGraphStatic();
	virtual ~CGraphStatic();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

};


