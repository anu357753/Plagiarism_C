/*
*** Author : Anudeepthi Cherlapally
*** Title  : Plagiarism Detector
*** Date   : 18-09-2017
*/


/*This file contains the main program which drives the entire program*/


/* a user defined header file which contains all the other needed header files
     and function declarations */
#include "main_header.h"


/* Main function drives the entire Plagiarism program */
void main()
{
	DIR *d;
	struct  dirent *dir;
	char str[100], file_name[25];
	char str2[100];
	char file_list[20][100], file_list2[20][100];
	char print_list[20][100];
	int len, count = 0;
	FILE *log;

	log = fopen("log_file.txt","a"); // opens the log file 

	
	/* Retrieves and enters the current time into the log file */
	time_t time_stamp;
    time_stamp = time(NULL);
    fprintf(log,ctime(&time_stamp));


	printf("Enter directory: \n");
	gets(str);                        // takes the user entered directory path
	int path_len = strlen(str);
	d = opendir(str);                // opens the directory
	
	
	/* Filters the files of type '.txt' from the directory needed for testing 
	     excluding out two files with names "stop_words.txt" and "log_file.txt" */
	if (d)
	{
		while((dir = readdir(d)) != NULL)
		{
			strcpy(file_name,dir -> d_name);
			len = dir -> d_namlen;
			
			if ((strcmp(file_name + len - 4, ".txt")) == 0 && (strcmp(file_name,"stop_words.txt")) != 0 && (strcmp(file_name,"log_file.txt")) != 0)
			{
				strcpy(str2,str);
				strcat(str2,"\\");
				strcpy(file_list[count],strcat(str2,file_name));
				count++;
			}

		}
		closedir(d);

	}
	
	int j = 0;
	
	
	printf("\n");
	for (int i = 0; i < count; i++)
	{
		if (!(empty_file(file_list[i]))) // Function empty_file takes a file as input and returns true if the file is empty
		{
			strcpy(file_list2[j],file_list[i]); // if a file is not empty, copies the file name into another array
			j++;
		}
		else
		{	
			/* lets the user know if a file is empty, this file will not be given to the program as input */
			printf("%s is an empty file. It will not be tested for plagiarism\n", file_list[i] + path_len +1);
			fprintf(log, "%s is an empty file. It will not be tested for plagiarism\n",  file_list[i] + path_len +1);
		}
	}
	printf("\n");
	fprintf(log,"\n");
	printf("     Plagiarism Test \n");
	fprintf(log,"     Plagiarism Test \n");
	printf("------------------------\n");
	fprintf(log,"------------------------\n");
	printf("\n");
	fprintf(log,"\n");


	/* The files which contain characters are taken into the loop and are tested for plagiarism in three different methods,
	      and prints out the percentage given out by each method
	   Each of the function call below takes in two files, length of the directory path and the pointer to the log files as input.
	   The funtions will calculate the percentage of plagiarism and prints the value before returning. */
	for (int i = 0; i < j; i++)
	{
		for (int k = i+1; k < j; k++)
		{
			printf("Plagiarism for %s %s\n", file_list2[i] + path_len + 1, file_list2[k] + path_len + 1);
			fprintf(log,"Plagiarism for %s %s\n", file_list2[i] + path_len + 1, file_list2[k] + path_len + 1);
			printf("\n");
			fprintf(log,"\n");
			printf("Bag of Words: ");
			fprintf(log,"Bag of Words: ");
			bag_of_words(file_list2[i], file_list2[k], path_len, log); //calls the bag of words function for two files
			printf("LCS:  ");
			fprintf(log,"LCS:  ");
			lcs(file_list2[i], file_list2[k], path_len, log); // calls lcs function for two files
			printf("Finger Printing: ");
			fprintf(log,"Finger Printing: ");
			finger_printing(file_list2[i], file_list2[k], path_len, log); // calls finger printing function for two files
			printf("\n");
			fprintf(log,"\n");
			printf("\n");
			fprintf(log,"\n");
		}
	}

	fprintf(log, "***********************************************************\n");

	

}

