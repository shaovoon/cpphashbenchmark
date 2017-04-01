// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LEGACYHASH_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LEGACYHASH_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LEGACYHASH_EXPORTS
#define LEGACYHASH_API __declspec(dllexport)
#else
#define LEGACYHASH_API __declspec(dllimport)
#endif

extern "C"
{
LEGACYHASH_API void Initialize(std::vector<std::wstring>* pvecEngDict, std::vector<CString>* pvecEngDictCString);
LEGACYHASH_API void Destroy();

LEGACYHASH_API bool PopulateMap		(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
LEGACYHASH_API bool PopulateMultimap	(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
LEGACYHASH_API bool PopulateSet		(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
LEGACYHASH_API bool PopulateMultiset	(UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);

LEGACYHASH_API bool BenchmarkMap		(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
LEGACYHASH_API bool BenchmarkMultimap	(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
LEGACYHASH_API bool BenchmarkSet		(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);
LEGACYHASH_API bool BenchmarkMultiset	(UINT nRandomSeed, UINT nTotal, UINT* pTimeTaken, volatile UINT* pProgress, wchar_t* pName, USHORT* pLen);

LEGACYHASH_API int GetIndex();

LEGACYHASH_API bool SupportMap();
LEGACYHASH_API bool SupportMultimap();
LEGACYHASH_API bool SupportSet();
LEGACYHASH_API bool SupportMultiset();
}