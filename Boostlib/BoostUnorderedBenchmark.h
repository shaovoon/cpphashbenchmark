#pragma once

#include <boost/unordered/unordered_map.hpp>
#include <boost/unordered/unordered_set.hpp>
#include <vector>
#include <string>

class BoostUnorderedBenchmark
{
public:
	BoostUnorderedBenchmark(void);
	~BoostUnorderedBenchmark(void);

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

	int GetIndex() { return 20; }

	bool SupportMap() { return true; }
	bool SupportMultimap() { return true; }
	bool SupportSet() { return true; }
	bool SupportMultiset() { return true; }

private:
	std::wstring m_szMapName;
	std::wstring m_szMultimapName;
	std::wstring m_szSetName;
	std::wstring m_szMultisetName;

	boost::unordered_map<std::wstring, int> m_map;
	boost::unordered_multimap<std::wstring, int> m_multimap;
	boost::unordered_set<std::wstring> m_set;
	boost::unordered_multiset<std::wstring> m_multiset;

	std::vector<std::wstring>* m_pvecEngDict;
};

