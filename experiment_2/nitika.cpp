#include<bits/stdc++.h>

using namespace std;

int count_chairs(pair<int , int>* vect, int n)
{
    vector <int> x;
    auto pt=vect;
    x.push_back((*pt).second);
    int chair = 1,seats = 1;
    pt++;
    for(int i = 1 ; i < n ; i++)
    {
        auto it = x.begin();
        while(*it < (*pt).first)
        {
            it++;
            x.erase(it - 1);
            seats--;
        }
        while((it)!=x.end()&&*it < (*pt).second){
            it++;
        }
        if((it)==x.end()){
                x.push_back((*pt).second);
        }
        else
            x.insert(it,(*pt).second);
        seats++;
        if(seats > chair)
            chair++;
        pt++;
    }
    return chair;
}
int main() {
    int n,x;
    cin >> n;
    pair <int , int> vect[n] ;
    for(int i = 0;i < n;i++)
    {
        cin >> x;
        vect[i].first = x;
    }
    for(int i = 0;i < n;i++)
    {
        cin >> x;
        vect[i].second = x;
    }
    sort(vect, vect + n);
    cout << count_chairs(vect,n);
    return 0;
}