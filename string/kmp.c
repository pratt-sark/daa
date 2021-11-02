//C Program for KMP String Matching Algorithm
//Pratyay Sarkar (BSc. Semester IV)
//Program : 27

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void computeLPSArray(char* pat, int M, int* lps);
void KMPSearch(char* pat, char* txt);

//Execution begins here
int main()
{
	printf("\n\n_________Knuth-Morris-Pratt String Matching Algorihtm__________\n");
	//the substring
	char *s = (char*)(calloc(20,sizeof(char)));
    //the main string
    char *main_string = (char*)(calloc(100,sizeof(char)));

    printf("\nEnter main string:  ");
    gets(main_string);
    printf("\n\nEnter substring to be searched:  ");
    gets(s);

    int len = strlen(s); //length of substring
    int len_main = strlen(main_string); //length of main string

    if (len_main<len)
    {
        printf("\nSubstring to be searched for is longer than the main string.\n");
        exit(1);
    }

	printf("\n\n______________________________________\n\n");
	KMPSearch(s, main_string);
	printf("\n______________________________________\n\n");
	return 0;
}

// Prints occurrences of txt[] in pat[]
void KMPSearch(char* pat, char* txt)
{
	int M = strlen(pat); //length of substring
	int N = strlen(txt); //length of main string

	// create lps[] that will hold the longest prefix suffix
	// values for pattern
	int lps[M];

	// Preprocess the pattern (calculate lps[] array)
	computeLPSArray(pat, M, lps);

	printf("\nARR: ");
	for (int l=0;l<M;l++)
	{
		printf("%d\t",lps[l]);
	}

	int i = 0; // index for txt[]
	int j = 0; // index for pat[]
	while (i < N) 
    {
        //if a character from main string matches the substring
		if (pat[j] == txt[i]) 
        {
			j++;
			i++;
		}

		if (j==M) //if substring is found
        {
			printf("\nFound substring at index %d\n", i-j);
			j = lps[j-1];
		}

		//Implies that a mismatch after j matches
		else if (i < N && pat[j] != txt[i])
        {
			//now, determine from where in substring to start
            //checking matches
			if (j != 0)
				j = lps[j-1];
			else
				i = i+1;
		}
	}
}

//Computes the lps[] for given substring of legnth 'M'
void computeLPSArray(char* pat, int M, int* lps)
{
	//stores length of the previous longest prefix suffix
	int len = 0;

	lps[0] = 0; //lps[0] is always 0

	// the loop calculates lps[i] for i = 1 to M-1
	int i = 1;
	while (i < M) 
    {
		if (pat[i] == pat[len]) 
        {
			len++;
			lps[i] = len;
			i++;
		}
		else //if (pat[i] != pat[len])
		{
			if (len != 0) 
            {
				len = lps[len - 1];
                //we shouldn't increment 'i' here
			}
			else // if (len == 0)
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}