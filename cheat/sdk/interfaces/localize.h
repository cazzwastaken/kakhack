#pragma once
#include "appsystem.h"

// [TODO] -> complete this interface
// https://github.com/perilouswithadollarsign/cstrike15_src/blob/master/public/localize/ilocalize.h

class Localize : public AppSystem
{
public:
	// adds the contents of a file to the localization table
	virtual bool AddFile(const char* fileName, const char* pPathID = NULL, bool bIncludeFallbackSearchPaths = false) = 0;

	// Remove all strings from the table
	virtual void RemoveAll() = 0;

	// Finds the localized text for tokenName. Returns NULL if none is found.
	virtual wchar_t* Find(const char* tokenName) = 0;

	// Like Find(), but as a failsafe, returns an error message instead of NULL if the string isn't found.
	virtual const wchar_t* FindSafe(const char* tokenName) = 0;
};
