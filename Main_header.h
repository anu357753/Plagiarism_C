/* This file includes all the header files needed to run the program*/

/* System defined headers */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <time.h>


/* Function declarations */
bool empty_file();
int get_char();
void lget_word_array();
void char_array();
int calc_k();
void get_hash_table();
long int calc_hash_value();
void get_finger_print();
float get_plagiarism_percentage();
int get_word_array();
int get_mem();
void get_freq();
int dot_prod();
float calc_freq();

/* User defined headers */
#include "Function_file.h"
#include "Bag_of_words.h"
#include "LCS.h"
#include "Finger_Printing.h"