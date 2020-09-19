#include "war.h"

#include <algorithm>
#include <chrono>
#include <initializer_list>
#include <iostream>
#include <random>

War::War(){
	deck = {1,2,3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13,1,2,3,4,5,6,7,8,9,10,11,12,13};
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
	int deckLen = (int)deck.size() / 2;
	for(int i = 0; i < deckLen; i++){
		hand1.push_back(deck.back());
		deck.pop_back();
		hand2.push_back(deck.back());
		deck.pop_back();
	}
}

int War::playRound(){
	if(hand1.size() == 0){
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(hand1Winnings.begin(), hand1Winnings.end(), std::default_random_engine(seed));
		for(int card : hand1Winnings){
			hand1.push_back(card);
		}
		hand1Winnings = {};
	}
	if(hand2.size() == 0){
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(hand2Winnings.begin(), hand2Winnings.end(), std::default_random_engine(seed));
		for(int card : hand2Winnings){
			hand2.push_back(card);
		}
		hand2Winnings = {};
	}
	if(hand1.size() == 0){
		return 2;
	} else if(hand2.size() == 0){
		return 1;
	}

	if(hand1.back() > hand2.back()){
		hand1Winnings.push_back(hand1.back());
		hand1Winnings.push_back(hand2.back());
		hand1.pop_back();
		hand2.pop_back();
	} else if(hand1.back() < hand2.back()){
		hand2Winnings.push_back(hand1.back());
		hand2Winnings.push_back(hand2.back());
		hand1.pop_back();
		hand2.pop_back();
	} else{
		return (war(0));
	}
	return 0;
}

int War::war(int depth){
	if(hand1.size() + hand1Winnings.size() == 0){
		return 2;
	} else if(hand2.size() + hand2Winnings.size() == 0){
		return 1;
	}
	if((int)hand1.size() < depth + 5){
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(hand1Winnings.begin(), hand1Winnings.end(), std::default_random_engine(seed));
		for(int card : hand1Winnings){
			hand1.push_back(card);
		}
		hand1Winnings = {};
	}
	if((int)hand2.size() < depth + 5){
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(hand2Winnings.begin(), hand2Winnings.end(), std::default_random_engine(seed));
		for(int card : hand2Winnings){
			hand2.push_back(card);
		}
		hand2Winnings = {};
	}
	int index1 = hand1.size() - (depth + 5);
	int index2 = hand2.size() - (depth + 5);
	if((int)hand1.size() < depth + 5){
		if(hand1.back() < hand2[index2]){
			return 2;
		} else if(hand1.back() > hand2[index2]){
			for(int card : hand1){
				hand1Winnings.push_back(card);
			}
			for(int i = 0; i < depth + 5; i++){
				hand1Winnings.push_back(hand2.back());
				hand2.pop_back();
			}
			hand1 = {};
		} else{
			return 2;
		}
	} else if((int)hand2.size() < depth + 5){
		if(hand1[index1] > hand2.back()){
			return 1;
		} else if(hand2.back() > hand1[index2]){
			for(int card : hand2){
				hand2Winnings.push_back(card);
			}
			for(int i = 0; i < depth + 5; i++){
				hand2Winnings.push_back(hand1.back());
				hand1.pop_back();
			}
			hand2 = {};
		} else{
			return 1;
		}
	} else if(hand1[index1] > hand2[index2]){
		for(int i = 0; i < depth + 5; i++){
			hand1Winnings.push_back(hand1.back());
			hand1Winnings.push_back(hand2.back());
			hand1.pop_back();
			hand2.pop_back();
		}
	} else if(hand1[index1] < hand2[index2]){
		for(int i = 0; i < depth + 5; i++){
			hand2Winnings.push_back(hand1.back());
			hand2Winnings.push_back(hand2.back());
			hand1.pop_back();
			hand2.pop_back();
		}
	} else{
		return war(depth + 4);
	}
	return 0;
}
