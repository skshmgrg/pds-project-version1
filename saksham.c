// subjects sub1 sub2 sub3 sub4 sub5
// numstudents variable ko vishwas wali files se uthaana h
// #include"vishwas.h"
// k is number of students and 1000 is max number of students
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// global declarations
int k = 0;
struct marks
{
    char rollno[9];
    float marks[5];
    int grade_weightage[5];
    float cgpa;
};
struct marks array[1000];
int index[100];
int credit[5];

// functions

void loaddata()
{
    FILE *ptr = fopen("marks.txt", "a");
    fclose(ptr);
    ptr = fopen("marks.txt", "r");
    if (ptr == NULL)
    {
        printf("Error in opening the file\n");
        return;
    }
    while (fscanf(ptr, "%s  %f  %f  %f  %f  %f", &array[k].rollno, &array[k].marks[0], &array[k].marks[1], &array[k].marks[2], &array[k].marks[3], &array[k].marks[4]) == 6)
    {
        k++;
        if (k >= 1000)
        {
            break;
        }
    }
    fclose(ptr);
}

void creditinput()
{

    for (int i = 1; i <= 5; i++)
    {
        printf("enter the credits corresponding to subject %d\n", i);
        scanf("%d", &credit[i - 1]);
    }
}

void toupperm(char str[])
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] > 96)
        {
            str[i] -= 32;
        }
        else
            continue;
    }

    return;
}

void marksinput()
{
    //k++;
here3:

    printf("enter roll number of student: ");
here4:
    scanf("%s", &array[k].rollno);
    toupperm(array[k].rollno);

    FILE *ptr = fopen("marks.txt", "a");
    
    if (strlen(array[k].rollno) == 9)
        fprintf(ptr, "%s ", array[k].rollno);
    else
    {
        printf("enter a valid roll number");
        goto here4;
    }

    for (int i = 1; i <= 5; i++)
    {
    here:
        printf("enter the marks out of 100 corresponding to subject %d\n", i);
        scanf("%f", &array[k].marks[i - 1]);
        if (array[k].marks[i - 1] >= 0 && array[k].marks[i - 1] <= 100)
            fprintf(ptr, "%f ", array[k].marks[i - 1]);
        else
        {
            printf("please enter a value between 0 to 100\n");
            goto here;
        }
    }
    fprintf(ptr, "\n");
    printf("marks added successfully\n");
    fclose(ptr);
    int a;
    printf("-> Enter 1 for adding marks of a student\n-> Enter 2 for calculating grades and cgpa of students\n");
    scanf("%d", &a);
    switch (a)
    {
    case 1:
        k++;
        goto here3;
        break;
    case 2:
        printf("grades and cgpa can be seen from the files created . thanks!");
        break;
    }
}

void subjectsorted(struct marks array[], int subjectnumber, FILE *ptr)
{
    float max = 0, large = 0;
    int m = 0, maxcount = 0;
    for (int i = 0; i < k; i++)
    {
        if (array[i].marks[subjectnumber] > max)
        {
            max = array[i].marks[subjectnumber];
            m = i;
        }
    }
    index[maxcount] = m;
    maxcount++;

    fprintf(ptr, "%s %f\n", array[index[maxcount - 1]].rollno, array[index[maxcount - 1]].marks[subjectnumber]);

    for (int p = 0; p < (k - 1); p++)
    {
        for (int i = 0; i < k; i++)
        {
            int j;
            for (j = 0; j < maxcount; j++)
            {
                if (i == index[j])
                {
                    break;
                }
            }
            if (j != maxcount)
            {
                continue;
            }
            if (array[i].marks[subjectnumber] <= max && array[i].marks[subjectnumber] >= large)
            {
                large = array[i].marks[subjectnumber];
                m = i;
            }
        }
        index[maxcount] = m;
        maxcount++;

        fprintf(ptr, "%s %f\n", array[index[maxcount - 1]].rollno, array[index[maxcount - 1]].marks[subjectnumber]);
        max = large;
        large = 0;
    }
}

