#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <queue>
#include <time.h>
#include <random>
#include <chrono>
#include <conio.h>
#include <sstream>
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
    using namespace std;
    chrono::system_clock::time_point start, end, end1;

    int a, b;
    double time = 0.0, time2 = 0.0;
    bool flag = 0;
    string buf;
    vector<string> v;
    int input;

    start = chrono::system_clock::now();
    //入力があるまで時間を計り続ける
    while(!flag && time<=4){
        end = chrono::system_clock::now();
        time = static_cast<double>(chrono::duration_cast<chrono::milliseconds>(end - start).count() / 1000.0);
        // cout << "time: " << time << endl;

        time2 = 0.0;
        while(!_kbhit() && time2<=1){
            end1 = chrono::system_clock::now();
            time2 = static_cast<double>(chrono::duration_cast<chrono::milliseconds>(end1 - end).count() / 1000.0);  
            // cout << time2 << endl;
        }
        // cout << time2 << endl;
        if(time2<=1){
            char ch = _getch();
            if((int)ch==13){
                string s;
                stringstream ss{buf};
                //v[0]には数字、v[1]にはrまたはlが入力されているはず
                while(getline(ss, s, ' ')) v.push_back(s);
                
                //数字に変換できるかのエラー処理
                try {
                    input = stoi(v[0]);
                }
                catch(invalid_argument& e){
                    cout << "INPUT RETRY" << endl;
                    continue;
                }
                //入力が多すぎたり数値が大きすぎたらエラー
                if((int)v.size()!=2 || input<1 || input>13 || !(v[1]=="r"||v[1]=="l")){
                    cout << "INPUT RETRY" << endl;
                    continue;
                }
                else {
                    flag = 1;
                    string ms = (v[1]=="r") ? "right":"left";
                    cout << input << " " << ms << endl;
                }
            }
            else buf.push_back(ch);
        }        
    }
    if(!flag) cout << "CPU played" << endl; 
    return 0;
}