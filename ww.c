#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

int readFile( int file , int width, int );
int isADirectory(const char *path);
int writeFile (char* dirname, int);

int main(int argc, char** argv){

	int file, width;
	width = atoi(argv[1]);
	if ( isADirectory(argv[2]) != 0  ) {

		

		int x = writeFile(argv[2], width );
		if ( x == 0) {
			return EXIT_SUCCESS;

		} 
		else{
			return EXIT_FAILURE;

		}
		
		return 0;


		 
	} 

	
	
	file = open(argv[2], O_RDONLY);
	if ( file < 0 ) {

		perror("file does not exist"); 
		
		return EXIT_FAILURE;

	
	} 
	else {
		
		int x = readFile(file, width, 1);
		close(file);
		if ( x == 0) {

			return EXIT_SUCCESS;

		} else {

			return EXIT_FAILURE;

		}
  	
	
	}
}


int writeFile ( char* dirname, int width){

	

	struct dirent *sd;
	DIR *dir;
	dir = opendir(dirname);
	struct stat filestat;
	int wordChecker = 0;
	if ( dir == NULL){

		return 1;
	}
	int count = 0;
	while (     (sd = readdir(dir)) != NULL    ){

		
		
		
		

		int i = 0;
		while ( i < 5){
				
			if ( i == 0){
				if ( sd->d_name[i] == 'w') i++;
				else break;

			}
			if ( i == 1){
				if ( sd->d_name[i] == 'r') i++;
				else break;

			}

			if ( i == 2){

				if ( sd->d_name[i] == 'a') i++;
				else break;

			}
			if ( i == 3){

				if ( sd->d_name[i] == 'p') i++;
				else break;

			}
			if ( i == 4){

				if ( sd->d_name[i] == '.') i++;
				else break;

			}
		}
		if ( i == 5) continue;

		
		
		
		if (count > 1) {

			if (sd->d_name[0] == '.') continue;
			char* wordarray = malloc(sizeof(char) * (strlen(dirname) + strlen(sd->d_name) + 2));
			strcpy(wordarray, dirname); 
			strcat(wordarray, "/");
			strcat(wordarray, sd->d_name);

			stat(wordarray, &filestat);
		
			if (S_ISDIR(filestat.st_mode)) {

				free(wordarray);

				continue;

		
			}
			
			
			

			char* file = malloc(sizeof(char) * strlen(dirname) + 7);
			strcpy(file, dirname);

			file = strcat(file, "/wrap.");
			char* filename = malloc(sizeof(char) * strlen(file) + strlen(sd->d_name) + 1);


			strcpy(filename, file);
			filename = strcat(filename, sd->d_name);
			
			int fd3=open(filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRGRP | S_IROTH | S_IRUSR | S_IWGRP | S_IWOTH | S_IWUSR);
			int fd = open(wordarray, O_RDONLY);
			
			int x = readFile(fd, width, fd3);
			if ( x == 1) wordChecker = 1;
			close(fd);
			close(fd3);
			free(file);	
			free(filename);
			free(wordarray);
			
				
					
		



			
			
			
			
			
			
        		
    		}
		

		count++;


	}
	closedir(dir);

	return wordChecker;



}




















int readFile( int file , int width, int newFile){

	
	
	char* c = malloc(sizeof(char) * INT_MAX);
	
	
	int wordRead = 0;
	int sz;
	int i = 0;
	do {
		
		char character = 0;
		sz = read(file, &character, 1);
		c[i++] = character;

	} while ( sz != 0);
	i--;
	
	c[i] = '\0';
	
	
	while(c[0] == '\t' || c[0] == '\n' || c[0] == ' '){ // check all starting spaces till there is a letter

		for(int k=0;k<i;k++){
			c[k] = c[k+1];
		}
		i--;
		
	}
	if ( i == 0){

		free(c);
		return 0;

	} 
	c[i] = '\0';

	while(isspace(c[i - 1]) != 0){// get rid of ending spaces

		c[i - 1] = c[i];
		i--;
		
	}
	
	

	int k = 0;
	//looping through until the end of Initial array with all bytes read
	int tempWidth = width;
	char* wordArray;
	int linechecker = 0;
	
	while ( k < i){

		
		int prevRef = k;
		
		//checking for first space, if it space increment and break, else, just increment
		
		
		while ( k <= i ){

			if ( isspace(c[k]) != 0){
				if ( c[k] == '\n' ) linechecker++;
				k++;
				break;
			}
			else{
				k++;
			}
		}
		int g = k;
		while ( isspace(c[g]) != 0){
			if ( c[g] == '\n' ) {
				linechecker++;
			}
			g++;
	
		}

		if ( k == i) break;
		int u = k;


		int wordLength = (k - prevRef) - 1;
		wordArray = (char *) calloc(wordLength + 1, sizeof(char));
		int arrayCounter = 0;
		for ( int j = prevRef; j < k - 1; j++){
			wordArray[arrayCounter] = c[j];
			arrayCounter++; 
		}


	
		

		

			if ( wordLength < tempWidth ){
				

				for ( int j = 0; j < wordLength; j++){
					write(newFile,&wordArray[j],1);
				}
				char p = ' ';
				write(newFile,&p,1);
				tempWidth = tempWidth - (wordLength + 1);
				char d = '\n';
				if ( linechecker > 1) {
					write(newFile,&d,1);
					write(newFile,&d,1);
					tempWidth = width;
				}

				if ( k > i){
					char y = '\n';
					write(newFile,&y,1);

				}
				
				



			}
			else {
				
				if ( wordLength == tempWidth){

					

					for ( int j = 0; j < wordLength; j++){
						write(newFile,&wordArray[j],1);
					}
					char y = '\n';
					write(newFile,&y,1);
					if ( linechecker > 1) {
						write(newFile,&y,1);
					}
					tempWidth = width;
					

				}
				else {
					char y = '\n';
					
					write(newFile,&y,1);
					for ( int j = 0; j < wordLength; j++){
						write(newFile,&wordArray[j],1);
					}
					char p = ' ';
					write(newFile,&p,1);
					if ( linechecker > 1 ) {
						write(newFile,&y,1);
						if (wordLength < width ){
							write(newFile,&y,1);
						}
						
						tempWidth = width;
					}
					tempWidth = width - (wordLength + 1);
					if ( k > i ) {

						char y = '\n';
						write(newFile,&y,1);

					}
					
					


				}
				
			}
		
		
		while ( isspace(c[u]) != 0 ){
			
			
			u++; 
		}
		
		
		k = u;
		
		linechecker = 0;

		free(wordArray);

		

	}

	
	
	

	free(c);
	if ( wordRead == 1){
		return 1;

	} else {
		return 0;

	}
	

	

}

int isADirectory(const char *pathname) {
   struct stat statbuf;
   if (stat(pathname, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}