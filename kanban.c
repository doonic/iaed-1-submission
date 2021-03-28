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


/* Macros*/

                   
#define START 1         /* true value for the command line parsing*/
 
#define TASKSMAX  10000 /* maximum number of tasks*/ 
 
#define TASKINFO 50     /* maximum number of characters of a task description*/

#define ACTIVITYMAX 10  /* maximum number of activities in the system*/

#define ACTIVITYINFO 20 /* maximum number of characters of an activity description*/

#define USERMAX 50      /* maximum number of users in the system*/
                        
#define USERNAME 20     /* maximum number of charactes of a user description*/  



/*  Definition of Structures type*/


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

int tasks_counter;       /*  counts the number of tasks in the system*/
int users_counter;       /*  counts the number of users in the system*/
int activities_counter;  /*  counts the number of activities in the system*/


// a global timer is it valid ?

/*  Function Prototypes*/

void addTaskToSystem();  /*  adds a new task to the system, command: t*/
void listTask();         /*  lists tasks in the system, command l*/
void advanceTimeSystem();/*  advances time of the system, command n*/
void addUserListUser();  /*  adds an user or lists all the users in the system, command u */
void moveTaskActivity(); /*  moves a Task from an activity to another, command m */
void listTaskActvity();  /*  lists all tasks in a given activity, command d*/
void addOrListActivity();/*  adds an activity or lists all activities in the system, command a*/


/* Auxiliary Functions*/

int duplicateInfo(char []);
int isTaskinSystem(int id);
int nonNegativeIntChecker(int time);
int isUserinSystem(char name[]);
int isActivityinSystem(char name[]);
int taskStage(Tasks_t task);
int activityNameChecker(Activity_t activity);



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