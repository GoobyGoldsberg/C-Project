#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#define DICT_SIZE 5757
#define WORD_SIZE 5


// IMPORTANT!!:  Please dont enter words that have more than 5 letters, otherwise the program will bug out
// I couldnt fix it in time and I don't understand why it bugs out in the first place


//=====================================================================================================================

// SORTING CODE

// Additional function used to compare strings used to compare words which is used as a parameter
// for the Qsort function which is built in to a stdlib.h library

int compareStrings(const char *stringA, const char *stringB) {
    while (*stringA) // Loop until '/0' is found
    {
        // if characters differ, or end of the second string is reached, break the loop
        if (*stringA != *stringB) {
            break;
        }
        // else
        // move to the next pair of characters
        stringA++;
        stringB++;
    }
 
    // we convert the strings to unsigned chars, then return the difference between them
    return *(const unsigned char*)stringA - *(const unsigned char*)stringB;
}

// This function exists for the qsort function to work
// The qsort function uses this function to compare two strings, while this function uses the above function to
// compare the strings, this is because qsort function 4th parameter requires "const void*" in its 4th parameter function

int compare(const void* wordA, const void* wordB) {
    const char* pWordA = (const char*)wordA;
    const char* pWordB = (const char*)wordB;
    return compareStrings(pWordA, pWordB);
}

// This function takes in the unsorted array that we get from the file using load_word_list and sorts it using quick sort algorithm
void sort_word_list(char dictionary[DICT_SIZE][WORD_SIZE+1]) {

    qsort(dictionary, DICT_SIZE, WORD_SIZE+1, compare);

}




// UTILS.C CODE

void load_word_list(char dictionary[DICT_SIZE][WORD_SIZE+1]){
    
    char *file_name = "./word_list.txt";
	
	FILE* f = fopen(file_name, "r");
	int idx = 0;

	if (f == NULL){
		printf("%s does not exist. Please ensure you have downloaded it from Canvas.", file_name);
	}
	else{
		while(fscanf(f, "%s", dictionary[idx++]) != EOF);
	}

	
}


//=======================================================================================================================




// VALIDATION CODE I.e checking if the entered word exists in the word_list


// The index numbers below were calculated using a piece of code that is now commented
// at the very bottom of this file for proof reasons, and also using windows calculator so it is not a 1 to 1
// exact result that I used, it only helped me get get the right answers


// This function is used to find the index of a word starting with a given letter of the alphabet
// It does so using a switch case of all the letters of the english alphabet and comparing it to the first letter of the word
// Then it returns the index

int find_starting_index(char word[6]) {
    int index = 0;
    switch (word[0]) {
            case 'a':
                index = 0;
                break; // Last A word is at index 295

            case 'b':
                index = 296;
                break; // Last B word is at index 727

            case 'c':
                index = 728;
                break; // Last C word is at index 1168

            case 'd':
                index = 1169;
                break; // Last D word is at index 1479

            case 'e':
                index = 1480;
                break; // Last E word is at index 1608
            
            case 'f':
                index = 1609;
                break; // Last F word is at index 1926
            
            case 'g':
                index = 1927;
                break; // Last G word is at index 2205
            
            case 'h':
                index = 2206;
                break; // Last H word is at index 2444

            case 'i':
                index = 2445;
                break; // Last I word is at index 2518

            case 'j':
                index = 2519;
                break; // Last J word is at index 2591

            case 'k':
                index = 2592;
                break; // Last K word is at index 2682

            case 'l':
                index = 2683;
                break; // Last L word is at index 2953

            case 'm':
                index = 2954;
                break; // Last M word is at index 3251

            case 'n':
                index = 3252;
                break; // Last N word is at index 3369

            case 'o':
                index = 3370;
                break; // Last O word is at index 3477

            case 'p':
                index = 3478;
                break; // Last P word is at index 3863

            case 'q':
                index = 3864;
                break; // Last Q word is at index 3902

            case 'r':
                index = 3903;
                break; // Last R word is at index 4170

            case 's':
                index = 4171;
                break; // Last S word is at index 4894

            case 't':
                index = 4895;
                break; // Last T word is at index 5270

            case 'u':
                index = 5271;
                break; // Last U word is at index 5345

            case 'v':
                index = 5346;
                break; // Last V word is at index 5454

            case 'w':
                index = 5455;
                break; // Last W word is at index 5682

            case 'x':
                index = 5683;
                break; // Last X word is at index 5686

            case 'y':
                index = 5687;
                break; // Last Y word is at index 5733

            case 'z':
                index = 5734;
                break; // Last Z word is at index 5757

        }

    return index;
}


// This function takes in the user's word from the main function and checks if such word exists in the array of words


