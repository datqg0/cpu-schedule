//???
#include <bits/stdc++.h>
using namespace std;

struct process {
  string process_name;
  double arrival_time;
  double duration;
};

void display (vector<process>&process_box,vector<double>&gantt_chart_time,vector<string>&gantt_run_order,double&waitting_time) {
    cout<<0<<" ";
    for (double i=0;i<gantt_chart_time.size();i++) {
      cout<<gantt_run_order[i]<<" "<<gantt_chart_time[i]<<" ";
    }
    cout<<endl;
    cout<<"thoi gian cho trung binh la : "<<waitting_time/(double)(process_box.size());
}

void firstcomefirstserve (vector<process>&process_box,vector<string>&gantt_run_order,vector<double>&gantt_chart_time,double&waitting_time) {
  if(process_box.size()==0) {
    return;
  }
  double now=0;
  now=max(now,process_box[0].arrival_time);
  for (double i=0;i<process_box.size();i++) {
    if(now<process_box[i].arrival_time) {
      now=process_box[i].arrival_time;
      gantt_chart_time.push_back(now);
      gantt_run_order.push_back("N");
    }
    now=now+process_box[i].duration;
    gantt_chart_time.push_back(now);
    gantt_run_order.push_back(process_box[i].process_name);
    waitting_time+=(now-process_box[i].arrival_time);
  }
  display (process_box,gantt_chart_time,gantt_run_order,waitting_time);
  process_box.clear();
  gantt_chart_time.clear();
  gantt_run_order.clear();
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  //read some unused data
  string a,b,c;
  cin>>a>>b>>c;
  string s;
  vector<process> process_box;
  vector<double> gantt_chart_time;
  vector<string> gantt_run_order;
  double waitting_time=0;
  while(cin>>s) {
    double a,b;
    cin>>a>>b;
    process temp= {s,a,b};
    process_box.push_back(temp);
  }
  firstcomefirstserve(process_box,gantt_run_order,gantt_chart_time,waitting_time);
}
