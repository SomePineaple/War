#ifndef WAR_H_
#define WAR_H_

#include <vector>

class War{
public:
	War();
	int playRound();
private:
	int war(int depth = 0);
	std::vector<int> deck;
	std::vector<int> hand1;
	std::vector<int> hand2;
	std::vector<int> hand1Winnings;
	std::vector<int> hand2Winnings;
};


#endif /* WAR_H_ */
