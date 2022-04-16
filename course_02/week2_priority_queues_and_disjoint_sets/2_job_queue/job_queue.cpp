#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::priority_queue;

class Thread{
  public:
    int id;
    long long nextFreeTime;
    Thread(int id){
      this->id = id;
      nextFreeTime = 0;
    }
    bool operator() (const Thread & a, const Thread & b){
      // a precedes if a's id smaller than that of b
      if (a.nextFreeTime == b.nextFreeTime)
        return a.id > b.id;
      return a.nextFreeTime > b.nextFreeTime;
    };

    
};

struct ThreadCompare{
  bool operator() (const Thread & a, const Thread & b){
      // a precedes if a's id smaller than that of b
      if (a.nextFreeTime == b.nextFreeTime)
        return a.id > b.id;
      return a.nextFreeTime > b.nextFreeTime;
    };
};



class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;
  vector<int> thread_priority;  //min_heap to keep track of assignment priority

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  int GetMin(){
    return thread_priority[0];
  }

  void ChangePriority(int i, int val){
    // i: current index
    // j: priority to be changed into

    if (i < val)
      SiftDown(i, val);
    else if(i > val)
      SiftUp(i, val);
  }

  void SiftDown(int i, int val){
    // given heap_array, it applies siftdown to node i
    // args:
    //  - int i: the node to be sifted down
    //  - vector<int> heap_array: array to stores heap data structure
    // returns:
    //  - indices swapped (this is for the particular task of this file)
    //  - (-1,-1) if there is no swap anymore
    // applies siftdown function to node i
    // index convention  used to represent is based on heap array convention

    int min_index = i;

    int old = thread_priority[i];

    thread_priority[i] = val;

    // Assign left child
    int l = 2*i+1;           

    if ((l < thread_priority.size()) && (thread_priority[l] < thread_priority[min_index]))
      min_index = l;
    
    // Assign right child
    int r = 2*i+2;
    if ((r < thread_priority.size()) && (thread_priority[r] < thread_priority[min_index]))
      min_index = r;

    thread_priority[i] = old;
    if (i != min_index){
      // swap the nodes i and max_index
      int temp = thread_priority[i];
      thread_priority[i] = thread_priority[min_index];
      thread_priority[min_index] = temp;

      SiftDown(min_index, val);
    }
  }


  void SiftUp(int i, int val){
    // given heap_array, it applies siftdown to node i
    // args:
    //  - int i: the node to be sifted down
    //  - vector<int> heap_array: array to stores heap data structure
    // returns:
    //  - indices swapped (this is for the particular task of this file)
    //  - (-1,-1) if there is no swap anymore
    // applies siftdown function to node i
    // index convention  used to represent is based on heap array convention

    int max_index = i;

    int old = thread_priority[i];

    thread_priority[i] = val;

    // Assign left child
    int l = 2*i+1;           

    if ((l < thread_priority.size()) && (thread_priority[l] > thread_priority[max_index]))
      max_index = l;
    
    // Assign right child
    int r = 2*i+2;
    if ((r < thread_priority.size()) && (thread_priority[r] > thread_priority[max_index]))
      max_index = r;

    thread_priority[i] = old;
    if (i != max_index){
      // swap the nodes i and max_index
      int temp = thread_priority[i];
      thread_priority[i] = thread_priority[max_index];
      thread_priority[max_index] = temp;

      SiftUp(max_index, val);
    }
  }

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs_naive() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }
  }

    void AssignJobs_fast() {
      
      assigned_workers_.resize(jobs_.size());
      start_times_.resize(jobs_.size());
      // create th priority queue for thread processing
      priority_queue <Thread, vector<Thread>, ThreadCompare> prior_q;
      // go over each waiting job
      for (int i = 0; i < num_workers_; ++i){
        prior_q.push(Thread(i));
      }

      for (int i=0; i < jobs_.size() ; ++i){

        // Get the thread with the highest priority
        Thread freeThread = prior_q.top();
        
        prior_q.pop();

        // put the id of Thread processing the job
        assigned_workers_[i]  = freeThread.id;

        // starts when the thread is free
        start_times_[i] = freeThread.nextFreeTime;

        // thread becomes free after the current job is done
        freeThread.nextFreeTime += jobs_[i];

        prior_q.push(freeThread);
      }
    }

 public:
  void Solve() {
    ReadData();
    AssignJobs_fast();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
