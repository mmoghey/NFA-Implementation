#include "StateNFA.h"



StateNFA::StateNFA()
{
	for (int i = 0; i < MAX_ALPHABET_SIZE; i++)
		for (int j = 0; j < MAX_NFA_STATES; j++)
			m_nfaTransitions[i][j] = -1;
}
