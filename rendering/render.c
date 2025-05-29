#include "../header.h"

int main()
{
    int i = 0;
    char c = 'a';

    while (i < 10)
    {
        write(1, &c, 1);
        write(1, "\n", 1);
        // now lets move the cursor to return next to a again
        write(1, "\033[1A", 4); // Move cursor up one line
        int j = 0;
         // Move cursor up one line
         while(j < i)
         {
            write(1, "\033[1C", 4);
            j++;
         }
         i++;
    }
    

    // printf("\033[42m\033[31m\033[1;3mWelcome\033[0m to \033[32mThe Rendering engine!!\033[0m\n");
}