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
    bool flag = 0;
    while(!flag){
        int input; char c; 
            
        //数字かどうかのエラー処理
        if(input==0){
            cout << "INPUT RETRY0" << endl;
            continue;
        }
        //入力が多すぎたり数値が大きすぎたらエラー
        if(input<1 || input>13 || !(c=='r'||c=='l')){
            cout << "INPUT RETRY1" << endl;
            continue;
        }
    }


    return 0;
}