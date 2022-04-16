#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement {
	// struct for individual elements in the Disjoint sets
	// size: the size of vector of which the element is a parent
	// parent: parent of the element
	// rank: rank of the corresponding children set
	int size, parent, rank;
	
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	// set of elements that comprises disjoint sets
	// each element of this struct is an instance of struct above
	// for theoretical details visit coursera lecture notes
	int size;
	int max_table_size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size): size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}

	int getParent(int table) {
		// find parent and compress path
		if (sets[table].parent != table)
			sets[table].parent = getParent(sets[table].parent);

		return sets[table].parent;

	}

	void merge(int destination, int source) {
		int dest_id = getParent(destination);
		int src_id = getParent(source);
		if (dest_id != src_id) {
			// merge two components
			// use union by rank heuristic
			if (dest_id == src_id)
				return ;
			
			if (sets[dest_id].rank > sets[src_id].rank){
				sets[src_id].parent = dest_id;
				sets[dest_id].size += sets[src_id].size;

				// source becomes just a rreference symbol link
				sets[src_id].size = 0;
			}

			else{
				sets[dest_id].parent = src_id;
				sets[src_id].size += sets[dest_id].size;

				//destination becomes just a reference symbol link
				sets[dest_id].size = 0;
				if (sets[dest_id].rank == sets[src_id].rank)
					sets[dest_id].rank += 1;
			}
			// update max_table_size
			max_table_size = max({max_table_size, sets[src_id].size, sets[dest_id].size});
		}		
	}
};

int main() {
	int n, m;
	cin >> n >> m;

	DisjointSets tables(n);
	for (auto &table : tables.sets) {
		cin >> table.size;
		tables.max_table_size = max(tables.max_table_size, table.size);
	}

	for (int i = 0; i < m; i++) {
		int destination, source;
		cin >> destination >> source;
                --destination;
                --source;
		
		tables.merge(destination, source);
	        cout << tables.max_table_size << endl;
	}

	return 0;
}
