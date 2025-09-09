#include <iostream>
#include <random>

struct Wallet
{
    int balance{ 50 };
};

struct GameStats
{
    int CashFlowCount{ 0 };
    bool banned{ false };
};

namespace CasinoConfig
{
    constexpr int inputBufferSize{ 10000 };
    constexpr int gameOverCriteria{ 0 };
    constexpr int minimumBetAmount{ 5 };
}
namespace OddEvenConfig
{
    constexpr int winLimit{ 125 };
    constexpr int diceMinRoll{ 1 };
    constexpr int diceMaxRoll{ 6 };
    constexpr int payoutRatio{ 2 };
    constexpr int winnerMsgThreshhold{ 80 };
    constexpr int loserMsgThreshhold{ -40 };
}
namespace DiceGuessConfig
{
    constexpr int winLimit{ 175 };
    constexpr int diceMinRoll{ 1 };
    constexpr int diceMaxRoll{ 6 };
    constexpr int amtOfDice{ 2 };
    constexpr int payoutRatio{ 9 };
    constexpr int winnerMsgThreshHold{ 70 };
    constexpr int loserMsgThreshHold{ -40 };
}

struct WinLossHistory
{
    static constexpr int historySize{ 5 };

    char playHistory[historySize] = { ' ', ' ', ' ', ' ', ' ' };
    int historySlot = 0;

    void SaveResult(char aRoundResult)
    {
        playHistory[historySlot] = aRoundResult;
        historySlot = (historySlot + 1) % historySize;
    }

    void ShowResults()
    {
        std::cout << "Recent round history\n\n";

        for (int i{ 0 }; i < 5; ++i)
        {
            std::cout << "Round " << i + 1 << ": ";
            if (playHistory[i] == ' ')
            {
                std::cout << "-----\n";
            }
            else if (playHistory[i] == 'W')
            {
                std::cout << "Won\n";
            }
            else if (playHistory[i] == 'L')
            {
                std::cout << "Lost";
                std::cout << '\n';
            }
        }
    }
};


int DiceRoll(int aLowestSide, int aHighestSide);
int BetCheckpoint(int aBalance);
bool PlayAgain();
void OddEvenGamePrintResult(int aRoll, int aRoll2, int anInputFromUser);
void OddEvenGame(GameStats& gameStats, Wallet& wallet, WinLossHistory& history);
bool OddEvenGameIntro(GameStats& gameStats);
void OddEvenGameLogic(int aMinRoll, int aMaxRoll, GameStats& oddEvenStats, Wallet& wallet, WinLossHistory& history);
void DiceGuessGame(GameStats& gameStats, Wallet& wallet, WinLossHistory& history);
void DiceGuessPrintResult(int userInput, int roll1, int roll2, int rollTotal);
void DiceGuessGameLogic(int aMinRoll, int aMaxRoll, int anAmountOfDice, GameStats& diceGameStats, Wallet& wallet, WinLossHistory& history);
bool DiceGuessIntro(GameStats& gameStats);
void Lobby(Wallet& wallet, WinLossHistory& history, GameStats& oddEvenStats, GameStats& diceGuessStats);
bool PostTutorialPrompt();
void GameOver();


//remove glob alhistory for struct, reference, function, namespace

//2.0implement enums (prefer scoping them within namespaces or classes for less pollution)for ex. choice based prompts (menus, yes/no)
//enumerated types related to a class inside the scope region of the class
//enums for choice switches

//4.0divide functions into separate files and headers

//add game3 throw dice, dont even ask for input bigger num wins

//add game4 higher or lower?

int main()
{
    Wallet wallet;
    GameStats oddEvenGame;
    GameStats diceGuessGame;
    WinLossHistory history;

    Lobby(wallet, history, oddEvenGame, diceGuessGame);

    return 0;
}

void Lobby(Wallet& wallet, WinLossHistory& history, GameStats& oddEvenStats, GameStats& diceGuessStats)
{
    int choice{};
    bool showMenu{ true };

    while (showMenu && wallet.balance > CasinoConfig::gameOverCriteria)
    {
        std::cout << "Welcome to the Casino! My name is D6 and I'm your host for the evening.\n\n"
            << "Current balance: " << wallet.balance << " Gil" << "\n\n"
            << "What would you like to do?\n1: Play Guess The Number\n2: Play Even/Odd\n"
            << "3: Show Win/Loss History (The 5 most recent rounds played)\n4: Exit\n";
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(CasinoConfig::inputBufferSize, '\n');
        system("cls");

        switch (choice)
        {
        case 1:
            DiceGuessGame(diceGuessStats, wallet, history);
            break;
        case 2:
            OddEvenGame(oddEvenStats, wallet, history);
            break;
        case 3:
            history.ShowResults();
            system("pause");
            system("cls");
            break;
        case 4:
            std::cout << "Thanks for playing!\n\nYou left the casino with " << wallet.balance << " Gil in your pocket.\n";
            showMenu = false;
            system("pause");
            break;
        }
    }
}

