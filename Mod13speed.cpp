#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <queue>
#include <random>
#include <time.h>
#define INF 1e9
#define vi vector<int>
#define vb vector<bool>
#define vll vector<long long>
#define v2i vector<vector<int>>
#define v3i vector<vector<vector<int>>>
#define v2b vector<vector<bool>>
#define v2ll vector<vector<long long>>
#define all(x) x.begin(),x.end()
using namespace std;
using ll = long long;

vi MOD13inv = {0, 1, 7, 9, 10, 8, 11, 2, 5, 3, 4, 6, 12, 0};
//四則演算
int add(int a, int b) {return (a+b)%13;}
int sub1(int a, int b) {return (a+13-b)%13;}
int sub2(int a, int b) {return (b+13-a)%13;}
int multi(int a, int b) {return (a*b)%13;}
int div1(int a, int b) {return (a*MOD13inv[b])%13;}
int div2(int a, int b) {return (b*MOD13inv[a])%13;}

int main(){
    srand((unsigned int) time(NULL));

    queue<int> p1, p2;
    vi card;
    for(int i=1; i<=13; i++){
        for(int j=0; j<4; j++){
            card.push_back(i);
        }
    }
    mt19937 engine((unsigned int) time(NULL));
    shuffle(all(card), engine);

    //カードを配布する
    for(int i=0; i<26; i++){
        p1.push(card[i]);
        p2.push(card[i+26]);
    }

    //場の4枚のカード
    vi p1_card(4), p2_card(4);
    for(int i=0; i<4; i++){
        int p1top = p1.front();
        int p2top = p2.front();
        p1.pop(); p2.pop();
        p1_card[i] = p1top;
        p2_card[i] = p2top;
    }
    //場の2枚のカード
    int a = p1.front(); p1.pop();
    int b = p2.front(); p2.pop();

    cout << a << " " << b << endl;
    cout << add(a,b)<<" "<<sub1(a,b)<<" "<<sub2(a,b)<<" "<<multi(a,b)<<" "<<div1(a,b)<<" "<<div2(a,b)<<endl;

    return 0;
}