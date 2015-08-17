#include <iostream>
#include <vector>
#include <string>

using namespace std;

string reverse_str(string word) {
	string rWord;
	for (string::reverse_iterator it=word.rbegin(); it != word.rend(); it++) {
		rWord += *it;
	}
	return rWord;
}

int countWords(string sentence) {
	int count = 0;
	for (int i=0; i < sentence.length(); i++) {
		if (sentence[i] == ' ') {
			count++;
		}
	}
	count++;
	return count;	
}

string reverseWords(string sentence) {
	string revWords;
	string curWord;
	for (int i=0; i < sentence.length(); i++) {
		if (sentence[i] == ' ') {
			revWords += reverse_str(curWord);
			revWords += " ";
			curWord = "";
			continue;
		}
		curWord += sentence[i];
	}
	revWords += reverse_str(curWord);
	return revWords;	
}

string reverseSentence(string sentence) {
	string revSent = reverse_str(sentence); 
	revSent = reverseWords(revSent);
	return revSent;
}

void removeSpaces(char *s) {
	char *p1 = s, *p2 = s; 

	while (*p2 != '\0') {
		cout << *p2 << endl;
		while (*p2 == ' ') {
			p2++;
		}
		*p1 = *p2;
		p1++;
		p2++;
	}
}

int main (int argc, char *argv[]) {
	char *cStr = "The cat is white but the rat is black\0";
	cout << "Sentence : " << cStr << "\n";
	string s(cStr);

	cout << "Sentence : " << s << "\n";	
	cout << "Sentence - # of Words : " << countWords(s) << "\n";	
	cout << "Sentence - Reversed Words : " << reverseWords(s) << "\n";	
	cout << "Sentence - Reversed Sentence : " << reverseSentence(s) << "\n";	
	//cout << "Sentence - Remove Spaces : "; removeSpaces(cStr);
	
	return 0;
}
