#define MAX 20
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

void *Student(void *param);
void *Teacher(void *param);

sem_t chairs_mutex;
sem_t sem_Student;
sem_t sem_Teacher;
int num_chairs = 3;
int StudentWait = 2;
int main() {
	pthread_t Teacherid;
	pthread_t Studentids[MAX];
	
	printf("Main thread beginning\n");
   
   int runTime,Students,i;
   
   printf("Enter Office hours\n");
   scanf("%d",&runTime);
   
   printf("Enter Number of student\n");
   scanf("%d",&Students);
    
    if(runTime<0 | Students<0)
    main();
   
   
   
   
   sem_init(&chairs_mutex,0,1);
   sem_init(&sem_Student,0,0);
   sem_init(&sem_Teacher,0,0);
   
   pthread_create(&Teacherid, NULL, Teacher, NULL);
   printf("Creating Teacher thread with id %lu\n",Teacherid);
   
   for (i = 0; i < Students; i++){
	   pthread_create(&Studentids[i], NULL, Student, NULL);
	   printf("Creating Student thread with id %lu\n",Studentids[i]);
   }
   
   printf("Main thread sleeping for %d seconds\n", runTime);
   sleep(runTime);
   
   printf("Main thread exiting\n");
   exit(0);
}

void *Teacher(void *param) {
   int worktime;
  
   while(1) {
      
	  sem_wait(&sem_Student);
      
	  sem_wait(&chairs_mutex);
      
	  num_chairs += 1;
	  printf("Teacher: Taking a Student. Number of chairs available = %d\n",num_chairs);
      
	  sem_post(&sem_Teacher);
      
	  sem_post(&chairs_mutex);
      
	  worktime = (rand() % 4) + 1;
      
	  printf("Teacher: Teaching for %d seconds\n", worktime);
	  sleep(worktime);
    } 
}

void *Student(void *param) {
   int waittime;

   while(1) {
      
	  sem_wait(&chairs_mutex);
      
	  if(num_chairs <= 0){
           
		   printf("Student: %u leaving without Teaching Help\n", (unsigned int)pthread_self());
		   sem_post(&chairs_mutex);
	  }
      
	  else{
           
		   num_chairs -= 1;
		   printf("Student: %u Sitting to wait. Number of chairs left = %d\n",(unsigned int)pthread_self(),num_chairs);
           
		   sem_post(&sem_Student);
           
		   sem_post(&chairs_mutex);
           
		   sem_wait(&sem_Teacher);
           
		   printf("Student: %u getting Teachers Help\n",(unsigned int)pthread_self());
	  }
      
	  waittime = (rand() % StudentWait) + 1;
      
	  printf("Student: %u waiting %d seconds before asking next question\n",(unsigned int)pthread_self(),waittime);
	  sleep(waittime);
     }
}

