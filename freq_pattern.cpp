#include <iostream>
#include <vector>
#include <fstream>
#define no_of_items 5
#define min_sup 2
using namespace std;
int exit_cond_combine_set = 0;


struct frequent {
	vector<int> itemset;
	int support; 
};

void display(vector<vector<frequent> > candidate_set) {
	for(int i=0; i<candidate_set.size(); i++) {
		// cout<<"\nC"<<i+1<<":\n";
		cout<<i+1<<"\n";
		for(int j=0; j<candidate_set[i].size(); j++) {
			// cout<<"{";
			for(int k=0; k<candidate_set[i][j].itemset.size(); k++)
				cout<<candidate_set[i][j].itemset[k]<<" ";
			cout<<"-1 ";
			// cout<<"}\t";
			cout<<candidate_set[i][j].support<<endl;
		}
	}

}

vector<vector<frequent> > do_combination(vector<vector<frequent> > candidate_set, vector<frequent> pattern1, vector<frequent> pattern2) {
	vector<frequent> pattern;
	pattern.clear();
	for(int i=0; i<pattern1.size(); i++) {
		for(int j=i+1; j<pattern2.size(); j++) {
			int k, flag = 0;
			for(k=0; k<pattern1[i].itemset.size()-1; k++)
				if(pattern1[i].itemset[k] != pattern2[j].itemset[k]) {
					flag = 1;
					break;
				}
			if(flag)
				continue;
			frequent temp;
			temp.support = 0;
			for(k=0; k<pattern1[i].itemset.size(); k++)
				temp.itemset.push_back(pattern1[i].itemset[k]);
			temp.itemset.push_back(pattern2[j].itemset[k-1]);
			pattern.push_back(temp);
			
		}
	}
	if(!pattern.size()) {
		exit_cond_combine_set = 1;
		return candidate_set;
	}
	candidate_set.push_back(pattern);
	return candidate_set;
}

vector<frequent> find_support(vector<frequent> pattern) {
	for(int i=0; i<pattern.size(); i++) {
		ifstream fin;
		fin.open("datagraph_output.txt");
		int n;
		fin>>n;
		for(int j=0; j<9; j++) {
			fin>>n;
			int ctr = 0;
			int item_ctr = 0;
			while(n != -1 && item_ctr < pattern[i].itemset.size()) {
				if(pattern[i].itemset[item_ctr] == n) {
					item_ctr++;
					ctr++;
				}
				else if(pattern[i].itemset[item_ctr] < n) {
					item_ctr++;
				}
				fin>>n;
			}
			while(n != -1)
				fin>>n;
			if(ctr == pattern[i].itemset.size())
				pattern[i].support++;
		}
		fin.close();
	}
	return pattern;
}

vector<frequent> do_prune(vector<frequent> pattern) {
	vector<frequent> temp;
	temp = pattern;
	pattern.clear();
	for(int i=0; i<temp.size(); i++) {
		if(temp[i].support >= min_sup)
			pattern.push_back(temp[i]);
	}
	return pattern;
}

int main() {
	ifstream fin;
	fin.open("datagraph_output.txt");
	int n, item;
	fin>>n;
	int first[no_of_items] = {0};
	int max = 0;
	for(int i=0; i<9; i++) {
		fin>>item;
		while(item != -1) {
			first[item-1]++;
			fin>>item;
		}
	}
	vector<frequent> pattern;
	vector<vector<frequent> > candidate_set;
	frequent temp;
	for(int i=0; i<no_of_items; i++) {
		if(first[i] >= min_sup) {
			temp.support = first[i];
			temp.itemset.push_back(i+1);
			pattern.push_back(temp);
			temp.itemset.clear();
		}
	}
	candidate_set.push_back(pattern);
	while(!exit_cond_combine_set) {
		candidate_set = do_combination(candidate_set, candidate_set[candidate_set.size()-1], candidate_set[candidate_set.size()-1]);
		candidate_set[candidate_set.size()-1] = find_support(candidate_set[candidate_set.size()-1]);
		candidate_set[candidate_set.size()-1] = do_prune(candidate_set[candidate_set.size()-1]);
	}
	while(candidate_set[candidate_set.size()-1].size() == 0)
		candidate_set.pop_back();
	display(candidate_set);
}