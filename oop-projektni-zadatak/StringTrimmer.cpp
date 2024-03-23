#include "StringTrimmer.h"
#include <algorithm>

void StringTrimmer::trim(std::string& str) {
	// Trim leading whitespaces
	auto start = std::find_if_not(str.begin(), str.end(), [](int c) {
		return isspace(c);
		});

	// Trim trailing whitespaces
	auto end = std::find_if_not(str.rbegin(), str.rend(), [](int c) {
		return isspace(c);
		}).base();

	// Return the trimmed string
	if (start < end)
		str = std::string(start, end);
}