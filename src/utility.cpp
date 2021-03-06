//
// Created by Denis Afendikov on 06.03.2021.
//

#include <algorithm>
#include <string>
#include "utility.h"

// Utility function to find minimum of three numbers
int min(int x, int y, int z) { return std::min(std::min(x, y), z); }

int editDist( const std::string& str1, const std::string& str2, int m, int n )
{
	// If first string is empty, the only option is to
	// insert all characters of second string into first
	if (m == 0)
		return n;

	// If second string is empty, the only option is to
	// remove all characters of first string
	if (n == 0)
		return m;

	// If last characters of two strings are same, nothing
	// much to do. Ignore last characters and get count for
	// remaining strings.
	if (str1[m - 1] == str2[n - 1])
		return editDist(str1, str2, m - 1, n - 1);

	// If last characters are not same, consider all three
	// operations on last character of first string,
	// recursively compute minimum cost for all three
	// operations and take minimum of three values.
	return 1
	       + min(editDist(str1, str2, m, n - 1), // Insert
		       editDist(str1, str2, m - 1, n), // Remove
		       editDist(str1, str2, m - 1,
			       n - 1) // Replace
	       );
}
