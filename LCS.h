
/*Function lcs takes in two file names, length of the directory path and pointer of the log file,
   and prints the percentage of plagiarism for the files.*/

void lcs(char lread1[], char lread2[], int path_len, FILE *log)
{
	FILE *lfptr1, *lfptr2;

	char *larr1, *larr2;

	lfptr1 = fopen(lread1,"r");
	lfptr2 = fopen(lread2,"r");

	/* the function get_char takes the file pointer as input and returns the number of legible characters present in each file.
	   Count is used to declare the size of the character array for each file*/
	int count1 = get_char(lfptr1);
	int count2 = get_char(lfptr2);
	
	
	larr1= (char*) calloc(count1+1,sizeof(char));
	larr2= (char*) calloc(count2+1,sizeof(char));

	
	/* This function takes a file pointer and an array as input and stores legible characters in an array*/
	lget_word_array(lfptr1,larr1);
	lget_word_array(lfptr2,larr2);

	int matrix [count1+1][count2+1]; 

	// initializes the first row and column with zero
	for (int i = 0; i<=count1; i++)
	{
		matrix[i][0] = 0;
	}
	for (int i=0; i<=count2; i++)
	{
		matrix[0][i] = 0;
	}
	int m, max = 0;	


	/* Assumes one of the character array as a row to the matrix and another one as column,
	    As the loop runs if an element of one array is equal to the other array, the preceding diagonal element is added to the concurrent point
	     and the maximum is count is stored in a variable.
	    The maximum element once the loop is done is the length of the longest common sequence. */
	for(int i = 1; i<=count1; i++)
	{
		for (int j = 1; j<=count2; j++)
		{
			if(larr1[i] == larr2[j])
			{
				m = matrix[i-1][j-1];
				matrix[i][j] = m+1;
				if (max < matrix[i][j])
				{
					max = matrix[i][j];
				}
			}
			else
			{
				matrix[i][j] = 0;
			}
		}
	}
	
	float fcount1 = count1;
	float fcount2 = count2;
	float lcs = ((max * 2)/ (fcount2 + fcount1)) * 100; // calculates the percentage of longest common sequence in both the files

	/* This loop alerts the user if a file contains only one invalid input*/
	if (count1 > 0 && count2 > 0)
	{
		printf("%f\n", lcs);
		fprintf(log,"%f\n", lcs);	
	}
	else if(count1 == 0)
	{
		printf("            %s is an invalid file\n", lread1 + path_len + 1);
		fprintf(log,"            %s is an invalid file\n", lread1 + path_len + 1);
	}
	else if(count2 == 0)
	{
		printf("            %s is an invalid file\n", lread2  + path_len + 1);
		fprintf(log,"            %s is an invalid file\n", lread2  + path_len + 1);
	}
	

}


/* Function get_char takes a file pointer as input and returns the number of valid characters in the file*/
int get_char(FILE *fptr)
{
	char ch;
	int i = 0;
	fseek(fptr,0,SEEK_SET);
	ch = fgetc(fptr);
	
	while (ch != EOF)
	{
		if (ch != '\n' && (isalnum(ch) || (ch == '_'))) 
		{
			i++;
		}
		ch = fgetc(fptr);
		
	}
	
	return (i);
}

/* This function takes a file pointer and an array as input and stores legible character in an array*/
void lget_word_array(FILE *fptr, char* arr)
{
	char ch;

	fseek(fptr,0,SEEK_SET); //sets the file pointer to the beginning of the file
	int j = 0;
	
	arr[j] = '\0';
	j++;
	while ((ch=fgetc(fptr)) != EOF)
	{
		if (isalnum(ch) || (ch == '_'))
		{
			arr[j] = ch;
			j++;
		}
		
		
	}

}
