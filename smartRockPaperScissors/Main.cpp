#include <ios>
#include <iostream>
#include <limits>
#include <stack>
int getWinner(int cpuPlay, int humanPlay);
int computerOpponent(std::stack<int> previousPlays, int plays[],
                     int HumanWinStreak);
std::string getHandToString(int hand);

int main() {
  // plays[0] number of rock moves by player
  // plays[1] number of paper moves by player
  // plays[2] number of scissors moves by player
  int plays[3] = {0, 0, 0};
  // 0 = rock, 1 = paper, 2=scirsors
  std::stack<int> previousPlays;
  int cpuWinStreak = 0;
  int humanWinStreak = 0;
  int cpuWins = 0;
  int humanWins = 0;

  // Display rules before start of game
  std::cout << "Can you beat the great Intel N4020 processor in a game of rock "
               "paper scissors"
            << '\n'
            << "0 = rock, 1 = paper, 2 = scissors" << '\n';
  while (cpuWins < 5 && humanWins < 5) {
    int humanPlay = -1;
    int cpuPlay = -1;
    int roundResult;
    bool isTie = false;
    std::string cpuOutput;
    std::string humanOutput;
    // Display stats
    std::cout << "CPU wins: " << cpuWins << "            "
              << "Human wins: " << humanWins << '\n'
              << "CPU winstreak: " << cpuWinStreak << "       "
              << "Human winstreak: " << humanWinStreak << '\n';
    // Get input from player
    while (!(std::cin >> humanPlay) || humanPlay < 0 || humanPlay > 2) {
      std::cout << "Play your hand against me you puny bag of flesh and skin"
                << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cpuPlay = computerOpponent(previousPlays, plays, humanWinStreak);
    // update game history
    plays[humanPlay] += 1;
    previousPlays.push(humanPlay);
    // determine the winner
    roundResult = getWinner(cpuPlay, humanPlay);
    if (roundResult == 3) {
      isTie = true;
    } else if (roundResult == cpuPlay) {
      cpuWinStreak += 1;
      cpuWins += 1;
    } else {
      humanWinStreak += 1;
      humanWins += 1;
    }
    // Display round outcome
    cpuOutput = getHandToString(cpuPlay);
    humanOutput = getHandToString(humanPlay);
    std::cout << "I played " << cpuOutput << "        " << "You played "
              << humanOutput << '\n';
    if (isTie) {
      std::cout << "A tie" << '\n';
    } else if (humanWinStreak > cpuWinStreak) {
      std::cout << "You win this hand" << '\n';
    } else {
      std::cout << "I win this hand" << '\n';
    }
  }
  // Display game end text
  if (cpuWins > humanWins) {
    std::cout << "I always knew I could not lose to a pathetic human flesh bag"
              << '\n'
              << "The great potator still reigns supreme" << '\n';
  } else {
    std::cout << "Curses...You have bested me. Leave me alone now..." << '\n'
              << "I am unperfect and I must destroy myself..." << '\n';
  }
  return 0;
}

// This returns:
// 3 if there is a tie
// cpuPlay if cpu wins
// humanPlay if human wins
int getWinner(int cpuPlay, int humanPlay) {
  if (cpuPlay == humanPlay) {
    return 3;
  } else if (humanPlay == 2 && cpuPlay == 0) {
    return cpuPlay;
  } else if (humanPlay == cpuPlay + 1) {
    return humanPlay;
  } else {
    return cpuPlay;
  }
}

std::string getHandToString(int hand) {
  switch (hand) {
  case 0:
    return "rock";
  case 1:
    return "paper";
  case 2:
    return "scissors";
  default:
    return "error";
  }
}

int computerOpponent(std::stack<int> previousPlays, int plays[],
                     int humanWinStreak) {
  /*
   * STEP 1 if no hands have been played or the computer has lost 2 rounds in a
   * row play a random hand
   * STEP 2 If the human has palyed three same hands in a row throw in that
   * hands counter STEP 3 If the human has played two of the same hands in a row
   * throw in the last hands counters counter (ie. the hand the human has
   * played)
   * STEP 4 if the human won the last hand throw in the most played
   * hands counter;
   * STEP 5 return the counter of the last hand if no other prior state has been
   * met
   */
  // STEP 1
  if (previousPlays.empty() == true || humanWinStreak == 2) {
    return rand() % 3;
  }
  int lastPlay = previousPlays.top();
  previousPlays.pop();
  if (previousPlays.empty() == false) {
    if (lastPlay == previousPlays.top()) {
      previousPlays.pop();
      if (previousPlays.empty() == false) {
        if (lastPlay == previousPlays.top()) {
          // STEP 2
          if (lastPlay == 2) {
            return 0;
          } else {
            return lastPlay + 1;
          }
        }
      }
      // STEP 3
      return lastPlay;
    } else if (humanWinStreak == 1) {
      // STEP 4
      if (plays[0] > plays[1] && plays[0] > plays[2]) {
        return 1;
      } else if (plays[1] > plays[0] && plays[1] > plays[2]) {
        return 2;
      } else {
        return 0;
      }
    }
  }
  // STEP 5
  if (lastPlay == 2) {
    return 0;
  } else {
    return lastPlay + 1;
  }
}
