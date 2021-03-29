/*
 *
 *File: kanban.c
 *Author: Allan Donizette Cravid Fernades, nº 97281
 *Description: a schedulling system for tasks management
 *  
 */


/*  Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


/*  Macros*/               
#define START 1         /* true value for the command line parsing*/
#define TASKSMAX  10000 /* maximum number of tasks*/ 
#define TASKINFO 50     /* maximum number of characters of a task description*/
#define ACTIVITYMAX 10  /* maximum number of activities in the system*/
#define ACTIVITYINFO 20 /* maximum number of characters of an activity description*/
#define USERMAX 50      /* maximum number of users in the system*/
#define USERNAME 20     /* maximum number of characters of an user description*/
#define ONE 1           /* comparison/computation value*/

  


/*booleans definitons*/
typedef enum {false = 0,true = !false}boolean;

/*  Definition of Structures type*/

/*
 * Structure Name: Activity_t
 * ----------------------
 * Description: Activity structure definition
 * A task is characterized by the following:
 * 
 *         * a name,       what is it with want to accomplish 
 * 
 */

typedef struct{

    char name[ACTIVITYINFO];
    

}Activity_t;


/*
 * Structure Name: User_t
 * ----------------------
 * Description: User structure definition
 * A task is characterized by the following:
 * 
 *         * a name
 * 
 */

typedef struct{

    char name[USERNAME];

}User_t;

/*
 * Structure Name: Task_t
 * ----------------------
 * Description: Task structure definition
 * A task is characterized by the following:
 * 
 *          * an identifier,    id
 *          * a description,    info
 *          * an user
 *          * an activity 
 *          * a duration
 *          * a starting time   instant
 * 
 */

typedef struct{ 

    short int id;
    char info[TASKINFO];
    User_t user;
    Activity_t activity;
    short int duration;
    short int instant;

}Tasks_t;

/*  (Global)*/

/* array variables*/

                        /*  an array of Users in which the index indentifies the current user,
                        the system supports a
                        maximum of 50 users*/
User_t users[USERMAX];

                        /*  an array of Activities in which the index indentifies the current
                        activity,the system allows a
                         maximum of 10 activities */
Activity_t activities[ACTIVITYMAX];

                         /*  an array of Tasks, the index + 1 indentifies the current task 
                         externally,the system supports
                         a maximum of 1000 tasks*/
Tasks_t tasks[TASKSMAX];



/*  variables*/
int tsk_counter;       /*  counts the number of tasks in the system*/
int usr_counter;       /*  counts the number of users in the system*/
int act_counter;       /*  counts the number of activities in the system*/
int clock;             /*  current time in the system, associated with the command n*/
int task_id_tracker;    /*  tracks */

/*  Function Prototypes*/

void addTaskToSystem();  /*  adds a new task to the system, command: t*/
void listTask();         /*  lists tasks in the system, command l*/
void advanceTimeSystem();/*  advances time of the system, command n*/
void addUserListUser();  /*  adds an user or lists all the users in the system, command u */
void moveTaskActivity(); /*  moves a Task from an activity to another, command m */
void listTaskActvity();  /*  lists all tasks in a given activity, command d*/
void addOrListActivity();/*  adds an activity or lists all activities in the system, command a*/

/* Auxiliary Functions*/


int isTaskinSystem(int id); /* done  */
int nonNegativeIntChecker(int time); 
int isUserinSystem(char name[]); /*done*/
/*
int isActivityinSystem(char name[]); // not  
int taskStage(Tasks_t task); // not  
int activityNameChecker(Activity_t activity); // not 
*/
int isTaskInfoDuplicated(char s[]);  /*done */ 



int  main(){

    char cmd;

    while(START){
        
        cmd = getchar();
        switch(cmd){
            case    'q':
                return EXIT_SUCCESS;

            case    't':
                addTaskToSystem();
                break;

            case    'l':
                listTask();
                break;

            case    'n':
                advanceTimeSystem();
                break;

            case    'u':
                addUserListUser(); 
                break;

            case    'm':
                moveTaskActivity();
                break;

            case    'd':
                listTaskActvity();
                break;

            case    'a':
                addOrListActivity();
                break; 
        }
        
    }
    return EXIT_FAILURE;
}


/* Auxiliary Functions Definitions*/

int  nonNegativeIntChecker(int num){
    
    int res;
    res = (num >= false) ? true:false;
    return res;
}

int isTaskInfoDuplicated(char s[]){

    int i;
    
    for(i = 0; i < tsk_counter;i++){
        if(tasks[tsk_counter].info == s){
            return true;
        }
    }
    return false;
}

/* verifies if an user name is already in the system*/
int isUserinSystem(char name[]){

    int i;

    for(i = 0; i < usr_counter; i++){
        if(strcmp(users[i].name,name) == false){
            return true;
        }
    }
    return false;
}

/* verifies if the task with the given id is in the system*/
int isTaskinSystem(int id){

    int i;
    for(i = 0; i < tsk_counter; i++){
        if(tasks[tsk_counter].id == id){
            return true;
        }
    }
    return false;
}

 /*  main functions */


void addTaskToSystem(){

    int duration;
    char info[TASKINFO];
    scanf("%d%[^\n]s",&duration,info);

    if(!(info[0] == '\0') && nonNegativeIntChecker(duration)){
        
        if(tsk_counter > TASKSMAX){
            printf("too many tasks");
        }
        else if(isTaskInfoDuplicated(info)){
            printf("duplicate description");
        }
        else{
            tasks[tsk_counter].duration = duration;
            tasks[tsk_counter].id = tsk_counter + ONE;
            strcpy(tasks[tsk_counter].info,info);
            printf("task %d\n",tasks[tsk_counter].id);
            tsk_counter++;
        }       
    }

}

void  listTask(){
    /*int c,status = false,i;*/

    getchar(); /*removes the first white space*/

} 

void  advanceTimeSystem(){

    int duration;
    scanf("%d",&duration);

    if(!nonNegativeIntChecker(duration)){
        printf("invalid time");

    }
    else{
        clock++;
        printf("%d\n",clock);
        
    }


}

void  addUserListUser(){ /*Command u*/
    char user[USERMAX];
    int i = 0,savechar,c;      /*associado a presenca unicamente de carateres brancos */

    /*removes the first white space immediately after the u command */
    getchar();

    savechar = getchar(); /*checks whether or not the following character is a blank space */
    putchar(savechar);

    if(!(isspace(savechar))){

        user[0] = savechar; /*saves the first non whitespace character to an auxiliary array*/
	    while ((c=getchar())!='\n' && c!=EOF && i < USERNAME){
            user[i++] = c;
        }
        user[i] = '\0';
        if(isUserinSystem(user)){
            print("user already exists");

        }
        else if(usr_counter > USERMAX){
            printf("too many users");
        }
        else{
        printf("%s",user);
        strcpy(users[usr_counter].name,user); 
        usr_counter++;  /*increases the number of users in the system*/
        }
    }
    else{
        putchar('a');
    }
    
    
}

void moveTaskActivity(){
    ;
}
void listTaskActvity(){
    ;

}
void addOrListActivity(){
    ;
}