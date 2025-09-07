#include <iostream>
#include <random>

int globalBalance{ 65 };

int DiceRoll(int aLowestSide, int aHighestSide);
int BetCheckpoint(int aBalance);
bool PlayAgain();
void ChosenOddEven(int betChoice);
void OddEvenGamePrintResult(int rollA, int rollB, int inputFromUser);
void OddEvenGame(int aMinRoll, int aMaxRoll);
void OddEvenGameIntro();
void DiceGuessGame();
void DiceGuessGameLogic(int aMinRoll, int aMaxRoll, int anAmountOfDice);
void DiceGameIntro();
void Lobby();
void PostTutorialPrompt();
void GameOver();


//add game3
// 
//add show playhistory after each round, + add menubutton to show playhistory
// 
//add hidden profit/loss counter for each game
//---if profit or loss over threshhold give out corresponding thematic message
//add kick function if player wins too much (KICKED PER TABLE)
// ___lossthreshhold___normal___winthreshhold___kickthreshhold___

int main()
{
    Lobby();
    return 0;
}

int DiceRoll(int aLowestSide, int aHighestSide)
{
    std::random_device rng;
    std::mt19937 el(rng());
    std::uniform_int_distribution<int> uniform_dist(aLowestSide, aHighestSide);
    int roll{ uniform_dist(el) };
    return roll;
}

