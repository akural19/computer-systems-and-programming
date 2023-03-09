#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

/************  COMP201 ASSIGNMENT 2  ************/

// Alp Kural


int main(int argc, char *argv[]) {

	//TODO:Task 1
	
       	if (strcmp(argv[1], "calculate-tf") == 0) { //frequencyAnalysis 
 	
		FILE *file = fopen("SMSSpamCollection.txt","r");            // to open a file 	
		
		char str[1000];  	 
		char *ptr;

		int hamNum = 0; 
		int spamNum = 0; 
		int wordInHam = 0; 
		int wordInSpam = 0; 
	
		char *word = strdup(argv[2]);                              // reserving heap memory to be able to change the string characters later on 
		int wordLen = strlen(word);

		for (int jj = 0; jj < wordLen; jj++) {       		   // to obtain all lowercase word  
			word[jj] = tolower(word[jj]);
		}

		do {							   // iterating through the file to read line by line until fgets function returns null which indicates nothing left to read 
			ptr = fgets(str, 1000, file);			    
			
			if (ptr	!= NULL) {

				int lineLen = strlen(ptr);
				
				for (int ii = 0; ii < lineLen; ii++) {     // to obtain all lowercase line 
					ptr[ii] = tolower(ptr[ii]);
				}

				char *newPtr = strchr(ptr, '\t') + 1;      // to obtain a pointer pointing right after '\t' char which corresponds the start of the message
				
				int index = newPtr - ptr;		   // to keep track of index in a line 

				if (strspn(ptr, "spham") == 4) {	   // if before '\t' charachter, there is 4 chars, than it is spam 
					
					spamNum++;			   // increment number of spam line  

					while (index < lineLen) {          // while pointer is still pointing the characters in line 

						newPtr = strstr(newPtr, word);          // string search, if the string is found function return a pointer pointing the first character of the string 
											// looks for the first occurance of a needle in haystack 

						if (newPtr != NULL) {            

							if (!isalpha(newPtr[-1]) && !isalpha(newPtr[wordLen])) {         // checks whether or not the character before word and after word is alphabetical or not 
								wordInSpam++;                                            // if so increment word in spam by 1 
							}
							newPtr += wordLen;             // to obtain a pointer pointing right after the found word 
						}
						else {                                 // if the return value is null, the search function could not find any string
							break;                         // then break
						}
					}
				}

				else {					   // if before '\t' character, there is not 4 char, than it is ham

					hamNum++;			   // increment number of ham line 
				
					while (index < lineLen) {
						
						newPtr = strstr(newPtr, word);

						if (newPtr != NULL) {

							if (!isalpha(newPtr[-1]) && !isalpha(newPtr[wordLen])) {
								wordInHam++;
							}
							newPtr += wordLen;
							index = newPtr - ptr;
						}
						else {
							break;
						}
					}
				}
			}	

		} while (ptr != NULL);

		if (wordInHam == 0 && wordInSpam == 0) {
			printf("This word doesn't occur in the text!\n");
		}
		else {
			printf("Total Ham:   %d\n", hamNum);
			printf("Word in Ham:   %d\n", wordInHam);
		
			float tfHam = (float) wordInHam / (float) hamNum; 
			printf("Calculated tf value for this word:   %.6f\n", tfHam);
	
			printf("Total Spam:   %d\n", spamNum);
			printf("Word in Spam:   %d\n", wordInSpam);

			float tfSpam = (float) wordInSpam / (float) spamNum;
			printf("Calculated tf value for this word:   %0.6f\n", tfSpam);
		
			if (tfHam != tfSpam) {
				printf("This word is mostly used for %s messages\n", (tfHam > tfSpam)?"non spam":"spam");
			}
			else {
				printf("This word is used equally for both spam and not spam messages\n");
			}
		}

		fclose(file);	
       	}

    
	//TODO:Task 2

    
	else if (strcmp(argv[1], "predict") == 0) { //spamDetection 

		char *wordsArray[5] = {argv[2], argv[3], argv[4], argv[5], argv[6]};             // to store each word in an array  

		float tdfidfHamTotal = 0; 
		float tdfidfSpamTotal = 0; 

		for (int ii = 0; ii < 5; ii++) { 						 // to iterate through wordsArray array 

			FILE *file = fopen("SMSSpamCollection.txt","r");           

			char str[1000];  	 
			char *ptr;

			int hamNum = 0; 
			int spamNum = 0; 
			int wordInHam = 0; 
			int wordInSpam = 0; 
			int occuredLine = 0;

			char *word = strdup(wordsArray[ii]);                                     
			int wordLen = strlen(word);

			for (int jj = 0; jj < wordLen; jj++) {       		  
			word[jj] = tolower(word[jj]);
			}	

			do {							 
				ptr = fgets(str, 1000, file);			    
			
				if (ptr	!= NULL) {

					bool flag = false;                                     	// flag to check whether the desired word is found in the line or not  
												// initialize the flag 
					int lineLen = strlen(ptr);
				
					for (int ii = 0; ii < lineLen; ii++) {     
						ptr[ii] = tolower(ptr[ii]);
					}
		
					char *newPtr = strchr(ptr, '\t') + 1;  
				
					int index = newPtr - ptr;		  

					if (strspn(ptr, "spham") == 4) {	  
					
						spamNum++;			    

						while (index < lineLen) {          

							newPtr = strstr(newPtr, word);       
										
							if (newPtr != NULL) {            

								if (!isalpha(newPtr[-1]) && !isalpha(newPtr[wordLen])) {         
									wordInSpam++;  
									if (!flag) {     		// if the word is not found in line yet 
										occuredLine++;      	// increment number of line with word 
										flag = true;            // turn on the flag    
									}						
								}
								newPtr += wordLen;             
							}
							else {                                
								break;                      
							}
						}
					}

					else {					  	
						hamNum++;			   
				
						while (index < lineLen) {
						
							newPtr = strstr(newPtr, word);
	
							if (newPtr != NULL) {
	
								if (!isalpha(newPtr[-1]) && !isalpha(newPtr[wordLen])) {
									wordInHam++;
									if (!flag) {
										occuredLine++;
										flag = true;
									}
								}
								newPtr += wordLen;
								index = newPtr - ptr;
							}
							else {
								break;
							}
						}
					}
				}	

			} while (ptr != NULL);

			float tfHam = (float) wordInHam / (float) hamNum; 
			float tfSpam = (float) wordInSpam / (float) spamNum;
			float idf = 0; 

			if (occuredLine != 0) {
				idf = logf((float)(hamNum + spamNum) / (float) occuredLine);        // to obtain the idf value 
			}
			
			tdfidfHamTotal += tfHam * idf;                                              // to accumulate tf-idf scores of each word for ham lines 
			tdfidfSpamTotal += tfSpam * idf;                                            // to accumulate tf-idf scores of each word for spam lines 

			fclose(file);
		}
		
		printf("Total tf-idf score from non spam messages for the sentence: %f\n", tdfidfHamTotal);	
		printf("Total tf-idf score from spam messages for the sentence: %f\n", tdfidfSpamTotal);

		if (tdfidfHamTotal != tdfidfSpamTotal) {
				printf("This sentence is %s.\n", (tdfidfHamTotal > tdfidfSpamTotal)?"not spam":"spam");
			}
		else {
				printf("This sentence is neither spam nor not spam.\n");
			}
       	}

   
       	//TODO:Task Extra
	
    
	else if (strcmp(argv[1], "predict-wo-stopwords") == 0) { //stopWords 
  
		char *wordsArray[5] = {argv[2], argv[3], argv[4], argv[5], argv[6]};            

		float tdfidfHamTotal = 0; 
		float tdfidfSpamTotal = 0; 

		for (int ii = 0; ii < 5; ii++) { 	

			FILE *file = fopen("SMSSpamCollection.txt","r");         
			FILE *myFile = fopen("99webtools.txt", "r");                   // to open the stop-words file 

			char str[1000];  	 
			char *ptr;

			int hamNum = 0; 
			int spamNum = 0; 
			int wordInHam = 0; 
			int wordInSpam = 0; 
			int occuredLine = 0;

			char *word = strdup(wordsArray[ii]);                                     
			int wordLen = strlen(word);
			
			for (int jj = 0; jj < wordLen; jj++) {       		  
			word[jj] = tolower(word[jj]);
			}	

			char myStr[30];
			char *myPtr; 
			bool check = false;                                           // boolean flag to indicate whether the word is in stop words file or not 

			do {
				myPtr = fgets(myStr, 30, myFile);

				if (myPtr != NULL) {

					int len = strlen(myPtr) - 1;                  // to obtain the length of the word in the file and exclude '\n' from the length of the word  
				
					if (len == wordLen && strncmp(word, myPtr, len) == 0) {         // if the word lenghts are matching of word in stops words and given argument word and 
													// string comparison function indicates that they are the same word 
						check = true;						// set flag as true 
						printf("%s is a stop word, it is not used in tf-idf calculations.\n", word);
						break;							// if found in stop words file, no need to continuing the file, therefore, break the do-while loop
					}
				}
				
			} while (myPtr != NULL);

			fclose(myFile);     // to close the stop words file 
	
			if (check) {        // if boolean flag is true end the current iteration and pass to the next one 
				continue;
			}

			do {							 
				ptr = fgets(str, 1000, file);			    
			
				if (ptr	!= NULL) {

					bool flag = false;                                     	  
												 
					int lineLen = strlen(ptr);
				
					for (int ii = 0; ii < lineLen; ii++) {     
						ptr[ii] = tolower(ptr[ii]);
					}
		
					char *newPtr = strchr(ptr, '\t') + 1;  
				
					int index = newPtr - ptr;		  

					if (strspn(ptr, "spham") == 4) {	  
					
						spamNum++;			    

						while (index < lineLen) {          

							newPtr = strstr(newPtr, word);       
										
							if (newPtr != NULL) {            

								if (!isalpha(newPtr[-1]) && !isalpha(newPtr[wordLen])) {         
									wordInSpam++;  
									if (!flag) {     	 
										occuredLine++;   
										flag = true;        
									}						
								}
								newPtr += wordLen;             
							}
							else {                                
								break;                      
							}
						}
					}

					else {					  	
						hamNum++;			   
				
						while (index < lineLen) {
						
							newPtr = strstr(newPtr, word);
	
							if (newPtr != NULL) {
	
								if (!isalpha(newPtr[-1]) && !isalpha(newPtr[wordLen])) {
									wordInHam++;
									if (!flag) {
										occuredLine++;
										flag = true;
									}
								}
								newPtr += wordLen;
								index = newPtr - ptr;
							}
							else {
								break;
							}
						}
					}
				}	

			} while (ptr != NULL);

			float tfHam = (float) wordInHam / (float) hamNum; 
			float tfSpam = (float) wordInSpam / (float) spamNum;
			float idf = 0; 

			if (occuredLine != 0) {
				idf = logf((float)(hamNum + spamNum) / (float) occuredLine);     
			}
			
			tdfidfHamTotal += tfHam * idf;                                           
			tdfidfSpamTotal += tfSpam * idf;                                         

			fclose(file);
		}
		
		printf("Total tf-idf score from non spam messages for the sentence: %f\n", tdfidfHamTotal);	
		printf("Total tf-idf score from spam messages for the sentence: %f\n", tdfidfSpamTotal);

		if (tdfidfHamTotal == 0 && tdfidfSpamTotal == 0) {
			printf("Tf-idf scores are found to be 0, spam detection failed!\n");
		}
		else if (tdfidfHamTotal != tdfidfSpamTotal) {
			printf("This sentence is %s.\n", (tdfidfHamTotal > tdfidfSpamTotal)?"not spam":"spam");
		}
		else {
			printf("This sentence is neither spam nor not spam.\n");
		} 
	}
    
	else {      
	       	printf("Wrong Function!\n");
      	}
	return 0;
}
