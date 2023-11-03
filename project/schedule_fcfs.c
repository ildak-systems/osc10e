#include "schedulers.h"
#include "list.h"
#include "cpu.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// In this scenario, every task in schedule.txt arrives at the start of the program.
// run tasks by lexagraphical order
int totalTime = 0;

// make a schedule_fcfs.c specific List object that will store the incoming task
// consumed by add() called from driver.c
struct node *list = NULL;

bool comesBefore(char *a, char *b) { return strcmp(a, b) < 0; }

// based on traverse from list.c
// finds the task whose name comes first in dictionary
Task* pickNextTask() {
  // if list is empty, nothing to do
  if (!list)
    return NULL;

  struct node *temp;
  temp = list;
  Task *best_sofar = temp->task;

  while (temp != NULL) {
    if (comesBefore(temp->task->name, best_sofar->name))
    {
        best_sofar = temp->task;
    }
      
    temp = temp->next;
  }
  // delete the node from list, Task will get deleted later
  delete (&list, best_sofar);
  return best_sofar;
}

// add a task to the list: FCFS
void add(char *name, int priority, int burst)
{
    Task *newTask = malloc(sizeof(Task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;

    insert(&list, newTask);
}

// invoke the scheduler
void schedule()
{
    // simply run pickNextTask() using lexicographical order since
    // all tasks arrive at the same time in FCFS algorithm
    Task* nextRun = pickNextTask();
    while (nextRun != NULL)
    {   
        run(nextRun, nextRun->burst);
        totalTime += nextRun->burst;
        printf("\t Time is now: %d \n", totalTime);
        nextRun = pickNextTask();
    }
}