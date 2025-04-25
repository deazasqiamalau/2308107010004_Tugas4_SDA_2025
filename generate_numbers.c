/**
 * generate_numbers.c
 * Program to generate random number data for sorting algorithm analysis
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 
 void generate_random_numbers(const char *filename, int count, int max_value) 
 {
     FILE *fp = fopen(filename, "w");
     if (!fp) {
         perror("File tidak dapat dibuka");
         return;
     }
 
     srand(time(NULL)); // Inisialisasi seed
 
     printf("Generating %d random numbers...\n", count);
     for (int i = 0; i < count; i++) {
         int num = rand() % max_value;
         fprintf(fp, "%d\n", num);
         
         // Show progress every 10%
         if (i % (count / 10) == 0) {
             printf("Progress: %d%%\n", i * 100 / count);
         }
     }
 
     fclose(fp);
 }
 
 int main() {
     printf("Generating random number data...\n");
     generate_random_numbers("data_angka.txt", 2000000, 2000000);
     printf("Done! Data saved to data_angka.txt\n");
     return 0;
 }