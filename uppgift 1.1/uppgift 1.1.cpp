#include <iostream>
#include <random>

int DiceRoll(int aLowestSide, int aHighestSide);
int BetCheckpoint(int aBalance);
bool PlayAgain();
void DiceGuessGame(int aMinRoll, int aMaxRoll, int anAmountOfDice, int aBalance);

int main()
{
    std::cout << "Welcome to the Casino! My name is D6 and I'm your host for the evening.\n\n";
    int choice{};
    int balance{ 65 };

    while (choice < 1 || choice > 3)
    {
        std::cout << "Current balance: " << balance << " Gil" << "\n\n";
        std::cout << "What would you like to do?\n1: Play Guess The Number\n2: Play Even/Odd\n3: Exit\n";
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        system("cls");
    }

    switch (choice)
    {
    case 1:
        DiceGuessGame(1, 6, 2, balance);
        break;
    case 2:
        std::cout << "Not implemented yet.\n";
        break;
    case 3:
        std::cout << "Goodbye!\n\n";
        system("pause");
        break;
    }
    return 0;
}

//wronginput -> inputagain for current round instead of restartíng round and wager
//---maybe use a while switch?   <---------------------------]
//                                                           I
//if play again NO ---> return to menu                       I
//---could be bool while yes stay in func else end func <----]
//------could add call to main after bool at func end

//return ingame balance to global balance when returning to menu
//---maybe set wager before game(in main) and game returns win 0/1(bool?) if 0/1 wager+-balance

//make "response" own function to reuse in both games: (value entered, win/loss, gold won/lost, current balance)

//add game2



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
        std::cout << "Enter wager: \n";
        std::cin >> wager;
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        if (wager < 1)
        {
            system("cls");
            std::cout << "You have to bet something, no fun otherwise!\n";
        }
        else if (wager > aBalance)
        {
            system("cls");
            std::cout << "You're a little short on cash for that.\n";
        }
    }

    if (wager == aBalance)
    {
        system("cls");
        std::cout << "Well well well, someone's feeling lucky!\n";
    }
    return wager;
}

bool PlayAgain()
{
    while (true)
    {
        char choice{};
        std::cout << "Keep playing? Enter y/n: \n";
        std::cin >> choice;
        system("cls");
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        switch (choice)
        {
        case 'y': return true;
        case 'n': return false;
        }
    }
}

void DiceGuessGame(int aMinRoll, int aMaxRoll, int anAmountOfDice, int aBalance)
{
    int choice{};
    int currentBalance{ aBalance };

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
        system("cls");
        std::cout << "The rules are simple!\n"
            << "First, choose the amount you wish to bet.\nI'm then going to roll two six-sided dice, and if you guess their "
            << "combined total.....you'll win a prize!\nWhy don't you give it a try!\n\n";
        break;
    case 2:
        system("cls");
        std::cout << "Very well.\n\n";
        break;
    case 3:
        main();
        return;
    }
    do
    {
        int amountBet{ BetCheckpoint(currentBalance) };
        std::cout << "Enter a number between " << aMinRoll * anAmountOfDice << " and " << aMaxRoll * anAmountOfDice << ":""\n\n";
        int userInput{};
        std::cin >> userInput;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            system("cls");
            std::cout << "That doesn't look like a number to me.......\n\n";
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
                currentBalance -= amountBet;
                std::cout << "Current balance is: " << currentBalance << " Gil\n";
            }
            else if (rollTotal == userInput)
            {
                std::cout << "You entered ..." << userInput << "!\n\n";
                std::cout << "And the dice rolled...\n" << roll1 << ".." << '\n' << roll2 << ".." << "\nfor a total of " << rollTotal << "!\n\n";
                std::cout << "Conratulations!\n\nYou won " << amountBet << " Gil!\n\n";
                currentBalance += amountBet;
                std::cout << "Current balance is: " << currentBalance << " Gil\n";
            }
            else if (userInput > rollMax * amountOfRolls || userInput < rollMin * amountOfRolls)
            {
                std::cout << "Hey... It has to be a number between " << aMinRoll * anAmountOfDice << " and " << aMaxRoll * anAmountOfDice
                    << "... Give it another try!\n\n";
            }
        }
        if (currentBalance < 1)
        {
            system("cls");
            std::cout << "You're out of gil! Get out of here chump!\n\nGAME OVER\n";
            system("pause");
            return;
        }
    } while (PlayAgain());
}