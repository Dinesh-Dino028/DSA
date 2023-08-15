#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>

using namespace std;

struct Student
{

    char name[10], res[5];
    int sno, m1, m2, m3, total;
    float avg;
} s[10];

void create(int n);
void display(int n);
void cal(int n);

int main()
{
    int n, ch, t = 1;

    do
    {
        cout << "Enter the Chioce: "
             << "\t"
             << "1.CREATE"
             << "\t"
             << "2.DISPLAY"
             << "\t";
        cin >> ch;
        cout << "Enter the no of Student: ";
        cin >> n;
        switch (ch)
        {
        case 1:
            cout << "create" << endl;
            create(n);
            break;
        case 2:
            cout << "display" << endl;
            display(n);
            break;
        default:
            cout << "Invalid Option";
            break;
        }
        cout << "Do you want to continue? Press(0/1)";
        cin >> t;
    } while (t != 0);
    return 0;
}

void create(int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Student Name: ";
        cin >> s[i].name;
        cout << "Enter Student Rollno: ";
        cin >> s[i].sno;
        cout << "Enter Student mark1: ";
        cin >> s[i].m1;
        cout << "Enter Student mark2: ";
        cin >> s[i].m2;
        cout << "Enter Student mark3: ";
        cin >> s[i].m3;
    }
}

void display(int n)
{
    cal(n);
    cout << "NAME"
         << "\t"
         << "SNO"
         << "\t"
         << "MARK1"
         << "\t"
         << "MARK2"
         << "\t"
         << "MARK3"
         << "\t"
         << "TOTAL"
         << "\t"
         << "AVG"
         << endl;
    for (int i = 0; i < n; i++)
    {
        cout << s[i].name << "\t" << s[i].sno << "\t" << s[i].m1 << "\t" << s[i].m2 << "\t" << s[i].m3 << "\t" << s[i].total << "\t" << s[i].avg << endl;
    }
}

void cal(int n)
{
    for (int i = 0; i < n; i++)
    {
        s[i].total = s[i].m1 + s[i].m2 + s[i].m3;
        s[i].avg = s[i].total / 3;
    }

    //sorting
    for (int i = 0; i < n; i++){
        for(int j = i; j <n; j++){
            if(s[i].total <= s[j+1].total){
                char temp7[10];
                int temp1, temp2, temp3, temp4, temp5;
                float temp6;
                temp5 = s[i].total; s[i].total = s[j+1].total; s[j+1].total = temp5;
                strcpy(temp7, s[i].name); strcpy(s[i].name, s[j+1].name); strcpy(s[j+1].name, temp7);
                temp1 = s[i].sno; s[i].sno = s[j+1].sno; s[j+1].sno = temp1;
                temp2 = s[i].m1; s[i].m1 = s[j+1].m1; s[j+1].m1 = temp2;
                temp3 = s[i].m2; s[i].m2 = s[j+1].m2; s[j+1].m2 = temp3;
                temp4 = s[i].m3; s[i].m3 = s[j+1].m3; s[j+1].m3 = temp4;
                temp6 = s[i].avg; s[i].avg = s[j+1].avg; s[j+1].avg = temp6;
            }
        }
    }
}