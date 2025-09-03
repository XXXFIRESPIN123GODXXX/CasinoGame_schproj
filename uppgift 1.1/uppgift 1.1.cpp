#include <iostream>
#include <random>

int balance{ 65 };

int DiceRoll(int aLowestSide, int aHighestSide);
int BetCheckpoint(int aBalance);
bool PlayAgain();
void ChosenOddEven(int betChoice);
void OddEvenGameDiceRoll(int rollA, int rollB, int inputFromUser);
void DiceGuessGame(int aMinRoll, int aMaxRoll, int anAmountOfDice, int aBalance);
void OddEvenGame(int aMinRoll, int aMaxRoll, int aBalance);

//wronginput -> inputagain for current round instead of restartíng round and wager
//---maybe use a while switch? between line(145-186). 4 cases for notNumber, notWithinRange, win,lose(win/lose can be case:true/false callign bool function)

int main()
{

    int choice{};

    while (choice < 1 || choice > 3)
    {
        std::cout << "Welcome to the Casino! My name is D6 and I'm your host for the evening.\n\n";
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
        OddEvenGame(1, 6, balance);
        break;
    case 3:
        std::cout << "Goodbye!\n\n";
        system("pause");
        break;
    }

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
        std::cout << "Enter wager: \n";
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
        case 'y': return true;
        case 'n': return false;
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
        std::cout << " even!\n";
    }
    else if (chosenEven == false)
    {
        std::cout << " odd!\n";
    }
}

void OddEvenGameDiceRoll(int rollA, int rollB, int inputFromUser)
{
    std::cout << "You bet on the dice rolling";
    ChosenOddEven(inputFromUser);
    std::cout << "\nThe dice rolled...\n" << rollA << ".." << '\n' << rollB << ".." << "\n\n";
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
            << "Once you've placed your bet I'm going to roll two six-sided dice, and if you guess their "
            << "combined total.....you win!\nSimple really, why don't you give it a try!\n\nThis game has a payout of 1:1.\n\n";
        break;
    case 2:
        system("cls");
        std::cout << "Very well! Please, place your bet to commence the game.\n\n";
        break;
    case 3:
        main();
        return;
    }
    do
    {
        int amountBet{ BetCheckpoint(currentBalance) };
        std::cout << "\nEnter a number between " << aMinRoll * anAmountOfDice << " and " << aMaxRoll * anAmountOfDice << ":""\n\n";
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
            std::cout << "You're all out of gil? Get out of here chump!\n\n...the guards kicked you out of the casino.\n\nGAME OVER\n";
            system("pause");
            return;
        }
    } while (PlayAgain());
    balance = currentBalance;
    main();
}

void OddEvenGame(int aMinRoll, int aMaxRoll, int aBalance)
{
    int menuChoice{};
    int betChoice{};
    int currentBalance{ aBalance };

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
        system("cls");
        std::cout << "Very well!\n"
            << "Once the bets are placed I'm going to roll two six-sided dice and"
            << " you'll have to guess whether BOTH of the dice will roll odd or even numbers.\n"
            << "Guess correctly and you win! "
            << "However...if the dice happen to roll both an even AND an odd number... the house wins regardless of your choice!\n"
            << "It's easier than you think, give it a try!\n\nThis game has a payout of 2:1.\n\n";
        break;
    case 2:
        system("cls");
        std::cout << "Very well! Please, place your bet to commence the game.\n\n";
        break;
    case 3:
        main();
        return;
    }
    do
    {
        int amountBet{ BetCheckpoint(currentBalance) };

        std::cout << "\nWhat will you be betting on?\n1: Odd Dice\n2: Even Dice\n";
        std::cin >> betChoice;


        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            system("cls");
            std::cout << "That's not a valid choice.\n\n";
        }
        else
        {
            int rollMin{ aMinRoll }, rollMax{ aMaxRoll };
            int roll1{ DiceRoll(rollMin,rollMax) };
            int roll2{ DiceRoll(rollMin,rollMax) };

            if (betChoice == 1 && roll1 % 2 != 0 && roll2 % 2 != 0)
            {
                system("cls");
                OddEvenGameDiceRoll(roll1, roll2, betChoice);
                std::cout << "Conratulations!\n\nYou won " << amountBet << " Gil!\n\n";
                currentBalance += amountBet;
                std::cout << "Current balance is: " << currentBalance << " Gil\n";
            }
            else if (betChoice == 1 && roll1 % 2 == 0 && roll2 % 2 == 0)
            {
                system("cls");
                OddEvenGameDiceRoll(roll1, roll2, betChoice);
                std::cout << "You lost!\n\n";
                currentBalance -= amountBet;
                std::cout << "Current balance is: " << currentBalance << " Gil\n";
            }
            else if (betChoice == 2 && roll1 % 2 == 0 && roll2 % 2 == 0)
            {
                system("cls");
                OddEvenGameDiceRoll(roll1, roll2, betChoice);
                std::cout << "Conratulations!\n\nYou won " << amountBet << " Gil!\n\n";
                currentBalance += amountBet;
                std::cout << "Current balance is: " << currentBalance << " Gil\n";
            }
            else if (betChoice == 2 && roll1 % 2 != 0 && roll2 % 2 != 0)
            {
                system("cls");
                OddEvenGameDiceRoll(roll1, roll2, betChoice);
                std::cout << "You lost!\n\n";
                currentBalance -= amountBet;
                std::cout << "Current balance is: " << currentBalance << " Gil\n";
            }
            else
            {
                system("cls");
                OddEvenGameDiceRoll(roll1, roll2, betChoice);
                std::cout << "Neither odd nor even! You lost!\n";
                currentBalance -= amountBet;
                std::cout << "Current balance is: " << currentBalance << " Gil\n";
            }
            if (currentBalance < 1)
            {
                system("cls");
                std::cout << "You're all out of gil? Get out of here chump!\n\n...the guards kicked you out of the casino.\n\nGAME OVER\n";
                system("pause");
                return;
            }
        }

    } while (PlayAgain());
    balance = currentBalance;
    main();
}