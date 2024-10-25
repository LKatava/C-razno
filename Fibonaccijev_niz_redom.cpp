#include <iostream>
#include <queue>
using namespace std;

int main(){
    queue <unsigned long long int> fib;
    int n;
    cout << "Zeljeni broj generiranja elemenata: "; cin >> n;
    unsigned long long int t1 = 1, t2 = 1, nT;
     for (int i = 0; i <n; i++) {
        fib.push(t1);
        nT = t1 + t2;
        t1 = t2;
        t2 = nT;
    }
    cout << "Velicina reda: " << fib.size() << endl;
    cout << "Prvi element reda: " << fib.front() << endl;
    cout << "Zadnji element reda: " << fib.back() << endl;
    cout << "Fibonaccijev niz: ";
    for (int j=0;j<n;j++){
        cout << fib.front();
        if (j != n-1)
            cout <<", " ;
        fib.pop();
    }
    return 0; 
}
