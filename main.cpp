#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class BlackjackCalculator {
private:
	std::vector<int> remainingCards;

public:
        BlackjackCalculator() {
		initializeDeck();
	}

	void initializeDeck() {
		remainingCards.clear();
		for (int i = 1; i <= 10; ++i) {
			remainingCards.push_back(i);
			remainingCards.push_back(10);
			remainingCards.push_back(10);
			remainingCards.push_back(10);
		}
	}

	double calculateCardProbability(int cardValue) const {
		int occurrences = std::count(remainingCards.begin(), remainingCards.end(), cardValue);
		int totalCards = remainingCards.size();
		return static_cast<double>(occurrences) / totalCards;
	}

	double calculateBustProbability(int currentHandValue) const {
		int possibleBusts = 0;

		for (int card : remainingCards) {
			if (currentHandValue + card > 21) {
				possibleBusts++;
			}
		}

		int totalCards = remainingCards.size();
		return static_cast<double>(possibleBusts) / totalCards;
	}

	double calculateWinningProbability(int playerHandValue, int dealerHandValue) const {
		int playerPointsLeft = 21 - playerHandValue;
		int winningCards = 0;

		for (int card : remainingCards) {
			if (card <= playerPointsLeft && playerHandValue + card > dealerHandValue) {
				winningCards++;
			}
		}

		int totalCards = remainingCards.size();
		return static_cast<double>(winningCards) / totalCards;
	}

	void simulateGame(int playerHandValue, int dealerHandValue) {
		double winProbability = calculateWinningProbability(playerHandValue, dealerHandValue);
		double bustProbability = calculateBustProbability(playerHandValue);

		std::cout << "Simulation Results:\n";
		std::cout << "Win Probability: " << (winProbability * 100) << "%\n";
		std::cout << "Bust Probability: " << (bustProbability * 100) << "%\n";
	}

	void play() {
		srand(static_cast<unsigned int>(time(0))); // random shuffle
		
// initial hand values
		int playerHandValue, dealerHandValue;
		std::cout << "Enter initial hand value for the player: ";
		std::cin >> playerHandValue;

		std::cout << "Enter initial hand value for the dealer: ";
		std::cin >> dealerHandValue;

		simulateGame(playerHandValue, dealerHandValue);
	}
};

int main() {
	BlackjackCalculator calculator;
	calculator.play();

	return 0;
}
