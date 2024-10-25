#include <iostream>
#include <map>
using namespace std;

int main(){
    map <int, int> ap;
    map <int, int> ::iterator it;
    int long n,m;
    cout << "Upisite donju granicu raspona: "; cin>>n;
    cout << "Upisite gornju granicu raspona: ";cin>>m; //16 je max
    for (;n<m+1;n++){
        int fact = 1, i;
        for(i=1; i<=n; i++)
            fact = fact * i;
        ap[fact]=fact;
    }
    try{
        for (it = ap.begin(); it != ap.end(); ++it){
            if (it->second <= 0)
                throw runtime_error ("Dosli smo do granice!");
            cout << it->first <<" | " << it->second << endl;
        }
    }
    catch (runtime_error e){
        cout << "Greska: " << e.what()  << endl;
   }
    return 0;
}
