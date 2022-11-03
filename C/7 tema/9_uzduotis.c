#include <stdio.h>

void help_message()
{
    printf("Issue not found");
}

void exit_message()
{
    printf("Exited");
}

void showMenu(char* menuTitle, char* menuOptions[], int menuSize, char* inputMsg, void (*functionList[])())
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
    {
        (*functionList[answer - 1])();
        return;
    }

    showMenu(menuTitle, menuOptions, menuSize, inputMsg, functionList);
}

int main()
{
    char* options[256] = {"Help", "Exit"};
    void (*functions[])() = {help_message, exit_message};

    showMenu("Pasirinkimu meniu", options, 2, "Iveskite skaiciu: ", functions);

    return 0;
}
