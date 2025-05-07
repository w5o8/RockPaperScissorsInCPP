#include <iostream>
using namespace std;
enum enChoiceType {Paper = 1, Rock = 2, Scissors = 3};
enum enResultType {PlayerWin = 1, ComputerWin = 2 , Draw = 3};

struct stRoundInfo {
    short roundNumber = 0;
    enChoiceType playerChoice;
    enChoiceType computerChoice;
    enResultType Winner;
    string winnerName;
};

struct stGameInfo {
    short numberOfRounds = 0;
    short playerWins = 0;
    short computerWins = 0;
    short drawTimes = 0;
    enResultType winner;
    string winnerName = "";
};

int generateNumber(int from , int to) {
    int num = 0;
    num = rand() % (to - from + 1) + from;
    return num;
}

short readNumberOfRounds() {
    short x;
    do {
        cout<<"How many rounds you want to play ? ( 1 To 10 )\n";
        cin>>x;
    }while (x<1 || x>10);
        return x;
}

enChoiceType getComputerChoice() {
    return (enChoiceType) generateNumber(1,3);
}

enChoiceType readChoiceFromPlayer() {
    short choice;
    do {
        cout<<"Choose : [1] Paper , [2] Rock , [3] Scissors\n";
        cin>>choice;
    }while (choice<1 || choice > 3);
    return (enChoiceType) choice;
}

enResultType whoWonTheRound(stRoundInfo roundInfo) {
    if (roundInfo.computerChoice == roundInfo.playerChoice)
        return enResultType::Draw;
    switch (roundInfo.playerChoice) {
        case enChoiceType::Paper:
            if (roundInfo.computerChoice == enChoiceType::Scissors)
                return enResultType::ComputerWin;
            break;
        case enChoiceType::Rock:
            if (roundInfo.computerChoice == enChoiceType::Paper)
                return enResultType::ComputerWin;
            break;
        case enChoiceType::Scissors:
            if (roundInfo.computerChoice == enChoiceType::Rock)
                return enResultType::ComputerWin;
            break;
    }
    return enResultType::PlayerWin;
}

enResultType whoWonTheGame(short playerWins , short computerWins) {
    if (playerWins > computerWins)
        return enResultType::PlayerWin;
    if (playerWins < computerWins)
        return enResultType::ComputerWin;
    else
        return enResultType::Draw;
}


string choiceName(enChoiceType choice) {
    string choices[3] = {"Paper" , "Rock" , "Scissors"};
    return choices[choice-1];
}

string WinnerName(enResultType Winner)
{
    string arrWinnerName[3] = { "Player1", "Computer", "No Winner (Draw)" };
    return arrWinnerName[Winner - 1];
}

void printResultsOfRound(stRoundInfo roundInfo) {
    cout<<"Player Choice : " << choiceName(roundInfo.playerChoice);
    cout<<"\nComputer Choice : " << choiceName(roundInfo.computerChoice);
    cout<<"\nWinner : " <<roundInfo.winnerName<<endl;


}

stGameInfo playGame(short numberOfRounds) {
    stRoundInfo roundInfo;
    short playerWins = 0 , computerWins = 0 , draw = 0;
    for (int i = 1 ; i <= numberOfRounds ; i++) {
        cout<<"- - - - Round["<<i<<"] - - - -\n";
        roundInfo.roundNumber = i;
        roundInfo.playerChoice = readChoiceFromPlayer();
        roundInfo.computerChoice = getComputerChoice();
        roundInfo.Winner = whoWonTheRound(roundInfo);
        roundInfo.winnerName = WinnerName(roundInfo.Winner);

        if (roundInfo.Winner == enResultType::PlayerWin)
            playerWins++;
        else if (roundInfo.Winner == enResultType::ComputerWin)
            computerWins++;
        else
            draw++;
        printResultsOfRound(roundInfo);
    }
    return {numberOfRounds,playerWins,computerWins,draw,whoWonTheGame(playerWins,computerWins),WinnerName(whoWonTheGame(playerWins, computerWins))};
}

void gameOver(stGameInfo gameResults) {
    cout<<" - - - - GAME OVER - - - -\n";
    cout<<"Number of rounds : " << gameResults.numberOfRounds;
    cout<<"\nPlayer Wins : " << gameResults.playerWins;
    cout<<"\nComputer Wins : " << gameResults.computerWins;
    cout<<"\nDraw Times : " << gameResults.drawTimes;
    cout<<"\nWinner : "<<WinnerName(gameResults.winner)<<endl;


}

void startGame() {
    char playAgain = 'Y';
    do {
        stGameInfo gameInfo = playGame(readNumberOfRounds());
        gameOver(gameInfo);
        cout<<"Do u want to play again ? (Y/N)\n";
        cin>>playAgain;
    }while (playAgain == 'Y' || playAgain == 'y');
}
int main() {
    srand((unsigned)time(NULL));
    startGame();
    return 0;
}