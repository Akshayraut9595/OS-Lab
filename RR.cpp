#include <bits/stdc++.h>
using namespace std;

struct Process{
    int pid;
    int bt;
    int art;
};

void findwaitingtime(Process p[], int wt[], int n, int qt){
    queue<int>rq;
    int completed = 0, t=0;

    int rt[n];
    for(int i=0;i<n;i++){
        rt[i] = p[i].bt;
    } 
    int i=0;
    while(completed != n){
        while(i<n &&p[i].art<=t && rt[i] >0){
            rq.push(i);
            i++;
        }
        if(rq.size()>0){
            int idx = rq.front();
            rq.pop();
            
            if(rt[idx] > qt){
                rt[idx] -= qt;
                t+=qt;
            }
            else if(rt[idx] <= qt){
                t += rt[idx];
                rt[idx] = 0;
                completed++;

                wt[idx] = t - p[idx].bt-p[idx].art;
                cout<<t<<" "<<p[idx].bt<<" "<<p[idx].art<<endl;
            }
            else{
                t++;
            }
            while(i<n &&p[i].art<=t && rt[i] >0){
                rq.push(i);
                i++;
            }
            if(rt[idx] > 0){
                rq.push(idx);
            }
        }
    }
}

void findturnaround(Process p[], int wt[], int tat[], int n){
    for(int i=0;i<n;i++){
        tat[i] = p[i].bt+wt[i];
    }
}

void round_robin(Process proc[], int n, int qt){
    int wt[n], tat[n],total_wt=0,total_tat=0;

    findwaitingtime(proc,wt,n, qt);

    findturnaround(proc,wt,tat,n);

    cout << " P\t\t"<< "BT\t\t"<< "WT\t\t"<< "TAT\t\t\n"; 

	// Calculate total waiting time and total turnaround time 
	for (int i = 0; i < n; i++) { 
		total_wt = total_wt + wt[i]; 
		total_tat = total_tat + tat[i]; 
		cout << " " << proc[i].pid << "\t\t"<< proc[i].bt << "\t\t " << wt[i] << "\t\t " << tat[i] << endl; 
	} 

	cout << "\nAverage waiting time = "<< (float)total_wt / (float)n; 
	cout << "\nAverage turn around time = "<< (float)total_tat / (float)n; 
}

int main(){
    int n;
    cout<<"Enter the number of process ";
    cin>>n;

    Process p[n];
    for(int i=0;i<n;i++){
        cout<<"\nEnter the pid ";
        cin>>p[i].pid;
        cout<<"Enter the brust time ";
        cin>>p[i].bt;
        cout<<"Enter the arrival time ";
        cin>>p[i].art;
    }

    int q;
    cout<<"Enter the time slice ";
    cin>>q;

    round_robin(p,n,q);

	return 0; 
}