// It does so efficiently by starting the search from the index, i.e If the user word starts with the letter 'K',
// the code starts its search FROM the letter K and if it does not find a match, it ends as fast as the next letter words starting with L begin
// It does not waste time by starting its search from the beginning and ending it at the end of the list.
// The sorting function was created for this function to use

int is_valid(char word[WORD_SIZE+1], char dictionary[DICT_SIZE][WORD_SIZE+1]) {
    int is_valid = 1;
    // 1 means no match has been found
    // 0 if the strings are equal

    int index = find_starting_index(word);

    while (dictionary[index][0] == word[0]) {
        // Using the compare function made in sorter.c to compare the strings
        if (compare(dictionary[index], word) == 0) {
            is_valid = 0;
            break;
        }
        index++;
    }

    return is_valid;
} 



//=================================================================================================================


// MAIN CODE




// Note: correct_word is the word that the program chooses from the list and the user has to guess it
// 		 guessed_word is the word that the user entered, it is their guess
//		 hidden_word is the "-----" output that changes whenever the user guesses a letter correctly
//		 words is the dictionary, the main array of all the words
// 		 word_picker is the random integer from rand that is used to get the correct_word for the game session
int main() {
	int cWordIter;
	int gWordIter;
	int hWordIter;
	// ^ These iters are iterators for the logic code, I used them instead of "i, j, k" in the For loops for better readability
	int bankIter;
	int round = 1;
	int hasDuplicates = 0;
	int lives = 6+1;
	int wrongInput = 0;


	char* correct_word = malloc(6*sizeof(char));
	char hidden_word[WORD_SIZE+1] = "-----";
	char* guessed_word = malloc(6*sizeof(char));
	char bank[WORD_SIZE+1] = {' ', ' ', ' ', ' ', ' '};
	char words[DICT_SIZE][WORD_SIZE+1];
	load_word_list(words);
	sort_word_list(words);

	srand(time(NULL));
	int word_picker = rand() % DICT_SIZE + 1;

	correct_word = words[word_picker];

	

	printf("\nWelcome to the Guessing Game!\n");
	printf("=================================\n");

	do {
		printf("\n===========ROUND %d===============\n\n", round);

		// Get the user input by using a while loop
		printf("Please enter your guess: \n");
		int input;
		int count = 0;
		input = getchar();
		while(input != EOF && count < WORD_SIZE) {
			guessed_word[count++] = input;
			input = getchar();
		}

		
		// Converting all letters in the entered word into lowercase
		for (int i=0; i < WORD_SIZE; i++) {
			guessed_word[i] = tolower(guessed_word[i]);
			
		}

		// Checking if the entered word exists in the word list
		if (is_valid(guessed_word, words) != 0) {
			printf("\nThis word is not in the list of words, Try again");
			continue;
		}


		// Main logic among: correct_word, guessed_word, hidden_word and bank
		
		// for clarity:
		// cWordIter = Iterator for the correct_word
		// gWordIter = Iterator for the guessed_word
	
		for (cWordIter = 0; cWordIter < WORD_SIZE; cWordIter++) {
			for (gWordIter = 0; gWordIter < WORD_SIZE; gWordIter++) {

				if (guessed_word[gWordIter] == correct_word[gWordIter]) {
					hidden_word[gWordIter] = guessed_word[gWordIter];

					
				} else if (guessed_word[gWordIter] == correct_word[cWordIter]) {
					
					for (bankIter = 0; bankIter < WORD_SIZE; bankIter++) {
						if (bank[bankIter] == guessed_word[gWordIter]) {
							hasDuplicates = 1;
						}
					}

					if (hasDuplicates == 0) {
						bank[gWordIter] = guessed_word[gWordIter];
					}

					hasDuplicates = 0;
				}
				
			}
		}
		
		// The output section of the game
		printf("\nYour guess was: ");
		puts(guessed_word);

		if (compareStrings(guessed_word, correct_word) == 0) {
			printf("\nCongratulations! You guessed the word and won the game!");
			break;
		}

		printf("\nCurrent word is: ");
		puts(hidden_word);

		printf("\nCorrectly guessed letters: ");
		for (bankIter = 0; bankIter < WORD_SIZE; bankIter++) {
			printf("%c ", bank[bankIter]);
		}

		lives--;
		printf("\nRemaining lives: %d", lives);

		round++;

		if (lives == 0) {
			printf("\nLooks like you ran out of lives! You lose!");
		}

		free(guessed_word); // Free the guess for the next round

	} while (lives > 0);

	printf("\n======GAME OVER======");
	printf("\nThe correct word was: ");
	puts(correct_word);

	printf("\n\n  Play again?");
	printf("\n(Yes)    (NO)");

	free(correct_word);
	free(guessed_word);


	return 0;
	
}










