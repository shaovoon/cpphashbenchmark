#include "StdAfx.h"
#include "PaintGraph.h"
#include <sstream>

PaintGraph::PaintGraph(void)
{
	m_szTitle = L"";

	m_vecGradients.push_back(std::make_pair(Gdiplus::Color(0,255,64), Gdiplus::Color(0,64,10)));
	m_vecGradients.push_back(std::make_pair(Gdiplus::Color(0,255,255), Gdiplus::Color(0,0,255)));
	m_vecGradients.push_back(std::make_pair(Gdiplus::Color(255,255,0), Gdiplus::Color(255,0,0)));
	m_vecGradients.push_back(std::make_pair(Gdiplus::Color(255,128,255), Gdiplus::Color(64,0,128)));
	m_vecGradients.push_back(std::make_pair(Gdiplus::Color(255,255,0), Gdiplus::Color(0,255,0)));
	m_vecGradients.push_back(std::make_pair(Gdiplus::Color(0,255,0), Gdiplus::Color(40,51,255)));
	m_vecGradients.push_back(std::make_pair(Gdiplus::Color(255,116,17), Gdiplus::Color(40,51,255)));
	m_vecGradients.push_back(std::make_pair(Gdiplus::Color(0,255,0), Gdiplus::Color(255,128,64)));
}

PaintGraph::~PaintGraph(void)
{
}

void PaintGraph::SetTitle(const std::wstring& szTitle)
{
	m_szTitle = szTitle;
}

void PaintGraph::AddBarName(const std::wstring& szBarName)
{
	BarValue barValue;
	barValue.szBarName = szBarName;

	m_vecBars.push_back(barValue);
}

void PaintGraph::SetBarValue(size_t index, float value, const std::wstring& szValue)
{
	if (index >= m_vecBars.size())
		return;

	m_vecBars[index].fValue = value;
	m_vecBars[index].szValue = szValue;
}

float PaintGraph::GetMaxValue()
{
	float max = 0.0f;
	for(size_t i=0; i < m_vecBars.size(); ++i)
	{
		if (m_vecBars[i].fValue > max)
			max = m_vecBars[i].fValue;
	}
	return max;
}

void PaintGraph::Paint(Gdiplus::Graphics* graphics, int nWidth, int nHeight)
{
	if (graphics == NULL)
		return;

	// 12+6.5+2 = 20.5 = 41/2

	float fTotalBars = m_vecBars.size() > 0 ? m_vecBars.size() : 4.0f;

	//float dMargin = nWidth / 41.0f * 2.0f;
	float dMargin = nWidth / (fTotalBars * 3 / 2 + 2.5f);
	//float dGraphableWidth = (12.0f + 6.5f) * dMargin;
	float dGraphableWidth = (fTotalBars * 3 / 2 + 0.5f) * dMargin;
	float dGraphableHeight = nHeight - dMargin*2.0f;
	float max = GetMaxValue();

	using namespace Gdiplus;
	// draw x and y axes
	Pen penBlack(Color(0,0,0),2.0f);

	Gdiplus::Rect fillClientRect(
		0, 0, nWidth, nHeight);
	LinearGradientBrush brushWhite(
		fillClientRect,
		Gdiplus::Color(230,230,230),
		Gdiplus::Color(255,255,255),
		LinearGradientModeVertical);

	graphics->FillRectangle(&brushWhite, fillClientRect);
	graphics->DrawRectangle(&penBlack, fillClientRect);

	// Draw the title
	if(m_szTitle.length() > 0 && m_szTitle != L"")
	{
		Gdiplus::RectF rectTextShifted(
			1.0f, 1.0f,
			(float)(nWidth), dMargin);
		Gdiplus::Font font(L"Arial", 12.0, FontStyleBold);
		SolidBrush brushTextWhite(Color(255,255,255));
		StringFormat strFormat;
		strFormat.SetAlignment(StringAlignmentCenter);
		strFormat.SetLineAlignment(StringAlignmentCenter);
		graphics->DrawString(m_szTitle.c_str(), 
			m_szTitle.length(), &font, rectTextShifted, &strFormat, &brushTextWhite);

		Gdiplus::RectF rectText(
			0.0f, 0.0f,
			(float)(nWidth), dMargin);
		SolidBrush brushTextBlack(Color(0,0,0));
		graphics->DrawString(m_szTitle.c_str(), 
			m_szTitle.length(), &font, rectText, &strFormat, &brushTextBlack);
	}

	// draw the grid lines
	Pen penGrey(Color(180,180,180),1.0f);
	for(int a=1; a<4; ++a)
	{
		graphics->DrawLine(&penGrey,
			PointF(dMargin, dMargin + dGraphableHeight * a / 4),
			PointF(dMargin + dGraphableWidth, dMargin + dGraphableHeight * a / 4));
	}

	// draw y axis line
	graphics->DrawLine(&penBlack, 
		PointF(dMargin, dMargin),
		PointF(dMargin, dMargin+dGraphableHeight));
	// draw x axis line
	graphics->DrawLine(&penBlack,
		PointF(dMargin, dMargin + dGraphableHeight),
		PointF(dMargin + dGraphableWidth, dMargin + dGraphableHeight));

	for(size_t i=0; i<m_vecBars.size(); ++i)
	{
		//if(! (m_vecBars[i].fValue <= 0.0f) )
		//{

		double dGraphableHeight2 = dGraphableHeight * 0.9;
		float fBarHeight = (m_vecBars[i].fValue / max * dGraphableHeight2);
		PointF ptTopLeft((dMargin * i) + (dMargin * 0.5f * i) + dMargin * 1.5f, dMargin + (dGraphableHeight - fBarHeight));
		PointF ptBottomRight(ptTopLeft.X + dMargin, dMargin + dGraphableHeight);
		Gdiplus::Rect rectGradBrush(
			(int)ptTopLeft.X, 
			(int)ptTopLeft.Y,
			(int)dMargin,
			(int)fBarHeight);
		LinearGradientBrush brush(
			rectGradBrush,
			m_vecGradients[i%m_vecGradients.size()].first,
			m_vecGradients[i%m_vecGradients.size()].second,
			LinearGradientModeVertical);
		Gdiplus::Rect rectDrawRect(
			(int)ptTopLeft.X, (int)ptTopLeft.Y,
			(int)(ptBottomRight.X - ptTopLeft.X),
			(int)(ptBottomRight.Y - ptTopLeft.Y));

		graphics->FillRectangle(&brush, rectDrawRect);
		graphics->DrawRectangle(&penBlack, rectDrawRect);
		
		Gdiplus::RectF rectText(
			ptTopLeft.X, ptBottomRight.Y+3.0f,
			ptBottomRight.X - ptTopLeft.X, 
			60.0f);
		Gdiplus::Font font(L"Arial", 8.0, FontStyleRegular);
		SolidBrush brushText(Color(0,0,0));
		StringFormat strFormat;
		strFormat.SetAlignment(StringAlignmentCenter);
		graphics->DrawString(m_vecBars[i].szBarName.c_str(), 
			m_vecBars[i].szBarName.length(), &font, rectText, &strFormat, &brushText);
		StringFormat strFormat2;
		graphics->DrawString(m_vecBars[i].szValue.c_str(), 
			m_vecBars[i].szValue.length(), &font, PointF(ptTopLeft.X, ptTopLeft.Y - 18.0f), 
			&strFormat2, &brushText);

	}
}