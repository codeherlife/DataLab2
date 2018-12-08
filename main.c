//
//  Name this file: database.c
//  DatabaseLab
//
//  Student Name: Melanie Summers;
//  Student id: 012090935;
//  Name of the assignment: Database Lab;
//  Date: 11/27/18;
//  Name and version of the C Compiler: Xcode v. 10.1 (10B61);
//  Name of Operating System: Mac OS High Sierra v. 10.13.6;

//DON"T FORGET TO CHANGE ACCESS FULL PATH NAME TO SOMETHING THAT WILL WORK FOR PROF

#include <stdio.h>
#include <stdlib.h>

#define SIZE 20
#define MAX 100

FILE *fp, *fpIn;
FILE *fpIn;

typedef struct {
    char first[8];
    char initial[2];
    char last[10];
    char street[17];
    char city[12];
    char state[3];
    char zip[6];
    int age;
    char sex[2];
    int tenure;
    double salary;
} Employee;

int main(void);
int inputData(Employee workers[]);
void outputContents (Employee workers[], int workerCounter);
void outputMen (Employee workers[], int workerCounter);
void outputBallerLady (Employee workers[], int workerCounter);
void outputPoorGuy (Employee workers[], int workerCounter);
double averageSalary (Employee workers[], int workerCounter);
void womenGetLess (Employee workers[], int workerCounter, double averageSalaries);
void ratioMen (Employee workers[], int workerCounter, double averageSalaries);
void outputVariousInfo (Employee workers[], int workerCounter);
void gettingRaise (Employee workers[], int workerCounter);

int main(void) {
    Employee workers[SIZE];
    int workerCounter;
    double averageSalaries;
    
    fp = fopen("csis.txt", "w");
    
    
    //DON"T FORGET TO CHANGE THIS BEFORE SUBMITTING
    if(!(fpIn = fopen("/Users/codeherlife/Desktop/CSCI 112/DatabaseLab2/DatabaseLab2/DatabaseLab2/payfile.txt", "r"))) {
        printf(     "payfile.txt could not be opened for input.");
        fprintf(fp, "payfile.txt could not be opened for input.");
        fclose(fp);
        exit(1);
    }
    
    workerCounter = inputData(workers);
    outputContents(workers, workerCounter);
    
    outputMen(workers, workerCounter);
    outputBallerLady(workers, workerCounter);
    outputPoorGuy(workers, workerCounter);
    averageSalaries = averageSalary(workers, workerCounter);
    womenGetLess(workers, workerCounter, averageSalaries);
    ratioMen(workers, workerCounter, averageSalaries);
    outputVariousInfo(workers, workerCounter);
    gettingRaise (workers, workerCounter);
    
    fclose(fpIn);
    fclose(fp);
    return 0;
}

void strsub(char buf[], char sub[], int start, int end){
    int i, j;
    
    for(j=0, i=start; i<=end; i++, j++){
        sub[j] = buf[i];
    }
    sub[j] = '\0';
}

//(A) this function should read data for employees into an array of structures:
int inputData(Employee workers[]) {
    int i=0;
    char buf[MAX];
    char temp[MAX];
    FILE *fp;
    
    fp = fopen("/Users/codeherlife/Desktop/CSCI 112/DatabaseLab2/DatabaseLab2/DatabaseLab2/payfile.txt", "r");
    if (fp == NULL) {
        puts("File payfile.txt could not be opened for input.");
        exit(1);
    }
    while (!feof(fp)) {
        fgets(buf, MAX, fp);
        strsub(buf, workers[i].first, 0, 6);
        strsub(buf, workers[i].initial, 8, 8);
        strsub(buf, workers[i].last, 10, 18);
        strsub(buf, workers[i].street, 20, 35);
        strsub(buf, workers[i].city, 37, 47);
        strsub(buf, workers[i].state, 49, 50);
        strsub(buf, workers[i].zip, 52, 56);
        strsub(buf, temp, 58, 59);
        workers[i].age = atoi(temp);
        strsub(buf, workers[i].sex, 61, 61);
        strsub(buf, temp, 63, 63);
        workers[i].tenure = atoi(temp);
        strsub(buf, temp, 65, 70);
        workers[i].salary = atof(temp);
        ++i;
    }
    fclose(fp);
    return i;
}

