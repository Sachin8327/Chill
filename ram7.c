// gcc 7_pipes.c -o pipes   then   ./pipes
// Pipe p1: parent -> child (file name)
// Pipe p2: child -> parent (file contents)
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int p1[2], p2[2], n;
    char fname[100], buf[1000];
    FILE *fp;

    pipe(p1);
    pipe(p2);

    if (fork() > 0)                // parent
    {
        close(p1[0]);              // parent only writes on p1
        close(p2[1]);              // parent only reads on p2

        printf("Enter file name: ");
        scanf("%s", fname);
        write(p1[1], fname, strlen(fname) + 1);

        read(p2[0], buf, sizeof(buf));
        printf("\nContents of file:\n%s\n", buf);
        wait(NULL);
    }
    else                           // child
    {
        close(p1[1]);              // child only reads on p1
        close(p2[0]);              // child only writes on p2

        read(p1[0], fname, sizeof(fname));

        fp = fopen(fname, "r");
        if (fp == NULL)
            strcpy(buf, "File not found");
        else
        {
            n = fread(buf, 1, sizeof(buf) - 1, fp);
            buf[n] = '\0';
            fclose(fp);
        }
        write(p2[1], buf, strlen(buf) + 1);
    }
    return 0;
}

// H. Program Execution
// 1. File ka naam 7_pipes.c se save karo.
// 2. Terminal open karo aur us directory mein jao jahan file saved hai.
// 3. Compile command:
//    gcc 7_pipes.c -o pipes
// 4. Program execute karne ke liye:
//    ./pipes
// 5. Program "Enter file name:" input maangega.
// 6. File ka naam enter karo, jaise: abc.txt
// 7. Parent process file name child process ko send karega.
// 8. Child process file open karke uska content read karega.
// 9. Child process file content parent ko send karega.
// 10. Parent process received file content display karega.

// I. Sample Input
// Enter file name: abc.txt

// J. Sample Output
// Contents of file:
// Hello World
// This is a pipe communication program.

// K. Important Points
// 1. abc.txt file program ki same directory mein honi chahiye.
// 2. File pehle se exist honi chahiye.
// 3. Agar file exist nahi karti hai, toh "File not found" display hoga.
// 4. p1 parent-to-child communication ke liye use hota hai.
// 5. p2 child-to-parent communication ke liye use hota hai.
