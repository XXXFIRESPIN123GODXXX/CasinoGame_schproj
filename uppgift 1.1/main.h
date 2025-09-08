#pragma once

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
void SaveResult(char aRoundResult);
void ShowResults();