void OddEvenGame(GameStats& oddEvenStats, Wallet& wallet, WinLossHistory& history)
{
    if (oddEvenStats.banned)
    {
        std::cout << "The guards won't let you in! You could try playing at another table...\n\n";
        system("pause");
        system("cls");
        return;
    }

    if (!OddEvenGameIntro(oddEvenStats))
    {
        return;
    }

    do
    {
        OddEvenGameLogic(OddEvenConfig::diceMinRoll, OddEvenConfig::diceMaxRoll, oddEvenStats, wallet, history);

        if (oddEvenStats.CashFlowCount > OddEvenConfig::winLimit)
        {
            std::cout << "Uh-oh, you've caught the attention of the pit boss... The guards \"kindly\" escort you out out of the room\n\n";
            system("pause");
            system("cls");
            oddEvenStats.banned = true;
            return;
        }

        if (wallet.balance <= CasinoConfig::gameOverCriteria)
        {
            GameOver();
            return;
        }

    } while (PlayAgain());

    return;
}
bool OddEvenGameIntro(GameStats& oddEvenStats)
{
    if (oddEvenStats.CashFlowCount > OddEvenConfig::winnerMsgThreshhold)
    {
        std::cout << "You again? Bah...Welcome...\n";
    }
    else if (oddEvenStats.CashFlowCount < OddEvenConfig::loserMsgThreshhold)
    {
        std::cout << "Back for more? Never know when you'll strike it big hehe..\n";
    }
    else
    {
        std::cout << "Welcome to Odd or Even!\n";
    }
    int menuChoice{};

    while (menuChoice < 1 || menuChoice > 3)
    {
        std::cout << "Do you need a tutorial on how to play?\n1: Yes\n2: No\n3: Go Back\n";
        std::cin >> menuChoice;
        std::cin.clear();
        std::cin.ignore(CasinoConfig::inputBufferSize, '\n');
        system("cls");
    }

    switch (menuChoice)
    {
    case 1:
    {
        system("cls");
        std::cout << "Very well!\n"
            << "Once the bets are placed I'm going to roll two six-sided dice and"
            << " you'll have to guess whether BOTH of the dice will roll odd or even numbers.\n"
            << "Guess correctly and you win! "
            << "However...if the dice happen to roll both an even AND an odd number... the house wins regardless of your choice!\n"
            << "It's easier than you think, give it a try!\n\nThis game has a payout of 3:1.\n\n";
        if (!PostTutorialPrompt())
        {
            return false;
        }
        return true;
    }
    case 2:
    {
        system("cls");
        std::cout << "Very well! Please, place your bet to commence the game.\n\n";
        return true;
    }
    case 3:
    {
        return false;
    }
    }
    return true;
}
void OddEvenGamePrintResult(int aRoll, int aRoll2, int anInputFromUser)
{
    bool chosenEven = true;

    if (anInputFromUser == 1)
    {
        chosenEven = false;
    }

    if (chosenEven)
    {
        std::cout << "You bet on the dice rolling even!\n";
    }
    else if (!chosenEven)
    {
        std::cout << "You bet on the dice rolling odd!\n";
    }
    std::cout << "\nThe dice rolled...\n" << aRoll << ".." << '\n' << aRoll2 << ".." << "\n\n";
}
void OddEvenGameLogic(int aMinRoll, int aMaxRoll, GameStats& oddEvenStats, Wallet& wallet, WinLossHistory& history)
{
    int amountBet{ BetCheckpoint(wallet.balance) };
    char result{};
    int betChoice{};

    while (true)
    {
        std::cout << "\nWhat will you be betting on?\n1: Odd Dice\n2: Even Dice\n";
        std::cin >> betChoice;
        if (std::cin.fail() || betChoice < 1 || betChoice > 2)
        {
            std::cin.clear();
            std::cin.ignore(CasinoConfig::inputBufferSize, '\n');
            system("cls");
            std::cout << "That's not a valid choice.\n";
            continue;
        }

        const int rollMin{ aMinRoll }, rollMax{ aMaxRoll };
        const int roll1{ DiceRoll(rollMin,rollMax) };
        const int roll2{ DiceRoll(rollMin,rollMax) };
        const bool roll1IsEven = (roll1 % 2 == 0);
        const bool roll2IsEven = (roll2 % 2 == 0);
        const bool roll1IsOdd = !roll1IsEven;
        const bool roll2IsOdd = !roll2IsEven;

        if (betChoice == 1 && roll1IsOdd && roll2IsOdd)
        {
            system("cls");
            OddEvenGamePrintResult(roll1, roll2, betChoice);
            std::cout << "Conratulations! You won " << amountBet * OddEvenConfig::payoutRatio + amountBet << " Gil!\n\n";
            wallet.balance += amountBet * OddEvenConfig::payoutRatio;
            oddEvenStats.CashFlowCount += amountBet * OddEvenConfig::payoutRatio;
            result = 'W';
        }
        else if ((betChoice == 1 && roll1IsEven && roll2IsEven) || (betChoice == 2 && roll1IsOdd && roll2IsOdd))
        {
            system("cls");
            OddEvenGamePrintResult(roll1, roll2, betChoice);
            std::cout << "You lost!\n\n";
            wallet.balance -= amountBet;
            oddEvenStats.CashFlowCount -= amountBet;
            result = 'L';
        }
        else if (betChoice == 2 && roll1IsEven && roll2IsEven)
        {
            system("cls");
            OddEvenGamePrintResult(roll1, roll2, betChoice);
            std::cout << "Conratulations! You won " << amountBet * OddEvenConfig::payoutRatio + amountBet << " Gil!\n\n";
            wallet.balance += amountBet * OddEvenConfig::payoutRatio;
            oddEvenStats.CashFlowCount += amountBet * OddEvenConfig::payoutRatio;
            result = 'W';
        }
        else
        {
            system("cls");
            OddEvenGamePrintResult(roll1, roll2, betChoice);
            std::cout << "Both odd and even! You lost!\n";
            wallet.balance -= amountBet;
            oddEvenStats.CashFlowCount -= amountBet;
            result = 'L';
        }

        std::cout << "Current balance is: " << wallet.balance << " Gil\n\n";
        history.SaveResult(result);
        history.ShowResults();
        break;
    }
}

