#include <iostream>
#include <random>

int DiceRoll(int aLowestSide, int aHighestSide);
bool PlayAgain();
void DiceGuessGame(int aMinRoll, int aMaxRoll, int anAmountOfDice);
   
int main()
{
    std::cout << "Welcome to the Casino! I'm D6 and the name of the game is guess the number!\n\n" 
              << "The rules are simple!\n" 
              << "I'm going to roll two six-sided dice, and if you guess their combined total.....you'll win a prize!\nWhy don't you give it a try!\n\n";

    do
    {
        DiceGuessGame(1, 6, 2);

    } while(PlayAgain());

    std::cout << "Thanks for playing!\n\n";
    system("pause");

    return 0;
}



int DiceRoll(int aLowestSide, int aHighestSide)
{
    std::random_device rng;
    std::mt19937 el(rng());
    std::uniform_int_distribution<int> uniform_dist(aLowestSide, aHighestSide);
    int roll{ uniform_dist(el)};
    return roll;
}

bool PlayAgain()
{
    while (true)
    {
        char choice{};
        
        std::cout << "Keep playing? Enter y/n: \n";
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        switch (choice)
        {
        case 'y': return true;
        case 'n': return false;
        }
    }
}

void DiceGuessGame(int aMinRoll, int aMaxRoll, int anAmountOfDice)
{
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
            std::cout << "Better luck next time!\n\n";
        }
        else if (rollTotal == userInput)
        {
            std::cout << "You entered ..." << userInput << "!\n\n";
            std::cout << "And the dice rolled...\n" << roll1 << ".." << '\n' << roll2 << ".." << "\nfor a total of " << rollTotal << "!\n\n";
            std::cout << "Conratulations!\n\nYou won a...\n...croissant?\n\nYummy!\n\n";
        }
        else if (userInput > rollMax * amountOfRolls || userInput < rollMin * amountOfRolls)
        {
            std::cout << "Hey... It has to be a number between " << aMinRoll * anAmountOfDice << " and " << aMaxRoll * anAmountOfDice << "... Give it another try!\n\n";
        }
    }
    
}