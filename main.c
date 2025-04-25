/**
 * main.c
 * Program to analyze the performance of various sorting algorithms with tabular output
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <time.h>
 #include "sorting_algorithms.h"
 
 #define MAX_WORD_LENGTH 100
 #define MAX_MEMORY_MB 100.0  // Assuming max memory usage per test
 
 // Function to compare integers
 int compare_int(const void *a, const void *b) {
     return (*(int *)a - *(int *)b);
 }
 
 // Function to compare strings
 int compare_string(const void *a, const void *b) {
     return strcmp(*(char **)a, *(char **)b);
 }
 
 // Function to print divider line
 void print_divider(int width) {
     for (int i = 0; i < width; i++) {
         printf("-");
     }
     printf("\n");
 }
 
 // Function to print table header
 void print_table_header() {
     printf("| %-15s | %-10s | %-20s | %-10s |\n", "Algoritma", "Jumlah Data", "Waktu Eksekusi", "Memori (MB)");
     print_divider(64);
 }
 
 // Load integer data from file
 int* load_int_data(const char *filename, size_t count) {
     FILE *file = fopen(filename, "r");
     if (!file) {
         perror("Failed to open number data file");
         return NULL;
     }
     
     int *data = malloc(count * sizeof(int));
     if (!data) {
         perror("Memory allocation failed");
         fclose(file);
         return NULL;
     }
     
     for (size_t i = 0; i < count; i++) {
         if (fscanf(file, "%d", &data[i]) != 1) {
             if (feof(file)) {
                 printf("Warning: End of file reached after reading %zu numbers\n", i);
                 break;
             } else {
                 perror("Error reading from file");
                 free(data);
                 fclose(file);
                 return NULL;
             }
         }
     }
     
     fclose(file);
     return data;
 }
 
 // Load string data from file
 char** load_string_data(const char *filename, size_t count) {
     FILE *file = fopen(filename, "r");
     if (!file) {
         perror("Failed to open word data file");
         return NULL;
     }
     
     char **data = malloc(count * sizeof(char*));
     if (!data) {
         perror("Memory allocation failed");
         fclose(file);
         return NULL;
     }
     
     for (size_t i = 0; i < count; i++) {
         data[i] = malloc(MAX_WORD_LENGTH * sizeof(char));
         if (!data[i]) {
             perror("Memory allocation failed");
             
             // Free previously allocated memory
             for (size_t j = 0; j < i; j++) {
                 free(data[j]);
             }
             free(data);
             fclose(file);
             return NULL;
         }
         
         if (fscanf(file, "%s", data[i]) != 1) {
             if (feof(file)) {
                 printf("Warning: End of file reached after reading %zu words\n", i);
                 break;
             } else {
                 perror("Error reading from file");
                 
                 // Free previously allocated memory
                 for (size_t j = 0; j <= i; j++) {
                     free(data[j]);
                 }
                 free(data);
                 fclose(file);
                 return NULL;
             }
         }
     }
     
     fclose(file);
     return data;
 }
 
 // Function to duplicate integer array for testing
 int* duplicate_int_array(int *source, size_t count) {
     int *dest = malloc(count * sizeof(int));
     if (dest) {
         memcpy(dest, source, count * sizeof(int));
     }
     return dest;
 }
 
 // Function to duplicate string array for testing
 char** duplicate_string_array(char **source, size_t count) {
     char **dest = malloc(count * sizeof(char*));
     if (!dest) return NULL;
     
     for (size_t i = 0; i < count; i++) {
         dest[i] = malloc(MAX_WORD_LENGTH * sizeof(char));
         if (!dest[i]) {
             // Free previously allocated memory
             for (size_t j = 0; j < i; j++) {
                 free(dest[j]);
             }
             free(dest);
             return NULL;
         }
         
         strcpy(dest[i], source[i]);
     }
     
     return dest;
 }
 
 // Free string array
 void free_string_array(char **array, size_t count) {
     for (size_t i = 0; i < count; i++) {
         free(array[i]);
     }
     free(array);
 }
 
 // Test sorting algorithm with integer data and display results in table format
 void test_int_sort(const char *algo_name, void (*sort_func)(void*, size_t, size_t, int(*)(const void*, const void*)), 
                    int *data, size_t count) {
     int *test_data = duplicate_int_array(data, count);
     if (!test_data) {
         printf("| %-15s | %-10zu | %-20s | %-10s |\n", algo_name, count, "Memory allocation failed", "-");
         return;
     }
     
     clock_t start = clock();
     sort_func(test_data, count, sizeof(int), compare_int);
     clock_t end = clock();
     
     double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
     
     // Check if sorting was successful
     int is_sorted = 1;
     for (size_t i = 1; i < count; i++) {
         if (test_data[i] < test_data[i-1]) {
             is_sorted = 0;
             break;
         }
     }
     
     // Calculate approximate memory usage (simplified)
     double memory_mb = (count * sizeof(int)) / (1024.0 * 1024.0);
     
     if (!is_sorted) {
         printf("| %-15s | %-10zu | %-20s | %-10.2f |\n", algo_name, count, "Error: Not sorted", memory_mb);
     } else {
         printf("| %-15s | %-10zu | %-20.3f | %-10.2f |\n", algo_name, count, cpu_time_used, memory_mb);
     }
     
     free(test_data);
 }
 
 // Test sorting algorithm with string data and display results in table format
 void test_string_sort(const char *algo_name, void (*sort_func)(void*, size_t, size_t, int(*)(const void*, const void*)), 
                       char **data, size_t count) {
     char **test_data = duplicate_string_array(data, count);
     if (!test_data) {
         printf("| %-15s | %-10zu | %-20s | %-10s |\n", algo_name, count, "Memory allocation failed", "-");
         return;
     }
     
     clock_t start = clock();
     sort_func(test_data, count, sizeof(char*), compare_string);
     clock_t end = clock();
     
     double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
     
     // Check if sorting was successful
     int is_sorted = 1;
     for (size_t i = 1; i < count; i++) {
         if (strcmp(test_data[i], test_data[i-1]) < 0) {
             is_sorted = 0;
             break;
         }
     }
     
     // Calculate approximate memory usage (simplified)
     double memory_mb = (count * (sizeof(char*) + MAX_WORD_LENGTH * sizeof(char))) / (1024.0 * 1024.0);
     
     if (!is_sorted) {
         printf("| %-15s | %-10zu | %-20s | %-10.2f |\n", algo_name, count, "Error: Not sorted", memory_mb);
     } else {
         printf("| %-15s | %-10zu | %-20.3f | %-10.2f |\n", algo_name, count, cpu_time_used, memory_mb);
     }
     
     free_string_array(test_data, count);
 }
 
 // Run tests for a specific algorithm, data type, and dataset size
 void run_specific_test(int algo_choice, int data_type, int *int_data, char **string_data, size_t count) {
     if (data_type == 1) { // Integer data
         printf("\n=== Hasil Sorting Data Angka ===\n");
     } else { // String data
         printf("\n=== Hasil Sorting Data Kata ===\n");
     }
     
     print_table_header();
     
     if (data_type == 1) {
         switch (algo_choice) {
             case 1:
                 test_int_sort("Bubble Sort", bubble_sort, int_data, count);
                 break;
             case 2:
                 test_int_sort("Selection Sort", selection_sort, int_data, count);
                 break;
             case 3:
                 test_int_sort("Insertion Sort", insertion_sort, int_data, count);
                 break;
             case 4:
                 test_int_sort("Merge Sort", merge_sort, int_data, count);
                 break;
             case 5:
                 test_int_sort("Quick Sort", quick_sort, int_data, count);
                 break;
             case 6:
                 test_int_sort("Shell Sort", shell_sort, int_data, count);
                 break;
             case 7:
                 test_int_sort("Bubble Sort", bubble_sort, int_data, count);
                 test_int_sort("Selection Sort", selection_sort, int_data, count);
                 test_int_sort("Insertion Sort", insertion_sort, int_data, count);
                 test_int_sort("Merge Sort", merge_sort, int_data, count);
                 test_int_sort("Quick Sort", quick_sort, int_data, count);
                 test_int_sort("Shell Sort", shell_sort, int_data, count);
                 break;
         }
     } else {
         switch (algo_choice) {
             case 1:
                 test_string_sort("Bubble Sort", bubble_sort, string_data, count);
                 break;
             case 2:
                 test_string_sort("Selection Sort", selection_sort, string_data, count);
                 break;
             case 3:
                 test_string_sort("Insertion Sort", insertion_sort, string_data, count);
                 break;
             case 4:
                 test_string_sort("Merge Sort", merge_sort, string_data, count);
                 break;
             case 5:
                 test_string_sort("Quick Sort", quick_sort, string_data, count);
                 break;
             case 6:
                 test_string_sort("Shell Sort", shell_sort, string_data, count);
                 break;
             case 7:
                 test_string_sort("Bubble Sort", bubble_sort, string_data, count);
                 test_string_sort("Selection Sort", selection_sort, string_data, count);
                 test_string_sort("Insertion Sort", insertion_sort, string_data, count);
                 test_string_sort("Merge Sort", merge_sort, string_data, count);
                 test_string_sort("Quick Sort", quick_sort, string_data, count);
                 test_string_sort("Shell Sort", shell_sort, string_data, count);
                 break;
         }
     }
 }
 
 int main() {
     printf("\n=== Sorting Algorithm Performance Analysis ===\n\n");
     
     // Dataset sizes to test
     size_t test_sizes[] = {10000, 50000, 100000, 250000, 500000, 1000000, 1500000, 2000000};
     
     // Load the full datasets
     printf("Loading data files...\n");
     int *full_int_data = load_int_data("data_angka.txt", 2000000);
     char **full_string_data = load_string_data("data_kata.txt", 2000000);
     
     if (!full_int_data || !full_string_data) {
         printf("Failed to load dataset. Make sure the files exist and are readable.\n");
         
         if (full_int_data) free(full_int_data);
         if (full_string_data) free_string_array(full_string_data, 2000000);
         
         return 1;
     }
     
     printf("Data loaded successfully.\n\n");
     
     int continue_program = 1;
     
     while (continue_program) {
         // Menu for algorithm selection
         printf("\nPilih algoritma sorting:\n");
         printf("1. Bubble Sort\n");
         printf("2. Selection Sort\n");
         printf("3. Insertion Sort\n");
         printf("4. Merge Sort\n");
         printf("5. Quick Sort\n");
         printf("6. Shell Sort\n");
         printf("7. Semua Algoritma\n");
         printf("0. Keluar\n");
         printf("Pilihan Anda: ");
         
         int algo_choice;
         scanf("%d", &algo_choice);
         
         if (algo_choice == 0) {
             break;
         }
         
         if (algo_choice < 0 || algo_choice > 7) {
             printf("Pilihan tidak valid!\n");
             continue;
         }
         
         // Menu for data type selection
         printf("\nPilih jenis data:\n");
         printf("1. Data Angka\n");
         printf("2. Data Kata\n");
         printf("Pilihan Anda: ");
         
         int data_type;
         scanf("%d", &data_type);
         
         if (data_type != 1 && data_type != 2) {
             printf("Pilihan tidak valid!\n");
             continue;
         }
         
    
        // Replace the manual data size input with a menu

        // Menu for data size selection
        printf("\nPilih ukuran data yang ingin diuji:\n");
        printf("1. 10.000 elemen\n");
        printf("2. 50.000 elemen\n");
        printf("3. 100.000 elemen\n");
        printf("4. 250.000 elemen\n");
        printf("5. 500.000 elemen\n");
        printf("6. 1.000.000 elemen\n");
        printf("7. 1.500.000 elemen\n");
        printf("8. 2.000.000 elemen\n");
        printf("Pilihan Anda: ");

        int size_choice;
        scanf("%d", &size_choice);

        // Define dataset sizes
        size_t data_sizes[] = {10000, 50000, 100000, 250000, 500000, 1000000, 1500000, 2000000};

        if (size_choice < 1 || size_choice > 8) {
            printf("Pilihan tidak valid!\n");
            continue;
        }

        size_t data_size = data_sizes[size_choice - 1];

        // Warning for large datasets with inefficient algorithms
        if ((algo_choice == 1 || algo_choice == 2 || algo_choice == 3 || algo_choice == 7) && data_size > 100000) {
            printf("\nPERINGATAN: Algoritma O(n²) dengan data besar (>100000) bisa memakan waktu yang sangat lama!\n");
            printf("Lanjutkan? (1: Ya, 0: Tidak): ");
            
            int confirm;
            scanf("%d", &confirm);
            
            if (!confirm) {
                continue;
            }
        }
         
         run_specific_test(algo_choice, data_type, full_int_data, full_string_data, data_size);
         
         printf("\nIngin menjalankan program lagi? (1: Ya, 0: Tidak): ");
         scanf("%d", &continue_program);
     }
     
     // Clean up
     free(full_int_data);
     free_string_array(full_string_data, 2000000);
     
     printf("\nProgram selesai. Terima kasih!\n");
     
     return 0;
 }