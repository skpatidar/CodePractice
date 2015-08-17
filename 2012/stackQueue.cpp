#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

#define MAX_DATA 64

class myQueue {
	private:
		vector<int> data; 
		int front;
		int back;

	public:
		myQueue() { data.resize(MAX_DATA); front = 0; back = -1; }
		void pop() { if(!empty()) { front++; } }
		int top() { if(!empty()) { return data[front]; } }
		void push(int d) { back++; data[back] = d; }
		bool empty() { return (front > back); };
		void print() {
			int f = front; 
			while (f <= back) {
				cout << data[f] << " ";
				f++;
			}
			cout << "\n";
		}
};

class myStack {
	private:
		vector<int> data; 
		int t;

	public:
		myStack() { data.resize(MAX_DATA); t = -1; }
		void pop() { if(!empty()) { t--; } }
		int top() { if(!empty()) { return data[t]; } }
		void push(int d) { t++; data[t] = d; }
		bool empty() { return (t < 0); };
		void print() {
			int _t = t; 
			while (_t >= 0) {
				cout << data[_t] << " ";
				_t--;
			}
			cout << "\n";
		}
};

int main (int argc, char *argv[]) {
	myStack S;
	cout << "Push 1 : \n"; S.push(1);
	cout << "Push 2 : \n"; S.push(2);
	cout << "Push 3 : \n"; S.push(3);
	cout << "Push 4 : \n"; S.push(4);
	cout << "Print : "; S.print();
	cout << "Pop : \n"; S.pop();
	cout << "Pop : \n"; S.pop();
	cout << "Pop : \n"; S.pop();
	cout << "Print : "; S.print();
	cout << "Push 2 : \n"; S.push(2);
	cout << "Push 3 : \n"; S.push(3);
	cout << "Push 4 : \n"; S.push(4);
	cout << "Print : "; S.print();
	cout << "Print while ! empty : ";
	while(!S.empty()) {
		cout << S.top() << " ";
		S.pop();
	}
	cout << "\n";
	return 0;
}
