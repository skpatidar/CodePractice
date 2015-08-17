#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

#define MAX_DATA 1024

typedef struct hashElement {
	string key;
	string value;

	struct hashElement * next;
}hashElement;

class hashData {
	private:
		vector<hashElement*> hData;
		int hashFunc(string);
	public:
		hashData();
		bool isEmpty();
		void insert(string, string); 
		void remove(string);
		hashElement* search(string);
		void print();
};

hashData::hashData() { 
	hData.resize(MAX_DATA);  
	for (int i=0; i < MAX_DATA; i++) {
		hData[i] = NULL;
	}
}

int hashData::hashFunc(string s) {
	int index = 0;
	for (int i=0; i < s.length(); i++) {
		if (s[i] != ' ') {
			index += (s[i] - 'a');
			if (index > MAX_DATA) { 
				index %= MAX_DATA;
			}
		}
	}
	return index;
}

void hashData::insert(string key, string val) {
	int index = hashFunc(key);
	hashElement *h = new hashElement;
	h->key = key;
	h->value = val;
	h->next = NULL;
	if ( hData[index] != NULL ) {
		hashElement *iter = hData[index];
		while(iter->next != NULL) {
			iter = iter->next;
		}
		iter->next = h; 
	} else {
		hData[index] = h;
	}
	cout << "Inserting Data = (" << key << ", " << val << ")" << " at index = " << index << "\n";
}

void hashData::remove(string key) {
	int index = hashFunc(key);
	hashElement *iter = hData[index];
	if(iter == NULL) { 
		cout << "Not Good ! The key you want to delete is not found\n";
		return;
	}
	hashElement *prev = NULL;
	while( iter->key != key ) {
		prev = iter;
		iter = iter->next;
		if(iter == NULL) {
			cout << "Not Good ! The key you want to delete is not found\n";
			return;
		}
	}
	hashElement *nextNode = iter->next;
	if (prev) {
		prev->next = nextNode;
	} else {
		hData[index] = nextNode;
	}
	cout << "Deleting Data = (" << key << ", " << iter->value << ")" << " at index = " << index << "\n";
	delete iter;
}

hashElement* hashData::search(string key) {
	int index = hashFunc(key);
	hashElement *iter = hData[index];
	if(iter == NULL) cout << "Not Good ! The key you are looking for is not found\n";
	while( iter->key != key ) {
		iter = iter->next;
		if(iter == NULL) cout << "Not Good ! The key you want to delete is not found\n";
	}
	cout << "Found Data = (" << key << ", " << iter->value << ")" << "at index = " << index << "\n";
	return iter;
}
void hashData::print() {
	for(int i=0; i < MAX_DATA; i++) {
		if (hData[i] != NULL) {
			hashElement* iter = hData[i]; 
			while(iter != NULL) {
				cout << iter->key << "-->";
				iter = iter->next;
			}
			cout << "X\n";
		}
	}
}

int main(int argc, char *argv[]) {
	hashData h; 
	h.insert("Fonu Kumar","nick");
	h.insert("SonuJee","ghar");
	h.insert("Kumar fonu","nick1");
	h.insert("Kumar Fonu","nick2");
	h.insert("NonuJee","sai");
	h.insert("shashi","school");
	h.insert("motu","pati");
	h.print();
	h.remove("Fonu Kumar");
	h.remove("umar");
	h.remove("shashi");
	h.print();
	hashElement *s = h.search("motu");
	cout << "Search for - motu - returned " << s->key << ":" << s->value << "\n";

	return 1;
}
