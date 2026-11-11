// reader
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

#define FIFO_PIPE "xyz"

int main()
{
    int fd,i,c=0,w=0,l=0;
    char str[200];

    fd = open(FIFO_PIPE,O_RDONLY);
    read(fd,str,sizeof(str)-1);
    str[sizeof(str)-1] = '\0';

    for(i=0;str[i]!='\0';i++)
    {
        if(str[i] == ' ' || str[i] == '\n')
            w++;

        if(str[i] == '\n')
            l++;

        c++;
    }

    printf("\nNo of characters = %d",c);
    printf("\nNo of lines = %d",l+1);
    printf("\nNo of words = %d\n",w+1);

    close(fd);
    return 0;
}

// writer
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

#define FIFO_PIPE "xyz"

int main()
{
    int fd,i=0;
    char str[200],ch;

    mkfifo(FIFO_PIPE,0644);

    printf("\nPipe Successfully created\n");
    printf("\nEnter your message (press @ to terminate)\n");

    while((ch = fgetc(stdin)) != '@' && i < 198)
    {
        str[i++] = ch;
    }

    str[i] = '\0';

    fd = open(FIFO_PIPE,O_WRONLY);
    write(fd,str,strlen(str));

    close(fd);

    return 0;
}



// A. Header Files

// 1. stdio.h – printf(), fgetc() aur stdin ke liye.
// 2. string.h – strlen() function ke liye.
// 3. fcntl.h – open() aur O_RDONLY/O_WRONLY ke liye.
// 4. unistd.h – read(), write() aur close() ke liye.
// 5. sys/types.h – System data types ke liye.
// 6. sys/stat.h – mkfifo() function ke liye.


// B. Macro

// 1. FIFO_PIPE "xyz" – Named Pipe ka naam define karta hai.
//    Writer aur Reader dono same pipe name use karte hain.


// C. Writer Program

// 1. int fd, i=0 – fd pipe ka file descriptor aur i string ka index hai.
// 2. char str[200], ch – str message store karta hai aur ch ek character store karta hai.
// 3. mkfifo(FIFO_PIPE,0644) – "xyz" naam ka named pipe create karta hai.
// 4. printf() – User ko message enter karne ke liye bolta hai.
// 5. fgetc(stdin) – Keyboard se ek character read karta hai.
// 6. while loop – Jab tak user '@' enter nahi karta, input leta rehta hai.
// 7. str[i++] = ch – Entered character ko string mein store karta hai.
// 8. str[i] = '\0' – String ke end mein null character add karta hai.
// 9. open(FIFO_PIPE,O_WRONLY) – FIFO ko write-only mode mein open karta hai.
// 10. write(fd,str,strlen(str)) – Complete message FIFO pipe mein send karta hai.
// 11. close(fd) – FIFO pipe close karta hai.
// 12. return 0 – Writer program successfully terminate karta hai.


// D. Reader Program

// 1. int fd – FIFO ka file descriptor store karta hai.
// 2. int i,c=0,w=0,l=0 – i loop index, c characters, w words aur l lines count karta hai.
// 3. char str[100] – Writer se received message store karta hai.
// 4. open(FIFO_PIPE,O_RDONLY) – FIFO ko read-only mode mein open karta hai.
// 5. read(fd,str,sizeof(str)) – FIFO se message read karke str mein store karta hai.
// 6. for loop – String ke har character ko check karta hai.
// 7. if(str[i]==' ' || str[i]=='\n') – Space ya newline milne par word counter increment karta hai.
// 8. if(str[i]=='\n') – Newline milne par line counter increment karta hai.
// 9. c++ – Har character ke liye character counter increment karta hai.
// 10. printf() – Total characters display karta hai.
// 11. printf() – Total lines display karta hai (l+1).
// 12. printf() – Total words display karta hai.
// 13. close(fd) – FIFO pipe close karta hai.
// 14. return 0 – Reader program successfully terminate karta hai.


// E. Important Working

// 1. Writer – User se message input leta hai.
// 2. FIFO – Writer ka message Reader tak transfer karta hai.
// 3. Reader – Message receive karta hai.
// 4. Counting – Reader characters, words aur lines count karta hai.
// 5. @ – User ke input ko terminate karta hai.


