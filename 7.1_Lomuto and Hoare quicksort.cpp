//
//  main.cpp
//  QuickSort
//
//  Created by Jing Liang on 9/26/18.
//  Copyright © 2018 Jing Liang. All rights reserved.
//

#include <iostream>
#include <vector>
int Lpartition(std::vector<int>& aVector,int aStart,int aEnd){
    //Lomuto partition schema
    int pivot = aVector[aEnd];
    int i = aStart-1;
    for(int j=aStart;j<aEnd;j++){
        if(aVector[j]<=pivot){
            std::swap(aVector[++i],aVector[j]);
        }
    }
    std::swap(aVector[++i],aVector[aEnd]);
    return i;
}
int Hpartition(std::vector<int>& aVector,int aStart,int aEnd){
    //Hoare partition schema
    int pivot = aVector[aStart];
    int i=aStart-1,j=aEnd+1;
    while(true){
        do{
            i++;
        }while(aVector[i]<pivot);
        do{
            j--;
        }while(aVector[j]>pivot);
        if(i<j){
            std::swap(aVector[i],aVector[j]);
        }
        else
            return j;
    }
}
void LquickSort(std::vector<int>& aVector,int aStart,int aEnd){
    /*   using tail recursion here
    while(aStart<aEnd){
        int index = Lpartition(aVector, aStart, aEnd);
        quickSort(aVector, aStart, index-1);
        aStart = index+1;
    }*/
    if(aStart<aEnd){
        int index = Lpartition(aVector, aStart, aEnd);
        //int index  = Hpartition(aVector, aStart, aEnd);
        LquickSort(aVector, aStart, index-1);
        LquickSort(aVector, index+1,aEnd);
    }
}
void HquickSort(std::vector<int>& aVector,int aStart,int aEnd){
    //  using tail recursion here
     while(aStart<aEnd){
     int index = Hpartition(aVector, aStart, aEnd);
     HquickSort(aVector, aStart, index);
     aStart = index+1;
     }
    /*
    if(aStart<aEnd){
        int index  = Hpartition(aVector, aStart, aEnd);
        HquickSort(aVector, aStart, index);
        HquickSort(aVector, index+1,aEnd);
    }
    */
}
int main(int argc, const char * argv[]) {
    std::vector<int> test = {2,8,7,1,3,5,6,4};
    //LquickSort(test, 0, test.size()-1);
    HquickSort(test, 0, test.size()-1);
    for(int i=0;i<test.size();i++){
        std::cout<<test[i]<<" ";
    }
    std::cout<<std::endl;
    return 0;
}