void DiceGuessGame(GameStats& diceGameStats, Wallet& wallet, WinLossHistory& history)
{
    if (diceGameStats.banned)
    {
        std::cout << "The guards won't let you in! You could try playing at another table...\n\n";
        system("pause");
        system("cls");
        return;
    }

    if (!DiceGuessIntro(diceGameStats))
    {
        return;
    }

    do
    {
        DiceGuessGameLogic(DiceGuessConfig::diceMinRoll, DiceGuessConfig::diceMaxRoll, DiceGuessConfig::amtOfDice, diceGameStats, wallet, history);

        if (diceGameStats.CashFlowCount > DiceGuessConfig::winLimit)
        {
            std::cout << "Uh-oh, you've caught the attention of the pit boss... The guards \"kindly\" escort you out out of the room\n\n";
            system("pause");
            system("cls");
            diceGameStats.banned = true;
            return;
        }

        if (wallet.balance <= CasinoConfig::gameOverCriteria)
        {
            GameOver();
            return;
        }

    } while (PlayAgain());

    return;
}
bool DiceGuessIntro(GameStats& diceGameStats)
{
    if (diceGameStats.CashFlowCount > DiceGuessConfig::winnerMsgThreshHold)
    {
        std::cout << "Great, my \"favorite\" guest has arrived.\n";
    }
    else if (diceGameStats.CashFlowCount < DiceGuessConfig::loserMsgThreshHold)
    {
        std::cout << "Good luck pal, seems like ya need it!\n";
    }
    else
    {
        std::cout << "Welcome to Guess the Number!\n";
    }

    bool showTutorial{ true };
    int choice{};
    while (showTutorial)
    {
        std::cout << "Do you need a tutorial on how to play?\n1: Yes\n2: No\n3: Go Back\n";
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(CasinoConfig::inputBufferSize, '\n');
        system("cls");

        switch (choice)
        {
        case 1:
        {
            system("cls");
            std::cout << "The rules are simple!\n"
                << "Once you've placed your bet I'm going to roll two six-sided dice, and if you guess their "
                << "combined total.....you win!\nSimple really, why don't you give it a try!\n\nThis game has a payout of 10:1.\n\n";
            if (!PostTutorialPrompt())
            {
                return false;
            }
            return true;
        }
        case 2:
        {
            system("cls");
            std::cout << "Very well! Please, place your bet to commence the game.\n\n";
            showTutorial = false;
            return true;
        }
        case 3:
        {
            return false;
        }
        }
    }
    return true;
}
void DiceGuessPrintResult(int userInput, int roll1, int roll2, int rollTotal) {
    std::cout << "You entered ..." << userInput << "!\n\n"
        << "And the dice rolled...\n" << roll1 << "..\n" << roll2 << "..\n" << "for a total of " << rollTotal << "!\n\n";
}
void DiceGuessGameLogic(int aMinRoll, int aMaxRoll, int anAmountOfDice, GameStats& diceGameStats, Wallet& wallet, WinLossHistory& history)
{
    int amountBet{ BetCheckpoint(wallet.balance) };
    char result{};

    while (true)
    {
        std::cout << "\nEnter a number between " << aMinRoll * anAmountOfDice << " and " << aMaxRoll * anAmountOfDice << ": ";
        int userInput{};
        std::cin >> userInput;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(CasinoConfig::inputBufferSize, '\n');
            system("cls");
            std::cout << "That doesn't look like a number to me.......\n";
            continue;
        }

        system("cls");
        const int roll1{ DiceRoll(aMinRoll,aMaxRoll) };
        const int roll2{ DiceRoll(aMinRoll,aMaxRoll) };
        const int rollTotal{ roll1 + roll2 };


        if (userInput > aMaxRoll * anAmountOfDice || userInput < aMinRoll * anAmountOfDice)
        {
            std::cout << "Hey... It has to be a number between " << aMinRoll * anAmountOfDice << " and " << aMaxRoll * anAmountOfDice
                << "... Give it another try!\n";
            continue;
        }

        if (rollTotal == userInput)
        {
            DiceGuessPrintResult(userInput, roll1, roll2, rollTotal);
            std::cout << "Conratulations! You won " << amountBet * DiceGuessConfig::payoutRatio + amountBet << " Gil!\n\n";

            wallet.balance += amountBet * DiceGuessConfig::payoutRatio;
            diceGameStats.CashFlowCount += amountBet * DiceGuessConfig::payoutRatio;

            std::cout << "Current balance is: " << wallet.balance << " Gil\n\n";
            result = 'W';
            history.SaveResult(result);
            history.ShowResults();
        }
        else
        {
            DiceGuessPrintResult(userInput, roll1, roll2, rollTotal);
            std::cout << "You lost " << amountBet << " Gil...";
            std::cout << "Better luck next time!\n\n";

            wallet.balance -= amountBet;
            diceGameStats.CashFlowCount -= amountBet;

            std::cout << "Current balance is: " << wallet.balance << " Gil\n\n";
            result = 'L';
            history.SaveResult(result);
            history.ShowResults();
        }
        break;
    }
}

