/**
 * generate_words.c
 * Program to generate random word data for sorting algorithm analysis
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <string.h>
 
 void random_word(char *word, int length) {
     static const char charset[] = "abcdefghijklmnopqrstuvwxyz";
     for (int i = 0; i < length; i++) {
         int key = rand() % (int)(sizeof(charset) - 1);
         word[i] = charset[key];
     }
     word[length] = '\0';
 }
 
 void generate_random_words(const char *filename, int count, int max_word_length) {
     FILE *fp = fopen(filename, "w");
     if (!fp) {
         perror("File tidak dapat dibuka");
         return;
     }
 
     srand(time(NULL));
 
     printf("Generating %d random words...\n", count);
     char word[100];
     for (int i = 0; i < count; i++) {
         int length = (rand() % (max_word_length - 3)) + 3; // panjang kata minimal 3
         random_word(word, length);
         fprintf(fp, "%s\n", word);
         
         // Show progress every 10%
         if (i % (count / 10) == 0) {
             printf("Progress: %d%%\n", i * 100 / count);
         }
     }
 
     fclose(fp);
 }
 
 int main() {
     printf("Generating random word data...\n");
     generate_random_words("data_kata.txt", 2000000, 20);
     printf("Done! Data saved to data_kata.txt\n");
     return 0;
 }