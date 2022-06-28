//Simple student database management system

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void addstudent();
void studentrecord();
void searchstudent();
void delete();

struct student
{
    char first_name[20];
    char last_name[20];
    int roll_no;
    char dept[10];
    int semester;
    float _percentage;
};

void main()
{

    int choice;
    while (choice != 5)
    {

        printf("\t\t\t=====STUDENT DATABASE MANAGEMENT SYSTEM=====");
        printf("\n\n\n\t\t\t\t     1. Add Student\n");
        printf("\t\t\t\t     2. Student Records\n");
        printf("\t\t\t\t     3. Search Student\n");
        printf("\t\t\t\t     4. Delete Student\n");
        printf("\t\t\t\t     5. Exit\n");
        printf("\t\t\t\t    _____________________\n");
        printf("\t\t\t\t     ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            system("cls");   //Clear screen
            addstudent();
            system("cls");
            break;
        case 2:
            system("cls");
            studentrecord();
            printf("\t\t\t\t  Press any key to exit..... \n");
            getch();
            system("cls");

            break;

        case 3:
            system("cls");
            searchstudent();
            printf("\n\t\t\t\t  Press any key to exit.......\n");

            getch();
            system("cls");

            break;

        case 4:
            system("cls");
            delete ();
            printf("\n\t\t\t\tPress any key to exit.......\n");
            getch();
            system("cls");
            break;
        case 5:
            system("cls");
            printf("\n\t\t\t\t:)\n\n");
            exit(0);
            break;

        default:
            system("cls");
            getch();
            printf("\n\t\t\t\t\tEnter a valid number\n\n");
            printf("\t\t\t\tPress any key to continue.......");
            getch();
            system("cls");
            break;
        }
    }

    getch();
}

void addstudent()
{

    char another;
    FILE *fp;
    int n, i;
    struct student info;
    do
    {
        system("cls");
        printf("\t\t\t\t=======Add New Student Data=======\n\n\n");
        fp = fopen("data.txt", "a");

        printf("\n\t\t\tEnter First Name     : ");
        scanf("%s", &info.first_name);
        printf("\n\t\t\tEnter Last Name     : ");
        scanf("%s", &info.last_name);
        printf("\n\t\t\tEnter Roll-No       : ");
        scanf("%d", &info.roll_no);
        printf("\n\t\t\tEnter Department    : ");
        scanf("%s", &info.dept);
        printf("\n\t\t\tEnter Semester       : ");
        scanf("%d", &info.semester);
        printf("\n\t\t\tEnter Percentage    : ");
        scanf("%f", &info._percentage);
        printf("\n\t\t\t______________________________\n");

        if (fp == NULL)
        {
            fprintf(stderr, "can't open file");
        }
        else
        {
            printf("\t\t\tRecord stored successfuly\n");
        }

        fwrite(&info, sizeof(struct student), 1, fp);
        fclose(fp);

        printf("\t\t\tDo you want to add another record?(y/n) : ");

        scanf("%s", &another);

    } while (another == 'y' || another == 'Y');
}

void studentrecord()
{

    FILE *fp;

    struct student info;
    fp = fopen("data.txt", "r");

    printf("\t\t\t\t=======STUDENT RECORDS=======\n\n\n");

    if (fp == NULL)
    {

        fprintf(stderr, "can't open file\n");
        exit(0);
    }
    else
    {
        printf("\t\t\t\tRECORDS :\n");
        printf("\t\t\t\t___________\n\n");
    }

    while (fread(&info, sizeof(struct student), 1, fp))
    {
        printf("\n\t\t\t\t Student Name  : %s %s", info.first_name, info.last_name);
        printf("\n\t\t\t\t Roll NO       : %d", info.roll_no);
        printf("\n\t\t\t\t Department    : %s", info.dept);
        printf("\n\t\t\t\t Semester      : %d", info.semester);
        printf("\n\t\t\t\t Percentage    : %.2f%", info._percentage);
        printf("\n\t\t\t\t ________________________________\n");
    }
    fclose(fp);
    getch();
}

void searchstudent()
{
    struct student info;
    FILE *fp;
    int roll_no, found = 0;

    fp = fopen("data.txt", "r");
    printf("\t\t\t\t=======SEARCH STUDENT RECORD=======\n\n\n");
    printf("\t\t\tEnter the roll no : ");

    scanf("%d", &roll_no);

    while (fread(&info, sizeof(struct student), 1, fp) > 0)
    {

        if (info.roll_no == roll_no)
        {

            found = 1;
            printf("\n\n\t\t\tStudent Name : %s %s", info.first_name, info.last_name);
            printf("\n\t\t\tRoll NO        : %d", info.roll_no);
            printf("\n\t\t\tDepartment     : %s", info.dept);
            printf("\n\t\t\tSemester       : %d", info.semester);
            printf("\n\t\t\tPercentage     : %.2f%", info._percentage);
            printf("\n\t\t\t______________________________________\n");
        }
    }

    if (!found)
    {
        printf("\n\t\t\tRecord not found\n");
    }

    fclose(fp);
    getch();
}

void delete ()
{
    struct student info;
    FILE *fp, *fp1;

    int roll_no, found = 0;

    printf("\t\t\t\t=======DELETE STUDENTS RECORD=======\n\n\n");
    fp = fopen("data.txt", "r");
    fp1 = fopen("temp.txt", "w");
    printf("\t\t\t\tEnter the roll no : ");
    scanf("%d", &roll_no);
    if (fp == NULL)
    {
        fprintf(stderr, "can't open file\n");
        exit(0);
    }

    while (fread(&info, sizeof(struct student), 1, fp))
    {
        if (info.roll_no == roll_no)
        {

            found = 1;
        }
        else
        {
            fwrite(&info, sizeof(struct student), 1, fp1);
        }
    }
    fclose(fp);
    fclose(fp1);

    if (!found)
    {
        printf("\n\t\t\t\tRecord not found\n");
    }
    if (found)
    {
        remove("data.txt");
        rename("temp.txt", "data.txt");

        printf("\n\t\t\t\tRecord deleted succesfully\n");
    }

    getch();
}