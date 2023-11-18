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

//プレイヤーの状態を管理
struct Player{
    //プレイヤーが現在出せる4枚のカード
    vi card4;
    //プレイヤーの手持ちカード
    queue<int> q;
    Player(): card4(4,0) { }
};


//ゲームの進行を管理
struct Game{
    Player cpu, player;
    //それぞれのプレイヤーが場に出せるカードがあるか
    bool p1can, p2can;
    //場にある2枚のカード
    int x, y;
    
    Game()
    : p1can(0), p2can(0), cpu(), player(), x(0), y(0)
    {
        distribute_card();
    }

    void gamestart(){
        first_battle();
        //どちらかの手札がなくなって場に4枚しかなくなった場合
        if(cpu.q.empty()){
            if(second_battle(cpu, player)) final_battle(cpu, player);
        }
        else{
            if(second_battle(player, cpu)) final_battle(player, cpu);
        }

        cout << "FINISH" << endl;
    }

    void first_battle(){
        while(!(cpu.q.empty()) && !(player.q.empty())){

            //出せるカードがあるか
            set<int> cards = canbeplayed(x,y);
            int nump1 = canplayerpullout(cards, cpu);
            int nump2 = canplayerpullout(cards, player);
            
            //どちらもカードを出せない場合 新たに場にカードを供給する
            if(nump1==INF && nump2==INF){
                x = cpu.q.front(); cpu.q.pop();
                y = player.q.front(); player.q.pop();
                cout << "p1:"<<x<<" p2:"<<y<<endl;
            }
            //どちらのプレイヤーがカードを出すか
            //p2のみ出せる場合
            else if(nump1==INF && nump2!=INF){
                cardchange(nump2, player);
                cout << "p2:"<<nump2<<endl;
            }
            //p1のみ出せる場合
            else if(nump1!=INF && nump2==INF){
                cardchange(nump1, cpu);
                cout << "p1:"<<nump1<<endl;
            }
            //どちらも出せる場合
            else{
                if(selectplayer()){
                    cardchange(nump1, cpu);
                    cout << "p1:"<<nump1<<endl;
                }
                else{
                    cardchange(nump2, player);
                    cout << "p2:"<<nump2<<endl;
                }
            }

            for(int i=0; i<4; i++) cout << cpu.card4[i] << " ";
            cout << "rem: " << cpu.q.size() << endl;
            cout << "  "<< x << "  "<<y << endl;
            for(int i=0; i<4; i++) cout << player.card4[i] << " ";
            cout << "rem: " << player.q.size() << endl;
            cout << endl;

        }
    }
    //一方のプレイヤーの手札がなくなったときの処理
    int second_battle(Player& p1, Player& p2){
        //p1は手札がなくなったほう
        bool flag = 1;

        while(flag){
            //出せるカードがあるか
            set<int> cards = canbeplayed(x,y);
            int nump1 = canplayerpullout(cards, p1);
            int nump2 = canplayerpullout(cards, p2);

            if(nump1==INF && nump2==INF){
                x = random4(p1);
                y = p2.q.front(); p2.q.pop();
                cout << "p1:"<<x<<" p2:"<<y<<endl;
            }
            //どちらのプレイヤーがカードを出すか
            //p2のみ出せる場合
            else if(nump1==INF && nump2!=INF){
                cardchange(nump2, p2);
                cout << "p2:"<<nump2<<endl;
            }
            //p1のみ出せる場合
            else if(nump1!=INF && nump2==INF){
                cardchange_rem4(nump1, p1);
                cout << "p1:"<<nump1<<endl;
            }
            //どちらも出せる場合
            else{
                if(selectplayer()){
                    cardchange_rem4(nump1, p1);
                    cout << "p1:"<<nump1<<endl;
                }
                else{
                    cardchange(nump2, p2);
                    cout << "p2:"<<nump2<<endl;
                }
            }

            //出力
            int infcnt = 0;
            for(int i=0; i<4; i++){
                if(p1.card4[i]==INF) {infcnt++; cout << "- ";}
                else cout << p1.card4[i] << " ";
            }
            cout << endl;
            cout << "  "<< x << "  "<< y << endl;
            for(int i=0; i<4; i++) cout << p2.card4[i] << " ";
            cout << "rem: " << p2.q.size() << endl;
            cout << endl;
            
            //p2も手札がなくなったら次の段階に進む
            if(p2.q.empty() || infcnt==4) flag = 0;
        }
        //p2がemptyになったらfinal_battleへ進む，そうでなければp1の勝ちでゲームセット
        if(p2.q.empty()) return 1;
        else return 0;
    }
    //両方のプレイヤーが場にある札のみになったときの処理
    void final_battle(Player& p1, Player& p2){
        bool flag = 1;

        while(flag){
            //出せるカードがあるか
            set<int> cards = canbeplayed(x,y);
            int nump1 = canplayerpullout(cards, p1);
            int nump2 = canplayerpullout(cards, p2);

            if(nump1==INF && nump2==INF){
                x = random4(p1);
                y = random4(p2);
                cout << "p1:"<<x<<" p2:"<<y<<endl;
            }
            //どちらのプレイヤーがカードを出すか
            //p2のみ出せる場合
            else if(nump1==INF && nump2!=INF){
                cardchange_rem4(nump2, p2);
                cout << "p2:"<<nump2<<endl;
            }
            //p1のみ出せる場合
            else if(nump1!=INF && nump2==INF){
                cardchange_rem4(nump1, p1);
                cout << "p1:"<<nump1<<endl;
            }
            //どちらも出せる場合
            else{
                if(selectplayer()){
                    cardchange_rem4(nump1, p1);
                    cout << "p1:"<<nump1<<endl;
                }
                else{
                    cardchange_rem4(nump2, p2);
                    cout << "p2:"<<nump2<<endl;
                }
            }

            //出力
            int infcnt = 0;
            int tmp = 0;
            for(int i=0; i<4; i++){
                if(p1.card4[i]==INF) {tmp++; cout << "- ";}
                else cout << p1.card4[i] << " ";
            }
            cout << endl;
            infcnt = tmp;
            tmp = 0;
            cout << "  "<< x << "  "<< y << endl;
            for(int i=0; i<4; i++){
                if(p2.card4[i]==INF) {tmp++; cout << "- ";}
                else cout << p2.card4[i] << " ";
            }
            cout << endl;            
            cout << endl;
            
            infcnt = max(infcnt, tmp);
            if(infcnt==4) flag = 0;
        }
    }

