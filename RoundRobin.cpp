#include <iostream>
#include<iomanip>

using namespace std;

int qntm = 0;
int t = 0;

struct process
{
    int id,bt,at,tbt;
    int wt,tat;
    int st,et;
    process()
    {
        wt = 0;
        tat = 0;
    }
    void calculate()
    {
        st = t;
        t = et = st + bt;
    }
};

int find_max(process p[],int n)
{
    int temp = 0;
    int max_id;
    for(int i=0;i<n;i++)
    {
        if(p[i].bt>temp)
        {
            temp=p[i].bt;
            max_id = i;
        }
    }
    return max_id;
}
int main()
{
    int n;
    process p[10],p1[100];
    int max_burst;
    cout<<"Enter number of process : ";
    cin>>n;
    cout<<"\nEnter arival & burst"<<endl;
  
    for(int i = 0;i<n;i++)
    {
        p[i].id = i+1;
        cout<<"for process "<<i+1<<" : ";
        cin>>p[i].at>>p[i].bt;
        p[i].tbt = p[i].bt;
    }
    
	cout<<"\nEnter Quantum : ";
	cin>>qntm;
    max_burst = find_max(p,n);
    int c=0;
    while(p[max_burst].bt != 0)
    {
        for(int i = 0; i < n ; i++)
        {
            if(p[i].bt >= qntm)
            {
                p[i].bt -= qntm;
                p1[c].bt = qntm;
                p1[c].id = p[i].id;
                c++;
            }
            else if(p[i].bt > 0 && p[i].bt < qntm)
            {
                p1[c].bt = p[i].bt;
                p[i].bt = 0;
               
                p1[c].id = p[i].id;
                c++;
            }
        }
    }
	cout<<endl;
	cout<<setiosflags(ios::left)<<setw(9)<<"process"<<setw(9)<<"start"<<setw(9)<<"end"<<endl;
    for(int i = 0;i<c;i++)
    {
       
        p1[i].calculate();
        cout<<setw(9)<<p1[i].id<<setw(9)<<p1[i].st<<setw(9)<<p1[i].et<<endl;
        
    }
    float tWT = 0,tTAT = 0;
    for(int i = 0;i < n;i++)
    {
    
        int prev = -1;
        for(int j = 0 ;j < c;j++)
        {
            if(p1[j].id == p[i].id)
            {
                if(prev == -1)
                {
                    p[i].wt += p1[j].st - p[i].at;
                    prev = j;
                }
                else
                {
                    p[i].wt += p1[j].st - p1[prev].et;
                    prev = j;
                }
            }
        }
        tWT += p[i].wt; 
        p[i].tat = p[i].wt + p[i].tbt;
        tTAT += p[i].tat;
    }
    cout<<endl;
    
	cout<<setiosflags(ios::left)<<setw(10)<<"process"<<setw(16)<<"waiting time"<<setw(16)<<"turnaround time"<<endl;
    for(int i = 0;i<n;i++)
    { 
        cout<<setiosflags(ios::left)<<setw(10)<<p[i].id<<setw(16)<<p[i].wt<<setw(16)<<p[i].tat <<endl;
        
    }
    cout<<"\nAverage Waiting Time: "<<tWT/n<<",Average TurnAroundTime: "<<tTAT/n<<endl;
    
	system("PAUSE");
	return 0;
}
