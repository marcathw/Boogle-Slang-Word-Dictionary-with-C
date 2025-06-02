// Libraries
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Initialize Constant Value
#define ASCII 128

// Declare Struct to Store the Slang Words
struct Node {
	struct Node *child[ASCII];
	int isLastCharacter;
	char description[1000];
};

// Void to Print Menus
void menu() {
	printf("%42.sBOOGLE\n");
	printf("%Welcome to Boogle Program!\n");
	printf("Menu : \n");
	printf("1. Release a new slang word\n");
	printf("2. Search a slang word\n");
	printf("3. View all slang words starting with a certain prefix word\n");
	printf("4. View all slang words\n");
	printf("5. Exit\n");
}

// Function to Check Amount of Words
int checkWord(const char *string) {
	int count = 1, i = 0;
	
	for (i = 0; i < strlen(string); i++) {
		if (string[i] == ' ') {
			count += 1;
		}
	}
	
	return count;
}

// Functions to Insert Node
struct Node *createNode() {
	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
	int i = 0;
	newNode -> isLastCharacter = 0;
	
	for (i = 0; i < ASCII; i++) {
		newNode -> child[i] = NULL;
	}
	
	strcpy(newNode -> description, "");
	return newNode;
}

void insertSlang(struct Node **root, const char *slangWord, const char *slangDesc, int *newWord) {
	*newWord = 0;
	int i = 0;
	
	if (!(*root)) {
		*newWord = 1;
		*root = createNode();
	}
	
	struct Node *temp = *root;
	for (i = 0; i < strlen(slangWord); i++) {
		if (!(temp -> child[slangWord[i]])) {
			*newWord = 1;
			temp -> child[slangWord[i]] = createNode();
		}
		
		temp = temp -> child[slangWord[i]];
	}
	
	temp -> isLastCharacter = 1;
	strcpy(temp -> description, slangDesc);
}

// Function to Search Slang
struct Node *searchSlang(struct Node *root, const char *searchedWord) {
	if (!root) {
		printf("There is no word \"%s\" in the dictionary.\n");
		return root;
	}
	
	struct Node *temp = root;
	int i = 0;
	for (i = 0; i < strlen(searchedWord); i++) {
		if (!(temp -> child[searchedWord[i]])) {
			printf("There is no word \"%s\" in the dictionary.\n", searchedWord);
			return temp;
		}
		
		temp = temp -> child[searchedWord[i]];
	}
	
	if (strcmp(temp -> description, "") == 0) {
		printf("There is no word \"%s\" in the dictionary.\n", searchedWord);
	}
	else {
		printf("Slang word\t: %s\n", searchedWord);
		printf("Description\t: %s\n", temp -> description);
	}
	
	return temp;
}

// Function to Search Prefix
void displayWord(struct Node *root, const char *word, int *index) {
	char newWord[strlen(word) + 2];
	strcpy(newWord, word);
	newWord[strlen(word) + 1] = '\0';
	
	struct Node *temp = root;
	int i = 0;
	for (i = 0; i < strlen(word); i++) {
		temp = temp -> child[word[i]];
	}
	
	if (temp -> isLastCharacter) {
		printf("%d. %s\n", *index, newWord);
		(*index)++;
	}
	
	for (i = 0; i < ASCII; i++) {
		if (temp -> child[i]) {
			newWord[strlen(word)] = i;
			displayWord(root, newWord, index);
		}
	}
}

void searchPref(struct Node *root, const char *searchedPrefix) {
	if (!root) {
		printf("There is no prefix \"%s\" in the dictionary.\n", searchedPrefix);
		return;
	}
	
	struct Node *temp = root;
	int i = 0;
	for (i = 0; i < strlen(searchedPrefix); i++) {
		if (!(temp -> child[searchedPrefix[i]])) {
			printf("There is no prefix \"%s\" in the dictionary.\n", searchedPrefix);
			return;
		}
		
		temp = temp -> child[searchedPrefix[i]];
	}
	
	printf("Words starts with \"%s\" : \n", searchedPrefix);
	int index = 1;
	displayWord(root, searchedPrefix, &index);
	
	return;
}

// Void to Display All Slangs
void displaySlangs(struct Node *root) {
	if (!root) {
		printf("There is no slang word yet in the dictionary.\n");
		return;
	}
	int index = 1;
	printf("List of all slang words in the dictionary : \n");
	displayWord(root, "", &index);
	
	return;
}

int main () {
	// Declare Variables
	int choice = -1;
	struct Node *root = NULL;
	
	do {
		// Print Menu
		menu();
		
		// Scan Choice
		do {
			printf("Choice : ");
			scanf("%d", &choice); getchar();
		} while (!(choice >= 1 && choice <= 5));
		
		switch (choice) {
			// Menu 1 : Release a new slang word
			case 1 : {
				// Variable Declaration
				char inputNewSlang[200] = "";
				char inputNewSlangDesc[1000] = "";
				int newWord = -1;
				
				// Scan New Slang Word
				do {
					printf("Input a new slang word [More than 1 character and contains no space]: ");
					scanf("%[^\n]s", &inputNewSlang); getchar();
				} while (!(strlen(inputNewSlang) > 1 && checkWord(inputNewSlang) == 1));
				
				// Scan New Slang Description
				do {
					printf("Input a new slang word description [More than 2 words] : ");
					scanf("%[^\n]s", &inputNewSlangDesc); getchar();
				} while (!(strlen(inputNewSlang) > 1 && checkWord(inputNewSlangDesc) > 2));
				
				// Insert New Slang Word to Dictionary
				insertSlang(&root, inputNewSlang, inputNewSlangDesc, &newWord);
				
				if (newWord) {
					printf("Successfully released a new slang word.\n");
				}
				else if (newWord == 0) {
					printf("Successfully updated a slang word.\n");
				}
				
				printf("\nPress enter to continue...\n");
				getchar();
				break;
			}
			// Menu 2 : Search a slang word
			case 2 : {
				// Variable Declaration
				char inputSearchSlang[200] = "";
				struct Node *searchSlangFound = NULL;
				
				// Scan to-be-searched Word
				do {
					printf("Input a slang word to be searched [More than 1 character and contains no space] : ");
					scanf("%[^\n]s", &inputSearchSlang); getchar();
				} while (!(strlen(inputSearchSlang) > 1 && checkWord(inputSearchSlang) == 1));
				
				// Perform Search Slang Word
				searchSlangFound = searchSlang(root, inputSearchSlang);
				
				printf("\nPress enter to continue...\n");
				getchar();
				break;
			}
			// Menu 3 : View all slang words starting with a certain prefix word
			case 3 : {
				// Variable Declaration
				char prefixSearch[200] = "";
				
				// Scan to-be-searched Prefix
				printf("Input a prefix to be searched: ");
				scanf("%[^\n]s", &prefixSearch); getchar();
				
				// Perform Search Prefix
				searchPref(root, prefixSearch);
				
				printf("\nPress enter to continue...\n");
				getchar();
				break;
			}
			// Menu 4 : View all slang words
			case 4 : {
				displaySlangs(root);
				
				printf("\nPress enter to continue...\n");
				getchar();	
				break;
			}
			// Menu 5 : Exit Program
			case 5 : {
				printf("Thankyou for using this program. Have a nice day\n");
				
				getchar();
				break;
			}
		}
	} while (choice != 5);
	
	return 0;
}
