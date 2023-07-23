#include<stdio.h>
#include<string.h>
#include<stdlib.h>

	int m=8;
	FILE *u,*p,*logger,*loggerw;
	char user[20],pass[20],pass2[20],value,len,lg;


//declear the functions
void addEmployee();
void searchEmployee();
void deleteEmployee();
void getSalaryReport();
void displayAllEmployees();
int getEmployeeCount();
void updateEmployee();
void signup();
void login();

//HR system main menu
int main(){
	
	signup();
	
	int option;
	

    	printf("\t\t\t  Main Menu\n");
    	printf("\t\t\t-------------\n\n");
	
	printf("\t\t[1] Add Employee\n");
	printf("\t\t[2] Search Employee\n");
	printf("\t\t[3] Delete Employee\n");
	printf("\t\t[4] Salary Report\n");
	printf("\t\t[5] Display All Employee\n");
	printf("\t\t[6] Count Employee\n");
	printf("\t\t[7] Update Employee\n");
	
	printf("\n\nSelect Option :");
	scanf("%d",&option);
	
	switch(option){
		case 1:
			addEmployee();
			break;
		case 2:
			searchEmployee();
			break;
		case 3:
			deleteEmployee();
			break;
		case 4:
			getSalaryReport();
			break;
		case 5:
			displayAllEmployees();
			break;
		case 6:
			getEmployeeCount();
			break;
		case 7:
			updateEmployee();
			break;
		default:
			printf("\n\n\t\tEnter Above Number");
			printf("\n\n\t\t\tPress any key to Re enter.....");
			main();
		}
}


// Define the Employee structure
struct Employee{
    int id;
    char name[50];
    char department[50];
    float salary;
    int age;
};

// Function to add a new employee to the system
void addEmployee() {
	printf("\t---------------------------------------\n\n");
  	printf(" \t\t**** Add Employee ****\n\n");
  	printf("\t---------------------------------------\n\n");
	char op;
	do{

	    struct Employee e;
	    FILE *fp = fopen("employees.txt", "a");
	    printf("\nEnter employee ID: ");
	    scanf("%d", &e.id);
	    printf("\nEnter employee name: ");
	    scanf("%s", e.name);
	    printf("\nEnter employee department: ");
	    scanf("%s", e.department);
	    printf("\nEnter employee salary: ");
	    scanf("%f", &e.salary);
	    fprintf(fp, "%d %s %s %.2f\n", e.id, e.name, e.department, e.salary);
	    fclose(fp);
	printf("\n\n----------------------------\nDo you want to continue press (C)...\nGo to main menu press (M)...");
	scanf(" %c",&op);
	if(op=='m' || op=='M'){
		main();
		}
	}while(op=='c' || op=='C');
}

// Function to display all employees in the system
void displayAllEmployees() {
    printf("\t---------------------------------------\n\n");
    printf(" \t\t**** Display All Employees ****\n\n");
    printf("\t---------------------------------------\n\n");
    struct Employee e;
    FILE *fp = fopen("employees.txt", "r");
    printf("\nEmployees in the system:\n\n");
    printf("%-10s %-15s %-10s %-15s\n", "id","Employee Name","Department", "Salary");
    printf("-------------------------------------------------\n");
    while (fscanf(fp, "%d %s %s %f", &e.id, e.name, e.department, &e.salary) != EOF) {
        printf("%-10d %-15s %-10s Rs.%-14.2f\n", e.id, e.name, e.department, e.salary);
    }
    
    
    char op;
    printf("Do You Want to Continue [Y] :");
    getchar();
    scanf("%c",&op);
    if(op=='y'||op=='Y'){
    	main();
    }
    fclose(fp);
    
}

// Function to search for an employee by ID
void searchEmployee() {
    printf("\t---------------------------------------\n\n");
    printf(" \t\t**** Search Employee ****\n\n");
    printf("\t---------------------------------------\n\n");
    struct Employee e;
    int searchID;
    printf("\nEnter employee ID to search for: ");
    scanf("%d", &searchID);
    FILE *fp = fopen("employees.txt", "r");
    while (fscanf(fp, "%d %s %s %f", &e.id, e.name, e.department, &e.salary) != EOF) {
        if (e.id == searchID) {
            printf("\nEmployee found!\n\n");
            printf("-------------------\n");
            printf("ID:         %d\n", e.id);
            printf("Name:       %s\n", e.name);
            printf("Department: %s\n", e.department);
            printf("Salary:     %.2f\n", e.salary);
            printf("-------------------\n");
            fclose(fp);
            char op;
	    printf("Do You Want to Continue [Y] :");
	    getchar();
	    scanf("%c",&op);
	    if(op=='y'||op=='Y'){
	    	main();
	    }
        }
    }
    printf("\nEmployee not found.\n");
    fclose(fp);
    char op;
    printf("Do You Want to Try again [Y] :");
    getchar();
    scanf("%c",&op);
    if(op=='y'||op=='Y'){
    	searchEmployee();
    }
}

