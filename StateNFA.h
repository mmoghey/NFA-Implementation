#pragma once
#include <map>

#ifndef MAX_NFA_STATES
#define MAX_NFA_STATES 10
#endif 

#ifndef MAX_ALPHABET_SIZE
#define MAX_ALPHABET_SIZE 10
#endif // !MAX_ALPHABET_SIZE

class StateNFA
{
public:
	//int transitions[MAX_ALPHABET_SIZE][MAX_NFA_STATES];
	std::map<char, std::map<int, int>> m_nfaTransitions;
	StateNFA();
};

