//
//  main.cpp
//  matrix_chain_order
//
//  Created by Jing Liang on 10/14/18.
//  Copyright © 2018 Jing Liang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <iomanip>
int Calculate_chain_order(std::vector<int> p, std::vector<std::vector<int> > &s, std::vector<std::vector<int> > &r){
    int n=p.size()-1;
    if(n==1)
        return 0;
    for(int l=2;l<=n;l++){
        for(int start = 0;start<=n-l;start++){
            int end = start+l-1;
            int minTemp = INT_MAX;
            for(int k=start;k<end;k++){
                int q = s[start][k]+s[k+1][end]+p[start]*p[k+1]*p[end+1];
                if(q<minTemp){
                    minTemp = q;
                    s[start][end] = minTemp;
                    r[start][end] = k;
                }
            }
        }
    }
    return s[0][n-1];
}
void print_result(std::vector<std::vector<int> > r, int start, int end){
    if(start==end)
        std::cout<<"A"<<start;
    else{
        std::cout<<"(";
        print_result(r,start,r[start][end]);
        print_result(r,r[start][end]+1,end);
        std::cout<<")";
    }
}
template<typename T> void printElement(T t,const int& width){
     std::cout<< std::left<<std::setw(width)<<std::setfill(' ')<<t;
}
void print_matrix(std::vector<std::vector<int> > matrix){
    for(int i=0;i<matrix.size();i++){
        for(int j=0;j<matrix[0].size();j++){
            printElement(matrix[i][j], 15);
        }
        std::cout<<std::endl;
    }
}
int main(int argc, const char * argv[]) {
    std::vector<int> test = {5,10,3,12,5,50,6};
    
    int n=test.size()-1;
    std::vector<std::vector<int> > s(n,std::vector<int>(n,INT_MAX));
    for(int i=0;i<n;i++){
        s[i][i] = 0;
    }
    std::vector<std::vector<int> > r(n,std::vector<int>(n,0) );
    int result = Calculate_chain_order(test,s,r);
    std::cout<<"Record k matrix is: "<<std::endl;
    print_matrix(r);
    std::cout<<"Total number of calculation is :"<<std::endl;
    print_matrix(s);
    std::cout<<"Matrix multiplication solution: "<<std::endl;
    print_result(r,0,n-1);
    return 0;
}
