
/* This function takes two file names, the length of the directory path and the pointer to the log file as input 
     and prints out the percentage of plagiarism calculated through the method of finger printing */
void finger_printing(char fread1[], char fread2[], int path_len, FILE *log)
{
	FILE *fp1, *fp2;

	char *farr1, *farr2;
	long int  *hash_table1, *hash_table2;

	fp1 = fopen(fread1,"r");
	fp2 = fopen(fread2,"r");
	

	/* Function get_mem gets the memory required for the words in each file to be stored in an array.
		The function counts and returns the number of spaces in each file. This count is used to eliminate all the stop words from the file*/
	int count1 = get_mem(fp1);
	int count2 = get_mem(fp2);

	
	/* the function takes the file pointer as input and returns the number of legible characters present in each file.
	   Count is used to declare the size of the character array for each file*/
	int arr_size1 = get_char(fp1);
	int arr_size2 = get_char(fp2);

	
	farr1= (char*) calloc(arr_size1+1,sizeof(char));
	farr2= (char*) calloc(arr_size2+1,sizeof(char));


	/* This function takes a file pointer, an array and count of the number of words as input 
	       and stores legible characters in an array*/
	char_array(fp1,farr1,count1);
	char_array(fp2,farr2,count2);
	
	
	/* Calculates the number of hashes that can be made out of each character array*/
	int k_grams1 = calc_k(farr1);
	int k_grams2 = calc_k(farr2);
	
	

	int k_grams = (k_grams1>k_grams2?k_grams1:k_grams2); // this value is used to calculate the hash value 

	hash_table1= (long int*) calloc(k_grams1+1,sizeof(long int));
	hash_table2= (long int*) calloc(k_grams2+1,sizeof(long int));

	/*This function takes in a character array and an interger array as input and 
	    stores the hash values in the integer array*/
	get_hash_table(farr1, hash_table1);
	get_hash_table(farr2, hash_table2);
	
	
	long int fingerPrint1[k_grams1+1],fingerPrint2[k_grams2+1];
	
	int hash_value = calc_hash_value(k_grams); // calculates the hash value
	
	
	/* This function takes a hash_table array, hash_value and fingerprint array as input,
	     hashes each element of hash_table array with the hash_value and stores it in the fingerprint array*/
	get_finger_print(fingerPrint1, hash_value, hash_table1);
	get_finger_print(fingerPrint2, hash_value, hash_table2);
	

	/* This function takes the two fingerprint arrays and the k_grams values as input,
	     it calculates and returns the plagiarism percentage */
	float percentage = get_plagiarism_percentage(fingerPrint1,fingerPrint2,k_grams1,k_grams2); 
	

	/* if a file has only invalid characters, this loop alerts the user or else prints out the percentage of plagiarism*/
	if (farr1[0] != '\0' && farr2[0] != '\0')
	{
		printf("%f\n", percentage * 100);
		fprintf(log,"%f\n", percentage * 100);	
	}
	else if(farr1[0] == '\0')
	{
		printf(" %s is an invalid file\n", fread1 + path_len + 1);
		fprintf(log," %s is an invalid file\n", fread1 + path_len + 1);
	}
	else if(farr2[0] == '\0')
	{
		printf(" %s is an invalid file\n", fread2 + path_len + 1);
		fprintf(log," %s is an invalid file\n", fread2 + path_len + 1);
	}
	

}


/* This function takes a file pointer, an array and count of the number of words as input 
	       and stores legible characters in an array*/
void char_array(FILE *fp, char *arr, int count)
{
	char ch, word[20], stop[20];
	FILE *sp;

	int flag = 0, j = 0;
	fseek(fp, 0, SEEK_SET);
	
	sp = fopen("stop_words.txt","r"); //the file contains most of the stop words
	for (int m=0; m<=count; m++)
	{
		fscanf(fp, "%s", word);
		
		fseek(sp, 0, SEEK_SET);// sets the pointer of stop words file to the beginning 
		flag = 0;
		for (int i=0; i<312; i++)
		{
			fscanf(sp,"%s", stop);
			if(strcmp(word,stop) == 0)
			{

				flag = 1;
				break;
			}
		}
		
		if(flag == 0)
		{
			int len = strlen(word);
			
			for(int k=0; k<len; k++)
			{
				if (isalnum(word[k]) || word[k] == '_')
				{
					arr[j] = tolower(word[k]);
					j++;
				}
				
			}
		}

	}
	arr[j] = '\0';

}


/* Calculates the number of hashes that can be made out of each character array*/
int calc_k(char *arr)
{
	int i = 0;
	int hash_count = 0;
	
	
	while (arr[i+4] != '\0')
	{
		
		hash_count+=1;
		i++;
	}
	
	return hash_count;
}


/* This function takes in maximum no of elements in both the hash_table arrays,
     calculates and returns the next largest prime number after the product of the maximum number with hundred*/
long int calc_hash_value(int hash_count)
{
	long int count = hash_count * 100;

	int i;
	int flag = 0;
	if (count % 2 == 0)
	{
		count+=1;
	}
	while (true)
	{
		i = 2;
		
		while (i < sqrt(count))
		{
			if (count % i == 0)
			{
				flag = 1;
				break;
			}
			i++;
		}

		if (flag == 1)
		{
			count+=2;
			flag = 0;
		}
		else
		{
			return count;
		}
	}
}


/*This function takes in a character array and an interger array as input and 
	    stores the hash values in the integer array*/
void get_hash_table(char *arr, long int *hash_table)
{
	int i = 0;
	long int hash_value = 0;
	int j = 0;

	
	while(arr[i+4] != '\0')
	{
		hash_value += (int)arr[i] * (pow(5,5));
		hash_value += (int)arr[i+1] * (pow(5,4));
		hash_value += (int)arr[i+2] * (pow(5,3));
		hash_value += (int)arr[i+3] * (pow(5,2));
		hash_value += (int)arr[i+4] * (pow(5,1));

		hash_table[j] = hash_value;
		hash_value = 0;
		j++;
		i++;
	}
	hash_table[j] = 0;
}


/* This function takes a hash_table array, hash_value and fingerprint array as input,
	     hashes each element of hash_table array with the hash_value and stores it in the fingerprint array*/
void get_finger_print(long int fingerPrint[], long int hash_value, long int hash_table[])
{
	int i = 0;
	while(hash_table[i] != 0)
	{
		fingerPrint[i] = (hash_table[i] / hash_value);
		i++;
	}
	fingerPrint[i] = 0;
}


/* This function takes the two fingerprint arrays and the k_grams values as input,
	     it calculates and returns the plagiarism percentage */

float get_plagiarism_percentage(long int arr1[], long int arr2[], int len1, int len2)
{
	int count = 0;

	// int len = (len1<len2?len1:len2);

	for (int i=0; i<len1; i++)
	{
		for(int j=0; j<len2; j++)
		{
			if (arr1[i] == arr2[j])
			{
				count += 1;
				arr2[j] = 0;
				break;
			}
		}
		
	}
	
	float flen1 = len1;
	float flen2 = len2;

	float finper = (count * 2) / (flen1 + flen2);

	return finper;
}
