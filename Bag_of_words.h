

/* this function takes in two file names, length of the directory path and pointer to the log file,
    it calculate the percentage of plagiarism between two '.txt' files and prints the output.
    In case a file has invalid input, it alerts the user. */

void bag_of_words(char read_file1[], char read_file2[], int path_len, FILE *log)
{
	FILE *fptr1, *fptr2;
	char **arr1, **arr2;

	/* declaration of arrays of type struct Freq_count to store the frequencies of words present in the file*/
	struct Freq_count file1[200];
	struct Freq_count file2[200];

	/* opens both the files */
	fptr1 = fopen(read_file1,"r");
	fptr2 = fopen(read_file2,"r");


	/* Function get_mem gets the memory required for the words in each file to be stored in an array.
		The function counts and returns the number of spaces in each file. */
	int count1 = get_mem(fptr1);
	int count2 = get_mem(fptr2);

	
	arr1 = (char**) calloc(count1+3,sizeof(char*)); // an array of required size is created
	arr2 = (char**) calloc(count2+3,sizeof(char*));

	int flag1;
	int flag2;

	/* Function get_word_array gets all the legible words from the file and stores them in an array.
	    Returns either 0 or 1 depending on the legibility */
	flag1 = get_word_array(fptr1,arr1);
	flag2 = get_word_array(fptr2,arr2);


	/* Function get_freq counts the frequency of each word and stores the values in a structure.
	   Stores all the structures in an array */
	get_freq(count1,arr1,file1);
	get_freq(count2,arr2,file2);
	

	int dotprod = dot_prod(file1,file2); // calculates the dot product for the files

	/* Function calc_freq calculates and returns the Euclidean Norm for both the files */
	float squares1 = calc_freq(file1);
	float squares2 = calc_freq(file2);
	
	float cos = dotprod / (squares1 * squares2); //calculates the value of similarity 

	/* the loop checks if any of the file has invalid input and alerts the user,
			if not prints the percentage of similarity between the two files */
	if (flag1 == 1 && flag2 == 1)
	{
		printf("%f\n", cos * 100);	
		fprintf(log,"%f\n", cos * 100);	
	}
	else if (flag1 == 0)
	{
		printf("    %s is an invalid file\n", read_file1 + path_len + 1);
		fprintf(log,"    %s is an invalid file\n", read_file1 + path_len + 1);
	}
	else if (flag2 == 0)
	{
		printf("    %s is an invalid file\n", read_file2  + path_len + 1);
		fprintf(log,"    %s is an invalid file\n", read_file2  + path_len + 1);
	}

	/* closes the file */
	fclose(fptr1);
	fclose(fptr2);
}




