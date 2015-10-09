// Tries : Implement a Dictionary search 
// https://www.topcoder.com/community/data-science/data-science-tutorials/using-tries/

#include<stdlib.h>
#include<iostream>
#include<vector>
#include<string>

using namespace std;
 
typedef struct trieNode {
    int words;
    int prefixes;
    struct trieNode* edges[26];
} node;

class TrieDict {
    private :
        node *dictroot;
        
    public :
        TrieDict();
        node* getDictRoot() { return dictroot; };
        void addWord(node*, string); 
        int countWords(node*, string);
        int countPrefixes(node*, string);
};

void initNode(node* d) {
    d->words = 0;
    d->prefixes = 0;
    for (int i=0; i < 26; i++) {
        d->edges[i] = NULL;
    }
}

TrieDict::TrieDict() {
    dictroot = new node;
    initNode(dictroot); 
}

char getFirstCharacter(string word) {
    if (word.empty()) {
        exit(2); // should not happen
    }
    //cout << "Return : " << word.at(0) << " for getFirstChar with word = " << word << "\n";
    return word.at(0);
}

void cutFirstCharacter(string &word) {
    //cout << "Cut : " << word.at(0) << " for getFirstChar with word = " << word << "\n";
    word.erase(0, 1);
}

void TrieDict::addWord(node* dictRoot, string word) {
    if (word.length() == 0) {
        dictRoot->words++;
        //cout << "Setting word count : " << dictRoot->words << "\n";
        return;
    }
 
    char c = getFirstCharacter(word);
    int edgeIndex = c - 'a';
    //cout << "Character : " << c << " maps to Edge : " << edgeIndex << "\n";
    
    // If node does not exist, create one 
    node *edgeNode = dictRoot->edges[edgeIndex];
    if (edgeNode == NULL) {
        edgeNode = new node;
        initNode(edgeNode);
        dictRoot->edges[edgeIndex] = edgeNode;
    }
    
    // Increment prefix count for this node
    dictRoot->prefixes++;
    
    // Call addword with rest of the string 
    cutFirstCharacter(word);
    
    addWord(edgeNode, word);
    //cout << "Return from addWord with : " << word << " and word count = " << edgeNode->words << "\n";
    
}

int TrieDict::countWords(node* dictRoot, string word) {
    if (word.length() == 0) {
        return dictRoot->words;
    }
    
    char c = getFirstCharacter(word);
    int edgeIndex = c - 'a';
    node *edge = dictRoot->edges[edgeIndex];
    if ( edge == NULL) {
        //cout << "CountWord did not find an edge for letter : " << c << " in word : " << word << "\n";
        return 0;
    } else {
        cutFirstCharacter(word);
        //cout << "Count words called with : " << word << "\n";
        return countWords(edge, word);
    }
}

int TrieDict::countPrefixes(node* dictRoot, string prefix) {
    if (prefix.length() == 0) {
        return dictRoot->prefixes;
    }
    char c = getFirstCharacter(prefix);
    int edgeIndex = c - 'a';
    node *edge = dictRoot->edges[edgeIndex];
    if ( edge == NULL) {
        //cout << "CountPrefix did not find an edge for letter : " << c << " in prefix : " << prefix << "\n";
        return 0;
    } else {
        cutFirstCharacter(prefix);
        return countPrefixes(edge, prefix);
    }
}

int main() {
    TrieDict* tD = new TrieDict; 
    node* dR = tD->getDictRoot();

    tD->addWord(dR, "skp"); 
    tD->addWord(dR, "shashi"); 
    tD->addWord(dR, "shashi"); 
    tD->addWord(dR, "asdf"); 
    tD->addWord(dR, "sun");
    tD->addWord(dR, "surya");
    tD->addWord(dR, "sunshine");
    tD->addWord(dR, "shame");
    tD->addWord(dR, "shrine");
    tD->addWord(dR, "rain");
    tD->addWord(dR, "raid");
    tD->addWord(dR, "rainy");
    tD->addWord(dR, "rain");

    cout << "Prefix count for : [" << "" << "] : " << tD->countPrefixes(dR, "") << "\n";
    cout << "Word count for : [" << "shashi" << "] : " << tD->countWords(dR, "shashi") << "\n";
    cout << "Prefix count for : [" << "sh" << "] : " << tD->countPrefixes(dR, "sh") << "\n";
    cout << "Prefix count for : [" << "s" << "] : " << tD->countPrefixes(dR, "s") << "\n";
    cout << "Word count for : [" << "kar" << "] : " << tD->countWords(dR, "kar") << "\n";
    cout << "Prefix count for : [" << "kart" << "] : " << tD->countPrefixes(dR, "kart") << "\n";

    return 0;
}
