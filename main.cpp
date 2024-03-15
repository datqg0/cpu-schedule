#include <bits/stdc++.h>
using namespace std;

struct process {
  string process_name;
  double arrival_time;
  double duration;
  double pridegree;
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

void FCFS (vector<process>&process_box,vector<string>&gantt_run_order,vector<double>&gantt_chart_time,double&waitting_time) {
  // time complexity : O(n)
  // memory: O(n);
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
  gantt_chart_time.clear();
  gantt_run_order.clear();
  waitting_time=0;
}
//custom comparator for priority queue
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
class pricomp {
  public:
    bool operator () (process&a,process&b) {
        if(a.pridegree>b.pridegree) {
          return true;
        }
        if(a.duration==b.duration) {
          return a.arrival_time>b.arrival_time;
        }
        return false;
    }
  };
//non-preemptive
void SJF1 (vector<process>&process_box,vector<string>&gantt_run_order,vector<double>&gantt_chart_time,double&waitting_time) { 
  //time complexity :O(n^2*log(n))
  //Memory: O(n)
  //when arrivel time is big
  if(process_box.size()==0) {
    return;
  }

  //cout<<"run"<<endl;
  int n=process_box.size();
  int i=1;
  int now=0;
  priority_queue<process,vector<process>,shorter> pq;
  pq.push(process_box[0]);
  now=process_box[0].arrival_time;
  while(i<n&&process_box[i].arrival_time<=now) {
    pq.push(process_box[i]);
    i++;
  }
  while(pq.empty()==false||i<n) {
    process imple = pq.top();
    if(pq.empty()==true) {
      now=process_box[i].arrival_time;
    }
    if(imple.arrival_time>now) {
      now=imple.arrival_time;
      gantt_chart_time.push_back(now);
      gantt_run_order.push_back("N");
    }
    pq.pop();
    double take=now;
    gantt_run_order.push_back(imple.process_name);
    now+=imple.duration;
    gantt_chart_time.push_back(now);
    waitting_time+=(take-imple.arrival_time);
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
//preemptive
void SJF2 (vector<process>&process_box,vector<string>&gantt_run_order,vector<double>&gantt_chart_time,double&waitting_time) { 
  if(process_box.size()==0) {
    return;
  }
  int n=process_box.size();
  int i=1;
  int now=0;
  priority_queue<process,vector<process>,shorter> pq;
  pq.push(process_box[0]);
  now=process_box[0].arrival_time;
  while(i<n&&process_box[i].arrival_time<=now) {
    pq.push(process_box[i]);
    i++;
  }
  while(pq.empty()==false||i<n) {
    process imple = pq.top();
    if(pq.empty()==true) {
      now=process_box[i].arrival_time;
    }
    if(imple.arrival_time>now) {
      now=imple.arrival_time;
      gantt_chart_time.push_back(now);
      gantt_run_order.push_back("N");
    }
    pq.pop();
    double take=now;
    gantt_run_order.push_back(imple.process_name);
    now+=imple.duration;
    gantt_chart_time.push_back(now);
    waitting_time+=(take-imple.arrival_time);
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
void PRI1 (vector<process>&process_box,vector<string>&gantt_run_order,vector<double>&gantt_chart_time,double&waitting_time) { 
  if(process_box.size()==0) {
    return;
  }

}
void PRI2 (vector<process>&process_box,vector<string>&gantt_run_order,vector<double>&gantt_chart_time,double&waitting_time) { 
  if(process_box.size()==0) {
    return;
  }

}
void RR (vector<process>&process_box,vector<string>&gantt_run_order,vector<double>&gantt_chart_time,double&waitting_time,double qt) { 
  //cout<<"run"<<endl;
  if(process_box.size()==0) {
    //cout<<"run"<<endl;
    return;
  }
  //cout<<"ok"<<endl;
	queue<process> q;
	double now=0;
	int i=0;
	double n=process_box.size();
	while(process_box[i].arrival_time<=now&&i<n) {
		q.push(process_box[i]);
		i++;
	}
  //cout<<"ok"<<endl;
	while(i<n||q.empty()==false) {
    if(q.empty()==true) {
      now=process_box[i].arrival_time;
    }
		process temp=q.front();
		if(temp.arrival_time>now) {
			now=temp.arrival_time;
			gantt_chart_time.push_back(now);
    	gantt_run_order.push_back("N");
		}
		q.pop();
    double take=now;
		double runtime =min(qt,temp.duration);
		now += runtime;
		gantt_chart_time.push_back(now);
    gantt_run_order.push_back(temp.process_name);
    waitting_time+=(take-temp.arrival_time);

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
  //cout<<"ok"<<endl;
  display (process_box,gantt_chart_time,gantt_run_order,waitting_time);
  gantt_chart_time.clear();
  gantt_run_order.clear();
  waitting_time=0;
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
  FCFS(process_box,gantt_run_order,gantt_chart_time,waitting_time);
  SJF1(process_box,gantt_run_order,gantt_chart_time,waitting_time);
  double qt=2;
  RR (process_box,gantt_run_order,gantt_chart_time,waitting_time,qt);
}
