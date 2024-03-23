#include <bits/stdc++.h>
using namespace std;

struct process {
  string process_name;
  double arrival_time;
  double duration;
  double prioritydegree;
};
// write the result
void display (vector<process>&process_box,vector<double>&gantt_chart_time,vector<string>&gantt_run_order,double&waitting_time) {
    cout<<0<<" ";
    for (double i=0;i<gantt_chart_time.size();i++) {
      cout<<gantt_run_order[i]<<" "<<gantt_chart_time[i]<<" ";
    }
    cout<<endl;
    cout<<"thoi gian cho "<<waitting_time<<endl;
    cout<<"thoi gian cho trung binh la : "<<waitting_time/(double)(process_box.size());
    cout<<endl<<endl;
}
//custom comparator for priority queue
class priority {
  public:
    bool operator () (process&a,process&b) {
        if(a.prioritydegree>b.prioritydegree) {
          return true;
        }
        if(a.prioritydegree==b.prioritydegree) {
          return a.arrival_time>b.arrival_time;
        }
        return false;
    }
};

void PS2 (vector<process>&process_box,vector<string>&gantt_run_order,vector<double>&gantt_chart_time,double&waitting_time) { 
  if(process_box.size()==0) {
    return;
  }
  int n=process_box.size();
  int i=1;
  int now=0;
  priority_queue<process,vector<process>,priority> pq;
  pq.push(process_box[0]);
  now=process_box[0].arrival_time;
  while(i<n&&process_box[i].arrival_time<=now) {
    pq.push(process_box[i]);
    i++;
  }
  process current;
  current.arrival_time=-1;
  while(pq.empty()==false||i<n) {
    if(current.arrival_time==-1) {
      current=pq.top();
      pq.pop();
      if(now<current.arrival_time) {
        gantt_chart_time.push_back(current.arrival_time);
        gantt_run_order.push_back("N");
        now=current.arrival_time;
      }
    }
    else {
      if(current.prioritydegree>pq.top().prioritydegree) {
        process temp = pq.top();
        pq.pop();
        pq.push(current);
        current=temp;
      }
    }
    int take=now;
    if(i<n) {
      int av_time=process_box[i].arrival_time-now;
      if(av_time>=current.duration) {
        if(gantt_run_order.size()==0||gantt_run_order[gantt_run_order.size()-1]!=current.process_name) {
          gantt_run_order.push_back(current.process_name);
          now+=current.duration;
          gantt_chart_time.push_back(now);
          waitting_time+=(take-current.arrival_time);
          current.arrival_time=-1;
        }
        else {
          now+=current.duration;
          gantt_chart_time[gantt_chart_time.size()-1]=now;
          current.arrival_time=-1;
        }
      }
      else {
        if(gantt_run_order.size()==0||gantt_run_order[gantt_run_order.size()-1]!=current.process_name) {
          now+=av_time;
          gantt_run_order.push_back(current.process_name);
          gantt_chart_time.push_back(now);
          current.duration-=av_time;
          waitting_time+=(take-current.arrival_time);
          current.arrival_time=now; 
        }
        else {
          now+=av_time;
          gantt_chart_time[gantt_chart_time.size()-1]=now;
          current.duration-=av_time;
          current.arrival_time=now; 
        }
      }
    }
    else {
      if(gantt_run_order.size()==0||gantt_run_order[gantt_run_order.size()-1]!=current.process_name) {
          gantt_run_order.push_back(current.process_name);
          now+=current.duration;
          gantt_chart_time.push_back(now);
          waitting_time+=(take-current.arrival_time);
          current.arrival_time=-1;    
        }
        else {
          now+=current.duration;
          gantt_chart_time[gantt_chart_time.size()-1]=now;
          current.arrival_time=-1;
        }
    }
    while(i<n&&process_box[i].arrival_time<=now) {
        pq.push(process_box[i]);
        i++;
    }
  }
  display (process_box,gantt_chart_time,gantt_run_order,waitting_time);
  gantt_chart_time.clear();
  gantt_run_order.clear();
  waitting_time=0;
}

void PS1 (vector<process>&process_box,vector<string>&gantt_run_order,vector<double>&gantt_chart_time,double&waitting_time) { 
  if(process_box.size()==0) {
    return;
  }

  //cout<<"run"<<endl;
  int n=process_box.size();
  int i=1;
  int now=0;
  priority_queue<process,vector<process>,priority> pq;
  pq.push(process_box[0]);
  now=process_box[0].arrival_time;
  while(i<n&&process_box[i].arrival_time<=now) {
    pq.push(process_box[i]);
    i++;
  }
  while(pq.empty()==false||i<n) {
    process current = pq.top();
    if(pq.empty()==true) {
      now=process_box[i].arrival_time;
    }
    if(current.arrival_time>now) {
      now=current.arrival_time;
      gantt_chart_time.push_back(now);
      gantt_run_order.push_back("N");
    }
    pq.pop();
    double take=now;
    gantt_run_order.push_back(current.process_name);
    now+=current.duration;
    gantt_chart_time.push_back(now);
    waitting_time+=(take-current.arrival_time);
    if(i<n) {
      while(i<n&&process_box[i].arrival_time<=now) {
        pq.push(process_box[i]);
        i++;
      }
    }
  }
  display (process_box,gantt_chart_time,gantt_run_order,waitting_time);
  gantt_chart_time.clear();
  gantt_run_order.clear();
  waitting_time=0;
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  //read some unused data
  string a,b,c,d;
  cin>>a>>b>>c>>d;
  string s;
  vector<process> process_box;
  vector<double> gantt_chart_time;
  vector<string> gantt_run_order;
  double waitting_time=0;
  while(cin>>s) {
    double a,b,p;
    cin>>a>>b>>p;
    process temp= {s,a,b,p};
    process_box.push_back(temp);
  }
  PS2(process_box,gantt_run_order,gantt_chart_time,waitting_time);
}
