#pragma once


#define NUM_STARTING_CARDS 4
#define MAX_NAME_LENGTH 20
#define NOTCLOCKWISE -1
#define STOP_CARD 10
#define PLUS_CARD 11
#define DIRECTION_CHANGE_CARD 12
#define COLOR_CARD 13
#define TAKI_CARD 14
#define SELECTED_COLOR_CARD 15
#define YELLOW 1
#define NO 0
#define RED 2
#define BLUE 3
#define GREEN 4
#define NO_COLOR 5
#define NO_COLOR_LETTER 'X'
#define MAX_NUM_CARD 9
#define NUM_OF_CARDS 14
#define NUM_OF_COLORS 4
#define NO_WINNER 0
#define CLOCKWISE 1
#define YES 1
#define WINNER_FOUND 1
#define DRAW_ACTION 0

typedef struct CARD {
	int num;
	char color;
}CARD;

typedef struct PLAYER {
	CARD* playerCards;
	int PhysicalSize;
	int LogicalSize;
	char  firstName[MAX_NAME_LENGTH];
}PLAYER;

typedef struct cardsFrequency {
	int typeOfCard;
	int freq;
}CardsFrequency;

void checkAllocation(void* arr);
CARD* resizeCardsArray(CARD* cardsArr, int* size);
PLAYER* getPlayers(int numOfPlayers);
CARD deckCard(CardsFrequency* freqArr);
char convertNumToColor(int number);
void gameSetup(PLAYER* playersArr, int numOfPlayers, CARD* upperCard, CardsFrequency* freqArr);
void printCard(CARD* center_card);
void gameLoop(PLAYER* playersArr, int numOfPlayers, CARD* upperCard, CardsFrequency* freqArr);
void printPlayerCards(PLAYER* player);
void removePlayerCard(CARD* cardsArr, CARD* card, int* size);
int isValidCard(CARD* upperCard, CARD* card);
void replaceUpperCard(CARD* upper_card, CARD* selected_card);
void takiLoop(CARD* cardsArr, int* size, CARD* upperCard, int* askForAction, int* gameDirection, int* currPlayer, PLAYER* playersArr, int numOfPlayers, CardsFrequency freqArr[]);
void mergeSort(CardsFrequency arr[], int size);
void merge(CardsFrequency a1[], int n1, CardsFrequency a2[], int n2, CardsFrequency res[]);
void copyingArray(CardsFrequency dest[], CardsFrequency src[], int size);
void gameStatistics(CardsFrequency* freqArr);
void freeAllocation(PLAYER* playersArr, int numOfPlayers);
void initFreqArr(CardsFrequency* freqArr);