void gradingsystem(struct marks array[], int index[], FILE *ptr, int subject_number)
{
    // ex=k/10  a =3k/10 b=3k/10 c=15/100 d=5k/100 pass=5k/100 fail=5k/100
    int no_ex, no_a, no_b, no_c, no_d, no_p, no_f;
    no_ex = ceil(k / 10);
    no_a = ceil(3 * k / 10);
    no_b = ceil(3 * k / 10);
    no_c = ceil(15 * k / 100);
    no_d = ceil(5 * k / 100);
    no_p = ceil(5 * k / 100);
    no_f = k - no_ex - no_a - no_b - no_c - no_d - no_p;

    for (int i = 0; i <= no_ex; i++)
    {
        char grade[] = "ex";
        fprintf(ptr, "%s %s\n", array[index[i]].rollno, grade);
        array[index[i]].grade_weightage[subject_number] = 10;
    }
    for (int i = no_ex + 1; i <= no_ex + no_a; i++)
    {
        char grade = 'A';
        fprintf(ptr, "%s %c\n", array[index[i]].rollno, grade);
        array[index[i]].grade_weightage[subject_number] = 9;
    }
    for (int i = no_ex + no_a + 1; i <= no_ex + no_a + no_b; i++)
    {
        char grade = 'B';
        fprintf(ptr, "%s %c\n", array[index[i]].rollno, grade);
        array[index[i]].grade_weightage[subject_number] = 8;
    }
    for (int i = no_ex + no_a + no_b + 1; i <= no_ex + no_a + no_b + no_c; i++)
    {
        char grade = 'C';
        fprintf(ptr, "%s %c\n", array[index[i]].rollno, grade);
        array[index[i]].grade_weightage[subject_number] = 7;
    }
    for (int i = no_ex + no_a + no_b + no_c + 1; i <= no_ex + no_a + no_b + no_c + no_d; i++)
    {
        char grade = 'D';
        fprintf(ptr, "%s %c\n", array[index[i]].rollno, grade);
        array[index[i]].grade_weightage[subject_number] = 6;
    }
    for (int i = no_ex + no_a + no_b + no_c + no_d + 1; i <= no_ex + no_a + no_b + no_c + no_d + no_p; i++)
    {
        char grade = 'P';
        fprintf(ptr, "%s %c\n", array[index[i]].rollno, grade);
        array[index[i]].grade_weightage[subject_number] = 5;
    }
    for (int i = no_ex + no_a + no_b + no_c + no_d + no_p + 1; i < no_ex + no_a + no_b + no_c + no_d + no_p + no_f; i++)
    {
        char grade = 'F';
        fprintf(ptr, "%s %c\n", array[index[i]].rollno, grade);
        array[index[i]].grade_weightage[subject_number] = 0;
    }
}

void cg(int credit[], struct marks array[])
{
    FILE *ptr = fopen("cg.txt", "w");
    // index wale se index utha ke us hisaab se ex=10 a=9 b=8 c=7 d=6 p=5 f=0..... credit*weightage/total credit
    int total_credits = 0;
    for (int i = 0; i < 5; i++)
    {
        total_credits += credit[i];
    }

    for (int i = 0; i < k; i++)
    {
        array[i].cgpa = 0;
        for (int j = 0; j < 5; j++)
        {
            array[i].cgpa += (array[i].grade_weightage[j] * credit[j]) / (float)total_credits;
        }
        fprintf(ptr, "%s %f\n", array[i].rollno, array[i].cgpa);
    }
}

int main()
{
    loaddata();
    creditinput();
    system("cls");
    marksinput();
    
    FILE *ptr = fopen("subject0sort.txt", "w");
    subjectsorted(array, 0, ptr);
    gradingsystem(array, index, ptr, 0);
    fclose(ptr);

    FILE *ptr1 = fopen("subject1sort.txt", "w");
    subjectsorted(array, 1, ptr1);
    gradingsystem(array, index, ptr, 1);
    fclose(ptr1);

    FILE *ptr2 = fopen("subject2sort.txt", "w");
    subjectsorted(array, 2, ptr2);
    gradingsystem(array, index, ptr, 2);
    fclose(ptr2);

    FILE *ptr3 = fopen("subject3sort.txt", "w");
    subjectsorted(array, 3, ptr3);
    gradingsystem(array, index, ptr, 3);
    fclose(ptr3);

    FILE *ptr4 = fopen("subject4sort.txt", "w");
    subjectsorted(array, 4, ptr4);
    gradingsystem(array, index, ptr, 4);
    fclose(ptr4);

    cg(credit, array);
}