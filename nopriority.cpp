#include <bits/stdc++.h>
using namespace std;

struct process {
  string process_name;
  double arrival_time;
  double duration;
};
class timesort {
   public:
    bool operator()(process&a,process&b) {
      if(a.arrival_time<=b.arrival_time) {
        return true;
      }
      return false;
  }
};
class shorter {
  public:
    bool operator () (process&a,process&b) {
        if(a.duration>b.duration) {
          return true;
        }
        if(a.duration==b.duration) {
          return a.arrival_time>b.arrival_time;
        }
        return false;
    }
};
void display (vector<process>&process_box,vector<double>&gantt_chart_time,vector<string>&gantt_run_order) {
    //display gantt chart
    map<string,double> waittable;
    map<string,double> inputtime;
    for (int i=0;i<process_box.size();i++) {
      inputtime[process_box[i].process_name]=process_box[i].arrival_time;
    }
    double taketime=0;
    double sum=0;
    for (int i=0;i<gantt_chart_time.size();i++) {
      if(i>0) {
        taketime=gantt_chart_time[i-1];
      }
      waittable[gantt_run_order[i]]+=taketime-inputtime[gantt_run_order[i]];
      inputtime[gantt_run_order[i]]=gantt_chart_time[i];
    }
    vector<pair<int,int>> range;
    int now=0;
    cout<<0;
    for (int i=0;i<gantt_chart_time.size();i++) {
      string s(gantt_run_order[i].size(),' ');
      cout<<" "<<s<<" "<<gantt_chart_time[i];
      int clone =gantt_chart_time[i];
      int nus=0;
      while(clone>0) {
        clone/=10;
        nus++;
      }
      double clone2 = gantt_chart_time[i];
      bool check=false;
      while(clone2!=(int)clone2) {
        clone2*=10;
        nus++;
        check=true;
      }
      nus+=check;
      range.push_back({now,now+1+s.size()+1+1});
      now=now+1+s.size()+nus+1;
    }
    cout<<endl;
    now=0;
    for (int i=0;i<range.size();i++) {
      int pos=(range[i].first+range[i].second)/2;
      while(now<range[i].first) {
        cout<<' ';
        now++;
      }
      while(now<range[i].second) {
        if(now==pos) {
          cout<<gantt_run_order[i];
          now+=gantt_run_order[i].size();
        }
        else if(now==range[i].first) {
          cout<<'|';
          now++;
        }
        else {
          cout<<' ';
          now++;
        }
       }
       if(i==range.size()-1) {
          cout<<'|';
        }
    }
    cout<<endl;
    for (int i=0;i<process_box.size();i++) {
      cout<<"thoi gian cho cua "<<process_box[i].process_name<<" : "<<waittable[process_box[i].process_name]<<endl;
      sum+=waittable[process_box[i].process_name];
    }
    cout<<"tong thoi gian cho "<<sum<<endl;
    cout<<"thoi gian cho trung binh la : "<<sum/(double)(process_box.size());
    cout<<endl<<endl;
}
void FCFS (vector<process>&process_box,vector<string>&gantt_run_order,vector<double>&gantt_chart_time) {
  if(process_box.size()==0) {
    return;
  }
  double now=0;
  now=max(now,process_box[0].arrival_time);
  for (int i=0;i<process_box.size();i++) {
    if(now<process_box[i].arrival_time) {
      now=process_box[i].arrival_time;
      gantt_chart_time.push_back(now);
      gantt_run_order.push_back("No process");
    }
    now=now+process_box[i].duration;
    gantt_chart_time.push_back(now);
    gantt_run_order.push_back(process_box[i].process_name);
  }
  display (process_box,gantt_chart_time,gantt_run_order);
  gantt_chart_time.clear();
  gantt_run_order.clear();
}

