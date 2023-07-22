#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining maximum string characters
#define MAX 15

// Defining struct to represent a single student node in the singly linked list
struct Student{
 int id;
 char name[MAX+1];// +1 is used to allocate space for the null-terminator character used to mark the end of a string
 float gpa;
 struct Student*next;
};

// Declaring functions used
void addStudent(struct Student** head,int id,char* name,float gpa);
int deleteStudent(struct Student** head, int id);
void printList(struct Student* head);
struct Student** listToArray(struct Student* head,int* arraySize);
void printArray(struct Student** arr, int arraySize);


int main(void) {
 struct Student* head=NULL;
  addStudent(&head,2,"Bob",3.7);
  addStudent(&head,10,"Jack",3.0);
  addStudent(&head,3,"Charlie",3.5);
  addStudent(&head,6,"Frank",3.1);
  addStudent(&head,7,"Grace",3.4);
  addStudent(&head,9,"Ivy",3.2);
  addStudent(&head,5,"Eva",3.8);
  addStudent(&head,1,"Alice",3.9);
  addStudent(&head,8,"Hank",3.3);
  addStudent(&head,4,"David",3.6);

  printList(head);
  
  deleteStudent(&head,1);
  printList(head);

  deleteStudent(&head,5);
  printList(head);

  deleteStudent(&head,10);
  printList(head);

  deleteStudent(&head,11);
  printList(head);

  int arraySize;
  struct Student** arr=listToArray(head,&arraySize);
  printArray(arr,arraySize);
  
  return 0;
}

// Defining the function used to add a new student to the linked list
void addStudent(struct Student** head,int id,char* name,float gpa){
     // Creating new student node using dynamic memory allocation
  struct Student* newStudent=(struct Student*)malloc(sizeof(struct Student));
     // Adding the student id to the id field of the new student node
  newStudent->id=id;
     // Copying student name to the name field of the new student node
  int i=0;
  while(name[i]!='\0' && i<MAX){
    newStudent->name[i]=name[i];
    i++;
  }
     // Ensure the name is properly null-terminated
  newStudent->name[i]='\0';
     // Adding the student gpa to the gpa field of the new student node
  newStudent->gpa=gpa;
  newStudent->next=NULL;
     // Making sure that the ascending order is maintained when adding new nodes
  if(*head==NULL || (*head)->id>=id){
    newStudent->next=*head;
    *head=newStudent;
  }else{
    struct Student* current=*head;
    while(current->next!=NULL && current->next->id<id){
      current=current->next;
    }
    newStudent->next=current->next;
    current->next=newStudent;
  }
}


// Defining the funtion used to delete a student node based on provided id
int deleteStudent(struct Student** head, int id){
     // Checking if the linked list is empty
  if(*head==NULL){
    printf("List is empty");
    return;
  }
     // If the deleting node is the head of the list, updating the head to the next node and freeing the old head node
  if((*head)->id==id){
    struct Student*temp=*head;
    *head=(*head)->next;
    free(temp);
    return 1;
  }
     // Traversing the list until the node with matching id is found
  struct Student* current=*head;
  while(current->next!=NULL && current->next->id !=id){
    current=current->next;
  }
     // Displaying student not found if the node with matching id is not found
  if(current->next==NULL){
    printf("Failure,Student not found\n\n");
    return 0;
  }
     // If the node with matching id is found pointing the next of previous to the next node of that node and freeing the matching node
  struct Student* temp=current->next;
  current->next=temp->next;
  free(temp);
  return 1;
}


// Defining the function used to print the linked list
void printList(struct Student* head){
  printf("List:\n");
  struct Student* current=head;
  while(current!=NULL){
    printf("ID: %d,Name: %s,GPA: %.1f\n",current->id,current->name,current->gpa);
    current=current->next;
  }
  printf("\n");
}


// Defining the function used to convert the linked list to an array
struct Student** listToArray(struct Student* head,int* arraySize){
     // Finding the number of elements in the linked list
  int size=0;
  struct Student*current=head;
  while(current!=NULL){
    size++;
    current=current->next;
  }
     // Creating a new array of pointers to struct Student with correct size
  struct Student**arr=(struct Student**)malloc(size* sizeof(struct Student*));
     // Copying each element form the linked list to the array
  current=head;
  int i=0;
  while(current!=NULL){
    arr[i]=(struct Student*)malloc(sizeof(struct Student));
    arr[i]->id=current->id;
     // Copying the name character by character
    int j=0;
    while(current->name[j]!='\0' && j<MAX){
      arr[i]->name[j]=current->name[j];
      j++;
    }
    arr[i]->name[j]='\0';
    arr[i]->gpa=current->gpa;
    arr[i]->next=NULL;
    current=current->next;
    i++;
  }
  *arraySize=size;
  return arr;
}

// Defining the function used to print the created array
void printArray(struct Student** arr, int arraySize){
  printf("Array:\n");
  for(int i=0;i<arraySize;i++){
    printf("Array[%d]->ID: %d, Name: %s, GPA: %.1f\n",i,arr[i]->id,arr[i]->name,arr[i]->gpa);
  }
  printf("\n");
}

