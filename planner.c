#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <direct.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <windows.h>
#include <time.h>

int remove_directory(const char *path)
{
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    char searchPath[MAX_PATH];

    // Create a search path for all files and subdirectories
    snprintf(searchPath, sizeof(searchPath), "%s\\*", path);

    // Start finding the first file/directory
    hFind = FindFirstFile(searchPath, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        // No files or directories found
        return RemoveDirectory(path) != 0 ? 0 : -1;
    }

    do
    {
        // Skip "." and ".." directories
        if (strcmp(findFileData.cFileName, ".") != 0 &&
            strcmp(findFileData.cFileName, "..") != 0)
        {
            // Create the full path to the file/directory
            char filePath[MAX_PATH];
            snprintf(filePath, sizeof(filePath), "%s\\%s", path, findFileData.cFileName);

            // Recursively remove subdirectories and files
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if (remove_directory(filePath) != 0)
                {
                    FindClose(hFind);
                    return -1;
                }
            }
            else
            {
                if (remove(filePath) != 0)
                {
                    FindClose(hFind);
                    return -1;
                }
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);

    // Remove the empty directory
    return RemoveDirectory(path) != 0 ? 0 : -1;
}
typedef struct node
{
    char *name;
    char *priority;
    int year;
    int month;
    int day;
    struct node *next;
} task;

int input(int *n, int i);
void sinput(char *array, int n);
int sign_up();
int log_in();
int making_boards_and_lists();
int view(int *s, char buffer[100]);
void free2DArray(char **arr, int rows);
int Delete();
int add_task(task *head);
int tprint();
int delete_task(char buffer[1024]);
int EDIT();
int sort();
void reminder();

int main()
{
    // system("color 70");
    task *head;
    head = malloc(sizeof(task));
    char x;
    char buffer[100];
    char dum[1024];
    char *buffer2;
    buffer2 = malloc(sizeof(char));
    char *buffer3;
    buffer3 = malloc(sizeof(char));
    printf("are you already have an account?\nif yes press 1, and if no\npress 2 and make an account :) ");
    while (1)
    {
        x = getch();
        if (x == 50)
        {
            while (1)
            {
                if (sign_up() == 0)
                {
                    break;
                }
                system("cls");
                printf("This acount exist! please try another name...\n");
            }
            break;
        }
        if (x == 49)
        {
            while (1)
            {
                if (log_in() == 0)
                {
                    break;
                }
                system("cls");
                printf("there is no such an account");
            }
            break;
        }
        printf("\nyou entered wrong key, please try again ~>");
    }

    while (1)
    {
        reminder();
        printf("1. view Boards\n2. Create New Boards\n3. Delete Board\n");

        int c = getch();
        int s;
        system("cls");
        switch (c)
        {
        case '1':
        {
            printf("Available Boards: \n");
            view(&s, buffer);
            system("cls");
            if (s == 1)
            {
                system("cls");
                printf("THERE IS NO BOARD!");
                Sleep(1000);
                system("cls");
                s = 0;
                break;
            }
            int z;
            strcpy(buffer3, buffer);
            while (1)
            {
                printf("Board: <%s> \n", buffer3);
                printf("1. View List\n2. Create New list\n3. Delete List\n4. Go Back\n");
                int x = getch();
                system("cls");
                switch (x)
                {
                case '1':
                {
                    printf(" Lists in <%s> Board:", buffer3);
                    view(&s, buffer);
                    system("cls");
                    if (s == 1)
                    {
                        system("cls");
                        printf("THERE IS NO LIST!");
                        Sleep(1000);
                        system("cls");
                        s = 0;
                        continue;
                    }
                    strcpy(buffer2, buffer);
                    while (1)
                    {
                        printf("List: <%s>\n\nTASKS:", buffer);
                        tprint();
                        printf("\n\nOptions:\n1. Add Task\n2. Edit Task\n3. Delete Task\n4. Move Task To Another List\n5. Sort Tasks\n6. GO BACK");
                        int p = 0;
                        int t = getch();
                        system("cls");
                        switch (t)
                        {
                        case '1':
                        {
                            fflush(stdin);
                            add_task(head);
                        }
                            continue;
                        case '2':
                        {
                            fflush(stdout);
                            EDIT();
                            continue;
                        }
                        case '3':
                        {
                            printf("Delete Task:\n\nWhich Task Do You Want To Delete?\n");
                            delete_task(dum);
                            continue;
                        }
                        case '4':
                        {
                            printf("Move Task To Another List:\n\nWhich Task Do You Want To Move?\n");
                            delete_task(dum);
                            chdir("..");
                            printf("Which List Would You Like To Move The Task To?\n");
                            view(&s, buffer);
                            system("cls");
                            FILE *new = fopen("task.csv", "a");
                            fprintf(new, "%s", dum);
                            fclose(new);
                            continue;
                        }
                        case '5':
                        {
                            sort();
                            continue;
                        }
                        case '6':
                        {
                            p++;
                            chdir("..");
                        }
                        default:
                            break;
                        }
                        if (p == 1)
                        {
                            break;
                        }
                    }
                    continue;
                }
                case '2':
                {
                    fflush(stdin);
                    system("cls");
                    printf("Add New List to <%s>:\n", buffer);
                    printf("What's the name of the new List? ");
                    making_boards_and_lists();
                    continue;
                }
                case '3':
                {
                    fflush(stdin);
                    printf("Delete list from <%s>:\n", buffer);
                    printf("Which List Do you want to Delete?\n");
                    Delete();
                    continue;
                }
                case '4':
                {
                    z = 1;
                    system("cls");
                    chdir("..");
                }
                default:
                    break;
                }
                if (z)
                {
                    break;
                }
                system("cls");
            }
            z = 0;
            break;
        }
        case '2':
        {
            fflush(stdin);
            printf("whats the name of the new Board?");
            making_boards_and_lists();
            break;
        }
        case '3':
        {
            fflush(stdin);
            Delete();
        }
        default:
            break;
        }
        system("cls");
    }
    free(buffer2);
    free(buffer3);
    return 0;
}

int sign_up()
{
    char username[100];
    char passkey[100];
    printf("\nplease enter your username:\n");
    sinput(username, 100);
    if (mkdir(username) == 0)
    {
        printf("hello <%s> now make sure you have a strong password :)\n", username);
    }
    else
    {
        return -1;
    }
    if (chdir(username) != 0)
    {
        perror("Error changing directory");
        return 1;
    }

    printf("Please enter your password :\n");
    sinput(passkey, 100);
    FILE *password = fopen("password.csv", "wb");

    if (password == NULL)
    {
        perror("Error creating file");
        return 1;
    }
    fprintf(password, "%s", passkey);
    fclose(password);
    system("cls");
    return 0;
}

int log_in()
{

    char username[100];
    char passkey[100];
    char filepath[200];
    char *key = NULL;
    FILE *password;
    while (1)
    {
        printf("\nplease enter your username:\n");
        sinput(username, 100);
        if (chdir(username) != 0)
        {
            printf("there is no such an account");
            return 1;
        }
        else
        {
            printf("hello <%s>, Im so happy to see you :)\n", username);
            break;
        }
    }
    snprintf(filepath, sizeof(filepath), "password.csv");

    password = fopen(filepath, "r");
    if (password == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    fseek(password, 0, SEEK_END);
    long length = ftell(password);
    fseek(password, 0, SEEK_SET);

    key = (char *)malloc(length + 1); // +1 for null-termination
    if (key == NULL)
    {
        perror("Memory allocation error");
        fclose(password);
        return 1;
    }

    fread(key, 1, length, password);
    key[length] = '\0'; // Ensure null-termination
    while (1)
    {
        printf("%s Please enter your password:\n", username);
        fgets(passkey, 100, stdin);
        int num = strlen(passkey);
        if (passkey[num - 1] == '\n')
        {
            passkey[num - 1] = '\0';
        }
        system("cls");

        int u = strcmp(key, passkey);
        if (u == 0)
        {
            printf("Welcome, %s!\n", username);
            break;
        }
        else
        {
            printf("Incorrect password.\n");
        }
    }

    free(key);
    fclose(password);
    return 0;
}

int making_boards_and_lists()
{
    char name[100];
    char filepath[200];
    sinput(name, 100);
    if (mkdir(name) == 0)
    {
        printf("%s sucsessfuly added!", name);
        Sleep(1000);
        system("cls");
    }
    else
    {
        printf("already excist.\n");
        Sleep(1000);
        return 0;
    }
    snprintf(filepath, sizeof(filepath), "name.csv");
    FILE *table = fopen(filepath, "ab");
    if (table == NULL)
    {
        perror("Error creating file");
        return 1;
    }
    fprintf(table, "%s,", name);
    fclose(table);
}

int view(int *s, char buffer[100])
{
    char line[256];
    int length = 0;
    int i = 0;

    // Get the current working directory
    char currentDir[FILENAME_MAX];
    GetCurrentDirectory(FILENAME_MAX, currentDir);

    // Build the full path to the file
    char filepath[FILENAME_MAX];
    snprintf(filepath, sizeof(filepath), "%s\\name.csv", currentDir);

    FILE *name = fopen(filepath, "rb");
    if (name == NULL)
    {
        printf("THERE IS NOTHING!");
        *s = 1;
        return 0;
    }

    while (fgets(line, sizeof(line), name) != NULL)
    {
        char *s = strtok(line, ",");
        while (s != NULL)
        {
            i++;
            printf("\n%d. %s  ", i, s);
            s = strtok(NULL, ",");
            length++;
        }
    }
    printf("\n~> ");
    fclose(name);
    char **list = malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++)
    {
        list[i] = malloc(sizeof(char) * 100);
    }
    i = 0;
    name = fopen(filepath, "rb");
    while (fgets(line, sizeof(line), name) != NULL)
    {
        char *s = strtok(line, ",");
        while (s != NULL)
        {
            list[i] = s;
            s = strtok(NULL, ",");
            i++;
        }
    }
    int n;
    input(&n, i);
    if (chdir(list[n - 1]) != 0)
    {
        printf("there is nothing");
    }
    else
    {
        printf("<%s> is now open\n", list[n - 1]);
        strcpy(buffer, list[n - 1]);
    }
    fclose(name);
    free2DArray(list, length);
    return 1;
}

void free2DArray(char **arr, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

int Delete()
{
    char line[256];
    int length = 0;
    int i = 0;

    // Get the current working directory
    char currentDir[FILENAME_MAX];
    GetCurrentDirectory(FILENAME_MAX, currentDir);

    // Build the full path to the file
    char filepath[FILENAME_MAX];
    snprintf(filepath, sizeof(filepath), "%s\\name.csv", currentDir);

    FILE *name = fopen(filepath, "rb");
    if (name == NULL)
    {
        printf("There is Nothing to Delete!");
        Sleep(3000);
        system("cls");
        return 1;
    }

    while (fgets(line, sizeof(line), name) != NULL)
    {
        char *s = strtok(line, ",");
        while (s != NULL)
        {
            i++;
            printf("\n%d. %s  ", i, s);
            s = strtok(NULL, ",");
            length++;
        }
    }
    printf("\n~> ");
    char **list = malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++)
    {
        list[i] = malloc(sizeof(char) * 100);
    }
    i = 0;
    fseek(name, 0, SEEK_SET);
    while (fgets(line, sizeof(line), name) != NULL)
    {
        char *s = strtok(line, ",");
        while (s != NULL)
        {
            list[i] = s;
            s = strtok(NULL, ",");
            i++;
        }
    }
    fclose(name);
    int n;
    input(&n, i);
    if (remove_directory(list[n - 1]) == 0)
    {
        printf("\n%s is sucsessfully Deleted!", list[n - 1]);
        Sleep(3000);
        system("cls");
    }
    name = fopen(filepath, "w");
    fclose(name);
    name = fopen(filepath, "a");
    for (i = 0; i < length; i++)
    {
        if (i != (n - 1))
        {
            fprintf(name, "%s,", list[i]);
        }
    }
    fclose(name);
    length--;
    if (length == 0)
    {
        DeleteFile(filepath);
    }
    free2DArray(list, length);
}

int add_task(task *head)
{
    task *current;
    current = head;
    current->next = malloc(sizeof(task));
    current = current->next;
    current->name = malloc(sizeof(char) * 100);
    if (current->name == NULL)
    {
        return 0;
    }
    printf("Please Enter Your Task name: ");
    sinput(current->name, 100);
    current->priority = malloc(sizeof(char) * 100);
    system("cls");
    printf("Please Enter Your Task Priority (Low\\Medium\\High): ");
    sinput(current->priority, 100);
    system("cls");
    printf("Please Enter Your Task Deadline (YYYY-MM-DD): ");
    scanf("%4d-%2d-%2d", &current->year, &current->month, &current->day);
    system("cls");
    FILE *task = fopen("task.csv", "a");
    if (task == NULL)
    {
        perror("Error creating file");
        return 1;
    }
    fprintf(task, "%s,%s,%d,%d,%d,\n", current->name, current->priority, current->year, current->month, current->day);
    fclose(task);
    free(current->name);
    free(current->priority);
    free(current);
    return 0;
}
int tprint()
{
    int nl = 1;
    char *num;
    num = malloc(sizeof(char) * 4);
    task *buffer;
    buffer = malloc(sizeof(task));
    char *line;
    line = malloc(sizeof(char) * 1024);
    FILE *task = fopen("task.csv", "r");
    if (task == NULL)
    {
        printf("\n\n\t\t<<There Is No Task Yet>>");
        return 1;
    }
    while (fgets(line, 1024, task) != NULL)
    {
        buffer->name = strtok(line, ",");
        buffer->priority = strtok(NULL, ",");
        num = strtok(NULL, ",");
        buffer->year = atoi(num);
        num = strtok(NULL, ",");
        buffer->month = atoi(num);
        num = strtok(NULL, ",");
        buffer->day = atoi(num);
        printf("\n%d. Task: %s, Priority: %s, Deadline: %d-%d-%d", nl, buffer->name, buffer->priority, buffer->year, buffer->month, buffer->day);
        nl++;
    }
    fclose(task);
    free(num);
    free(buffer);
    free(line);
    return 0;
}
int delete_task(char buffer[1024])
{
    char currentDir[FILENAME_MAX];
    GetCurrentDirectory(FILENAME_MAX, currentDir);
    char filepath[FILENAME_MAX];
    snprintf(filepath, sizeof(filepath), "%s\\task.csv", currentDir);
    int i = 1;
    FILE *remove = fopen("task.csv", "r");
    char *taskname;
    char *line;
    line = malloc(sizeof(char) * 1024);
    while (fgets(line, 1024, remove) != NULL)
    {
        taskname = malloc(sizeof(char) * 256);
        strcpy(taskname, strtok(line, ","));
        printf("%d. %s\n", i, taskname);
        i++;
        free(taskname);
    }
    i--;
    free(line);
    line = malloc(sizeof(char) * 1024);
    printf("~>");
    fseek(remove, 0, SEEK_SET);
    char **list = malloc(sizeof(char *) * i);
    for (int j = 0; j < i; j++)
    {
        list[j] = malloc(sizeof(char) * 1024);
    }
    int t = 0;
    while (fgets(line, 1024, remove) != NULL)
    {
        list[t] = strdup(line);
        t++;
    }
    free(line);
    int n;
    input(&n, i);
    fclose(remove);
    remove = fopen("task.csv", "w");
    fclose(remove);
    remove = fopen("task.csv", "a");
    for (int j = 0; j < i; j++)
    {
        if (j != (n - 1))
        {
            fprintf(remove, "%s", list[j]);
        }
    }
    strcpy(buffer, list[n - 1]);
    fclose(remove);
    free2DArray(list, i);
    i--;
    if (i == 0)
    {
        DeleteFile(filepath);
    }
    system("cls");
}

int input(int *n, int i)
{
    while (1)
    {
        if (scanf("%d", n) == 1 && *n >= 1 && *n <= i)
        {
            break;
        }
        else
        {
            printf("\nyour input is unfortunately wrong please enter again (:");
            printf("\n~> ");
            while (getchar() != '\n')
                ;
        }
    }
}
void sinput(char *array, int n)
{
    fgets(array, n, stdin);
    int num = strlen(array);
    if (array[num - 1] == '\n')
    {
        array[num - 1] = '\0';
    }
}
int EDIT()
{
    int i = 1;
    printf("Edit Task:\n\nWhich Task Do You Want To Edit?\n");
    FILE *edit = fopen("task.csv", "r");
    char *taskname;
    char *line;
    line = malloc(sizeof(char) * 1024);
    while (fgets(line, 1024, edit) != NULL)
    {
        taskname = malloc(sizeof(char) * 256);
        strcpy(taskname, strtok(line, ","));
        printf("%d. %s\n", i, taskname);
        i++;
        free(taskname);
    }
    i--;
    free(line);
    line = malloc(sizeof(char) * 1024);
    printf("~>");
    fseek(edit, 0, SEEK_SET);
    char **list = malloc(sizeof(char *) * i);
    for (int j = 0; j < i; j++)
    {
        list[j] = malloc(sizeof(char) * 1024);
    }
    int t = 0;
    while (fgets(line, 1024, edit) != NULL)
    {
        list[t] = strdup(line);
        t++;
    }
    free(line);
    int n;
    input(&n, i);

    task *current;
    current = malloc(sizeof(task));
    current->next = malloc(sizeof(task));
    current = current->next;
    current->name = malloc(sizeof(char) * 100);
    if (current->name == NULL)
    {
        return 0;
    }
    fflush(stdin);
    printf("Edit  Task Name: ");
    sinput(current->name, 100);
    current->priority = malloc(sizeof(char) * 100);
    system("cls");
    printf("Edit  Priority: ");
    sinput(current->priority, 100);
    system("cls");
    printf("Edit  Deadline (YYYY-MM-DD): ");
    scanf("%4d-%2d-%2d", &current->year, &current->month, &current->day);

    fclose(edit);
    edit = fopen("task.csv", "w");
    fclose(edit);
    edit = fopen("task.csv", "a");
    for (int j = 0; j < i; j++)
    {
        if (j != (n - 1))
        {
            fprintf(edit, "%s", list[j]);
        }
        else
        {
            fprintf(edit, "%s,%s,%d,%d,%d,\n", current->name, current->priority, current->year, current->month, current->day);
        }
    }
    fclose(edit);
    free2DArray(list, i);
    system("cls");
}

// int time_calculate(char* f_time)
// {
//     char *token = strtok(f_time, "-");
//     char* year = token;
//     token = strtok(NULL, "-");
//     char* mounth = token;
//     token = strtok(NULL, "-");
//     char* day = token;

//     // Define two time structures
//     struct tm time1 = {0}; // Initialize to all zeros
//     struct tm time2 = {0};

//     time_t current_time = time(NULL);
//     struct tm *time_info = localtime(&current_time);

//     // Set the values for the two times
//     time1.tm_year = atoi(year) - 1900; // Year - 1900
//     time1.tm_mon = atoi(mounth) - 1;            // Month (0-11)
//     time1.tm_mday = atoi(day);           // Day

//     time2.tm_year = time_info->tm_year;
//     time2.tm_mon = time_info->tm_mon;
//     time2.tm_mday = time_info->tm_mday;

//     // Convert time structures to time_t
//     time_t t1 = mktime(&time1);
//     time_t t2 = mktime(&time2);

//     // Calculate the time difference in seconds
//     double difference_seconds = difftime(t2, t1);

//     // Convert seconds to days
//     double difference_days = difference_seconds / (24 * 3600);

//     return difference_days;
// }

int sort()
{
    int n;
    printf("what do you prefer for sorting? (1.deadline, 2.priority): ");
    input(&n, 2);

    switch (n)
    {
        // sorting by deadline
    case 1:
    {
        char lines[100];
        char *data;
        FILE *test = fopen("task.csv", "r");

        while (fgets(lines, sizeof(lines), test))
        {
            // first data
            data = strtok(lines, ",");
            printf("%s\n", data);

            // second data
            data = strtok(NULL, ",");
            printf("%s\n", data);

            // thread data
            data = strtok(NULL, ",");
            printf("%s\n", data);
        }

        break;
    }

        // sorting by priority
    case 2:

    {
        char lines[100];
        char *data;
        FILE *test = fopen("task.csv", "r");

        while (fgets(lines, sizeof(lines), test))
        {
            // first data
            data = strtok(lines, ",");
            printf("%s\n", data);

            // second data
            data = strtok(NULL, ",");
            printf("%s\n", data);

            // thread data
            data = strtok(NULL, ",");
            printf("%s\n", data);
        }

        break;
    }

    default:
        break;
    }
}

// Function to check for upcoming deadlines within 3 days
void reminder()
{
    // seting the current time
    time_t now = time(NULL);
    struct tm *current_time = localtime(&now);
    int current_day = current_time->tm_mday;
    int current_month = current_time->tm_mon + 1; // tm_mon is 0-indexed

    // access to the boards name file
    FILE *boards_f = fopen("name.csv", "r");
    if (boards_f != NULL) // if there is a boards file
    {
        char boards[1024];
        fgets(boards, sizeof(boards), boards_f);

        // read all boards name
        char *board = strtok(boards, ",");
        char path[1024];
        while (board != NULL)
        {
            // Copy the first string into the variable
            strcpy(path, board);
            strcat(path, "/name.csv"); // path of (list name file)

            // access to the lists name file
            FILE *lists_f = fopen(path, "r");
            strcpy(path, board); // reset path to board
            if (lists_f != NULL)
            {
                char lists[1024];
                fgets(lists, sizeof(lists), lists_f);

                // read all lists name
                char *list = strtok(lists, ",");
                char line[1024];
                while (list != NULL)
                {

                    // setting path
                    strcpy(path, board);

                    strcat(path, "/");
                    strcat(path, list);
                    strcat(path, "/task.csv");
                    FILE *task = fopen(path, "r");
                    if (task == NULL)
                    {
                        printf("Error opening task file.\n");
                        printf("%s\n", path);
                        return;
                    }

                    // Move to the next list
                    list = strtok(NULL, ",");

                    while (fgets(line, sizeof(line), task) != NULL)
                    {

                        // geting task data (name, priority, deadline)
                        char *name = strtok(line, ",");
                        char *priority = strtok(NULL, ",");
                        int year = atoi(strtok(NULL, ","));
                        int month = atoi(strtok(NULL, ","));
                        int day = atoi(strtok(NULL, ","));

                        // Check if the task is due within the next 3 days
                        if (year == current_time->tm_year + 1900 && // tm_year is years since 1900
                                (month == current_month && day - current_day <= 3) ||
                            (month == current_month + 1 && day + (30 - current_day) <= 3))
                        {
                            printf("Upcoming Deadline: Task: %s, Priority: %s, Deadline: %d-%d-%d\n",
                                   name, priority, year, month, day);
                        }
                    }
                    fclose(task);
                }
            }
            // Move to the next board
            // printf("befor: %s\n", board);
            board = strtok(NULL, ",");
            // printf("after: %s\n", board);

            fclose(lists_f);
        }
        fclose(boards_f);
    }
}
