#include <stdio.h>
/*定义一个进程*/
struct pcb{
  int id;
  int arr_time;/*到达时间*/
  int req_time;/*进程执行时间*/
  int end_time;
  int cir_time;/*进程周转时间*/
};

struct pcb p[10],temp_p;/*定义结构体数组和变量*/
int q;
int num,sum_cir_time;/*定义进程周转时间*/
main()
{
   int i,j;
   for(i=0;i<10;i++) {
      p[i].id=999;

      p[i].end_time=0;
      p[i].cir_time=0;
    }

   printf("\nPlease input Process info:id,arr_time,req_time\n");
   for(i=0;i<10;i++)
   {
      scanf("%d,%d,%d\n",&p[i].id,&p[i].arr_time,&p[i].req_time);
      if (p[i].id==-999) { p[i].id=999;break;}
   }

   for (i=0;i<9;i++)
    for (j=i+1;j<10;j++)
	if (p[i].arr_time>p[j].arr_time){
	   temp_p=p[i];
	   p[i]=p[j];
	   p[j]=temp_p;
	}

   sum_cir_time=p[0].arr_time;
   num=0;
   for(i=0;i<10;i++)
     if (p[i].id<999) {
	 num++;/*如果ID<999，则总进程数+1*/
	 sum_cir_time=p[i].req_time + sum_cir_time;
	 p[i].end_time=sum_cir_time;
	 p[i].cir_time=p[i].end_time-p[i].arr_time;
      }

   for(i=0;i<10;i++)
    printf("%5d%9d%9d%9d%9d\n",p[i].id,p[i].arr_time,p[i].req_time,p[i].end_time,p[i].cir_time);

   sum_cir_time=sum_cir_time-p[0].arr_time;

   printf("Schedule Result:\n");
   printf("id  arr_time req_time end_time cir_time:\n");
   for(i=0;i<10;i++)
   {
      if (p[i].id<999)
	  printf("%5d%9d%9d%9d%9d\n",p[i].id,p[i].arr_time,p[i].req_time,p[i].end_time,p[i].cir_time);
   }

   printf("Total Cir_time: %d\n",sum_cir_time);
   printf("Average Cir_time: %d\n",sum_cir_time/num);
}
