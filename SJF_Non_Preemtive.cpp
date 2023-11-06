#include <bits/stdc++.h>
using namespace std;

struct Process{
    int pid;
    int bt;
    int art;
};

void findtrunarrountime(Process p[], int tat[], int wt[],int n){
    // turnaround time = brust time + waiting time
    for(int i=0;i<n;i++){
        tat[i] = p[i].bt + wt[i];
    }
}

void findwaitingtime(Process p[], int wt[], int n){
    // waiting time = finish - brust time - arrival time
    int rt[n];
    for(int i=0;i<n;i++){
        rt[i] = p[i].bt;
    }

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time = 0;

    bool check = false;
    while(complete != n){
        for(int i=0;i<n;i++){
            if(p[i].art <= t && rt[i] > 0 && rt[i] <minm){
                minm = rt[i];
                shortest = i;
                check = true;
            } 
        }

        if(!check){
            t++;
            continue;
        }

        rt[shortest] = 0;
        minm = INT_MAX;

        if(rt[shortest] == 0){
            complete++;
            check = false;

            finish_time = t;

            wt[shortest] = finish_time - p[shortest].art;

            if(wt[shortest] < 0) {
                wt[shortest] = 0;
            }
        }

        t+=p[shortest].bt;
    }
}

void sjf_non_preemtive(Process p[], int n){
    int wt[n], tat[n], time = 0, total_wt=0, total_tat = 0;

    findwaitingtime(p,wt,n);
    findtrunarrountime(p,tat,wt,n);
    cout<<" P\t\t"<<"BT\t\t"<<"WT\t\t"<<"TAT\t\t"<<endl;
    for(int i=0;i<n;i++){
        total_wt += wt[i];
        total_tat += tat[i];
        cout<<" "<<p[i].pid<<"\t\t"<<p[i].bt<<"\t\t"<<wt[i]<<"\t\t"<<tat[i]<<endl;
    } 
    cout<<"\nAverage waiting time = "<<(float)total_wt/(float)n;
    cout<<"\nAverage turn around time = "<<(float)total_tat/(float)n; 

}

int main(){
    int n = 4;
    // cout<<"Enter the number of process ";
    // cin>>n;

    // Process p[n];
    // for(int i=0;i<n;i++){
    //     cout<<"\nEnter the pid ";
    //     cin>>p[i].pid;
    //     cout<<"Enter the brust time ";
    //     cin>>p[i].bt;
    //     cout<<"Enter the arrival time ";
    //     cin>>p[i].art;
    // }

    Process p[] = {{1,7,0}, {2,4,2}, {3,1,4}, {4,4,5}};
    sjf_non_preemtive(p,n);
}