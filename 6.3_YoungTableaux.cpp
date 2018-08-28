//
//  main.cpp
//  Young_tableaus
//
//  Created by Jing Liang on 8/27/18.
//  Copyright © 2018 Jing Liang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#define row 5
#define col 4

int count=0;
void showTable(std::vector<std::vector<int> > &aTable);
void insertTable(std::vector<std::vector<int> > &aTable,int aKey);
int  extract_min(std::vector<std::vector<int> > &aTable);
void AdjustTable(std::vector<std::vector<int> > &aTable,int aStartRow, int aStartCol);
bool valid(int aRow,int aCol);
int  get_last_row(int aCount);
int  get_last_col(int aCount);
int  get_new_row(int aCount);
int  get_new_col(int aCount);
bool find_key(std::vector<std::vector<int> > &aTable,int aKey);


int main(int argc, const char * argv[]) {
    std::vector<std::vector<int> > table(row,std::vector<int>(col,INT_MAX));
    std::vector<int> input = {9,16,3,2,4,8,5,14,12,1,2,3,20};
    for(int i=0;i<input.size();i++){
        insertTable(table, input[i]);
    }
    showTable(table);
    std::vector<int> existTestSet = {9,16,3,2,10,15,6,20};
    for(int i=0;i<existTestSet.size();i++){
        bool exist = find_key(table,existTestSet[i]);
        if(exist){
            std::cout<<std::left<<std::setw(4)<<existTestSet[i]<<" exists in the tableaus."<<std::endl;
        }else{
            std::cout<<std::left<<std::setw(4)<<existTestSet[i]<<" dosn't exist in the tableaus."<<std::endl;
        }
    }
    
    
    
    
    return 0;
}
void showTable(std::vector<std::vector<int> > &aTable){
    for(int i=0;i<aTable.size();i++){
        for(int j=0;j<aTable[0].size();j++){
            if(aTable[i][j]==INT_MAX){
                std::cout<<std::left<<std::setw(8)<<"INT";
            }
            else{
                std::cout<<std::left<<std::setw(8)<<aTable[i][j];
            }
        }
        std::cout<<std::endl;
    }
}
void insertTable(std::vector<std::vector<int> > &aTable,int aKey){
    if(count<row*col){
        int aRow = get_new_row(count);
        int aCol = get_new_col(count);
        int larger_row=0,larger_col=0;
        aTable[aRow][aCol] = aKey;
        while(true){
            int larger = aKey;
            if(valid(aRow,aCol-1) && aTable[aRow][aCol-1]>aKey){
                larger = aTable[aRow][aCol-1];
                larger_row = aRow;
                larger_col = aCol-1;
            }
            if(valid(aRow-1,aCol) && aTable[aRow-1][aCol]>larger){
                larger = aTable[aRow-1][aCol];
                larger_row = aRow-1;
                larger_col = aCol;
            }
            if(larger==aKey){
                break;
            }
            else{
                std::swap(aTable[aRow][aCol],aTable[larger_row][larger_col]);
                aRow = larger_row;
                aCol = larger_col;
            }
        }
        count++;
        std::cout<<"Insert "<<aKey<<" successfully!"<<std::endl;
    }
    else{
        std::cout<<"Young Tableaus is full!"<<std::endl;
    }
}
void AdjustTable(std::vector<std::vector<int> > &aTable,int aStartRow, int aStartCol){
    int smaller = INT_MAX;
    int currentValue = aTable[aStartRow][aStartCol];
    int downRow = aStartRow+1;
    int newRow = 0; int newCol=0;
    if(valid(downRow,aStartCol)&& aTable[downRow][aStartCol]<currentValue){
        smaller = aTable[downRow][aStartCol];
        newRow = downRow;
        newCol = aStartCol;
    }
    int rightCol = aStartCol+1;
    if(valid(aStartRow,rightCol) && aTable[aStartRow][rightCol]<smaller){
        smaller = aTable[aStartRow][rightCol];
        newRow = aStartRow;
        newCol = rightCol;
    }
    if(smaller==INT_MAX)
        return;
    std::swap(aTable[aStartRow][aStartCol],aTable[newRow][newCol]);
    AdjustTable(aTable, newRow, newCol);
}
int extract_min(std::vector<std::vector<int> > &aTable){
    int minimum = INT_MIN;
    if(count==0){
        std::cout<<"The Young Tableaus is empty!";
        return 0;
    }
    else if(count==1){
        count--;
        minimum = aTable[0][0];
        aTable[0][0] = INT_MAX;
    }
    else{
        minimum = aTable[0][0];
        aTable[0][0] = aTable[get_last_row(count)][get_last_col(count)];
        aTable[get_last_row(count)][get_last_col(count)] = INT_MAX;
        count--;
        AdjustTable(aTable, 0, 0);
    }
    return minimum;
}
int  get_last_row(int aCount){
    return (aCount-1)/col;
}
int  get_last_col(int aCount){
    return (aCount-1)%col;
}
int  get_new_row(int aCount){
    return aCount/col;
}
int  get_new_col(int aCount){
    return aCount%col;
}
bool valid(int aRow,int aCol){
    if(aRow>=0 && aRow<row && aCol>=0 && aCol<col)
        return true;
    return false;
}
bool find_key(std::vector<std::vector<int> > &aTable,int aKey){
    int currentRow = 0;
    int currentCol = col-1;
    while(true){
        if(aKey==aTable[currentRow][currentCol]){
            return 1;
        }
        else if( aKey<aTable[currentRow][currentCol] ){
            currentCol--;
            if(!valid(currentRow,currentCol))
                return 0;
        }
        else{
            currentRow++;
            if(!valid(currentRow,currentCol) || (valid(currentRow,currentCol)&& aTable[currentRow][currentCol]==INT_MAX&& currentRow!=get_last_row(count)) )
                return 0;
        }
    }
}

