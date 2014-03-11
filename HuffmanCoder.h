#include <string>
#include <algorithm>
#include <vector>
#include <functional>

// K denotes the base of the encoded number that is outputted
template<int K> class HuffmanCoder {
	std::vector<std::string> encoded;
	std::vector<float> probabilities;
	struct Node {
		bool isVertex;
		float prob;
		int value;
		Node *children[K];
		Node() {
			for ( int i = 0 ; i < K ; i++ ) children[i] = NULL;
		}
		~Node() {
			for ( int i = 0 ; i < K ; i++ ) {
				delete children[i];
			}
		}
	};
	Node *root;
	int N;
	
	void generateCodes(Node* t,std::string s) {
		if ( t == NULL ) return;
		if ( t->isVertex ) {
			encoded[t->value] = s;
			return;
		}
		for ( int i = 0 ; i < K ; i++ ) {
			generateCodes( t->children[i] , s + (char)(i+'0') );
		}
	}
	
	static const float EPSILON = 1e-9; // minimum probability under which it assumes non existent
	
	public:
	void makeTree(int n, float list[]) {
		N = n;
		encoded.clear();
		encoded.resize(N,"");
		probabilities.clear();
		probabilities.resize(N);
		std::vector < std::pair<float,Node*> > heap;
		for ( int i = 0 ; i < N ; i++ ) {
			Node *temp = new Node;
			temp->isVertex = true;
			temp->prob = list[i];
			temp->value = i;
			if ( temp->prob <= EPSILON ) {
				encoded[i] = "Unused";
				continue;
			}
			heap.push_back(std::make_pair(list[i],temp));
			probabilities[i] = list[i];
		}
		make_heap(heap.begin(),heap.end(),std::greater< std::pair<float,Node*> >());
		while ( heap.size() > 1 ) {
			Node *t = new Node;
			t->prob = 0;
			for ( int i = 0 ; i < K ; i++ ) {
				if ( heap.size() == 0 ) {
					t->children[i] = NULL;
					continue;
				}
				t->children[i] = heap[0].second;
				t->prob += heap[0].first;
				pop_heap(heap.begin(),heap.end(),std::greater< std::pair<float,Node*> >());
				heap.pop_back();
			}
			t->isVertex = false;
			t->value = -1;
			heap.push_back(std::make_pair(t->prob,t));
			push_heap(heap.begin(),heap.end(),std::greater< std::pair<float,Node*> >());
		}
		root = heap[0].second;
		generateCodes(root,"");
	}
	
	bool getCode(int i, std::string &s) {
		if ( i < 0 || i >= N ) {
			return false;
		}
		s = encoded[i];
		return true;
	}
	
	float averageLength() {
		float runningTotal = 0;
		for ( int i = 0 ; i < N ; i++ ) {
			std::string s;
			getCode(i,s);
			runningTotal += s.size() * probabilities[i];
		}
		runningTotal /= root->prob; // allows for actual counts instead of probabilities to be used
		return runningTotal;
	}
};
