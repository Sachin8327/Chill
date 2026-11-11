#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int copy_data(FILE *source, FILE *destination)
{
    char buffer[4096];
    size_t n;

    while ((n = fread(buffer, 1, sizeof buffer, source)) > 0) {
        if (fwrite(buffer, 1, n, destination) != n)
            return -1;
    }

    if (ferror(source))
        return -1;

    return fflush(destination);
}

int main(int argc, char *argv[])
{
    int request[2], response[2], status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    if (pipe(request) == -1 || pipe(response) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t child = fork();

    if (child == -1) {
        perror("fork");
        return 1;
    }

    if (child == 0) {
        close(request[1]);
        close(response[0]);

        FILE *input = fdopen(request[0], "r");
        FILE *output = fdopen(response[1], "w");

        if (input == NULL || output == NULL) {
            perror("fdopen");
            return 1;
        }

        char *pathname = NULL;
        size_t capacity = 0;

        if (getdelim(&pathname, &capacity, '\0', input) == -1) {
            fprintf(stderr, "Could not read the pathname\n");
            free(pathname);
            return 1;
        }

        fclose(input);

        FILE *file = fopen(pathname, "rb");
        if (file == NULL) {
            perror(pathname);
            free(pathname);
            return 1;
        }

        free(pathname);

        int result = copy_data(file, output);
        if (result == -1)
            perror("Copying file");

        fclose(file);
        fclose(output);
        return result == -1;
    }

    close(request[0]);
    close(response[1]);

    if (dprintf(request[1], "%s%c", argv[1], '\0') < 0) {
        perror("Sending pathname");
        return 1;
    }

    close(request[1]);

    FILE *input = fdopen(response[0], "r");
    if (input == NULL) {
        perror("fdopen");
        return 1;
    }

    int result = copy_data(input, stdout);
    if (result == -1)
        perror("Displaying file");

    fclose(input);

    if (waitpid(child, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }

    return result == -1 || !WIFEXITED(status) || WEXITSTATUS(status) != 0;
}

// A. Header Files
// 1. stdio.h – printf(), fprintf(), FILE, fopen(), fread() aur fwrite() ke liye.
// 2. stdlib.h – malloc/free aur general utility functions ke liye.
// 3. sys/wait.h – Child process ka wait karne ke liye.
// 4. unistd.h – pipe(), fork() aur close() ke liye.

// B. Copy Data Function
// 1. copy_data() – Source se data read karke destination mein write karta hai.
// 2. buffer[4096] – Data temporarily store karne ke liye 4096 bytes ka buffer.
// 3. fread() – Source se data read karta hai.
// 4. fwrite() – Read kiya hua data destination mein write karta hai.
// 5. ferror() – Source mein reading error check karta hai.
// 6. fflush() – Destination ka buffered data immediately flush karta hai.

// C. Main Function – Variables
// 1. argc – Command-line arguments ki total count store karta hai.
// 2. argv[] – Command-line arguments ki values store karta hai.
// 3. request[2] – Parent se Child ko filename send karne ke liye pipe.
// 4. response[2] – Child se Parent ko file content send karne ke liye pipe.
// 5. status – Child process ka exit status store karta hai.

// D. Argument Checking
// 1. argc != 2 – Check karta hai ki filename diya gaya hai ya nahi.
// 2. fprintf() – Galat arguments hone par usage message display karta hai.

// E. Pipe Creation
// 1. pipe(request) – Parent aur Child ke beech filename send karne ke liye pipe create karta hai.
// 2. pipe(response) – File content receive karne ke liye second pipe create karta hai.
// 3. pipe() == -1 – Pipe creation failure check karta hai.

// F. Process Creation
// 1. fork() – New Child process create karta hai.
// 2. child == -1 – Fork failure check karta hai.
// 3. child == 0 – Child process execute hota hai.
// 4. child > 0 – Parent process execute hota hai.

// G. Child Process
// 1. close(request[1]) – Request pipe ka unused write end close karta hai.
// 2. close(response[0]) – Response pipe ka unused read end close karta hai.
// 3. fdopen(request[0], "r") – Request pipe ko reading stream mein convert karta hai.
// 4. fdopen(response[1], "w") – Response pipe ko writing stream mein convert karta hai.
// 5. pathname = NULL – Filename store karne ke liye pointer initialize karta hai.
// 6. capacity = 0 – Filename ke liye allocated memory capacity initialize karta hai.
// 7. getdelim() – Request pipe se NULL character tak filename read karta hai.
// 8. fclose(input) – Request pipe ka input stream close karta hai.
// 9. fopen(pathname, "rb") – Received filename ki file read-binary mode mein open karta hai.
// 10. free(pathname) – Filename ke liye allocated memory free karta hai.
// 11. copy_data(file, output) – File ka content response pipe mein send karta hai.
// 12. perror() – Copying mein error hone par error message display karta hai.
// 13. fclose(file) – Opened file close karta hai.
// 14. fclose(output) – Response pipe ka output stream close karta hai.
// 15. return result == -1 – Error hone par Child failure return karta hai.

// H. Parent Process
// 1. close(request[0]) – Request pipe ka unused read end close karta hai.
// 2. close(response[1]) – Response pipe ka unused write end close karta hai.
// 3. dprintf() – Request pipe ke through Child ko filename send karta hai.
// 4. argv[1] – Command-line se diya gaya filename access karta hai.
// 5. '\0' – Filename ke end ko indicate karta hai.
// 6. close(request[1]) – Filename send karne ke baad request pipe close karta hai.
// 7. fdopen(response[0], "r") – Response pipe ko reading stream mein convert karta hai.
// 8. copy_data(input, stdout) – Child se received file content screen par display karta hai.
// 9. perror() – Displaying mein error hone par error message show karta hai.
// 10. fclose(input) – Response pipe ka input stream close karta hai.

// I. Child Process Synchronization
// 1. waitpid(child, &status, 0) – Parent ko Child process complete hone tak wait karata hai.
// 2. WIFEXITED(status) – Check karta hai ki Child normally terminate hua ya nahi.
// 3. WEXITSTATUS(status) – Child ka exit status check karta hai.
// 4. return 1 – Error hone par program failure return karta hai.
// 5. return 0 – Program successfully complete hone par 0 return karta hai.