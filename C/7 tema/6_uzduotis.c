#include <stdio.h>

int showMenu(char* menuTitle, char* menuOptions[], int menuSize, char* inputMsg)
{
    printf("%s\n", menuTitle);

    for(int i = 0; i < menuSize; ++i)
        printf("%d - %s\n", i + 1, menuOptions[i]);

    printf("%s", inputMsg);


    int answer;
    scanf("%d", &answer);

    if(getchar() != '\n')
    {
        scanf("%*[^\n]");
        scanf("%*c");
    }

    else if(answer >= 1 && answer <= menuSize)
        return answer - 1;


    showMenu(menuTitle, menuOptions, menuSize, inputMsg);
}

int main()
{
    char* options[256] = {"Help", "Exit"};

    showMenu("Pasirinkimu meniu", options, 2, "Iveskite skaiciu: ");

    return 0;
}
