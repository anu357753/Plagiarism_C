/* Functions for main file */


/* Takes in a file name, opens the file 
     and if the first call to fgetc is EOF, it returns true as an indication of empty file*/
bool empty_file(char file_name[])
{
	FILE *fptr;

	fptr = fopen(file_name,"r");
	char ch = fgetc(fptr);
	if (ch == EOF)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* --------------------------------------------------- */

/* Functions for bow.h file */

/* Definition of a structure that has a word and frequency as its attributes.
    The structure is used to store each words that occurs and the number of times the word occurs in the file*/
struct Freq_count
{
	char word[15];
	int freq;
};


/* Function get_word_array takes a file pointer and a double pointer character array as input.
   The function stores words from a file into the character array filtering invalid characters.

   The function returns 0 if there are no valid characters in the file and 1 if the file contains one or more valid characters */

int get_word_array(FILE *fptr, char** arr)
{
	char ch, word[50];
	int flag = 0;

	fseek(fptr,0,SEEK_SET); // sets the file pointer to zero
	ch = fgetc(fptr);
	int j = 0;
	

	while (ch != EOF)
	{
		
		int i = 0;
		while((ch != ' ') && (ch != EOF) && (ch != '\n') )
		{
			if (isalnum(ch) || (ch == '_')) // takes in only valid characters
			{
				word[i] = ch;
				i++;
				flag = 1;
			}
			
			ch = fgetc(fptr);
			
		}

		ch = fgetc(fptr);
		word[i] = '\0';
		arr[j] = strdup(word); // stores the word into an array
		
		j++;
		
		
	}
	arr[j] = "\0";

	
	return flag;
}


/* Function get_mem takes a file pointer as input, counts the number of spaces in the file 
     and returns the count. */
int get_mem(FILE *fptr)
{
	char ch;
	int i = 0;
	ch = fgetc(fptr);
	while (ch != EOF)
	{
		
		if (ch == ' ')
		{
			i++;
		}
		ch = fgetc(fptr);
	}
	
	return (i);

}



/* Function get_freq takes in the length of an array, a double pointer character array and a struct Freq_count array as input
     the function checks for the frequency of each word present in the array and stores it in as an element of type Freq_count.
     This element is appended to the struct Freq_count*/
void get_freq(int count, char** arr, struct Freq_count file[])
{
	int c = 0;
	int p = 0;
	
	for (int k=0; k <= count; k++)
	{
		c =1;
		if (strcmp(arr[k],"\0") != 0) // if the element of the array is NULL, it is not checked for comparision
		{
			for(int m=0; m <= count; m++)
			{
				
				if ((strcmp(arr[k],arr[m]) == 0) && k!=m) //compares if the two strings are equal, if yes then increases the count
				{
					
					c+=1;
					strcpy(arr[m],"\0");
					
					
				}
				
			}

			strcpy(file[p].word,arr[k]); // stores the word in structure attribute word
			file[p].freq = c; // stores the frequency in structure attribute frequency
			p++;
		}	


	}

	strcpy(file[p].word,"\0");
	file[p].freq = 0;
	
}


/* Function dot_prod takes in two arrays of type struct Freq_count as inputs,
     calculates  and returns the dot product based on the common words in both the arrays*/
int dot_prod(struct Freq_count x[], struct Freq_count y[])
{
	int dotprod = 0;
	
	int a = 0;
	int b = 0;


	while(strcmp(x[a].word,"\0") != 0)
	{
		b = 0;
		while(strcmp(y[b].word,"\0") != 0)
		{
			
			if (strcmp(x[a].word,y[b].word) == 0)
			{
				dotprod+=(x[a].freq * y[b].freq);
				
			}
			b++;
		}
		a++;
	}

	return dotprod;
}


/* Function calc_freq takes in an array of type struct Freq_count as input,
     calucates and returns the Euclidean Norm for the frequency values present in the structure*/
float calc_freq(struct  Freq_count file[])
{
	float squares = 0;

	int a = 0;
	while(strcmp(file[a].word,"\0") != 0)
	{
		
		squares += pow(file[a].freq,2);
		a++;
	}

	squares = pow(squares,0.5);

	return squares;

}







