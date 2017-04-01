/*
CGraphStatic class to display graph in static control version 1.0.0

Copyright (c) 2008 Wong Shao Voon

The Code Project Open License (CPOL)
http://www.codeproject.com/info/cpol10.aspx
*/

// GifStatic.cpp : implementation file
//

#include "stdafx.h"
#include "GraphStatic.h"


// CGifStatic

IMPLEMENT_DYNAMIC(CGraphStatic, CStatic)

CGraphStatic::CGraphStatic()
{
	m_pGraph = NULL;
}

CGraphStatic::~CGraphStatic()
{
}


BEGIN_MESSAGE_MAP(CGraphStatic, CStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CGifStatic message handlers



void CGraphStatic::OnPaint()
{
	CPaintDC dc(this); 

	if(m_pGraph)
	{
		using namespace Gdiplus;

		Graphics graphics(dc.GetSafeHdc());

		RECT rect;
		GetClientRect(&rect);

		Bitmap bmp(rect.right, rect.bottom, PixelFormat32bppARGB);
		Graphics graphics2(&bmp);

		m_pGraph->Paint(&graphics2, rect.right, rect.bottom);

		graphics.DrawImage(&bmp, 0, 0, rect.right, rect.bottom);
	}
}

BOOL CGraphStatic::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//return CDialog::OnEraseBkgnd(pDC);
	return TRUE;
}
