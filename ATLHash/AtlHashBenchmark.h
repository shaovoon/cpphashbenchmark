#pragma once

#include <atlcoll.h>
#include <atlstr.h>
#include <set>
#include <vector>
#include <string>

class AtlHashBenchmark
{
public:
	AtlHashBenchmark(void);
	~AtlHashBenchmark(void);

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

	int GetIndex() { return 35; }

	bool SupportMap() { return true; }
	bool SupportMultimap() { return false; }
	bool SupportSet() { return false; }
	bool SupportMultiset() { return false; }

private:
	std::wstring m_szMapName;
	std::wstring m_szMultimapName;
	std::wstring m_szSetName;
	std::wstring m_szMultisetName;

	CAtlMap<CString, int> m_map;

	std::vector<CString>* m_pvecEngDict;
};

