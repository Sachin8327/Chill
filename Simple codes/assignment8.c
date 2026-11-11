#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int RQ[100], n, initial, size;
int dataEntered = 0;

void getData()
{
   int i;

   printf("Enter the number of requests: ");
   if (scanf("%d", &n) != 1 || n < 1 || n > 100)
   {
       printf("Invalid number of requests\n");
       dataEntered = 0;
       return;
   }

   printf("Enter total disk size: ");
   if (scanf("%d", &size) != 1 || size <= 0)
   {
       printf("Invalid disk size\n");
       dataEntered = 0;
       return;
   }

   printf("Enter the request sequence:\n");
   for (i = 0; i < n; i++)
   {
       if (scanf("%d", &RQ[i]) != 1 ||
           RQ[i] < 0 || RQ[i] >= size)
       {
           printf("Invalid disk request\n");
           dataEntered = 0;
           return;
       }
   }

   printf("Enter initial head position: ");
   if (scanf("%d", &initial) != 1 ||
       initial < 0 || initial >= size)
   {
       printf("Invalid initial head position\n");
       dataEntered = 0;
       return;
   }

   dataEntered = 1;
}

void sstf()
{
   int visited[100] = {0};
   int current = initial;
   int i, j, index, min, d;
   int TotalHeadMoment = 0;

   printf("\nSSTF Head Movement: %d", current);

   for (i = 0; i < n; i++)
   {
       min = INT_MAX;
       index = -1;
       for (j = 0; j < n; j++)
       {
           if (visited[j] == 0)
           {
               d = abs(RQ[j] - current);

               if (d < min)
               {
                   min = d;
                   index = j;
               }
           }
       }

       TotalHeadMoment += min;
       current = RQ[index];
       visited[index] = 1;

       printf(" -> %d", current);
   }

   printf("\nTotal head movement is %d\n",
          TotalHeadMoment);
}

void sort(int arr[])
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

void scan()
{
   int arr[100], i, index = n;
   int current = initial;
   int TotalHeadMoment = 0;

   for (i = 0; i < n; i++)
       arr[i] = RQ[i];

   sort(arr);

   for (i = 0; i < n; i++)
   {
       if (arr[i] >= initial)
       {
           index = i;
           break;
       }
   }

   printf("\nSCAN Head Movement: %d", current);

   // Move towards higher cylinder numbers
   for (i = index; i < n; i++)
   {
       TotalHeadMoment += abs(arr[i] - current);
       current = arr[i];
       printf(" -> %d", current);
   }

   // Move to last cylinder
   TotalHeadMoment += abs((size - 1) - current);
   current = size - 1;
   printf(" -> %d", current);

   // Reverse direction
   for (i = index - 1; i >= 0; i--)
   {
       TotalHeadMoment += abs(arr[i] - current);
       current = arr[i];
       printf(" -> %d", current);
   }

   printf("\nTotal head movement is %d\n",
          TotalHeadMoment);
}

void clook()
{
   int arr[100], i, index = n;
   int current = initial;
   int TotalHeadMoment = 0;

   for (i = 0; i < n; i++)
       arr[i] = RQ[i];

   sort(arr);

   for (i = 0; i < n; i++)
   {
       if (arr[i] >= initial)
       {
           index = i;
           break;
       }
   }

   printf("\nC-LOOK Head Movement: %d", current);

   // Move towards higher requests
   for (i = index; i < n; i++)
   {
       TotalHeadMoment += abs(arr[i] - current);
       current = arr[i];
       printf(" -> %d", current);
   }

   // Jump to lowest request and move upwards
   for (i = 0; i < index; i++)
   {
       TotalHeadMoment += abs(arr[i] - current);
       current = arr[i];
       printf(" -> %d", current);
   }

   printf("\nTotal head movement is %d\n",
          TotalHeadMoment);
}

