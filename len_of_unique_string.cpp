#include<iostream>
#include<math.h>
#include<string.h>
#include <algorithm>    // std::max

using namespace std;

int lengthOfLongestSubstring(string s) {
	int m[256] = { 0 };			//用m来记录字符最近一次出现的位置，256只所有ASIC码中所有字符的个数，每个字符都有一个对应的asic码与之对应				
	int res = 0, left = 0;                 //res代表当前没有重复的子串长度，left代表当前没有重复的子串的最左侧的id
	for (int i = 0; i < s.size(); ++i)
	{
		if (m[s[i]] == 0 || m[s[i]] < left)   //当字符s[i]第一次出现或者上次出现位置在left左侧的时候，说明当前字符串没有重复，
		{
			res = max(res, i - left + 1);   //res为之前出现过和当前字符子串的最大值
		}
		else
		{
			left = m[s[i]];               //否则说明重复了，则最左侧的id为m[s[i]],  m[s[i]]等于上一次出现的id加1（即右侧一个元素）
		}
		m[s[i]] = i + 1;                      //更新当前字符最近出现的位置。
	}
	return res;
}
int main()
{
	string s = "hello 1234";
	lengthOfLongestSubstring(s);
}