// Function to update an employee's information by ID
void updateEmployee(int id) {
    printf("\t---------------------------------------\n\n");
    printf(" \t\t**** Update Employee Details ****\n\n");
    printf("\t---------------------------------------\n\n");
    struct Employee emp;
    FILE *fp;
    FILE *tmpfp;
    char line[1000];
    int found = 0;

    fp = fopen("employees.txt", "r");
    tmpfp = fopen("temp.txt", "w");
    if (fp == NULL || tmpfp == NULL) {
        printf("Error opening file");
        return;
    }
    printf("Enter Employee ID to Update Info. :");
    scanf("%d",&id);
    while (fgets(line, 1000, fp)) {
        sscanf(line, "%d %s %s %f", &emp.id, emp.name, emp.department,&emp.salary);
        if (emp.id == id) {
            found = 1;
            printf("Enter new details for employee %d:\n", id);
            printf("Name: ");
            scanf("%s", emp.name);
            printf("Salary: ");
            scanf("%f", &emp.salary);
            printf("Department: ");
            scanf("%s", emp.department);

            fprintf(tmpfp, "%d %s %s %.2f\n", emp.id, emp.name, emp.department, emp.salary);
            printf("Employee details updated successfully.\n");
        }
        else {
            fprintf(tmpfp, "%s", line);
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }

    fclose(fp);
    fclose(tmpfp);
    remove("employees.txt");
    rename("temp.txt", "employees.txt");
    char op;
    printf("Do You Want to Continue [Y] :");
    getchar();
    scanf("%c",&op);
    if(op=='y'||op=='Y'){
    	main();
    }
}


void deleteEmployee(int id) {
  printf("\t---------------------------------------\n\n");
  printf(" \t\t**** Delete Employee ****\n\n");
  printf("\t---------------------------------------\n\n");
  scanf("%d",&id);
  struct Employee emp;
  FILE *fp, *temp;

  fp = fopen("employees.txt", "r");
  if (fp == NULL) {
    printf("Error opening file");
    return;
  }

  temp = fopen("temp.txt", "w");
  if (temp == NULL) {
    printf("Error opening file");
    return;
  }

  while (fscanf(fp, "%d %s %s %f", &emp.id, emp.name, emp.department, &emp.salary) == 4) {
    if (emp.id != id) {
      fprintf(temp, "%d %s %s %.2f\n", emp.id, emp.name, emp.department, emp.salary);
    }
  }

  fclose(fp);
  fclose(temp);
  remove("employees.txt");
  rename("temp.txt", "employees.txt");
  printf("Employee with ID %d deleted successfully.\n", id);
  char op;
    printf("Do You Want to Continue [Y] :");
    getchar();
    scanf("%c",&op);
    if(op=='y'||op=='Y'){
    	main();
    }
}


void getSalaryReport() {
  int searchid;
  printf("\t---------------------------------------\n\n");
  printf(" \t\t**** Salary Report ****\n\n");
  printf("\t---------------------------------------\n\n");
  printf("\nEnter employee ID to Get Salary report : ");
  scanf("%d", &searchid);
  struct Employee emp;
  FILE *fp;
  
  
  
  

  fp = fopen("employees.txt", "r");
  if (fp == NULL) {
    printf("Error opening file\n");
    main();
  }

  float totalSalary = 0.0;

  
  
  while (fscanf(fp,"%d %s %s %f", &emp.id, emp.name, emp.department, &emp.salary) !=EOF) {
    int insurance=2000;    
    if (emp.id == searchid) {
      float salary = emp.salary-insurance;
      totalSalary += salary;
      printf("\tName:%s\n\tBasice salary: Rs.%.2f\n\tTotal salary: RS.%.2f\n\n", emp.name, emp.salary,totalSalary);
      fclose(fp);
      return;
    }
  }

  if (totalSalary > 0.0) {
    printf("\nTotal salary: $%.2f\n", totalSalary);
  } else {
    printf("\nNo data found for employee with ID %d\n", searchid);
  }

  fclose(fp);
  char op;
    printf("Do You Want to Continue [Y] :");
    getchar();
    scanf("%c",&op);
    if(op=='y'||op=='Y'){
    	getSalaryReport();
    }else{
    	main();
    	}
}


// Function to get the total number of employees in the system
int getEmployeeCount() {
    printf("\t---------------------------------------\n\n");
    printf(" \t\t**** Employee Count ****\n\n");
    printf("\t---------------------------------------\n\n");
    FILE *fp;
    int count = 0;
    char ch;
    
    // Open the file in read mode
    fp = fopen("employees.txt", "r");

    // If the file doesn't exist or is empty, return 0
    if (fp == NULL || feof(fp)) {
        printf("%d Employees are work here\n",count);
    }
    
    // Count the number of lines in the file
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }
    
    // Close the file
    fclose(fp);
    
    // Return the total count of employees
    printf("%d Employees are work here\n",count);
    char op;
    printf("Do You Want to Continue [Y] :");
    getchar();
    scanf("%c",&op);
    if(op=='y'||op=='Y'){
    	main();
    }
}