int main()
{
   int choice;
   while (1)
   {
       printf("\n\nDisk Scheduling Algorithms\n");
       printf("1. Enter Data\n");
       printf("2. SSTF\n");
       printf("3. SCAN\n");
       printf("4. C-LOOK\n");
       printf("5. Exit\n");
       printf("Enter your choice: ");

       if (scanf("%d", &choice) != 1)
           return 0;
       if (choice == 1)
       {
           getData();
       }
       else if (choice >= 2 && choice <= 4)
       {
           if (!dataEntered)
           {
               printf("Please enter data first!\n");
               continue;
           }

           switch (choice)
           {
               case 2:
                   sstf();
                   break;
               case 3:
                   scan();
                   break;
               case 4:
                   clook();
                   break;
           }
       }
       else if (choice == 5)
       {
           printf("Exiting program...\n");
           return 0;
       }
       else
       {
           printf("Invalid choice!\n");
       }
   }
}





// A. Header Files
// 1. stdio.h – printf() aur scanf() ke liye.
// 2. stdlib.h – abs() function ke liye.
// 3. limits.h – INT_MAX ki value use karne ke liye.

// B. Global Variables
// 1. RQ[100] – Disk requests ko store karne ke liye array.
// 2. n – Total disk requests ki number.
// 3. initial – Disk head ki starting position.
// 4. size – Total disk size (0 se size-1 tak cylinders).
// 5. dataEntered = 0 – Check karta hai ki user ne valid data enter kiya hai ya nahi.

// C. getData() Function
// 1. int i – Loop ke liye variable.
// 2. scanf("%d", &n) != 1 – Check karta hai ki integer input mila hai ya nahi.
// 3. n < 1 || n > 100 – Check karta hai ki requests ki number valid range mein hai ya nahi.
// 4. dataEntered = 0 – Invalid input hone par data ko invalid mark karta hai.
// 5. return – Function ko wahi terminate kar deta hai.
// 6. scanf("%d", &size) – Total disk size input leta hai.
// 7. size <= 0 – Check karta hai ki disk size positive hai ya nahi.
// 8. for loop – Sabhi disk requests input leta hai.
// 9. RQ[i] < 0 || RQ[i] >= size – Check karta hai ki request disk range ke andar hai ya nahi.
// 10. scanf("%d", &initial) – Initial head position input leta hai.
// 11. initial < 0 || initial >= size – Starting position valid hai ya nahi check karta hai.
// 12. dataEntered = 1 – Saara input valid hone par data ko valid mark karta hai.

// D. SSTF (Shortest Seek Time First) Function
// 1. visited[100] = {0} – Track karta hai ki kaunsi request complete ho chuki hai; 0 = pending, 1 = completed.
// 2. current = initial – Head ki current position starting position par set karta hai.
// 3. TotalHeadMoment = 0 – Total head movement calculate karne ke liye.
// 4. printf() – Initial head position display karta hai.
// 5. for loop – Total n requests ko process karta hai.
// 6. min = INT_MAX – Minimum distance find karne ke liye initially maximum value set karta hai.
// 7. index = -1 – Nearest request ka index store karne ke liye.
// 8. Inner for loop – Sabhi unvisited requests ko check karta hai.
// 9. visited[j] == 0 – Sirf pending requests ko consider karta hai.
// 10. d = abs(RQ[j] - current) – Current head se request ki distance calculate karta hai.
// 11. if (d < min) – Check karta hai ki current distance minimum hai ya nahi.
// 12. min = d – Minimum distance update karta hai.
// 13. index = j – Nearest request ka index store karta hai.
// 14. TotalHeadMoment += min – Minimum distance ko total movement mein add karta hai.
// 15. current = RQ[index] – Head ko nearest request par move karta hai.
// 16. visited[index] = 1 – Processed request ko visited mark karta hai.
// 17. printf() – Head ki new position display karta hai.
// 18. Final printf() – Total head movement display karta hai.

// E. sort() Function
// 1. sort(int arr[]) – Disk requests ko ascending order mein sort karta hai.
// 2. Outer for loop – Array ke sabhi elements ko sort karne ke liye.
// 3. Inner for loop – Adjacent elements ko compare karta hai.
// 4. if (arr[j] > arr[j+1]) – Check karta hai ki left element right element se bada hai ya nahi.
// 5. temp = arr[j] – Left element ko temporarily store karta hai.
// 6. arr[j] = arr[j+1] – Right element ko left position par rakhta hai.
// 7. arr[j+1] = temp – Temporary value ko right position par rakhta hai.
// 8. Is process ko Bubble Sort kehte hain.

