#include "Taki-Game.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h> 
#include <stdio.h>
#include <time.h>
#include <string.h>


void main() {

	PLAYER* playersArr;
	int numOfPlayers;
	CARD current_center_card;
	CardsFrequency gameStat[NUM_OF_CARDS];

	initFreqArr(gameStat);
	srand(time(NULL));

	printf("************  Welcome to TAKI game !!! ***********\n");
	printf("Please enter the number of players:\n");
	scanf(" %d", &numOfPlayers);

	playersArr = getPlayers(numOfPlayers);


	gameSetup(playersArr, numOfPlayers, &current_center_card, gameStat);

	gameLoop(playersArr, numOfPlayers, &current_center_card, gameStat); // Main function that runs the game

	mergeSort(gameStat, NUM_OF_CARDS); // Sorts the frequency array in ascending order       
	gameStatistics(gameStat); // Prints game stats          

	freeAllocation(playersArr, numOfPlayers); // Frees memory allocation           
	free(playersArr);
}