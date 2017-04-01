#pragma once

#include <vector>
#include <string>


typedef struct tagBarValue
{
	tagBarValue() : fValue(0.0f) {}

	float fValue;
	std::wstring szBarName;
	std::wstring szValue; 
} BarValue;

class PaintGraph
{
public:
	PaintGraph(void);
	~PaintGraph(void);
	void SetTitle(const std::wstring& szTitle);
	std::wstring GetTitle() { return m_szTitle; }
	void AddBarName(const std::wstring& szBarName);
	void SetBarValue(size_t index, float value, const std::wstring& szValue);
	float GetMaxValue();
	void ClearData() { m_vecBars.clear(); }
	void Paint(Gdiplus::Graphics* graphics, int nWidth, int nHeight);


private:
	std::wstring m_szTitle;
	std::vector<BarValue> m_vecBars;
	std::vector<std::pair<Gdiplus::Color, Gdiplus::Color> > m_vecGradients;
};
