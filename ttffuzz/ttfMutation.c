
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <fcntl.h>

int crashes = 0;

struct ORIGINAL_FILE {
    char * data;
    size_t length;
};

struct ORIGINAL_FILE get_data(char* fuzz_target) {

    FILE *fileptr;
    char *clone_data;
    long filelen;

   
    fileptr = fopen(fuzz_target, "rb");
    if (fileptr == NULL) {
        printf("[!] Unable to open fuzz target, exiting...\n");
        exit(1);
    }
    fseek(fileptr, 0, SEEK_END);
    filelen = ftell(fileptr);
    rewind(fileptr);

    
    clone_data = (char *)malloc(filelen * sizeof(char));

   
    size_t length = filelen * sizeof(char);

   
    fread(clone_data, filelen, 1, fileptr);
    fclose(fileptr);

    struct ORIGINAL_FILE original_file;
    original_file.data = clone_data;
    original_file.length = length;

    return original_file;
}

void create_new(struct ORIGINAL_FILE original_file, size_t mutations) {

 
    int* picked_indexes = (int*)malloc(sizeof(int)*mutations);
    for (int i = 0; i < (int)mutations; i++) {
        picked_indexes[i] = rand() % original_file.length;
    }

    char * mutated_data = (char*)malloc(original_file.length);
    memcpy(mutated_data, original_file.data, original_file.length);

    for (int i = 0; i < (int)mutations; i++) {
        char current = mutated_data[picked_indexes[i]];
       
        int decimal = ((int)current & 0xff);

        int bit_to_flip = rand() % 8;
        
  
        decimal ^= 1 << bit_to_flip;
        
        mutated_data[picked_indexes[i]] = (char)decimal;
    }

   
    FILE *fileptr;
    fileptr = fopen("fuzz.ttf", "wb");
    if (fileptr == NULL) {
        printf("[!] Unable to open mutated.jpeg, exiting...\n");
        exit(1);
    }
   
    fwrite(mutated_data, 1, original_file.length, fileptr);
    fclose(fileptr);
    free(mutated_data);
    free(picked_indexes);
}

void fuzz() {

    pid_t child_pid;
    int child_status;

    child_pid = fork();
    if (child_pid == 0) {
        int fd = open("/dev/null", O_WRONLY);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        close(fd);
        char *argv[] = { "/System/Applications/Font Book.app/Contents/MacOS/Font Book", "test.ttf", 0 };
        execvp(argv[0], argv);
        printf("error \n");
        exit(1);
    }
    else if(child_pid == -1)
    {  
        exit(1);
    }
    else {
    
        do {
            pid_t tpid = waitpid(child_pid, &child_status, WUNTRACED |
             WCONTINUED);
         
            if (tpid == -1) {
                printf("[!] Waitpid failed!\n");
                perror("waitpid");
            }
            if (WIFEXITED(child_status)) {
                printf("WIFEXITED: Exit Status: %d\n", WEXITSTATUS(child_status));
            } else if (WIFSIGNALED(child_status)) {
                crashes++;
                int exit_status = WTERMSIG(child_status);
                printf("Crashes: %d", crashes);
                fflush(stdout);
                char command[50];
                sprintf(command, "cp test.ttf crashes/%d.%d", rand(), 
                exit_status);
                system(command);
            } else if (WIFSTOPPED(child_status)) {
                printf("WIFSTOPPED: Exit Status: %d\n", WSTOPSIG(child_status));
            } else if (WIFCONTINUED(child_status)) {
                printf("WIFCONTINUED: Exit Status: Continued.\n");
            }
        } while (!WIFEXITED(child_status) && !WIFSIGNALED(child_status));
    }
}

int main(int argc, char** argv) {

    

   
    srand((unsigned)time(NULL));

    char* fuzz_target = argv[1];
   
       fuzz();
    
    return 0;
}
