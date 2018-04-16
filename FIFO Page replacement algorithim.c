#include<stdio.h>

int main()
{
  int i,j,length,referenceString[50],frame[10],frameSize,k,avail,count=0;

  printf("\nEnter the length of the Reference string:\n");
  scanf("%d",&length);

  printf("\nEnter the reference string:\n");
  for(i=1;i<=length;i++)
  scanf("%d",&referenceString[i]);

  printf("\nEnter the number of Frames:");
  scanf("%d",&frameSize);

  for(i=0;i<frameSize;i++)
  frame[i]= -1;
  j=0;
  printf("   Reference string\t     page frames\n");
  for(i=1;i<=length;i++)
  {
    printf("\t%d\t\t",referenceString[i]);
    avail=0;
    for(k=0;k<frameSize;k++)
    if(frame[k]==referenceString[i])
    avail=1;
    if (avail==0)
    {
      frame[j]=referenceString[i];
      j=(j+1)%frameSize;
      count++;
      for(k=0;k<frameSize;k++)
      printf("%d\t",frame[k]);
    }
    printf("\n\n");
  }
  printf("Page Fault is %d\n",count);
  return 0;
}