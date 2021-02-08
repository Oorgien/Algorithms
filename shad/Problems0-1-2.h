#pragma once
#include <string>
#include <stack>

int solve(std::string input) {
	std::stack<std::string> s;
	int cnt = 0;
	for (size_t i = 0; i < input.size(); i++) {
		if (input[i] == '{') {
			s.push("{");
			cnt++;
		}
		if (input[i] == '(') {
			s.push("(");
			cnt++;
		}
		if (input[i] == '[') {
			s.push("[");
			cnt++;
		}
		if (input[i] == '}') {
			if (s.empty()) {
				return cnt;
			}
			else if (!s.empty() && s.top() == "{") {
				s.pop();
				cnt++;
			}
		}
		else if (input[i] == ')') {
			if (s.empty()) {
				return cnt;
			}
			else if (!s.empty() && s.top() == "(") {
				s.pop();
				cnt++;
			}
		}
		else if (input[i] == ']') {
			if (s.empty()) {
				return cnt;
			}
			else if (!s.empty() && s.top() == "[") {
				s.pop();
				cnt++;
			}
		}
	}
	if (s.empty()) {
		return -1;
	}
	return cnt;
}