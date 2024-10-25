#include <vector>
#include <iostream>
using namespace std;

bool Prost(int n){
    if (n <= 1)
        return false;
    for (int i = 2; i <= n / 2; i++)
        if (n % i == 0)
            return false;
    return true;
}

int main(){
	vector <int> vek;
	for (int i=1;i<= 100;i++) vek.push_back(i);
	cout << "Velicina vektora: " << vek.size() << endl;
	cout << "Raspon vektora: 1-100" << endl;
	cout << "Prosti brojevi: ";
	for (int j = vek.size() - 1; j >= 0; j--)
		if (!Prost(vek[j]))
			vek.erase(vek.begin()+j);
	for (unsigned k=0;k<vek.size();k++) cout << vek[k] << " ";
	return 0;
}