int BetCheckpoint(int aBalance)
{
    int wager{};

    while (wager < 1 || wager > aBalance)
    {
        std::cout << "Current balance: " << aBalance << '\n';
        std::cout << "Enter wager: ";
        std::cin >> wager;
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        if (wager < 1)
        {
            system("cls");
            std::cout << "You have to bet something, it's no fun otherwise!\n";
        }
        else if (wager > aBalance)
        {
            system("cls");
            std::cout <<"Don't think you've got enough cash for that!\n";
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
        std::cout << "Play again? Enter y/n: \n";
        std::cin >> choice;
        system("cls");
        std::cin.clear();
        std::cin.ignore(10000, '\n');

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

void ChosenOddEven(int betChoice)
{
    bool chosenEven = true;
    if (betChoice == 1)
    {
        chosenEven = false;
    }

    if (chosenEven == true)
    {
        std::cout << "You bet on the dice rolling even!\n";
    }
    else if (chosenEven == false)
    {
        std::cout << "You bet on the dice rolling odd!\n";
    }
}

void OddEvenGamePrintResult(int rollA, int rollB, int inputFromUser)
{
    ChosenOddEven(inputFromUser);
    std::cout << "\nThe dice rolled...\n" << rollA << ".." << '\n' << rollB << ".." << "\n\n";
}

void OddEvenGame(int aMinRoll, int aMaxRoll)
{
    int betChoice{};
    OddEvenGameIntro();

    

    do
    {
        bool wrongInput{ true };
        int amountBet{ BetCheckpoint(globalBalance) };

        while (wrongInput == true)
        {


            std::cout << "\nWhat will you be betting on?\n1: Odd Dice\n2: Even Dice\n";
            std::cin >> betChoice;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                system("cls");
                std::cout << "That's not a valid choice.\n";
                wrongInput = true;
            }
            else
            {
                int rollMin{ aMinRoll }, rollMax{ aMaxRoll };
                int roll1{ DiceRoll(rollMin,rollMax) };
                int roll2{ DiceRoll(rollMin,rollMax) };

                if (betChoice == 1 && roll1 % 2 != 0 && roll2 % 2 != 0)
                {
                    system("cls");
                    OddEvenGamePrintResult(roll1, roll2, betChoice);
                    std::cout << "Conratulations!\n\nYou won " << amountBet * 3 << " Gil!\n\n";
                    globalBalance += amountBet * 2;
                    std::cout << "Current balance is: " << globalBalance << " Gil\n\n";
                }
                else if (betChoice == 1 && roll1 % 2 == 0 && roll2 % 2 == 0)
                {
                    system("cls");
                    OddEvenGamePrintResult(roll1, roll2, betChoice);
                    std::cout << "You lost!\n\n";
                    globalBalance -= amountBet;
                    std::cout << "Current balance is: " << globalBalance << " Gil\n\n";
                }
                else if (betChoice == 2 && roll1 % 2 == 0 && roll2 % 2 == 0)
                {
                    system("cls");
                    OddEvenGamePrintResult(roll1, roll2, betChoice);
                    std::cout << "Conratulations!\n\nYou won " << amountBet * 3 << " Gil!\n\n";
                    globalBalance += amountBet * 2;
                    std::cout << "Current balance is: " << globalBalance << " Gil\n\n";
                }
                else if (betChoice == 2 && roll1 % 2 != 0 && roll2 % 2 != 0)
                {
                    system("cls");
                    OddEvenGamePrintResult(roll1, roll2, betChoice);
                    std::cout << "You lost!\n\n";
                    globalBalance -= amountBet;
                    std::cout << "Current balance is: " << globalBalance << " Gil\n\n";
                }
                else
                {
                    system("cls");
                    OddEvenGamePrintResult(roll1, roll2, betChoice);
                    std::cout << "Both odd and even! You lost!\n";
                    globalBalance -= amountBet;
                    std::cout << "Current balance is: " << globalBalance << " Gil\n\n";
                }
                wrongInput = false;
            }
        }
        if (globalBalance < 1)
        {
            GameOver();
            return;
        }
    } while (PlayAgain());
    globalBalance = globalBalance;
    main();
}

void DiceGuessGame()
{
    DiceGameIntro();
    do
    {
        {
            DiceGuessGameLogic(1, 6, 2);
        }
        if (globalBalance < 1)
        {
            GameOver();
            return;
        }

    } while (PlayAgain());
    main();
}

void DiceGameIntro()
{
    int choice{};
    while (choice < 1 || choice > 3)
    {
        std::cout << "Welcome to Guess the Number! Do you need a tutorial on how to play?\n1: Yes\n2: No\n3: Go Back\n";
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        system("cls");
    }

    switch (choice)
    {
        case 1:
        {
            system("cls");
            std::cout << "The rules are simple!\n"
                      << "Once you've placed your bet I'm going to roll two six-sided dice, and if you guess their "
                      << "combined total.....you win!\nSimple really, why don't you give it a try!\n\nThis game has a payout of 2:1.\n\n";
            PostTutorialPrompt();
            break;
        }
        case 2:
        {
            system("cls");
            std::cout << "Very well! Please, place your bet to commence the game.\n\n";
            break;
        }
        case 3:
        {
            main();
            return;
        }
    }
}

void Lobby()
{
    int choice{};

    while (choice < 1 || choice > 3)
    {
        std::cout << "Welcome to the Casino! My name is D6 and I'm your host for the evening.\n\n"
                  << "Current balance: " << globalBalance << " Gil" << "\n\n"
                  << "What would you like to do?\n1: Play Guess The Number\n2: Play Even/Odd\n3: Exit\n";
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        system("cls");
    }

    switch (choice)
    {
    case 1:
        DiceGuessGame();
        break;
    case 2:
        OddEvenGame(1, 6);
        break;
    case 3:
        std::cout << "Thanks for playing!\n\nYou left the casino with " << globalBalance << " Gil in your pocket.\n";
        system("pause");
        break;
    }

}

void PostTutorialPrompt()
{
    int choice{};
    while (choice < 1 || choice > 2)
    {
        std::cout << "Play the game?\n1: Yes\n2: No\n";
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        system("cls");
    }

    switch (choice)
    {
        case 1:
        {
            break;
        }
        case 2:
        {
            main();
            return;
        }
    }
}

void DiceGuessGameLogic(int aMinRoll, int aMaxRoll, int anAmountOfDice)
{
    bool wrongInput{ true };
    int amountBet{ BetCheckpoint(globalBalance) };

    while (wrongInput == true)
    {
        std::cout << "\nEnter a number between " << aMinRoll * anAmountOfDice << " and " << aMaxRoll * anAmountOfDice << ": ";
        int userInput{};
        std::cin >> userInput;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            system("cls");
            std::cout << "That doesn't look like a number to me.......\n";
            wrongInput = true;
        }
        else
        {
            system("cls");
            int rollMin{ aMinRoll }, rollMax{ aMaxRoll };
            int amountOfRolls{ anAmountOfDice };
            int roll1{ DiceRoll(rollMin,rollMax) };
            int roll2{ DiceRoll(rollMin,rollMax) };
            int rollTotal{ roll1 + roll2 };

            if (userInput <= rollMax * amountOfRolls && userInput >= rollMin * amountOfRolls && rollTotal != userInput)
            {
                std::cout << "You entered ..." << userInput << "!\n\n";
                std::cout << "And the dice rolled...\n" << roll1 << ".." << '\n' << roll2 << ".." << "\nfor a total of " << rollTotal << "!\n\n";
                std::cout << "You lost " << amountBet << " Gil...\n";
                std::cout << "Better luck next time!\n\n";
                globalBalance -= amountBet;
                std::cout << "Current balance is: " << globalBalance << " Gil\n\n";
                wrongInput = false;
            }
            else if (rollTotal == userInput)
            {
                std::cout << "You entered ..." << userInput << "!\n\n";
                std::cout << "And the dice rolled...\n" << roll1 << ".." << '\n' << roll2 << ".." << "\nfor a total of " << rollTotal << "!\n\n";
                std::cout << "Conratulations!\n\nYou won " << amountBet * 2 << " Gil!\n\n";
                globalBalance += amountBet;
                std::cout << "Current balance is: " << globalBalance << " Gil\n\n";
                wrongInput = false;
            }
            else if (userInput > rollMax * amountOfRolls || userInput < rollMin * amountOfRolls)
            {
                std::cout << "Hey... It has to be a number between " << aMinRoll * anAmountOfDice << " and " << aMaxRoll * anAmountOfDice
                    << "... Give it another try!\n";
                wrongInput = true;
            }
        }
    }

}

void GameOver()
{
    system("pause");
    std::cout << "\nYou're all out of gil? Get out of here chump!\n\n...the guards kicked you out of the casino.\n\nGAME OVER\n";
    system("pause");
}

void OddEvenGameIntro()
{
    int menuChoice{};

    while (menuChoice < 1 || menuChoice > 3)
    {
        std::cout << "Welcome to Odd or Even! Do you need a tutorial on how to play?\n1: Yes\n2: No\n3: Go Back\n";
        std::cin >> menuChoice;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
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
        PostTutorialPrompt();
        break;
    }
    case 2:
    {
        system("cls");
        std::cout << "Very well! Please, place your bet to commence the game.\n\n";
        break;
    }
    case 3:
    {
        main();
        return;
    }
    }
}