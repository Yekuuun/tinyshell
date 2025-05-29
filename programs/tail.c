/**
 * A base & custom implementation of a minimalist tail program.
 * Author : Yekuuun 
 * Github : https://github.com/Yekuuun
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <sys/stat.h>
 #include <string.h>
 
 #define EXIT_SUCCESS 0
 #define EXIT_FAILURE 1
 #define MAX_TAIL_BYTES_READ 4096
 
 typedef struct tail_flags {
     int c_flag;
     int n_flag;
     int c_value;
     int n_value;
 } tail_flags;
 
 int optopt, optind;
 char *optarg;
 
 /**
  * Helper function.
  */
 static void help(){
     printf("[*] Usage : tail [OPTION]... [FILE]...\n");
     printf("    -c NUM   output the last NUM bytes\n");
     printf("    -n NUM   output the last NUM lines\n");
     printf("    -h       show this help\n");
 }
 /**
  * Check if a path to a file is valid.
  * @param path => path to a given file.
  */
 static int is_valid_file(const char *path){
     struct stat path_stat;
     if(stat(path, &path_stat) != 0)
         return 0;
 
     return S_ISREG(path_stat.st_mode);
 }
 
 /**
  * Main tail function. 
  * @param file  => path to file 
  * @param flags => ptr to flags for tail management.
  */
 static int tail(const char *file, tail_flags *flags){
     char buffer[MAX_TAIL_BYTES_READ] = {0};
     char ch;
     int count = 0;
     int lines = 0;
     long pos  = 0;
 
     FILE *file_ptr = NULL;
 
     file_ptr = fopen(file, "r");
     if(!file_ptr){
         printf("[!] Error opening file : %s\n", file);
         return 1;
     }
 
     if(fseek(file_ptr, 0, SEEK_END) != 0)
         return 1;
 
     pos = ftell(file_ptr);
 
     if(pos <= 0)
         goto __END;
 
     while(pos > 0 && count < MAX_TAIL_BYTES_READ){
         pos--;
         if (fseek(file_ptr, pos, SEEK_SET) != 0)
             return 1;
 
         ch = fgetc(file_ptr);
         if (ch == EOF) 
             break;
 
         if (ch == '\n')
             lines++;
 
         if(flags->c_flag == 1 && count >= flags->c_value)
             break;
 
         if(flags->n_flag == 1 && lines == flags->n_value + 1)
             break;
 
         buffer[count++] = ch;
     }
 
     //printing buffer
     for(int i = count -1; i >= 0; i--)
         putchar(buffer[i]);
 
     printf("\n");
 
 __END:
     if(file_ptr)
         fclose(file_ptr);
         
     return 0;
 }
 
 int main(int argc, char **argv){
     const char *file = NULL;
     int state = 0;
     int opt;
 
     if(argc < 2){
         printf("[!] Usage : tail [OPTION]... [FILE]... try --help for more informations.\n");
         return EXIT_FAILURE;
     }
 
     if(strcmp(argv[1], "--help") == 0){
         help();
         return EXIT_SUCCESS;
     }
 
     tail_flags *flags = (tail_flags*)calloc(1, sizeof(tail_flags));
     if(!flags)
         return EXIT_FAILURE;
     
     //parsing arguments.
     while((opt = getopt(argc, argv, "c:n:h")) != -1){
         switch(opt){
             case 'c':
                 flags->c_flag  = 1;
                 flags->c_value = atoi(optarg);
                 break;
             case 'n':
                 flags->n_flag  = 1;
                 flags->n_value = atoi(optarg);
                 break;
             case 'h':
                 help();
                 goto __CLEANUP;
             case '?':
                 help();
                 state = 1; goto __CLEANUP;
             default:
                 state = 1; goto __CLEANUP;
         }
     }
 
     //checking c & n flags.
     if(flags->c_flag && flags->n_flag){
         printf("[!] Cannot use -n & -c at the same time. \n");
         state = 1; goto __CLEANUP;
     }
 
     //file path.
     if (optind >= argc) {
         help();
         state = 1; goto __CLEANUP;
     }
     
     file = argv[optind];
     if(!is_valid_file(file)){
         printf("[!] %s is not a valid file path.\n", file);
         state = 1; goto __CLEANUP;
     }
 
     if(access(file, R_OK) != 0){
         printf("[!] No access to file %s\n", file);
         state = 1; goto __CLEANUP;
     }
         
     //calling main business logic.
     state = tail(file, flags);
 
 __CLEANUP:
     if(flags)
         free(flags);
 
     return state;
 }