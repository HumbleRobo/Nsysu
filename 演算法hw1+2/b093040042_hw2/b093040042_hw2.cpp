#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int dt_size = 3;

class Point{
public:
    int x,y;
    Point(int x,int y):x(x),y(y){}
};
class City{
public:
    string name;
    Point point;
    City(string name,int x,int y):name(name),point(x,y){}
    bool operator< (const City &that){
        return this->name < that.name;
    }
};
double dist(City& a,City& b){//distance between two city
    double x_diff = a.point.x-b.point.x;
    double y_diff = a.point.y-b.point.y;
    return sqrt(pow(x_diff,2)+pow(y_diff,2));
}
bool isclose(double& a, double& b){
    double rel_tol = 1e-9;
    return -rel_tol<a-b && a-b<rel_tol;
}
vector<City> greedy_TSP(vector<City>& cities){
    int n = cities.size();
    vector <City> ans;
    ans.push_back(cities[0]);//starting city:0(name = 1)
    bool visited[n] = {true};//city 0 is visited
    int from = 0;//current city
    while(ans.size()<n){
        int to;//closet city
        double mininum_distance = 1e308;
        for(int i=0;i<n;i++){
            if(!visited[i]){
                double distance = dist(cities[from],cities[i]);
                //cout<<cities[from].name<<", "<<cities[i].name<<": "<<distance<<endl;
                if(distance<mininum_distance && !isclose(distance,mininum_distance)){
                    mininum_distance = distance;
                    to = i;
                }
            }
        }
        visited[to] = true;
        ans.push_back(cities[to]);
        from = to;
    }
    return ans;
}
int main(){
    for(int i=1;i<=3;i++){
        //read
        string input_file_name = string("dt")+to_string(i)+"/point.txt";//dt1/point.txt
        ifstream ifs(input_file_name);
        //init
        vector <City> cities;
        string name; int x,y;
        while(ifs>>name>>x>>y){
            cities.push_back(City(name,x,y));
        }
        //search
        vector <City> ans = greedy_TSP(cities);
        int n = ans.size();
        //length of answer route
        double distance = dist(ans[0],ans[n-1]);
        for(int i=n-1;i>0;i--){
            distance += dist(ans[i],ans[i-1]);
        }
        //txt output
        string ouput_file_name = string("ans_dt")+to_string(i)+".txt";//ans_dt1.txt
        ofstream ofs(ouput_file_name);
        ofs<<"distance: "<<distance<<endl;
        for(int i=0;i<n;i++)
            ofs<<ans[i].name<<endl;
        //terminal output
        cout<<"distance: "<<distance<<endl;
        for(int i=0;i<n;i++)
            cout<<ans[i].name<<endl;
    }
    return 0;
}
