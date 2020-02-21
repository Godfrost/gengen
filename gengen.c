/*
 * Generates strings of characters randomly
 *
 * @author Godefroy Juteau
 * @version 17/02/2020
 */

#include <stdlib.h>
#include <stdio.h>

// Constants
#define FIRST 'A'
#define SECOND '1'
#define SPECIAL '@' 
#define N_FIRST_DEFAULT 2
#define N_SECOND_DEFAULT 3
#define OUTPUT_FILE "./genverif.txt"
#define APPEND "a"
const char separators[] = {'#', '$', '?', '~'};

// Main
int main(int argc, char** argv)
{
	// Initializing random number generator
	time_t t;
	srand(time(&t));
	
	// Variables for sizes
	unsigned char nFirst;
	unsigned char nSecond;
       	
	// Calculating sizes
	if (argc < 3)
	{
		nFirst = N_FIRST_DEFAULT;
		nSecond = N_SECOND_DEFAULT;
	}
	else
	{	
		nFirst = argv[1][1] - '0';
		nSecond = argv[2][1] - '0';
	}
	unsigned char size = (nFirst + nSecond) + 1;
	
	// Declaring array of elements
	char elements[size];

	// Generating elements
	for (unsigned char i = 0; i < size; ++i)
	{
		if (i < nFirst) 
		{
			elements[i] = FIRST + i;
		}
		else if (i < nFirst + nSecond) 
		{
			elements[i] = SECOND + i - nFirst;
		}
		else
		{
			elements[i] = SPECIAL;
		}
	}

	// Shuffling the array of elements
	for (unsigned char i = 0; i < size; i++)
	{
		// Swapping current element with a random one
		unsigned char j = (unsigned char) (rand() % size);

		char tmp = elements[i];
		elements[i] = elements[j];
		elements[j] = tmp;
	}

	// Generated string
	char generated[size * 2];
	// Generating the string
	for (unsigned char i = 0; i < size - 1; ++i)
	{
		unsigned char j = (unsigned char) (rand() % 
			(sizeof(separators) / sizeof(separators[0])));
		
		generated[i * 2] = elements[i];
		generated[i * 2 + 1] = separators[j];
	}
	generated[size * 2 - 2] = elements[size - 1];	
	generated[size * 2 - 1] = '\0';

	// Opening file and saving generated
	FILE* file = fopen(OUTPUT_FILE, APPEND);
	fprintf(file, "%s\n", generated);

	return EXIT_SUCCESS;
}
