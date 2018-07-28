#include "NFA.h"



NFA::NFA()
{
}


NFA::~NFA()
{
}


void NFA::epsilonClosure(int state, bitset<MAX_NFA_STATES> &closure) {
	for (int i = 0; i < m_nStates && m_NFAstates[state].m_nfaTransitions['0'][i] != -1; i++)
		if (closure[m_NFAstates[state].m_nfaTransitions['0'][i]] == 0)
		{
			closure[m_NFAstates[state].m_nfaTransitions['0'][i]] = 1;
			epsilonClosure(m_NFAstates[state].m_nfaTransitions['0'][i], closure);
		}
}

void NFA::epsilonClosure(bitset<MAX_NFA_STATES> state, bitset<MAX_NFA_STATES> &closure) {
	for (int i = 0; i < m_nStates; i++)
		if (state[i] == 1)
			epsilonClosure(i, closure);
}

void NFA::nextNFA(int X, char A, bitset<MAX_NFA_STATES> &Y) {
	for (int i = 0; i < m_nStates && m_NFAstates[X].m_nfaTransitions[A][i] != -1; i++)
		Y[m_NFAstates[X].m_nfaTransitions[A][i]] = 1;
}

void NFA::nextNFA(bitset<MAX_NFA_STATES> X, char A, bitset<MAX_NFA_STATES> &Y) {
	bitset<MAX_NFA_STATES> tmp;
	for (int i = 0; i < m_nStates; i++)
		if (X[i] == 1)
			nextNFA(i, A, tmp);
	Y = tmp;
}

void NFA::readNFAFile() {
	int numfStates, finalState;
	int numTransitions;
	char input;
	int prevState, numNextStates, nextState;
	int i;
	char ch;

	ifstream fin("NFAInput.txt");
	fin >> m_nStates;


	fin >> m_alphabetSize;
	m_alphabet[0] = '0';
	for (i = 1; i <= m_alphabetSize; i++)
		fin >> m_alphabet[i];
	m_NFAstates = new StateNFA[m_nStates];
	for (i = 0; i < m_nStates; i++) {
		for (int j = 0; j < m_nStates; j++)
			for (int k = 0; k <= m_alphabetSize; k++) {
				m_NFAstates[i].m_nfaTransitions[m_alphabet[k]][j] = -1;
			}
	}
	fin >> numfStates;
	for (i = 0; i < numfStates; i++)
	{
		fin >> finalState;
		if (finalState > m_nStates || finalState < 0) {
			cout << "INVALID FINAL STATES";
			cin >> ch;
			exit(-1);
		}

		m_NFAfinalStates.insert(finalState);
	}
	fin >> numTransitions;
	while (numTransitions--)
	{
		fin >> prevState >> input >> numNextStates;
		if (prevState < 0 && prevState > m_nStates) {
			cout << "\n Invalid State ! \n";
			cin >> ch;
			exit(-1);
		}

		bool valid = false;
		
		for (i = 0; i <= m_alphabetSize; i++) {
			if (m_alphabet[i] == input) {
				valid = true;
			}
		}

		if ((valid) == false) {
			cout << "\n Invalid symbol \n";
			cin >> ch;
			exit(-1);
		}

		for (i = 0; i < numNextStates; i++)
		{
			fin >> nextState;
			if (nextState < 0 && nextState > m_nStates) {
				cout << "\n Invalid State ! \n";
				cin >> ch;
				exit(-1);
			}
			m_NFAstates[prevState].m_nfaTransitions[input][i] = nextState;
			//transitions[input][i] = nextState;
		}
	}
	fin.close();
}

bool NFA::interpreter() {

	string inputStr;
	char symbol;
	bool found;
	int iter;
	int prevState = 0, nextState = 0;
currentStates[0] = 1;
	cout << "\n\n Enter the input String\n\n";
	cin >> inputStr;
	for (unsigned i = 0; i < inputStr.size(); i++) {
			symbol = inputStr[i];
			found = false;
			
			epsilonClosure(currentStates, currentStates);

			for (int j = 0; j <= m_alphabetSize; j++) {
				if (symbol == m_alphabet[j]) {
					found = true; break;
				}
			}

			if (found == false) {
				cout << "Invalid input";
				cin >> symbol;
				exit(-1);
			}
			else
			{
				nextNFA(currentStates, symbol, currentStates);
				epsilonClosure(currentStates, currentStates);
			}

		}

	for (int iter = 0; iter < m_nStates; iter++) {
		if (currentStates[iter] == 1 && m_NFAfinalStates.find(iter) != m_NFAfinalStates.end())
			return true;
	}
		
	return false;


}