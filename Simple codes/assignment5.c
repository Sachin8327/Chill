#include <stdio.h>

int main()
{
    int n, m, i, j, k;
    int alloc[10][10], max[10][10];
    int avail[10], need[10][10];
    int finish[10] = {0}, safeSeq[10];
    int count = 0, found;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum Requirement Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Calculate Need Matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Banker's Safety Algorithm
    while (count < n)
    {
        found = 0;

        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                        break;
                }

                if (j == m)
                {
                    for (k = 0; k < m; k++)
                        avail[k] += alloc[i][k];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0)
        {
            printf("\nSystem is in an UNSAFE state.\n");
            return 0;
        }
    }

    printf("\nNeed Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    printf("\nSystem is in a SAFE state.\n");
    printf("Safe Sequence: ");

    for (i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);

    printf("\n");

    return 0;
}


// Banker's Algorithm ek Deadlock Avoidance Algorithm hai.

// Iska main purpose hai:
// - System ko deadlock mein jaane se bachana.
// - Resource allocation se pehle check karna ki system safe state mein rahega ya nahi.
// - Processes ko resources safely execute karne dena.
// - Ek safe sequence find karna.
// Safe State kya hota hai?
// Agar system processes ko kisi particular order mein execute karke complete kar sakta hai aur har process ke complete hone ke baad uske resources release ho jaate hain, toh system Safe State mein hota hai.
// Unsafe State kya hota hai?
// Agar system ko koi safe sequence nahi milta, toh system Unsafe State mein hota hai.


// n stores the number of processes.
// m stores the number of resource types.
// i, j, k are loop variables.(Process index, Resource index, Resorurce index in loop)


// alloc[10][10] stores the currently allocated resources of each process.
// max[10][10] stores the maximum resource requirements of each process.
// avail[10] stores the currently available resources.
// need[10][10] stores the remaining resource requirements.


// finish[10] tracks whether a process is completed or not. Initially, all values are 0.
// safeSeq[10] stores the safe execution sequence.


// count maintains the number of completed processes.
// found checks whether any process was executed in the current iteration.
// Accept the number of processes and resource types from the user.
// Accept the Allocation Matrix, Maximum Matrix and Available Resources.
// Calculate the Need Matrix using the formula: Need = Max − Allocation.
// Use a while loop until all processes are completed.
// Initialize found = 0 at the beginning of each iteration.
// Use a for loop to check every process.

// Check finish[i] == 0 to consider only unfinished processes.

// Compare Need with Available for every resource type.
// If need[i][j] > avail[j], the process cannot execute currently, so break the inner loop.
// If j == m, all resource requirements are satisfied and the process can execute.
// Release the allocated resources using avail[k] += alloc[i][k].
// Store the completed process in safeSeq[count++].
// Mark the process completed using finish[i] = 1.
// Set found = 1 to indicate successful process execution.


// If found == 0, no process can execute and the system is declared UNSAFE.

// If all processes complete, the system is declared SAFE.
// Print the Need Matrix and Safe Sequence.
// Terminate the program using return 0.


// gcc banker.c -o banker && ./banker
// n = 5

// m = 3

// alloc = [
//     [0, 1, 0],
//     [2, 0, 0],
//     [3, 0, 2],
//     [2, 1, 1],
//     [0, 0, 2]
// ]

// max = [
//     [7, 5, 3],
//     [3, 2, 2],
//     [9, 0, 2],
//     [2, 2, 2],
//     [4, 3, 3]
// ]

// avail = [3, 3, 2]