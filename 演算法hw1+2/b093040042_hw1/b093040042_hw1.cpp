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
vector<City> exhaustive_search_TSP(vector<City>& cities){
    vector <City> ans;
    double mininum = 1e308;
    sort(cities.begin(),cities.end());//preprocessing for next_permutation()
    int n = cities.size();
    do{//iterate all permutation
        double sum = dist(cities[0],cities[n-1]);//0 to n-1
        for(int i=n-1;i>0;i--){
            sum += dist(cities[i],cities[i-1]);//n-1 to 0
        }
        if(sum<mininum && !isclose(sum,mininum)){//find a smaller route
            mininum = sum;
            ans = cities;
        }
    }while(next_permutation(cities.begin(),cities.end()));
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
        vector <City> ans = exhaustive_search_TSP(cities);
        int n = ans.size();
        //length of answer route
        double distance = dist(ans[0],ans[n-1]);//length of this route
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
