//C Program for Naive String Matching Algorithm
//Pratyay Sarkar (BSc. Semester IV)
//Program : 26

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void findPatt(char* patt, char* txt);

//Execution begins here
int main()
{
    printf("\n\n_________Naive String Matching Algorihtm__________\n");
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
	findPatt(s, main_string);
    printf("\n______________________________________\n\n");
	return 0;
}

//Uses Naive String Matching Algorithm to find
//occurences of a substring in a main string
void findPatt(char* patt, char* txt)
{
    int i,j;
    int len = strlen(patt);
    int len_main = strlen(txt);
 
    //Runs from 0 to (len-len_main), because if the (len - len_main)th character
    //doesn't match, there are no chances for the remaining characters matching
    for (i=0; i<=len_main-len; i++) 
    { 
        //For current index 'i', check for matching pattern of characters
        for (j=0; j<len; j++)
            if (txt[i+j] != patt[j])
                break;

        //if the j-loop hasn't encountered 'break', then 
        //the pattern of charaters must have matched
        if (j == len) 
            printf("\nPattern found at index %d\n", i);
    }
}