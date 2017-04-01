#pragma once

#include <map>
#include <set>
#include <vector>
#include <string>

class StlCStrBenchmark
{
public:
	StlCStrBenchmark(void);
	~StlCStrBenchmark(void);

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

	int GetIndex() { return 5; }

	bool SupportMap() { return true; }
	bool SupportMultimap() { return true; }
	bool SupportSet() { return true; }
	bool SupportMultiset() { return true; }

private:
	std::wstring m_szMapName;
	std::wstring m_szMultimapName;
	std::wstring m_szSetName;
	std::wstring m_szMultisetName;

	std::map<CString, int> m_map;
	std::multimap<CString, int> m_multimap;
	std::set<CString> m_set;
	std::multiset<CString> m_multiset;

	std::vector<CString>* m_pvecEngDict;
};

