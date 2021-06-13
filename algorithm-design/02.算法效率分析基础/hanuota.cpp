//
// Created by ree on 6/12/21.
//
#include "iostream"
#include "algorithm"
#include "math.h"
#include "string.h"
#include "stack"
#include "time.h"
using namespace std;
void move(int num, char from, char to)
{
    cout << "move plate " << num << " from " << from << " to " << to << endl;
}
void HannuoTa(int num, char from, char to, char bypass)
{
    if (num == 1) {
        move(num, from, to);
        return;
    }
    HannuoTa(num-1, from, bypass, to);
    move(num, from, to);
    HannuoTa(num-1, bypass, to, from);
}

int whichPlateToMove(int number)
{
    if (number==0) return number;
    int i = 0;
    int remainder = 0;
    while (remainder==0) {
        remainder=number%2;
        number=number/2;
        i++;
    }
    return i;
}

//首先知道哪一步挪动哪个盘子，然后每个盘子按一定的顺序挪动
void HannuoTaBit(const int num)
{
    int state[num+1];
    memset(state,0,sizeof(state));
    char maxNumOrder[3] = {'a', 'c', 'b'};
    char reverseNumOrder[3] = {'a', 'b', 'c'};
    int totalNum = pow(2,num) - 1;
    for (int j = 1; j <= totalNum; ++j) {
        int mover = whichPlateToMove(j);
        int newIdx;
        char oldPlate, newPlate;
        if ((num-mover)%2 == 0) {
            newIdx = (state[mover]+1)%3;
            oldPlate = maxNumOrder[state[mover]];
            newPlate = maxNumOrder[newIdx];
        } else {
            newIdx = (state[mover]+1)%3;
            oldPlate = reverseNumOrder[state[mover]];
            newPlate = reverseNumOrder[newIdx];
        }
        cout << "move plate " << mover << " from " << oldPlate << " to " << newPlate << endl;
        state[mover] = newIdx;
    }
}
bool moveForHannuoTaNew(int idFrom, int idTo,char* order, stack<int>* tower)
{
    stack<int>& tower1 = tower[idFrom];
    stack<int>& tower2 = tower[idTo];
    if (tower1.empty()) return false;
    int plate = tower1.top();
    if (tower2.empty() || plate < tower2.top()) {
        tower1.pop();
        tower2.push(plate);
        move(plate,order[idFrom],order[idTo]);
        return true;
    }
    return false;
}

void HannuoTaNew(int num)
{
    char maxNumOrder[3] = {'a', 'c', 'b'};
    char reverseNumOrder[3] = {'a', 'b', 'c'};
    stack<int> tower[3];
    for (int i = 0; i < num; i++) {
        tower[0].push(num-i);
    }
    int smallestPlateIdx = 0;
    int count = 0;
    char * order;
    if (num % 2 == 1) {
        order = maxNumOrder;
    } else {
        order = reverseNumOrder;
    }
    while (++count) {
        int temp1 = (smallestPlateIdx+1)%3;
        moveForHannuoTaNew(smallestPlateIdx,temp1,order, tower);
        int id1 = smallestPlateIdx;
        int id2 = (smallestPlateIdx+2)%3;
        smallestPlateIdx = temp1;
        if (!moveForHannuoTaNew(id1,id2,order, tower) && !moveForHannuoTaNew(id2,id1,order,tower)) {
            break;
        }
    }
}
stack<int> oldTower[3];
//此解法基于以下事实,只能从栈顶挪盘子，只能从栈顶小的向栈顶大的挪盘子，所以每次其实只有3种挪法，每种挪法产生有不同的条件，而且不能有两盘相邻差2的情况出现
bool compare(int id1, int id2){
    stack<int>& tower1 = oldTower[id1];
    stack<int>& tower2 = oldTower[id2];
    if (tower1.empty()) {
        if(tower2.empty()) return id1 < id2;
        return false;
    }
    int plate = tower1.top();
    if (tower2.empty() || plate < tower2.top()) {
        return true;
    }
    return false;
}
int moveCount;
int beforeIdx;
int afterIdx;
bool moveForHannuoTaOld(int idFrom, int idTo,char* order, stack<int>* tower)
{
    stack<int>& tower1 = oldTower[idFrom];
    stack<int>& tower2 = oldTower[idTo];
    if (tower1.empty()) return false;
    int plate = tower1.top();
    if (!tower2.empty() && (plate-tower2.top())%2==0) {
        return false;
    }
    tower1.pop();
    tower2.push(plate);
    move(plate,order[idFrom],order[idTo]);
    moveCount++;
    beforeIdx = idFrom;
    afterIdx = idTo;
    return true;
}

