#include <chrono>
#include <iostream>
#include <unistd.h>

#include "war.h"

using namespace std;
using namespace std::chrono;

int main (){
	War *game = new War();
	unsigned long int games;
	int max = -9999;
	int min = 9999;
	unsigned long total = 0;
	cout << "How many rounds of war do you want to test: ";
	cin >> games;
	auto start = high_resolution_clock::now();
	for(unsigned long int i = 0; i < games; i++){
		int result = 0;
		while (game->playRound() == 0){
			result++;
		}
		cout << i + 1 << " " << result << endl;
		total += result;
		if(result > max){
			max = result;
		} else if(result < min){
			min = result;
		}
		game->reset();
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	int avg = total / games;
	cout << "Avg: " << avg << " Max: " << max << " Min: " << min << endl;
	cout << "Execution time: " << (double)duration.count() / 1000 << " seconds" << endl;
	return 0;
}
