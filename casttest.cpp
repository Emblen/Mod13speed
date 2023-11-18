#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <queue>
#define INF 1e9
#define vi vector<int>
#define vb vector<bool>
#define vll vector<long long>
#define v2i vector<vector<int>>
#define v2b vector<vector<bool>>
#define v2ll vector<vector<long long>>
#define all(x) x.begin(),x.end()
using namespace std;
using ll = long long;


int main(){
    string s; cin>>s;
    try{
        cout << stoi(s) << endl;
    }
    catch(invalid_argument& e){
        cout << e.what() << endl;
        cout << "invalid input" << endl;
    }
    return 0;
}