void HannuoTaOld(int num)
{
    for (int i = 0; i < num; i++) {
        oldTower[0].push(num-i);
    }
    char order[3] = {'a','b','c'};
    int idRank[3] = {0,1,2};
    int totalNum = pow(2,num) - 1;
    if (num % 2 ==1) {
        moveForHannuoTaOld(0,2,order,oldTower);
    } else {
        moveForHannuoTaOld(0,1,order,oldTower);
    }
    int prevRoundRank1Idx = 3;
    while (moveCount < totalNum) {
        sort(idRank,idRank+3,compare);
        //刚放下不会再挪动，所以可以肯定不是从rank1挪动
        if (afterIdx==idRank[1]) { 
              if (prevRoundRank1Idx == beforeIdx) {
                  moveForHannuoTaOld(idRank[0],idRank[1],order,oldTower);     
              } else {
                  moveForHannuoTaOld(idRank[0],idRank[2],order,oldTower);     
              }
        } else {
            moveForHannuoTaOld(idRank[1],idRank[2],order,oldTower);
        }
        prevRoundRank1Idx = idRank[1];
    }

}

struct param
{
    int num;
    char from;
    char to;
    char bypass;
};

void HannuoTaStack(int num)
{
    char from = 'a';
    char to = 'c';
    char bypass = 'b'; 
    stack<param> input;
    param temp_out = {num,from,to,bypass};
    input.push(temp_out);
    while(!(input.empty())) {
        param temp_in = temp_out;
        while(temp_in.num>1)
        {
            temp_in.num--;
            swap(temp_in.to,temp_in.bypass);
            input.push(temp_in);
        }
        
        temp_out = input.top();
        input.pop();
        move(temp_out.num,temp_out.from,temp_out.to);
        if (temp_out.num!=1) {
            temp_out.num--;
            swap(temp_out.bypass,temp_out.from);
            input.push(temp_out);
        } 
    }

}

struct param1 {
        int n;
        char from;
        char pass;
        char to;
};
void hanoi(int n, char from, char pass, char to) {
        stack<param1> s;
        param1 par_outer = {n, from, pass, to};
        while (!(par_outer.n == 0 && s.empty())) {
                param1 par_inner = par_outer;
                while (par_inner.n > 0) {
                        s.push(par_inner);
                        par_inner.n --;
                        swap(par_inner.pass, par_inner.to);
                }

                par_outer = s.top();
                s.pop();

                move(par_outer.n, par_outer.from, par_outer.to);

                par_outer.n --;
                swap(par_outer.from, par_outer.pass);
        }
}
int main()
{
    int N;
    cin>>N;
    clock_t start,end;
    
    int totalTime1;
    start = clock();
    HannuoTaBit(N);
    end = clock();
    totalTime1 = end - start;
    cout << "=======" << endl;
 
    int totalTime2;
    start = clock();
    HannuoTa(N,'a','c','b');
    end = clock();
    totalTime2 = end - start;
    cout << "=======" << endl;

    int totalTime3;
    start = clock();
    HannuoTaNew(N);
    end = clock();
    totalTime3 = end - start;
    cout << "=======" << endl;

    int totalTime4;
    start = clock();
    //HannuoTaStack(N);
    hanoi(N, 'a', 'b', 'c');
    end = clock();
    totalTime4 = end - start;
    cout << "=======" << endl;

    int totalTime5;
    start = clock();
    HannuoTaStack(N);
    //hanoi(N, 'a', 'b', 'c');
    end = clock();
    totalTime5 = end - start;
    cout << "=======" << endl;

    int totalTime6;
    start = clock();
    HannuoTaOld(N);
    end = clock();
    totalTime5 = end - start;
    cout << "=======" << endl;

    cout << "bit takes " << totalTime1 << "ms" << endl; 
    cout << "recursion takes " << totalTime2 << "ms" << endl; 
    cout << "america takes " << totalTime3 << "ms" << endl; 
    cout << "stack_net takes " << totalTime4 << "ms" << endl; 
    cout << "stack takes " << totalTime5 << "ms" << endl;
    cout << "chinese takes " << totalTime6 << "ms" << endl;
 }