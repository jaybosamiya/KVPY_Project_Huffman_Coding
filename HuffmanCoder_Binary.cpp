// Huffman Coding

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <functional>

// K denotes the base of the number that is outputted
template<int K> class HuffmanCoder {
	std::vector<std::string> coding;
	std::vector<float> probabilities;
	struct treeNode {
		bool isVertex;
		float prob;
		int value;
		treeNode *children[K];
		treeNode() {
			for ( int i = 0 ; i < K ; i++ ) children[i] = NULL;
		}
		~treeNode() {
			for ( int i = 0 ; i < K ; i++ ) {
				delete children[i];
			}
		}
	};
	treeNode *root;
	int N;
	
	void __genCodes(treeNode* t,std::string s) {
		if ( t == NULL ) return;
		if ( t->isVertex ) {
			coding[t->value] = s;
			return;
		}
		for ( int i = 0 ; i < K ; i++ ) {
			__genCodes( t->children[i] , s + (char)(i+'0') );
		}
	}
	
	public:
	void makeTree(int n, float list[]) {
		N = n;
		coding.clear();
		coding.resize(N,"");
		probabilities.clear();
		probabilities.resize(N);
		std::vector < std::pair<float,treeNode*> > heap;
		for ( int i = 0 ; i < N ; i++ ) {
			treeNode *temp = new treeNode;
			temp->isVertex = true;
			temp->prob = list[i];
			temp->value = i;
			heap.push_back(std::make_pair(list[i],temp));
			probabilities[i] = list[i];
		}
		make_heap(heap.begin(),heap.end(),std::greater< std::pair<float,treeNode*> >());
		while ( heap.size() > 1 ) {
			treeNode *t = new treeNode;
			t->prob = 0;
			for ( int i = 0 ; i < K ; i++ ) {
				if ( heap.size() == 0 ) {
					t->children[i] = NULL;
					continue;
				}
				t->children[i] = heap[0].second;
				t->prob += heap[0].first;
				pop_heap(heap.begin(),heap.end(),std::greater< std::pair<float,treeNode*> >());
				heap.pop_back();
			}
			t->isVertex = false;
			t->value = -1;
			heap.push_back(std::make_pair(t->prob,t));
			push_heap(heap.begin(),heap.end(),std::greater< std::pair<float,treeNode*> >());
		}
		root = heap[0].second;
	}
	
	void generateCodes() {
		__genCodes(root,"");
	}
	
	bool getCode(int i, std::string &s) {
		if ( i < 0 || i >= N ) {
			return false;
		}
		s = coding[i];
		return true;
	}
	
	float averageLength() {
		float runningTotal = 0;
		for ( int i = 0 ; i < N ; i++ ) {
			std::string s;
			getCode(i,s);
			runningTotal += s.size() * probabilities[i];
		}
		runningTotal /= root->prob; // should be div by one but sometimes it may not be exactly 1 so...
		return runningTotal;
	}
};

int main() {
	HuffmanCoder<2> hc;
	int N;
	float val[100];
	std::cin >> N;
	for ( int i = 0 ; i < N ; i++ ) {
		std::cin >> val[i];
	}
	hc.makeTree(N,val);
	hc.generateCodes();
	std::cout << "\n\n";
	for ( int i = 0 ; i < N ; i++ ) {
		std::string s;
		hc.getCode(i,s);
		std::cout << i << " -> " << s << "\n";
	}
	std::cout << "\n\nAverage length of encoding: " << hc.averageLength() << "\n";
}