//(b)this function should output the contents of each structure into an easily read format, similar to the format of the input file:
void outputContents (Employee workers[], int workerCounter){
    int i;
    for(i = 0; i < workerCounter; i++){
        printf(     "\n%s", workers[i].first);
        fprintf(fp, "\n%s", workers[i].first);
        printf(     " %s", workers[i].initial);
        fprintf(fp, " %s", workers[i].initial);
        printf(     " %s", workers[i].last);
        fprintf(fp, " %s", workers[i].last);
        printf(     " %s", workers[i].street);
        fprintf(fp, " %s", workers[i].street);
        printf(     " %s", workers[i].city);
        fprintf(fp, " %s", workers[i].city);
        printf(     " %s", workers[i].state);
        fprintf(fp, " %s", workers[i].state);
        printf(     " %s", workers[i].zip);
        fprintf(fp, " %s", workers[i].zip);
        printf(     " %d", workers[i].age);
        fprintf(fp, " %d", workers[i].age);
        printf(     " %s", workers[i].sex);
        fprintf(fp, " %s", workers[i].sex);
        printf(     " %d", workers[i].tenure);
        fprintf(fp, " %d", workers[i].tenure);
        printf(     " %.2f", workers[i].salary);
        fprintf(fp, " %.2f", workers[i].salary);
    }
}

//(C)in this function- output the first and last name of all men on the payroll
void outputMen (Employee workers[], int workerCounter){
    int i;
    printf(     "\n\nAll men on the payroll:\n");
    fprintf(fp, "\n\nAll men on the payroll:\n");
    for(i = 0; i < workerCounter; i++){
        if(workers[i].sex[0] == 'M'){
            printf(     "%s %s\n", workers[i].first, workers[i].last);
            fprintf(fp, "%s %s\n", workers[i].first, workers[i].last);
        }
    }
}

//(D)in this function- output the first and last name of the highest paid woman on the payroll
void outputBallerLady (Employee workers[], int workerCounter){
    int i;
    int highestWage = 0;
    int indexOfHighestWage = 0;
    
    printf(     "\n\n Highest paid woman on the payroll:\n");
    fprintf(fp, "\n\n Highest paid woman on the payroll:\n");
    
    for(i = 0; i < workerCounter; i++){
        
        if(workers[i].sex[0] == 'F' && workers[i].salary > highestWage){
            highestWage = workers[i].salary;
            indexOfHighestWage = i;
    }
}
    printf(     "%s %s\n", workers[indexOfHighestWage].first, workers[indexOfHighestWage].last);
    fprintf(fp, "%s %s\n", workers[indexOfHighestWage].first, workers[indexOfHighestWage].last);

}
//(E)in this function- output the first and last name of the lowest paid man on the payroll should be James Kirk
void outputPoorGuy (Employee workers[], int workerCounter){
    int i;
    int lowestWage = 10000;
    int indexOfLowestWage = 0;
    
    printf(     "\n\n Lowest paid man on the payroll:\n");
    fprintf(fp, "\n\n Lowest paid man on the payroll:\n");
    
    for(i = 0; i < workerCounter; i++){
        if(workers[i].sex[0] == 'M' && workers[i].salary < lowestWage){
            lowestWage = workers[i].salary;
            indexOfLowestWage = i;
        }
    }
    printf(     "%s %s\n", workers[indexOfLowestWage].first, workers[indexOfLowestWage].last);
    fprintf(fp, "%s %s\n", workers[indexOfLowestWage].first, workers[indexOfLowestWage].last);
}

//(F) in this function- output the average salary for all employees
double averageSalary (Employee workers[], int workerCounter){
    double allSalarysTotal = 0;
    double averageSalarys;
    int i;
    
    printf(     "\n\n Average salary for all employees:\n");
    fprintf(fp, "\n\n Average salary for all employees:\n");
    
    for(i = 0; i < workerCounter; i++){
        allSalarysTotal += workers[i].salary;
        
    }
    averageSalarys = allSalarysTotal / workerCounter;
    
    printf(     "%.2f \n", averageSalarys);
    fprintf(fp, "%.2f \n", averageSalarys);
    return averageSalarys;
}