void signup(){

        char log_y_val='y';
        //logo part
        printf("\t---------------------------------------------------------------\n\n");
        printf(" \t\t**** Human Resource Management System ****\n\n");
        printf("\t---------------------------------------------------------------\n\n");

           //log file open
        logger=fopen("log.txt","r");
        // if log file doesnt have ,create newone
        if(logger==NULL){
            logger=fopen("log.txt","w");
            fprintf(logger,"n");
            fclose(logger);
            logger=fopen("log.txt","r");
            printf("installing file successfull \nplease log again....");
            exit(1);
        }

		// account details file for use in login
        fscanf(logger,"%c",&lg);
        u=fopen("ufile.txt","r+");
        p=fopen("pfile.txt","r+");
        fscanf(u,"%s",user);
        fscanf(p,"%s",pass);
        //checking already sign up and login
        if(lg=='y'){

                fclose(logger);
                login();

                }
		//if dont have account
        else if(lg=='n'){
        fclose(u);
        fclose(p);
        u=fopen("ufile.txt","w");
        p=fopen("pfile.txt","w");
        fclose(u);
        fclose(p);
        u=fopen("ufile.txt","r+");
        p=fopen("pfile.txt","r+");
        printf("----------Sign up ---------- \n\n");
        printf("Enter Username : ");
        scanf("%s",user);



do{
    loggerw=fopen("log.txt","w");

    printf("Enter password : ");
    scanf("%s",pass);

    printf("Re-Enter password : ");
    scanf("%s",pass2);
	//check password validation
    len = strlen(pass);
    value=strcmp(pass,pass2);

       if(value==0){
             len = strlen(pass);
            if(len<8){
                printf("Length is too short\n \n");

                     }
            else{


                fprintf(u,"%s",user);
                fprintf(p,"%s",pass);


                fprintf(loggerw,"%c",log_y_val);
                fclose(logger);
                printf("Account create Succesfully \n");
                login();

                break;

		  	}
	}
   	else{

   printf("Password Does not Match\n\n Ty Again...\n \n");
        }


	}
	while(m!=0);
}



    fclose(u);
    fclose(p);

}
 
void login(){
    char value,loguser[20],logpass[20],logpass2[20],valueuser,valuepass;
    int m=8;
    printf("---------------------------------------------------------------\n\n");
        printf(" **** Human Resource Management System ****\n\n");
    printf("\n----------Login Here---------\n\n");


    do{
    printf("Enter Username : ");
    scanf("%s",loguser);
    printf("Enter password : ");
    scanf("%s",logpass);

    //compare username and password with older username and password
    valueuser=strcmp(user,loguser);
    valuepass=strcmp(pass,logpass);

     //accept len>8 and password and username match
     if(valueuser==0 && valuepass==0){

         printf("Loggin Success\n");
            break;

       }

        else{

       printf("\nUsername or Password Incorrect\n \n");

            }
	





    }
    while(m!=0);
    

}

	
