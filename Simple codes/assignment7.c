#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd1[2], fd2[2], n;
    char filename[100], buffer[100];

    if (argc != 2) {
        printf("Usage: ./a.out filename\n");
        return 1;
    }

    pipe(fd1);  // Parent to Child
    pipe(fd2);  // Child to Parent

    pid_t p = fork();    

    if (p > 0)
    {
        // Parent Process

        close(fd1[0]);
        close(fd2[1]);

        write(fd1[1], argv[1], 100);
        close(fd1[1]);

        wait(NULL);

        printf("File Content:\n");

        while ((n = read(fd2[0], buffer, 100)) > 0) {
            write(1, buffer, n);
        }

        close(fd2[0]);
    }
    else if (p == 0)
    {
        // Child Process

        close(fd1[1]);
        close(fd2[0]);

        read(fd1[0], filename, 100);
        close(fd1[0]);

        FILE *fp = fopen(filename, "r");

        if (fp == NULL) {
            perror("File not found");
            exit(1);
        }

        while ((n = fread(buffer, 1, 100, fp)) > 0) {
            write(fd2[1], buffer, n);
        }

        fclose(fp);
        close(fd2[1]);
    }

    return 0;
}





// A. Header Files
// 1. stdio.h – printf(), perror() aur FILE ke liye.
// 2. unistd.h – pipe(), fork(), read(), write() aur close() ke liye.
// 3. sys/types.h – pid_t data type ke liye.
// 4. sys/wait.h – wait() function ke liye.
// 5. stdlib.h – exit() function ke liye.

// B. Command Line Arguments
// 1. argc – Total command line arguments ki count store karta hai.
// 2. argv[] – Command line arguments store karta hai.
// 3. argv[1] – User se diya gaya filename store karta hai.

// C. Global / Main Variables
// 1. fd1[2] – Parent se Child ko filename send karne ke liye pipe.
// 2. fd2[2] – Child se Parent ko file content send karne ke liye pipe.
// 3. n – read() aur fread() se read hue bytes ki count store karta hai.
// 4. filename[100] – File ka naam store karta hai.
// 5. buffer[100] – File ka content temporarily store karta hai.

// D. Main Function
// 1. argc != 2 – Check karta hai ki user ne filename provide kiya hai ya nahi.
// 2. pipe(fd1) – Parent to Child communication ke liye first pipe create karta hai.
// 3. pipe(fd2) – Child to Parent communication ke liye second pipe create karta hai.
// 4. fork() – New Child process create karta hai.
// 5. p > 0 – Parent process execute karta hai.
// 6. p == 0 – Child process execute karta hai.

// E. Parent Process
// 1. close(fd1[0]) – fd1 ka read end close karta hai, kyunki Parent sirf data send karega.
// 2. close(fd2[1]) – fd2 ka write end close karta hai, kyunki Parent sirf data receive karega.
// 3. write(fd1[1], argv[1], 100) – Filename Child ko send karta hai.
// 4. close(fd1[1]) – fd1 ka write end close karta hai.
// 5. wait(NULL) – Child process ke terminate hone ka wait karta hai.
// 6. printf() – File Content heading display karta hai.
// 7. read(fd2[0], buffer, 100) – Child se maximum 100 bytes receive karta hai.
// 8. write(1, buffer, n) – Received file content screen par print karta hai.
// 9. while loop – Jab tak data receive hota hai, tab tak execute hota hai.
// 10. close(fd2[0]) – fd2 ka read end close karta hai.

// F. Child Process
// 1. close(fd1[1]) – fd1 ka write end close karta hai, kyunki Child sirf data receive karega.
// 2. close(fd2[0]) – fd2 ka read end close karta hai, kyunki Child sirf data send karega.
// 3. read(fd1[0], filename, 100) – Parent se filename receive karta hai.
// 4. close(fd1[0]) – fd1 ka read end close karta hai.
// 5. fopen(filename, "r") – File ko read mode mein open karta hai.
// 6. fp == NULL – Check karta hai ki file successfully open hui hai ya nahi.
// 7. perror() – File open nahi hone par error message display karta hai.
// 8. exit(1) – Error aane par Child process terminate karta hai.
// 9. fread(buffer, 1, 100, fp) – File se maximum 100 bytes read karta hai.
// 10. write(fd2[1], buffer, n) – File content Parent ko send karta hai.
// 11. while loop – Jab tak file mein data available hai, tab tak execute hota hai.
// 12. fclose(fp) – Open file close karta hai.
// 13. close(fd2[1]) – fd2 ka write end close karta hai.

// G. Important Functions
// 1. pipe() – Do processes ke beech communication channel create karta hai.
// 2. fork() – Child process create karta hai.
// 3. read() – Pipe se data receive karta hai.
// 4. write() – Pipe mein data send karta hai.
// 5. close() – File descriptor close karta hai.
// 6. wait(NULL) – Parent ko Child process ke finish hone tak wait karata hai.
// 7. fopen() – File open karta hai.
// 8. fread() – File se data read karta hai.
// 9. fclose() – File close karta hai.
// 10. exit(1) – Error condition mein process terminate karta hai.
// 11. pid_t – Process ID store karne ke liye data type.
// 12. fd[0] – Pipe ka Read end.
// 13. fd[1] – Pipe ka Write end.
// 14. 1 – Standard Output (Screen).


// H. How to Run the Program
// 1. Save the program as pipe.c
// 2. Create a file named test.txt.
// 3. Write some content inside test.txt.
// 4. Open terminal in the same directory.
// 5. Compile the program using:
//    gcc pipe.c -o pipe
// 6. Run the program using:
//    ./pipe test.txt
// 7. Parent process filename Child ko send karega.
// 8. Child file read karke content Parent ko send karega.
// 9. Parent file content screen par display karega.