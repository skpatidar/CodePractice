#include<stdio.h>
#include<vector>
int main() {
    std::vector<int> v; 
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
	printf("Vector V of size : %d\n", v.size());
	return 0;
}
