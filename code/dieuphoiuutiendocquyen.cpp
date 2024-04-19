#include <bits/stdc++.h>
using namespace std;

struct process {
  string process_name;
  double arrival_time;
  double duration;
  double prioritydegree;
};

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

void display (vector<process>&process_box,vector<double>&gantt_chart_time,vector<string>&gantt_run_order) {
    map<string,double> waittable;
    map<string,double> inputtime;
    cout<<"So do gantt :"<<endl;
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
    cout<<"thoi gian cho trung binh la : "<<sum/(double)(process_box.size())<<endl<<endl;
}

void PS1 (vector<process>&process_box) { 
  vector<double>gantt_chart_time;
  vector<string>gantt_run_order;
  if(process_box.size()==0) {
    return;
  }
  int n=process_box.size();
  int i=1;
  double now=0;
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
    if(pq.empty()==true) {
        gantt_chart_time.push_back(process_box[i].arrival_time);
        gantt_run_order.push_back("No process");
        now=process_box[i].arrival_time;
        if(i<n) {
        while(i<n&&process_box[i].arrival_time<=now) {
          pq.push(process_box[i]);
          i++;
        }
      }
    }
    else {
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
      if(i<n) {
        while(i<n&&process_box[i].arrival_time<=now) {
          pq.push(process_box[i]);
          i++;
        }
      }
    }
  }
  display (process_box,gantt_chart_time,gantt_run_order);
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  string a,b,c,d;
  cin>>a>>b>>c>>d;
  string s;
  vector<process> process_box;
  double waitting_time=0;
  while(cin>>s) {
    double a,b,p;
    cin>>a>>b>>p;
    process temp= {s,a,b,p};
    process_box.push_back(temp);
  }
  cout<<"Dieu phoi uu tien doc quyen :"<<endl;
  PS1(process_box);
}