int BetCheckpoint(int aBalance)
{
    int wager{};

    while (wager < CasinoConfig::minimumBetAmount || wager > aBalance)
    {
        std::cout << "Current balance: " << aBalance << '\n'
            << "Enter wager: ";
        std::cin >> wager;
        std::cin.clear();
        std::cin.ignore(CasinoConfig::inputBufferSize, '\n');

        if (wager < CasinoConfig::minimumBetAmount)
        {
            system("cls");
            std::cout << "You have to bet at least " << CasinoConfig::minimumBetAmount << " Gil, it's no fun otherwise!\n";
        }
        else if (wager > aBalance)
        {
            system("cls");
            std::cout << "Don't think you've got enough cash for that!\n";
        }
    }

    if (wager == aBalance)
    {
        system("cls");
        std::cout << "Ohoh, feeling lucky today aren't we!\n";
    }
    return wager;
}

bool PlayAgain()
{
    while (true)
    {
        char choice{};
        std::cout << "\nPlay again? Enter y/n: \n";
        std::cin >> choice;
        system("cls");
        std::cin.clear();
        std::cin.ignore(CasinoConfig::inputBufferSize, '\n');

        switch (choice)
        {
        case 'y':
        {
            return true;
        }
        case 'Y':
        {
            return true;
        }
        case 'n':
        {
            return false;
        }
        case 'N':
        {
            return false;
        }
        }
    }
}
bool PostTutorialPrompt()
{
    int choice{};
    while (choice < 1 || choice > 2)
    {
        std::cout << "Play the game?\n1: Yes\n2: No\n";
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(CasinoConfig::inputBufferSize, '\n');
        system("cls");
    }

    switch (choice)
    {
    case 1:
    {
        return true;
    }
    case 2:
    {
        return false;
    }
    }
    return true;
}
void GameOver()
{
    system("pause");
    std::cout << "\nYou're all out of gil? Get out of here chump!\n\n...the guards kicked you out of the casino.\n\nGAME OVER\n";
    system("pause");
}



int DiceRoll(int aLowestSide, int aHighestSide)
{
    std::random_device rng;
    std::mt19937 el(rng());
    std::uniform_int_distribution<int> uniform_dist(aLowestSide, aHighestSide);
    const int roll{ uniform_dist(el) };
    return roll;
}

