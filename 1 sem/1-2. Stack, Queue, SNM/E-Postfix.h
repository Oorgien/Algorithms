#pragma once
#include <iostream>
#include <stack>
#include <cctype>

void compound() {
	std::string s;
	getline(std::cin, s);
	std::stack<int> st;
	for (int i = 0; i < s.size(); i+=2) {
		if (isdigit(s[i])) {
			st.push(s[i]-'0');
		}
		else {
			int x = st.top();
			st.pop();
			int y = st.top();
			st.pop();

			if (s[i] == '+') {
				st.push(x + y);
			}
			else if (s[i] == '-') {
				st.push(y-x);
			}
			else if (s[i] == '*') {
				st.push(x * y);
			}

		}
	}
	std::cout << st.top();
}