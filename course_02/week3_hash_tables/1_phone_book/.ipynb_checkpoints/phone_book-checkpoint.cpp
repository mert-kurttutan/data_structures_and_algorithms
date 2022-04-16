#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, name;
    int number;
};


struct Record {
    string name;
    int number=-1;
};


vector<Query> read_queries_naive();
void write_responses(const vector<string>& result);
vector<string> process_queries_naive(const vector<Query>& queries);
vector<string> process_queries_direct(const vector<Query>& queries);



int main() {
    write_responses(process_queries_direct(read_queries_naive()));
    return 0;
}


vector<Query> read_queries_naive() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries_direct(const vector<Query> &queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    int max_size=9999999+100;
    vector<Record> contacts(max_size );
    bool is_founded = false;
    for (size_t i = 0; i < queries.size(); ++i){

        is_founded = contacts[queries[i].number].number == queries[i].number;
        if (queries[i].type == "add") {

            // if we already have contact with such number,
            // we should rewrite contact's name
            if (is_founded) {
                contacts[queries[i].number].name = queries[i].name;
                }
            // otherwise, just add it
            else{
                contacts[queries[i].number].name = queries[i].name;
                contacts[queries[i].number].number = queries[i].number;
                //contacts.push_back(queries[idx_record[i]]);
            }
        } else if (queries[i].type == "del") {
            if (is_founded) {
                contacts[queries[i].number].number = -1;
                contacts[queries[i].number].name = "NULL";
            }
        } else {
            string response = "not found";
            if (is_founded) {
                response = contacts[queries[i].number].name;
                }
            result.push_back(response);
        }
    }
    return result;
}


vector<string> process_queries_naive(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<Query> contacts;
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") {
            bool was_founded = false;
            // if we already have contact with such number,
            // we should rewrite contact's name
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts[j].name = queries[i].name;
                    was_founded = true;
                    break;
                }
            // otherwise, just add it
            if (!was_founded)
                contacts.push_back(queries[i]);
        } 
        else if (queries[i].type == "del") {
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts.erase(contacts.begin() + j);
                    break;
                }
        } 
        else {
            string response = "not found";
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    response = contacts[j].name;
                    break;
                }
            result.push_back(response);
        }
    return result;
}