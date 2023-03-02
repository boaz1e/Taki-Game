// Boaz, TakiGame

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h> 
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Taki-Game.h"

void initFreqArr(CardsFrequency* freqArr)
// Initializes frequency array to 0
{
	for (int j = 0; j < NUM_OF_CARDS; j++)
	{
		freqArr[j].typeOfCard = j + 1;
		freqArr[j].freq = 0;
	}
}
void checkAllocation(void* arr)
// Checks if memory allocation succeeded. If so, do nothing. Else, exit.
{

	if (!arr) {
		printf("NOT ALLOCATED!\n");
		exit(1);
	}
}
CARD* resizeCardsArray(CARD* cardsArr, int* size)
// Enlarges array's size if needed. If logical size is equal to physical size, then enlarge.
{

	CARD* card;
	int i;

	card = malloc(*size * 2 * sizeof(CARD));
	checkAllocation(card);

	for (i = 0; i < *size; i++)
		card[i] = cardsArr[i];

	free(cardsArr);
	*size = *size * 2;

	return card;
}
PLAYER* getPlayers(int numOfPlayers)
// Allocates memory for players 
{

	PLAYER* playersArr;
	int i;

	playersArr = malloc(numOfPlayers * sizeof(PLAYER));
	checkAllocation(playersArr);

	for (i = 1; i <= numOfPlayers; i++) {
		printf("Please enter the first name of player #%d:\n", i);
		scanf("%s", (playersArr + i - 1)->firstName);

		(playersArr + i - 1)->playerCards = malloc(NUM_STARTING_CARDS * sizeof(CARD));
		checkAllocation((playersArr + i - 1)->playerCards);
		(playersArr + i - 1)->PhysicalSize = NUM_STARTING_CARDS;
		(playersArr + i - 1)->LogicalSize = NUM_STARTING_CARDS;
	}
	printf("\n");
	return playersArr;
}
char convertNumToColor(int number)
// Converting number (int) to color (char)
{
	switch (number)
	{
	case RED:
		return 'R';
	case BLUE:
		return 'B';
	case GREEN:
		return 'G';
	case YELLOW:
		return 'Y';
	case NO_COLOR:
		return  NO_COLOR_LETTER;
	}
}
CARD deckCard(CardsFrequency* freqArr)
// Returns random card from deck
{

	CARD card;
	int numColor;
	card.num = 1 + rand() % NUM_OF_CARDS;
	if (card.num != COLOR_CARD)
		numColor = 1 + rand() % NUM_OF_COLORS;
	else
		numColor = NO_COLOR;

	card.color = convertNumToColor(numColor);
	freqArr[card.num - 1].freq++;

	return card;
}
void gameSetup(PLAYER* playersArr, int numOfPlayers, CARD* upperCard, CardsFrequency* freqArr)
{

	int i, j, upperCardColor;

	for (i = 0; i < numOfPlayers; i++) {
		for (j = 0; j < NUM_STARTING_CARDS; j++) {

			playersArr[i].playerCards[j] = deckCard(freqArr);
		}
	}
	upperCard->num = 1 + rand() % MAX_NUM_CARD;
	upperCardColor = 1 + rand() % NUM_OF_COLORS;
	upperCard->color = convertNumToColor(upperCardColor);
}
void printCard(CARD* card)
// Function that prints the card
{
	switch (card->num) {
	case STOP_CARD:
		printf(
			"*********\n"
			"*       *\n"
			"*  STOP *\n"
			"*   %c   *\n"
			"*       *\n"
			"*********\n", card->color);
		break;
	case PLUS_CARD:
		printf(
			"*********\n"
			"*       *\n"
			"*  PLUS *\n"
			"*   %c   *\n"
			"*       *\n"
			"*********\n", card->color);
		break;
	case DIRECTION_CHANGE_CARD:
		printf(
			"*********\n"
			"*       *\n"
			"*  <->  *\n"
			"*   %c   *\n"
			"*       *\n"
			"*********\n", card->color);
		break;
	case COLOR_CARD:
		printf(
			"*********\n"
			"*       *\n"
			"* COLOR *\n"
			"*       *\n"
			"*       *\n"
			"*********\n");
		break;
	case SELECTED_COLOR_CARD:
		printf(
			"*********\n"
			"*       *\n"
			"* COLOR *\n"
			"*   %c   *\n"
			"*       *\n"
			"*********\n", card->color);
		break;
	case TAKI_CARD:
		printf(
			"*********\n"
			"*       *\n"
			"*  TAKI *\n"
			"*   %c   *\n"
			"*       *\n"
			"*********\n", card->color);
		break;
	default:
		printf(
			"*********\n"
			"*       *\n"
			"*   %d   *\n"
			"*   %c   *\n"
			"*       *\n"
			"*********\n", card->num, card->color);
		break;

	}

}
void merge(CardsFrequency a1[], int n1, CardsFrequency a2[], int n2, CardsFrequency res[])
// Part of the mergeSort function
{
	int first_Ind, ind2, resIndex;
	first_Ind = ind2 = resIndex = 0;

	while ((first_Ind < n1) && (ind2 < n2)) {
		if (a1[first_Ind].freq > a2[ind2].freq) {
			res[resIndex] = a1[first_Ind];
			first_Ind++;
		}
		else {
			res[resIndex] = a2[ind2];
			ind2++;
		}
		resIndex++;
	}
	while (first_Ind < n1) {
		res[resIndex] = a1[first_Ind];
		first_Ind++;
		resIndex++;
	}
	while (ind2 < n2) {
		res[resIndex] = a2[ind2];
		ind2++;
		resIndex++;
	}
}
void gameLoop(PLAYER* playersArr, int numOfPlayers, CARD* upperCard, CardsFrequency* freqArr)
// Main function that runs the game according to the game rules
{

	int currPlayer, action, getAction, winnerFlag = NO_WINNER, gameDirection = CLOCKWISE;

	PLAYER* currPlayerPtr;
	CARD* chooseCard;

	currPlayer = 1;

	while (winnerFlag == NO_WINNER) {

		getAction = YES;
		currPlayerPtr = playersArr + currPlayer - 1;
		printf("Upper card:\n");
		printCard(upperCard);

		printf("\n%s's turn:\n\n", currPlayerPtr->firstName);
		printPlayerCards(currPlayerPtr);
		while (getAction == YES) {
			printf(
				"Please enter 0 if you want to take a card from the deck\n"
				"or 1-%d if you want to put one of your cards in the middle:\n"
				, currPlayerPtr->PhysicalSize);
			scanf("%d", &action);

			if (action == DRAW_ACTION) {

				if (currPlayerPtr->LogicalSize == currPlayerPtr->PhysicalSize)
					currPlayerPtr->playerCards = resizeCardsArray(currPlayerPtr->playerCards, &currPlayerPtr->LogicalSize);
				currPlayerPtr->PhysicalSize++;
				currPlayerPtr->playerCards[currPlayerPtr->PhysicalSize - 1] = deckCard(freqArr);
				getAction = NO;
				break;

			}
			else {
				chooseCard = &currPlayerPtr->playerCards[action - 1];

				if (action > currPlayerPtr->PhysicalSize || action < 0
					|| isValidCard(upperCard, chooseCard) == NO)
				{
					printf("Invalid card! Try again.\n");
					continue;
				}
				switch (chooseCard->num) {
				case COLOR_CARD:

					replaceUpperCard(upperCard, chooseCard);
					removePlayerCard(currPlayerPtr->playerCards, upperCard, &currPlayerPtr->PhysicalSize);
					getAction = NO;
					break;
				case TAKI_CARD:

					replaceUpperCard(upperCard, chooseCard);
					removePlayerCard(currPlayerPtr->playerCards, upperCard, &currPlayerPtr->PhysicalSize);
					takiLoop(currPlayerPtr->playerCards, &currPlayerPtr->PhysicalSize, upperCard
						, &getAction, &gameDirection, &currPlayer, playersArr, numOfPlayers, freqArr);
					break;
				case PLUS_CARD:

					replaceUpperCard(upperCard, chooseCard);
					removePlayerCard(currPlayerPtr->playerCards, upperCard, &currPlayerPtr->PhysicalSize);
					if (currPlayerPtr->PhysicalSize == 0)
					{
						currPlayerPtr->PhysicalSize++;
						currPlayerPtr->playerCards[currPlayerPtr->PhysicalSize - 1] = deckCard(freqArr);
						getAction = NO;
						break;
					}
					currPlayer -= gameDirection;
					getAction = NO;
					break;
				case STOP_CARD:

					replaceUpperCard(upperCard, chooseCard);
					removePlayerCard(currPlayerPtr->playerCards, upperCard, &currPlayerPtr->PhysicalSize);
					if (numOfPlayers == 2 && currPlayerPtr->PhysicalSize == 0) {
						currPlayerPtr->PhysicalSize++;
						currPlayerPtr->playerCards[currPlayerPtr->PhysicalSize - 1] = deckCard(freqArr);
						getAction = NO;
						break;

					}
					currPlayer += gameDirection;
					getAction = NO;
					break;
				case DIRECTION_CHANGE_CARD:
					replaceUpperCard(upperCard, chooseCard);
					removePlayerCard(currPlayerPtr->playerCards, upperCard, &currPlayerPtr->PhysicalSize);
					if (gameDirection == CLOCKWISE)
						gameDirection = NOTCLOCKWISE;
					else
						gameDirection = CLOCKWISE;
					getAction = NO;
					break;
				default:
					replaceUpperCard(upperCard, chooseCard);
					removePlayerCard(currPlayerPtr->playerCards, upperCard, &currPlayerPtr->PhysicalSize);
					getAction = NO;
					break;
				}
				if (currPlayerPtr->PhysicalSize == 0) {
					winnerFlag = WINNER_FOUND;
					printf("\nThe winner is... %s! Congratulations!\n", currPlayerPtr->firstName);
				}
			}
		}
		currPlayer += gameDirection;
		if (currPlayer < 1)
			currPlayer = numOfPlayers;
		if (currPlayer > numOfPlayers)
			currPlayer = 1;
	}
}
void replaceUpperCard(CARD* upperCard, CARD* selectedCard)
// Replaces the upper card with player's card
{

	int colorChoice, validInput = NO;


	if (selectedCard->num == COLOR_CARD) {
		upperCard->num = SELECTED_COLOR_CARD;

		while (validInput == NO) {
			printf(
				"Please enter your color choice:\n"
				"1 - Yellow\n"
				"2 - Red\n"
				"3 - Blue\n"
				"4 - Green\n"
			);
			scanf("%d", &colorChoice);

			if (colorChoice >= 1 && colorChoice <= 4)
				validInput = YES;
			else
				printf("Invalid input. Try again.\n");
		}
		upperCard->color = convertNumToColor(colorChoice);
	}
	else {
		upperCard->num = selectedCard->num;
		upperCard->color = selectedCard->color;
	}
}
void printPlayerCards(PLAYER* player)
// Prints all player's cards
{
	int i;

	for (i = 0; i < player->PhysicalSize; i++) {

		printf("Card #%d:\n", i + 1);
		printCard(&(player->playerCards[i]));
		printf("\n");
	}
}
void removePlayerCard(CARD* cardsArr, CARD* card, int* size)
// Removes player's chosen card
{
	int i, j;

	for (i = 0; i < *size; i++) {
		if ((cardsArr[i].color == card->color && cardsArr[i].num == card->num)
			|| (cardsArr[i].num == COLOR_CARD && card->num == SELECTED_COLOR_CARD)) {
			if (i != *size - 1) {

				cardsArr[i] = cardsArr[*size - 1];
			}

			(*size)--;
			break;
		}
	}
}
void freeAllocation(PLAYER* playersArr, int numOfPlayers)
// Frees memory allocation
{
	int i;

	for (i = 0; i < numOfPlayers; i++) {
		free((playersArr + i)->playerCards);
	}
}
int isValidCard(CARD* upperCard, CARD* card)
// Checks if the chosen card is valid according to taki's rules
{
	if (card->num == COLOR_CARD)
		return YES;
	if (card->color == upperCard->color)
		return YES;
	if (card->num == upperCard->num)
		return YES;
	return NO;
}
void takiLoop(CARD* cardsArr, int* size, CARD* upperCard, int* askForAction, int* gameDirection, int* currPlayer, PLAYER* playersArr, int numOfPlayers, CardsFrequency freqArr[])
// Function for TAKI-CARD 
{
	int selectedCard, putAnotherCard = YES, validInput;
	PLAYER* currPlayerPtr;
	currPlayerPtr = playersArr + *currPlayer - 1;

	while (putAnotherCard == YES) {

		validInput = NO;

		if (*size == 0)
			break;
		printf("Upper card:\n");
		printCard(upperCard);

		printf("\n%s's turn:\n\n", currPlayerPtr->firstName);
		printPlayerCards(currPlayerPtr);

		while (validInput == NO) {

			printf("Please enter 0 if you want to finish your turn\n"
				"or 1-%d if you want to put one of your cards in the middle:\n"
				, *size);
			scanf("%d", &selectedCard);

			if (selectedCard == 0) {
				putAnotherCard = NO;
				break;
			}
			if (selectedCard > *size || selectedCard < 0
				|| isValidCard(upperCard, &cardsArr[selectedCard - 1]) == NO)
			{
				printf("Invalid card! Try again.\n");
				continue;
			}
			validInput = YES;
		}
		if (putAnotherCard == NO)
			break;
		if (cardsArr[selectedCard - 1].color != upperCard->color)
			putAnotherCard = NO;
		replaceUpperCard(upperCard, &cardsArr[selectedCard - 1]);
		removePlayerCard(cardsArr, &cardsArr[selectedCard - 1], size);
	}

	switch (upperCard->num) {

	case PLUS_CARD:

		if (currPlayerPtr->PhysicalSize == 0)
		{
			currPlayerPtr->PhysicalSize++;
			currPlayerPtr->playerCards[currPlayerPtr->PhysicalSize - 1] = deckCard(freqArr);
			*askForAction = NO;
			break;
		}
		currPlayer -= *gameDirection;
		*askForAction = NO;
		break;
	case STOP_CARD:
		if (numOfPlayers == 2 && currPlayerPtr->PhysicalSize == 0) {
			currPlayerPtr->PhysicalSize++;
			currPlayerPtr->playerCards[currPlayerPtr->PhysicalSize - 1] = deckCard(freqArr);
			*askForAction = NO;
			break;
		}

		currPlayer += *gameDirection;
		*askForAction = NO;
		break;
	case DIRECTION_CHANGE_CARD:
		if (*gameDirection == CLOCKWISE)
			*gameDirection = NOTCLOCKWISE;
		else
			*gameDirection = CLOCKWISE;
		*askForAction = NO;
		break;
	default:
		*askForAction = NO;
		break;
	}
}
void mergeSort(CardsFrequency arr[], int size)
// Sorts the frequency array
{
	int* tmpArr = NULL;
	if (size <= 1)
		return;

	mergeSort(arr, size / 2);
	mergeSort(arr + size / 2, size - size / 2);

	tmpArr = (CardsFrequency*)malloc(size * sizeof(CardsFrequency));
	checkAllocation(tmpArr);

	merge(arr, size / 2, arr + size / 2, size - size / 2, tmpArr);
	copyingArray(arr, tmpArr, size);
	free(tmpArr);
}
void copyingArray(CardsFrequency dest[], CardsFrequency src[], int size)
// Part of the mergeSort function
{
	int i;

	for (i = 0; i < size; i++)
		dest[i] = src[i];
}
void gameStatistics(CardsFrequency* freqArr)
// Prints the frequency array when player wins
{
	int i;

	printf("\n\n************ Game Statistics ************\n\n"
		"Card # | Frequency\n"
		"__________________\n");
	for (i = 0; i < NUM_OF_CARDS; i++) {
		if (freqArr[i].typeOfCard <= 9) {
			printf("   %d   |%4d\n", freqArr[i].typeOfCard, freqArr[i].freq);
			continue;
		}
		switch (freqArr[i].typeOfCard) {
		case DIRECTION_CHANGE_CARD:
			printf("  <->  |%4d\n", freqArr[i].freq);
			break;
		case TAKI_CARD:
			printf(" TAKI  |%4d\n", freqArr[i].freq);
			break;
		case PLUS_CARD:
			printf("   +   |%4d\n", freqArr[i].freq);
			break;
		case COLOR_CARD:
			printf(" COLOR |%4d\n", freqArr[i].freq);
			break;
		case STOP_CARD:
			printf(" STOP  |%4d\n", freqArr[i].freq);
			break;
		}
	}
}
