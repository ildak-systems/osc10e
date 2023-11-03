#include "schedulers.h"
#include "list.h"
#include "cpu.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

int totalTime = 0;
struct node *list = NULL;

bool comesBefore(char *a, char *b) { return strcmp(a, b) < 0; }

// modified pickNextTask(). Instead of comparing lexicographical, it compares burst time first,
// then lexicographical.
Task* pickNextTask() {
  // if list is empty, nothing to do
  if (!list)
    return NULL;

  struct node *temp;
  temp = list;
  Task *best_sofar = temp->task;

  while (temp != NULL) {
    if (temp->task->burst < best_sofar->burst)
    {
        best_sofar = temp->task;
    }
    else if (best_sofar->burst < temp->task->burst){}
    // if equal
    else
    {
        if (comesBefore(temp->task->name, best_sofar->name))
        {
            best_sofar = temp->task;
        }
    }
    temp = temp->next;
  }
  // delete the node from list, Task will get deleted later
  delete (&list, best_sofar);
  return best_sofar;
}

void add(char *name, int priority, int burst)
{
    Task *newTask = malloc(sizeof(Task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;

    insert(&list, newTask);
}

void schedule()
{
    Task* nextRun = pickNextTask();
    while (nextRun != NULL)
    {   
        run(nextRun, nextRun->burst);
        totalTime += nextRun->burst;
        printf("\t Time is now: %d \n", totalTime);
        nextRun = pickNextTask();
    }
}