// F. SCAN Function
// 1. arr[100] – Original requests ki copy store karne ke liye.
// 2. index = n – Initially assume karta hai ki initial position se bada ya equal request nahi mila.
// 3. current = initial – Head ki starting position set karta hai.
// 4. TotalHeadMoment = 0 – Total head movement calculate karta hai.
// 5. for loop – RQ[] ki sabhi requests ko arr[] mein copy karta hai.
// 6. sort(arr) – Requests ko ascending order mein sort karta hai.
// 7. for loop – Initial head position se badi ya equal first request find karta hai.
// 8. if (arr[i] >= initial) – Starting position se badi ya equal request check karta hai.
// 9. index = i – Us request ka index store karta hai.
// 10. break – Request milne ke baad loop stop karta hai.
// 11. First for loop (i = index) – Head ko higher requests ki direction mein move karta hai.
// 12. TotalHeadMoment += abs(arr[i] - current) – Current aur next request ke beech distance add karta hai.
// 13. current = arr[i] – Head ko next request par move karta hai.
// 14. Second movement – Head ko disk ke last cylinder (size-1) tak move karta hai.
// 15. TotalHeadMoment += abs((size-1) - current) – Last cylinder tak ka movement add karta hai.
// 16. current = size-1 – Head ki position last cylinder set karta hai.
// 17. Reverse direction – Ab head higher direction se lower direction mein move karta hai.
// 18. Second for loop – Initial position se chhoti requests ko reverse order mein process karta hai.
// 19. TotalHeadMoment += abs(arr[i] - current) – Har request tak ka movement add karta hai.
// 20. current = arr[i] – Head ko next request par move karta hai.
// 21. Final printf() – Total head movement display karta hai.

// G. C-LOOK Function
// 1. arr[100] – Original requests ki copy store karne ke liye.
// 2. index = n – Initially assume karta hai ki initial position se badi ya equal request nahi mili.
// 3. current = initial – Head ki starting position set karta hai.
// 4. TotalHeadMoment = 0 – Total head movement calculate karta hai.
// 5. for loop – RQ[] ki requests ko arr[] mein copy karta hai.
// 6. sort(arr) – Requests ko ascending order mein sort karta hai.
// 7. for loop – Initial position se badi ya equal first request find karta hai.
// 8. index = i – First higher request ka index store karta hai.
// 9. break – Request milne ke baad loop stop karta hai.
// 10. First for loop – Head ko higher requests ki direction mein move karta hai.
// 11. TotalHeadMoment += abs(arr[i] - current) – Head movement calculate karke total mein add karta hai.
// 12. current = arr[i] – Head ko next request par move karta hai.
// 13. Second for loop – Highest request ke baad directly lowest request par jump karke remaining requests process karta hai.
// 14. TotalHeadMoment += abs(arr[i] - current) – Jump aur next request ka movement total mein add karta hai.
// 15. current = arr[i] – Head ko next lower request par move karta hai.
// 16. Final printf() – Total head movement display karta hai.

// H. Main Function
// 1. int choice – User ka menu choice store karta hai.
// 2. while(1) – Menu ko continuously display karta hai.
// 3. printf() – Disk Scheduling Algorithms ka menu display karta hai.
// 4. scanf("%d", &choice) != 1 – Check karta hai ki valid integer input mila hai ya nahi.
// 5. choice == 1 – User Enter Data select karta hai to getData() call hota hai.
// 6. choice >= 2 && choice <= 4 – Check karta hai ki user ne koi scheduling algorithm select kiya hai ya nahi.
// 7. if (!dataEntered) – Check karta hai ki data enter nahi hua hai ya nahi.
// 8. printf() – Data enter na hone par warning display karta hai.
// 9. continue – Current iteration skip karke menu dobara display karta hai.
// 10. switch(choice) – Selected algorithm ke according function call karta hai.
// 11. case 2 – SSTF function execute karta hai.
// 12. case 3 – SCAN function execute karta hai.
// 13. case 4 – C-LOOK function execute karta hai.
// 14. break – Switch statement se bahar nikalta hai.
// 15. choice == 5 – User Exit select karta hai.
// 16. return 0 – Program successfully terminate karta hai.
// 17. else – Invalid menu choice hone par error message display karta hai.