//(G) in this function- output the first and last name of all women earning less than the average salary.
void womenGetLess (Employee workers[], int workerCounter, double averageSalaries){
    int i;
    
    printf(     "\n\n All women earning less than the average salary:\n");
    fprintf(fp, "\n\n All women earning less than the average salary:\n");
    
    for(i = 0; i < workerCounter; i++){
        if(workers[i].sex[0] == 'F' && workers[i].salary < averageSalaries){
            printf(     "%s %s\n", workers[i].first, workers[i].last);
            fprintf(fp, "%s %s\n", workers[i].first, workers[i].last);
        }
    }
}

//(H) in this function- output to 3 decimal places the ratio of the number of men above the average salary to the number  of men below the average salary.
void ratioMen (Employee workers[], int workerCounter, double averageSalaries){
    int i;
    int numMenTotal = 0;
    int numMenEarningMore = 0;
    int numMenEarningLess = 0;
    double ratioMenEarningMore;
    double ratioMenEarningLess;
    
    printf(     "\n\n The ratio of men earning above the average salary:\n");
    fprintf(fp, "\n\n The ratio of men earning above the average salary:\n");
    
    for(i = 0; i < workerCounter; i++){
        if(workers[i].sex[0] == 'M'){
            numMenTotal++;
        }
        if(workers[i].sex[0] == 'M' && workers[i].salary > averageSalaries){
            numMenEarningMore++;
        }
    }
    ratioMenEarningMore = (double) numMenEarningMore / numMenTotal;
    
    printf(     "%.3f\n",ratioMenEarningMore);
    fprintf(fp, "%.3f\n",ratioMenEarningMore);
    
    printf(     "\n\n The ratio of men earning below the average salary:\n");
    fprintf(fp, "\n\n The ratio of men earning below the average salary:\n");
    
    for(i = 0; i < workerCounter; i++){
        if(workers[i].sex[0] == 'M' && workers[i].salary < averageSalaries){
            numMenEarningLess++;
        }
    }
    ratioMenEarningLess = (double) numMenEarningLess / numMenTotal;
    
    printf(     "%.3f\n", ratioMenEarningLess);
    fprintf(fp, "%.3f\n", ratioMenEarningLess);
    
}

//(I) in this function- output the first and last name of all employees who make more than $35,000 per year, have been with the company for at least 5 years, and who are over 30 years old:
void outputVariousInfo (Employee workers[], int workerCounter){
    int i;
    double annualSalary = 0;
    int numWeeksInYear = 52;
    
    printf(     "\n\n The name(s) of all employees who make more than 35k, have been with the company for at least 5 years, and who are over 30 years old:\n");
    fprintf(fp, "\n\n The name(s) of all employees who make more than 35k, have been with the company for at least 5 years, and who are over 30 years old:\n");

    for(i = 0; i < workerCounter; i++){
        annualSalary = workers[i].salary * numWeeksInYear;
        if(annualSalary > 35000 && workers[i].tenure >= 5 && workers[i].age > 30){
            printf(     "%s %s\n", workers[i].first, workers[i].last);
            fprintf(fp, "%s %s\n", workers[i].first, workers[i].last);
        }
    }
}

//(J) Give a 10% raise to all employees who make less than $350.00 per week and output the first and last name and new salary for each of the employees who received the raise:

void gettingRaise (Employee workers[], int workerCounter){
    int i;
    double raiseAmount;
    double newRaisedSalaryAmount;
 
    printf(     "\n\n All employees who made less than $350 per week received a raise of 10 percent. Below are their names and their new salary amounts:\n");
    fprintf(fp, "\n\n All employees who made less than $350 per week received a raise of 10 percent. Below are their names and their new salary amounts:\n");
    for(i = 0; i < workerCounter; i++){
        if(workers[i].salary < 350.00){
            raiseAmount = workers[i].salary * .10;
            newRaisedSalaryAmount = raiseAmount + workers[i].salary;
            printf(     "%s %s %.2f\n", workers[i].first, workers[i].last, newRaisedSalaryAmount);
            fprintf(fp, "%s %s %.2f\n", workers[i].first, workers[i].last, newRaisedSalaryAmount);
        }
    }
}