// // DEAD CODE for PROOF ONLY
// The code below was used to count all the words starting with A,B,C etc.
// I used that data to calculate the starting index of each letter to know when A words end, and B words start
// Which I then used to help me in the validation part.


// void counterOfEachLetterWord(char dictionary[DICT_SIZE][WORD_SIZE+1]) {
//     int a=0, b=0, c=0, d=0, e=0, f=0, g=0, h=0, i=0, j=0,
//     k=0, l=0, m=0, n=0, o=0, p=0, q=0, r=0, s=0, t=0, u=0, v=0, w=0, x=0, y=0, z = 0;

//     int count = 0;
//     while (count < DICT_SIZE) {
        
//         switch (dictionary[count][0]) {
//             case 'a':
//                 printf("\n%d", a);
//                 a++; 
//                 break; // Last A word is at index 295

//             case 'b':
//                 printf("\n%d", b);
//                 b++;
//                 break; // Last B word is at index 727

//             case 'c':
//                 printf("\n%d", c);
//                 c++;
//                 break; // Last C word is at index 1168

//             case 'd':
//                 printf("\n%d", d);
//                 d++;
//                 break; // Last D word is at index 1479

//             case 'e':
//                 printf("\n%d", e);
//                 e++;
//                 break; // Last E word is at index 1608
            
//             case 'f':
//                 printf("\n%d", f);
//                 f++;
//                 break; // Last F word is at index 1926
            
//             case 'g':
//                 printf("\n%d", g);
//                 g++;
//                 break; // Last G word is at index 2205
            
//             case 'h':
//                 printf("\n%d", h);
//                 h++;
//                 break; // Last H word is at index 2444

//             case 'i':
//                 printf("\n%d", i);
//                 i++;
//                 break; // Last I word is at index 2518

//             case 'j':
//                 printf("\n%d", j);
//                 j++;
//                 break; // Last J word is at index 2591

//             case 'k':
//                 printf("\n%d", k);
//                 k++;
//                 break; // Last K word is at index 2682

//             case 'l':
//                 printf("\n%d", l);
//                 l++;
//                 break; // Last L word is at index 2953

//             case 'm':
//                 printf("\n%d", m);
//                 m++;
//                 break; // Last M word is at index 3251

//             case 'n':
//                 printf("\n%d", n);
//                 n++;
//                 break; // Last N word is at index 3369

//             case 'o':
//                 printf("\n%d", o);
//                 o++;
//                 break; // Last O word is at index 3477

//             case 'p':
//                 printf("\n%d", p);
//                 p++;
//                 break; // Last P word is at index 3863

//             case 'q':
//                 printf("\n%d", q);
//                 q++;
//                 break; // Last Q word is at index 3902

//             case 'r':
//                 printf("\n%d", r);
//                 r++;
//                 break; // Last R word is at index 4170

//             case 's':
//                 printf("\n%d", s);
//                 s++;
//                 break; // Last S word is at index 4894

//             case 't':
//                 printf("\n%d", t);
//                 t++;
//                 break; // Last T word is at index 5270

//             case 'u':
//                 printf("\n%d", u);
//                 u++;
//                 break; // Last U word is at index 5345

//             case 'v':
//                 printf("\n%d", v);
//                 v++;
//                 break; // Last V word is at index 5454

//             case 'w':
//                 printf("\n%d", w);
//                 w++;
//                 break; // Last W word is at index 5682

//             case 'x':
//                 printf("\n%d", x);
//                 x++;
//                 break; // Last X word is at index 5686

//             case 'y':
//                 printf("\n%d", y);
//                 y++;
//                 break; // Last Y word is at index 5733

//             case 'z':
//                 printf("\n%d", z);
//                 z++;
//                 break; // Last Z word is at index 5757

//         }

//         printf("\n%s, %d", dictionary[count], count);
//         count++;

        
        
// }   
//         printf("\nA: %d", a);
//         printf("\nB: %d", b);
//         printf("\nC: %d", c);
//         printf("\nD: %d", d);
//         printf("\nE: %d", e);
//         printf("\nF: %d", f);
//         printf("\nG: %d", g);
//         printf("\nH: %d", h);
//         printf("\nI: %d", i);
//         printf("\nJ: %d", j);
//         printf("\nK: %d", k);
//         printf("\nL: %d", l);
//         printf("\nM: %d", m);
//         printf("\nN: %d", n);
//         printf("\nO: %d", o);
//         printf("\nP: %d", p);
//         printf("\nQ: %d", q);
//         printf("\nR: %d", r);
//         printf("\nS: %d", s);
//         printf("\nT: %d", t);
//         printf("\nU: %d", u);
//         printf("\nV: %d", v);
//         printf("\nW: %d", w);
//         printf("\nX: %d", x);
//         printf("\nY: %d", y);
//         printf("\nZ: %d", z);
        
//         printf("\n%d", count);

// }