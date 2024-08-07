#include <stdio.h>
#include <stdlib.h>
#include <string.h>
float totalsalary ;
int  count = 0;
struct Employee
{
  int id;
  char name[50];
  char dept[30];
  float salary;
  int age;
  struct Employee *left;
  struct Employee *right;
};


struct Employee *createEmployee (int id, char name[], char dept[], int age, float salary)
{
  struct Employee *newEmployee = (struct Employee *) malloc (sizeof (struct Employee));
  newEmployee->id = id;
  strcpy (newEmployee->name, name);
  strcpy (newEmployee->dept, dept);
  newEmployee->salary = salary;
  newEmployee->age = age;
  newEmployee->left = NULL;
  newEmployee->right = NULL;
  totalsalary += salary;
  count++;
  return newEmployee;
}

struct Employee *insertEmployee (struct Employee *root, int id, char name[], char dept[],
		int age, float salary)
{
  if (root == NULL)
    {
      return createEmployee (id, name, dept, age, salary);
    }
  if (id < root->id)
    {
      root->left = insertEmployee (root->left, id, name, dept, age, salary);
    }
  else if (id > root->id)
    {
      root->right = insertEmployee (root->right, id, name, dept, age, salary);
    }
  return root;
}


struct Employee *searchEmployee (struct Employee *root, int id)
{
  if (root == NULL || root->id == id)
    {
      return root;
    }
  if (id < root->id)
    {
      return searchEmployee (root->left, id);
    }
  return searchEmployee (root->right, id);
}

struct Employee *removeEmployee(struct Employee *root, int id) {
    if (root == NULL) {
        printf("\n**Employee ID not found in database**\n");
        return root;
    }

    if (id < root->id) {
        root->left = removeEmployee(root->left, id);
    } else if (id > root->id) {
        root->right = removeEmployee(root->right, id);
    } else {

        if (root->left == NULL) {
            struct Employee *temp = root->right;
            free(root);
            count--;
            return temp;
        } else if (root->right == NULL) {
            struct Employee *temp = root->left;
            free(root);
            count--;
            return temp;
        }

        struct Employee *temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        root->id = temp->id;
        strcpy(root->name, temp->name);
        strcpy(root->dept, temp->dept);
        root->salary = temp->salary;
        root->age = temp->age;

        root->right = removeEmployee(root->right, temp->id);
    }
    return root;
}

void displayEmployee(struct Employee *root) {
  
  printf("\n");
  printf("Employee ID: %d\n", root->id);
  printf("Employee Name: %s\n", root->name);
  printf("Employee Department: %s\n", root->dept);
  printf("Employee Age: %d\n", root->age);
  printf("Employee Salary: %.2f\n", root->salary);
  printf("\n");
}

void displayAllEmployees(struct Employee *root) {
  if (root != NULL) {
    displayAllEmployees(root->left);
    displayEmployee(root);
    displayAllEmployees(root->right);
  }
}

float computeAverageSalary (struct Employee *root)
{
  if (root == NULL)
    {
      return 0.0;
    }
  return (totalsalary) / count;
}

int main ()
{
  struct Employee *root = NULL;
  int choice, id, age;
  char name[50], dept[30];
  float salary;
 printf("*******************************************************************\n");
  printf("***** Welcome to the Employee Management System *****\n");
  printf("*******************************************************************\n");

  while (1) {
    printf("\n");
    printf("1. Add New Employee\n");
    printf("2. Remove Existing Employee\n");
    printf("3. Search Employee by ID\n");
    printf("4. Display All Employee Details\n");
    printf("5. Compute Average Salary of All Employees\n");
    printf("6. Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        printf("Enter Employee ID: ");
        scanf("%d", &id);
        printf("Enter Employee Name: ");
        scanf("%s", name);
        printf("Enter Employee Age: ");
        scanf("%d", &age);
        printf("Enter Employee Department: ");
        scanf("%s", dept);
        printf("Enter Employee Salary: ");
        scanf("%f", &salary);

        root = insertEmployee(root, id, name, dept, age, salary);

        printf("\n*Employee Added Successfully*\n");
        break;

      case 2:
        
        printf("Enter Employee ID To Remove: ");
        scanf("%d", &id);

        struct Employee *removedEmployee = searchEmployee(root, id);
        if (removedEmployee == NULL) {
            printf("\n**Employee ID not found in database**\n");
        } else {
            root = removeEmployee(root, id);
            printf("\n**Employee Removed Successfully**\n");
        }
        break;

      case 3:
     
        printf("Enter Employee ID To Search: ");
        scanf("%d", &id);

        struct Employee *employee = searchEmployee(root, id);

        if (employee == NULL) {
          printf("\n*Sorry!, Employee not found in database*\n");
        } else {
          displayEmployee(employee);
        }
        break;

      case 4:
        printf("*******************************************************************\n");
        printf("***** Employee Details *****\n");
        printf("*******************************************************************\n");
        displayAllEmployees(root);
        break;

      case 5:
        
        printf("\nAverage Salary of All Employees: %.2f\n", computeAverageSalary(root));
        break;

      case 6:
       
        printf("\nExiting...\n");
        exit(0);

      default:
       
        printf("\n*****Invalid Choice. Please Try Again.*****\n");
    }
  }

  return 0;
}

