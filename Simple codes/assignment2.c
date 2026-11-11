#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void sortArray(int arr[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int binarySearch(int arr[], int n, int key)
{
    int low = 0;
    int high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] == key)
            return mid;
        if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main()
{
    int n, i, key, result;
    printf("Enter the number of integers: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("\nParent process started\n");
    printf("Parent Process ID: %d\n", getpid());
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("Fork failed.\n");
        return 1;
    }
    // ---------------- PARENT PROCESS ----------------
    if (pid > 0)
    {
        printf("Child Process ID: %d\n\n", pid);
        printf("Parent process sorting the integers...\n");
        sortArray(arr, n);
        printf("Parent sorted array: ");
        for (i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n\n");
        printf("Parent process waiting for child process...\n");
        wait(NULL);
        printf("Child process completed.\n");
        printf("\nParent process resumed after waiting for child.\n");
        // ---------------- ZOMBIE PROCESS ----------------
        printf("\nDemonstrating Zombie State:\n");
        pid_t zombie_pid = fork();
        if (zombie_pid == 0)
        {
            printf("Child process terminated.\n");
            exit(0);
        }
        else
        {
            printf("Child process created with PID: %d\n", zombie_pid);
            sleep(2);
            printf("Parent has not called wait(), so child is in ZOMBIE state.\n");
            printf("Zombie Process ID: %d\n", zombie_pid);
            printf("Parent process calling wait()...\n");
            waitpid(zombie_pid, NULL, 0);
            printf("Zombie process removed.\n");
        }
        // ---------------- ORPHAN PROCESS ----------------
        printf("\nDemonstrating Orphan State:\n");
        pid_t orphan_pid = fork();
        if (orphan_pid == 0)
        {
            sleep(2);
            printf("Child process is now an ORPHAN.\n");
            printf("Child Process ID: %d\n", getpid());
            printf("New Parent Process ID: %d\n", getppid());
            printf("Orphan process completed.\n");
        }
        else
        {
            printf("Child process created with PID: %d\n", orphan_pid);
            printf("Parent process terminating before child.\n");
            exit(0);
        }
        printf("\nParent process completed.\n");
    }
    // ---------------- CHILD PROCESS ----------------
    else
    {
        sleep(1);
        printf("Child process started\n");
        printf("Child Process ID: %d\n", getpid());
        printf("Parent Process ID: %d\n", getppid());
        sortArray(arr, n);
        printf("\nChild process performing Binary Search\n");
        printf("Enter element to search: ");
        scanf("%d", &key);
        result = binarySearch(arr, n, key);
        if (result != -1)
            printf("Element %d found at position %d\n", key, result + 1);
        else
            printf("Element %d not found in the array.\n", key);
        printf("\nChild process completed.\n");
        exit(0);
    }
    return 0;
}



// A. Header Files
// 1. stdio.h – printf() aur scanf() ke liye.
// 2. stdlib.h – exit() function ke liye.
// 3. unistd.h – fork(), getpid(), getppid() aur sleep() ke liye.
// 4. sys/wait.h – wait() aur waitpid() functions ke liye.

// B. Variables
// 1. n – Array mein total integers ki count store karta hai.
// 2. i – Loop iteration ke liye use hota hai.
// 3. key – Binary Search mein search hone wala element.
// 4. result – Binary Search ka returned index store karta hai.
// 5. arr[n] – User ke input integers store karta hai.

// C. Taking Input
// 1. scanf("%d", &n) – User se array ka size leta hai.
// 2. if(n <= 0) – Invalid array size check karta hai.
// 3. int arr[n] – Given size ka array create karta hai.
// 4. for loop – User se array ke saare elements input leta hai.

// D. Parent Process Creation
// 1. getpid() – Current parent process ki ID return karta hai.
// 2. pid_t pid = fork() – Ek new child process create karta hai.
// 3. pid < 0 – Process creation fail hone ko indicate karta hai.
// 4. pid > 0 – Parent process ko indicate karta hai.
// 5. pid == 0 – Child process ko indicate karta hai.

// E. Parent Process
// 1. printf() – Child process ki PID display karta hai.
// 2. sortArray(arr, n) – Parent process array ko ascending order mein sort karta hai.
// 3. for loop – Sorted array ke saare elements display karta hai.
// 4. wait(NULL) – Parent kisi child process ke terminate hone ka wait karta hai.
// 5. printf() – Child completion ke baad parent resumed message display karta hai.

// F. Zombie Process
// 1. pid_t zombie_pid = fork() – Zombie demonstration ke liye new child create karta hai.
// 2. zombie_pid == 0 – Child process wala block execute hota hai.
// 3. printf() – Child termination message display karta hai.
// 4. exit(0) – Child process terminate ho jata hai.
// 5. zombie_pid > 0 – Parent process wala block execute hota hai.
// 6. sleep(2) – Parent 2 seconds ke liye wait karta hai.
// 7. Child terminate hone ke baad wait na hone par zombie state mein reh sakta hai.
// 8. waitpid(zombie_pid, NULL, 0) – Specific child ka exit status collect karta hai aur zombie entry remove karta hai.

// G. Orphan Process
// 1. pid_t orphan_pid = fork() – Orphan demonstration ke liye new child create karta hai.
// 2. orphan_pid == 0 – Child process wala block execute hota hai.
// 3. sleep(2) – Child 2 seconds ke liye wait karta hai.
// 4. getpid() – Child ki current process ID display karta hai.
// 5. getppid() – Child ke current parent ki process ID display karta hai.
// 6. exit(0) – Child process terminate ho jata hai.
// 7. orphan_pid > 0 – Parent process wala block execute hota hai.
// 8. exit(0) – Parent child se pehle terminate ho jata hai.
// 9. Parent terminate hone ke baad child orphan process ban jata hai.

// H. Child Process – Binary Search
// 1. sleep(1) – Child process 1 second ke liye wait karta hai.
// 2. getpid() – Child process ki ID display karta hai.
// 3. getppid() – Parent process ki ID display karta hai.
// 4. sortArray(arr, n) – Child process apne array ko sort karta hai.
// 5. scanf() – User se search element input leta hai.
// 6. binarySearch(arr, n, key) – Sorted array mein element search karta hai.
// 7. result != -1 – Element found hone ko indicate karta hai.
// 8. result == -1 – Element not found hone ko indicate karta hai.
// 9. result + 1 – Array ka position 1-based indexing mein display karta hai.
// 10. exit(0) – Child process successfully terminate karta hai.

// I. Main Function Completion
// 1. return 0 – Main process successfully terminate hota hai.

// Parent process started
// Parent Process ID: 1234
// Child Process ID: 1235

// Parent process sorting the integers...
// Parent sorted array: 10 20 30 40 50

// Parent process waiting for child process...

// Child process started
// Child Process ID: 1235
// Parent Process ID: 1234

// Child process performing Binary Search
// Enter element to search: 30

// Element 30 found at position 3

// Child process completed.

// Child process completed.
// Parent process resumed after waiting for child.

// Demonstrating Zombie State:
// Child process created with PID: 1236
// Child process terminated.
// Parent has not called wait(), so child may be in ZOMBIE state.
// Zombie Process ID: 1236
// Parent process calling wait()...
// Zombie process removed.

// Demonstrating Orphan State:
// Child process created with PID: 1237
// Parent process terminating before child.
// Child process is now an ORPHAN.
// Child Process ID: 1237
// New Parent Process ID: 1
// Orphan process completed.