#pragma once

#include <atlcoll.h>
#include <atlstr.h>
#include <set>
#include <vector>
#include <string>

class AtlStdStrBenchmark
{
public:
	AtlStdStrBenchmark(void);
	~AtlStdStrBenchmark(void);

	void Initialize(std::vector<std::wstring>* pvecEngDict, std::vector<CString>* pvecEngDictCString);
	void Destroy();

	bool PopulateMap		(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
	bool PopulateMultimap	(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
	bool PopulateSet		(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
	bool PopulateMultiset	(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);

	bool BenchmarkMap		(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
	bool BenchmarkMultimap	(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
	bool BenchmarkSet		(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
	bool BenchmarkMultiset	(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);

	int GetIndex() { return 30; }

	bool SupportMap() { return true; }
	bool SupportMultimap() { return true; }
	bool SupportSet() { return false; }
	bool SupportMultiset() { return false; }

private:
	std::wstring m_szMapName;
	std::wstring m_szMultimapName;
	std::wstring m_szSetName;
	std::wstring m_szMultisetName;

	CRBMap<std::wstring, int> m_map;
	CRBMultiMap<std::wstring, int> m_multimap;

	std::vector<std::wstring>* m_pvecEngDict;
};

