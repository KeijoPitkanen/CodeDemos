#include <iostream>
#include <stack>

int computerOpponent(std::stack<int> previousPlays, int plays[],
                     int winStreak) {
  int lastPlay = previousPlays.top();
  previousPlays.pop();
  // If no hands have been played or the computer has lost 2 games in a row play
  // a random hand
  if (previousPlays.empty() == true || winStreak == -2) {
    return rand() % 3;
  }
  if (lastPlay == previousPlays.top()) {
    previousPlays.pop();
    // If the opponent has played three same hands in a row throw in thats
    // counter;
    if (lastPlay == previousPlays.top()) {
      if (lastPlay == 2) {
        return 0;
      } else {
        return lastPlay + 1;
      }
    }
    // If the opponent has played two of the same hands in a row throw in the
    // lasts hands counters counter;
    return lastPlay;
  } else if (winStreak == -1) {
    // return counter to most played hand
    if (plays[0] > plays[1] && plays[0] > plays[2]) {
      return 1;
    } else if (plays[1] > plays[0] && plays[1] > plays[2]) {
      return 2;
    } else {
      return 0;
    }
  } else if (lastPlay == 2) {
    // return the counter of the last hand if no prior state has been met
    return 0;
  } else {
    return lastPlay + 1;
  }
}

int main() {
  // plays[0] number of rock moves by player
  // plays[1] number of paper moves by player
  // plays[2] number of scissors moves by player
  int plays[3] = {0, 0, 0};
  // 0 = rock, 1 = paper, 2=scissors
  std::stack<int> previousPlays;
  int cpuWinStreak = 0;
  int humanWinStreak = 0;
  int cpuWins = 0;
  int humanWins = 0;

  std::cout
      << "Can you beat the potato processor in a game of rock paper scissors"
      << '\n'
      << "0 = rock, 1 = paper, 2 = scissors";
  while (cpuWins < 5 || humanWins < 5) {
    int currentPlay = -1;
    int cpuPlay = -1;
    std::cout << "CPU wins: " << cpuWins << "       "
              << "Human wins: " << humanWins << '\n'
              << "CPU winstreak: " << cpuWinStreak << "        "
              << "Human winstreak: " << humanWinStreak << '\n';
    // while (currentPlay < 0 && currentPlay > 2) {
    std::cout << "Play your hand against me you puny bag of flesh and skin"
              << '\n';
    std::cin >> currentPlay;
    //}
    switch (currentPlay) {
    case 0:
      plays[0] += 1;
      break;
    case 1:
      plays[1] += 1;
      break;
    case 2:
      plays[2] += 1;
      break;
    }
    previousPlays.push(currentPlay);
    cpuPlay = computerOpponent(previousPlays, plays, cpuWinStreak);
    if (currentPlay == 2 && cpuPlay == 0) {
      if (cpuWinStreak < 0) {
        cpuWinStreak = 1;
      } else {
        cpuWinStreak += 1;
      }
      humanWinStreak = 0;
      cpuWins += 1;
    } else if (cpuPlay == currentPlay + 1) {
      if (cpuWinStreak < 0) {
        cpuWinStreak = 1;
      } else {
        cpuWinStreak += 1;
      }
      humanWinStreak = 0;
      cpuWins += 1;
    } else {
      cpuWinStreak = 0;
      humanWins += 1;
      if (humanWinStreak < 0) {
        humanWinStreak = 1;
      } else {
        humanWinStreak += 1;
      }
    }
    std::string output = "";
    switch (cpuPlay) {
    case 0:
      output = "I play rock";
      break;
    case 1:
      output = "I play paper";
      break;
    case 2:
      output = "I play scissors";
      break;
    default:
      break;
    }
    std::cout << output << '\n';
    cpuPlay = -1;
    currentPlay = -1;
  }
  if (cpuWins > humanWins) {
    std::cout << "I always knew I could not lose to a pathetic human flesh bag"
              << '\n'
              << "The great potator still reigns supreme";
  } else {
    std::cout << "Curses...You have bested me. Leave me alone now..." << '\n'
              << "I am unperfect and I must destroy myself...";
  }
  return 0;
}