    //両方詰まったときに場にある手札の中からランダムに数字を選ぶ
    int random4(Player& p){
        vi remcards;
        for(int i=0; i<4; i++){
            if(p.card4[i]!=INF) remcards.push_back(p.card4[i]);
        }
        mt19937 engine((unsigned int) time(NULL));
        shuffle(all(remcards), engine);

        for(int i=0; i<4; i++){
            if(p.card4[i]==remcards[0]) {p.card4[i] = INF; break;}
        }
        return remcards[0];
    }


    //カードを出した後の操作
    void cardchange(int cardnum, Player& p){
        for(int i=0; i<4; i++){
            if(cardnum == p.card4[i]){
                int newcard = p.q.front(); p.q.pop();
                p.card4[i] = newcard;
                //カードをx,yどちらに出すか
                if(selectplayer()) x = cardnum;
                else y = cardnum;
                break;
            }
        }
    }
    //手札が場にあるものになったときの，カードを出した後の操作
    void cardchange_rem4(int cardnum, Player& p){
        for(int i=0; i<4; i++){
            if(cardnum == p.card4[i]){
                p.card4[i] = INF;
                //カードをx,yどちらに出すか
                if(selectplayer()) x = cardnum;
                else y = cardnum;
                break;
            }
        }
    }

    //出せるカードがなければINFを返す
    //出せるカードがあればその数を一つランダムで返す
    int canplayerpullout(set<int> cards, Player p){
        //同じカードが滞留するのを防ぐためにカードをシャッフル
        mt19937 engine((unsigned int) time(NULL));
        shuffle(all(p.card4), engine);

        for(int i=0; i<4; i++){
            int num = p.card4[i];
            for(auto c:cards){
                if(c==num) return num;
            }
        }
        return INF;
    }

    //両方のプレイヤーが場にカードを出せるとき、どちらが出すか確率的に決定する関数
    //てきとうな数を1つ生成して奇数か偶数か
    bool selectplayer(){
        int num = rand();
        // cout << num << endl;
        if(num%2) return 1;
        else return 0;
    }

    //場に出ているカードを把握して計算を行う関数
    set<int> canbeplayed(int a, int b){
        set<int> rt;
        rt.insert(add(a,b));
        rt.insert(sub1(a,b));
        rt.insert(sub2(a,b));
        rt.insert(multi(a,b));
        rt.insert(div1(a,b));
        rt.insert(div2(a,b));
        
        return rt;
    }

    //カードを配布する関数
    void distribute_card(){
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
            cpu.q.push(card[i]);
            player.q.push(card[i+26]);
        }
        //最初の4枚のカードを場に出す
        for(int i=0; i<4; i++){
            int p1card = cpu.q.front(); cpu.q.pop();
            int p2card = player.q.front(); player.q.pop();
            cpu.card4[i] = p1card;
            player.card4[i] = p2card;
        }
        x = cpu.q.front(); cpu.q.pop();
        y = player.q.front(); player.q.pop();

    }
};

int main(){
    srand((unsigned int) time(NULL));
    Game game;
    game.gamestart();
    return 0;
}
