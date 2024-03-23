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
    if(i<n) {
      int av_time=process_box[i].arrival_time-now;
      if(av_time>=imple.duration) {
        gantt_run_order.push_back(imple.process_name);
        now+=imple.duration;
        gantt_chart_time.push_back(now);
      }
      else {
        now+=av_time;
        gantt_run_order.push_back(imple.process_name);
        gantt_chart_time.push_back(now);
        imple.duration-=av_time;
        imple.arrival_time=now;
        pq.push(imple);
      }
    }
    else {
      gantt_run_order.push_back(imple.process_name);
      now+=imple.duration;
      gantt_chart_time.push_back(now);
    }
    while(i<n&&process_box[i].arrival_time<=now) {
        pq.push(process_box[i]);
        i++;
    }
    waitting_time+=(take-imple.arrival_time);
  }
  display (process_box,gantt_chart_time,gantt_run_order,waitting_time);
  gantt_chart_time.clear();
  gantt_run_order.clear();
  waitting_time=0;
}
