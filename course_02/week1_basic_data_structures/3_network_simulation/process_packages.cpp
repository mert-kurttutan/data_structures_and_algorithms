#include <iostream>
#include <queue>
#include <vector>

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
        size_(size),
        finish_time_()
    {}

    Response Process(const Request &request) {

        int start_time;
        bool dropped=false;

        // if buffer is empty, trivial case
        if (finish_time_.empty()){
            start_time = request.arrival_time;
            dropped = (size_ == 0);
        }

        // if the next job start after last finish or empty buffer, no need to go into buffer
        else if (request.arrival_time >= finish_time_.back()){

            //clear the buffer
            finish_time_= std::queue<int>();
            
            // if buffer has no size
            dropped = (size_ == 0);

            // change start of the current request to given arrival time
            start_time = request.arrival_time;
        }

        else{ // otherwise response has to be in buffer

            // otherwise start_time is the last finish time
            start_time = finish_time_.back();

            //pop requests that finishes before the arrivaş of the current request
            while(finish_time_.front() <= request.arrival_time){
                finish_time_.pop();
            }
            
            // should be dropped if the buffer is full
            dropped = (finish_time_.size() >= size_);
        }
        // if not dropped push the prepared response
        if (!dropped){
            // push the new element
            finish_time_.push(start_time + request.process_time);
        }

        // Response object to be returned
        Response current(dropped, start_time);
        return current;
    }
private:
    int size_;
    std::queue <int> finish_time_;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
