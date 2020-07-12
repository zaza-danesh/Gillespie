
static struct itimerval init_v;
static struct itimerval init_r;
#define MAX 86400;
void init_etime(void)
{
   init_v.it_interval.tv_sec=0;
   init_v.it_interval.tv_usec=0;
   init_v.it_value.tv_sec=MAX;
   init_v.it_value.tv_usec=0;
   setitimer(ITIMER_VIRTUAL,&init_v,NULL);
   init_r.it_interval.tv_sec=0;
   init_r.it_interval.tv_usec=0;
   init_r.it_interval.tv_sec=MAX;
   init_r.it_interval.tv_usec=0;
   setitimer(ITIMER_REAL,&init_r,NULL);
}
double get_vtime(void)/*timpul virtual*/
{
   struct itimerval curent;
   getitimer(ITIMER_VIRTUAL,&curent);
   return (double) ((init_v.it_value.tv_sec-curent.it_value.tv_sec)+
   (init_v.it_value.tv_usec-curent.it_value.tv_usec)*1e-6);
}
double get_rtime(void)/*timpul real*/
{
   struct itimerval curent;
   getitimer(ITIMER_REAL,&curent);
   return (double) ((init_r.it_value.tv_sec-curent.it_value.tv_sec)+
   (init_r.it_value.tv_usec-curent.it_value.tv_usec)*1e-6);
}

