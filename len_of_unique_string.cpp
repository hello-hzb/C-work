#include<iostream>
#include<math.h>
#include<string.h>
#include <algorithm>    // std::max

using namespace std;

int lengthOfLongestSubstring(string s) {
	int m[256] = { 0 };
	int res = 0, left = 0;
	for (int i = 0; i < s.size(); ++i)
	{
		if (m[s[i]] == 0 || m[s[i]] < left)
		{
			res = max(res, i - left + 1);
		}
		else
		{
			left = m[s[i]];
		}
		m[s[i]] = i + 1;
	}
	return res;
}
int main()
{
	string s = "hello 1234";
	lengthOfLongestSubstring(s);
}