void SJF1 (vector<process>&process_box,vector<string>&gantt_run_order,vector<double>&gantt_chart_time) { 
  if(process_box.size()==0) {
    return;
  }
  int n=process_box.size();
  int i=1;
  double now=0;
  priority_queue<process,vector<process>,shorter> pq;
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
      gantt_run_order.push_back("No process");
    }
    pq.pop();
    double take=now;
    gantt_run_order.push_back(current.process_name);
    now+=current.duration;
    gantt_chart_time.push_back(now);
    if(i<n) {
      while(i<n&&process_box[i].arrival_time<=now) {
        pq.push(process_box[i]);
        i++;
      }
    }
  }
  display (process_box,gantt_chart_time,gantt_run_order);
  gantt_chart_time.clear();
  gantt_run_order.clear();
}
void SJF2 (vector<process>&process_box,vector<string>&gantt_run_order,vector<double>&gantt_chart_time) { 
  if(process_box.size()==0) {
    return;
  }
  int n=process_box.size();
  int i=1;
  double now=0;
  priority_queue<process,vector<process>,shorter> pq;
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
        gantt_run_order.push_back("No process");
        now=current.arrival_time;
      }
    }
    else {
      if(current.duration>pq.top().duration) {
        process temp = pq.top();
        pq.pop();
        pq.push(current);
        current=temp;
      }
    }
    double take=now;
    if(i<n) {
      double av_time=process_box[i].arrival_time-now;
      if(av_time>=current.duration) {
        if(gantt_run_order.size()==0||gantt_run_order[gantt_run_order.size()-1]!=current.process_name) {
          gantt_run_order.push_back(current.process_name);
          now+=current.duration;
          gantt_chart_time.push_back(now);
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
  display (process_box,gantt_chart_time,gantt_run_order);
  gantt_chart_time.clear();
  gantt_run_order.clear();
}
void RR (vector<process>&process_box,vector<string>&gantt_run_order,vector<double>&gantt_chart_time,double qt) { 
  if(process_box.size()==0) {
    return;
  }
  queue<process> q;
  double now=0;
  int i=0;
  int n=process_box.size();
  while(process_box[i].arrival_time<=now&&i<n) {
    q.push(process_box[i]);
    i++;
  }
  while(i<n||q.empty()==false) {
    if(q.empty()==true) {
      now=process_box[i].arrival_time;
    }
    process temp=q.front();
    if(temp.arrival_time>now) {
      now=temp.arrival_time;
      gantt_chart_time.push_back(now);
      gantt_run_order.push_back("No process");
    }
    q.pop();
    double take=now;
    double runtime =min(qt,temp.duration);
    now += runtime;
    gantt_chart_time.push_back(now);
    gantt_run_order.push_back(temp.process_name);
    while(i<n) {
        if(process_box[i].arrival_time<=now) {
          q.push(process_box[i]);
          i++;
      }
      else {
        break;
      }
    }
    temp.duration-= runtime;
      temp.arrival_time=now;
      if(temp.duration>0) {
        q.push(temp);
    }
  }
  display (process_box,gantt_chart_time,gantt_run_order);
  gantt_chart_time.clear();
  gantt_run_order.clear();
}
int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  string a,b,c;
  cin>>a>>b>>c;
  string s;
  vector<process> process_box;
  vector<double> gantt_chart_time;
  vector<string> gantt_run_order;
  while(cin>>s) {
    double a,b;
    cin>>a>>b;
    process temp= {s,a,b};
    process_box.push_back(temp);
  }
  sort(process_box.begin(),process_box.end(),timesort());
  cout<<"Den truoc phuc vu truoc : "<<endl;
  FCFS(process_box,gantt_run_order,gantt_chart_time);
  cout<<"Thoi gian ngan truoc doc quyen : "<<endl;
  SJF1(process_box,gantt_run_order,gantt_chart_time);
  cout<<"Thoi gian ngan truoc khong doc quyen : "<<endl;
  SJF2(process_box,gantt_run_order,gantt_chart_time); 
  double qt=2;
  cout<<"Dieu phoi vong tron round robin : "<<endl;
  RR (process_box,gantt_run_order,gantt_chart_time,qt);
}
