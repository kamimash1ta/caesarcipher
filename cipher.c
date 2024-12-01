//Caesar Cipher

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 1024

//cipher function
char cipher(char a, int seed) {
	return a + seed;
}

//cipher the contents of an inputed file with the cipher function
char* cipherfile(char input[], int seed) {
  
  //clean up input string to input as path
  size_t path_length = strlen(input);
  if (input[path_length-1] == '\n'){
    input[path_length-1] = '\0';
  }
	//open file
	FILE* inputfile = fopen(input, "r");

	//declare output
	static char dirty_output[MAX_SIZE];

	//check if file could be opened
	if (inputfile == NULL) {
		perror("File could not be opened\n");
		exit(1);
	}

  //copy contents of file to dirty_output
  int i = 0;
  while (i < MAX_SIZE-1 && (dirty_output[i] = fgetc(inputfile)) != EOF){
    i++;
  }
  //make sure dirty_output is null-terminated
  dirty_output[i] = '\0';

  //print contents of file to encode
  printf("Encoding: %s\n", dirty_output);

  //cipher string from file
  static char encoded_dirty_output[MAX_SIZE];
  for (int n = 0; n < i; n++) {
	  encoded_dirty_output[n] = cipher(dirty_output[n], seed);
	}
  //make sure encoded_dirty_output is null-terminated
  encoded_dirty_output[i] = '\0';

	//close inputfile
	fclose(inputfile);

	//return ciphered output
	return encoded_dirty_output;
}

//cipher the contents of direct user input using the cipher function
char* ciphertext(char input[], int input_length, int seed) {
	//declare output
	static char dirty_output[MAX_SIZE];

	//cipher every character of input and set output equal to it
	for (int i = 0; i < input_length; i++) {
		dirty_output[i] = cipher(input[i], seed);
	}
  //ensure dirty_output is null-terminated
  dirty_output[input_length] = '\0';
	//return ciphered output
	return dirty_output;
}

//driver function
int main() {

	//variable declaration
	int seed;
	char input[MAX_SIZE], is_file;
  
  //ask if a file is being encoded
  printf("Encoding a file? (y/n): ");
  is_file = getchar();
  getchar(); //consumes '\n'

	//get text to encode
	printf("Text or file to encode: ");
	fgets(input,MAX_SIZE,stdin);

  //remove potential newline
  input[strcspn(input, "\n")] = '\0';

	//get seed for encoding
	printf("Seed: ");
	scanf("%d", &seed);

	//find the length of the input array
  int input_length = strlen(input);

  if (input[input_length-1] == '\n') {
    input[input_length-1] = '\0';
    input_length--;
  }

	//print ciphered input based on type
	if (is_file == 'y') {
		printf("Encoded text: %.*s\n",MAX_SIZE,cipherfile(input,seed));
	}
	else if (is_file == 'n') {
		printf("Encoded text: %s\n",ciphertext(input, input_length, seed));
	} else {
    printf("Input (y) if encoding a file, (n) if encoding direct user input. \n");
    exit(1);
  }

	//end driver function  
	return 0;
}