#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;
int compute_min_refills(int dist, int tank, vector<int> & stops);


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}



int compute_min_refills(int dist, int tank, vector<int> & stops) {
    
    int cur_dist = 0;
    vector<int> stops_c =  stops;
    stops_c.push_back(dist);                          //include the arrival point in the station, this makes the code much uniform and nicer

    int i = 0;
    int fill_num = 0;
    bool stuck=false;

    while(i < stops_c.size() & !stuck){
        stuck=true;

        while(((stops_c[i] - cur_dist) <= tank)  &  (i < stops_c.size()) ){
            stuck=false;                     //inform that there is an available station, not stuck
            i++;
        }
        cur_dist = stops_c[i-1];
        fill_num++ ;
    }

    if (stuck){
        return -1;
    }

    return fill_num -1 ;      //dont count arrival as fuel station
}








/*


    while(i < stops.size() & !stuck){
        stuck=true;
        while(((stops[i] - cur_dist) <= tank)  &  (i < stops.size())  ){
            stuck=false;                   //inform that there is an avialble station, not stuck
            i++;
        }
        if ((dist - cur_dist) > tank){
            cur_dist = stops[i];
            fill_num++;
        }
    }
    if (stuck){
        return -1;                   // we are stuck, impossible path
    }
    // check near arrival region
    if ((dist - cur_dist) > tank){
        cur_dist = stops[i];
        fill_num++;
        if ((dist - cur_dist) > tank){             //not possible
            return -1;
        }
    }
    */