#pragma once
#include <cstdio>
#include <fstream>
#include <iostream>
#include <bitset>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <set>

#include "StateDFA.h"
#include "StateNFA.h"

#ifndef MAX_NFA_STATES
#define MAX_NFA_STATES 10
#endif 

#ifndef MAX_ALPHABET_SIZE
#define MAX_ALPHABET_SIZE 10
#endif // !MAX_ALPHABET_SIZE


using namespace std;

class NFA
{
public:
	set<int> m_NFAfinalStates;
	bitset <MAX_NFA_STATES> currentStates;
	StateNFA *m_NFAstates;

	int m_nStates;
	int m_alphabetSize;
	char m_alphabet[MAX_ALPHABET_SIZE];

public:

	void epsilonClosure(int state, bitset<MAX_NFA_STATES> &closure);
	void epsilonClosure(bitset<MAX_NFA_STATES> state, bitset<MAX_NFA_STATES> &closure);
	void nextNFA(int X, char A, bitset<MAX_NFA_STATES> &Y);
	void nextNFA(bitset<MAX_NFA_STATES> X, char A, bitset<MAX_NFA_STATES> &Y);
	void readNFAFile();
	bool interpreter();


	NFA();
	~NFA();
};

