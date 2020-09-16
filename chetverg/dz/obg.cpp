#include <iostream>
#include <vector>
#include <list>
#include<fstream>
#include<queue>
using std::queue;
using std::list;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

/*s < 3 шум 3<=S<=5 -цель  S>5 -земля*/
struct dot{
    size_t x;
    size_t y;
};

bool top_exist (dot fixed, int** matrix, int matrix_width, int matrix_height){
    bool flag = false;
    if((fixed.x != 0) && (matrix[fixed.x - 1][fixed.y] == 1) ){
        flag = true;
        matrix[fixed.x - 1][fixed.y] = 0;
        }
    return flag;
}
bool bottom_exist(dot fixed, int** matrix, int matrix_width, int matrix_height){
    
    bool flag = false;
    if( (fixed.x != matrix_height -1) && (matrix[fixed.x + 1][fixed.y] == 1) ){
        flag = true;
        matrix[fixed.x + 1][fixed.y] = 0;
    }
    return flag;
}
bool left_exist(dot fixed, int** matrix, int matrix_width, int matrix_height){
    
    bool flag = false;
    if( (fixed.y != 0) && (matrix[fixed.x][fixed.y - 1] == 1) ){
        matrix[fixed.x][fixed.y - 1] = 0;
        flag = true;
    }
    return flag;
}
bool right_exist(dot fixed, int** matrix, int matrix_width, int matrix_height){
    
    bool flag = false;
    if( (fixed.y != matrix_width - 1 ) && (matrix[fixed.x][fixed.y + 1 ] == 1) ){
        matrix[fixed.x][fixed.y+1] = 0;
        flag = true;
    }
    return flag;
}

int main(){
    int height = 0;//высота (кол во строк) матрицы
    int width = 0;//ширина (кол во столбцов) матрицы
    cin>>height>>width;
    int** matrix = new int* [height]; //создаём двумерную матрицу
    for (int i = 0; i < height; i++){
        matrix[i] = new int[width];
    }
    for(int i = 0 ; i < height; i ++){//заполняем
        for(int j =0; j < width; j++){
            cin>>matrix[i][j];
        }
    }
    vector<dot>obj_koord;
    vector<int>obj_s;
    vector<dot>obj_ko_test;
    int s = 0;
    for(int i =0; i < height; i ++){
        for(int j = 0; j < width; j++){
            if (matrix[i][j] == 1){
                dot fixed;
                fixed.x = i;
                fixed.y = j;
                matrix[i][j] = 0;
                cout<< endl<<i<< " "<< j <<" "<< matrix[i][j]<<endl; //test delete me

                obj_koord.push_back(fixed);
                while(obj_koord.size() != 0 ){
                    fixed = obj_koord.back();
                    cout<<"fixed:("<<fixed.x<<","<<fixed.y<<")"<<endl;//test delete me
                    obj_koord.pop_back();
                    s++;
                    matrix[fixed.x][fixed.y] = 0;
                    
                    //test delete me
                    for(int i = 0 ; i < height; i ++){//выводим
                        for(int j =0; j < width; j++){
                            cout<<matrix[i][j]<<" ";
                        }
                        cout<<endl;
                    }
                    //-------------

                    if(top_exist(fixed,matrix,width,height) == true){
                        dot top;
                        top.x = fixed.x - 1;
                        top.y = fixed.y;
                        cout<<"("<<top.x<<","<<top.y<<") ";//test delete me
                        obj_koord.push_back(top);
                        matrix[top.x][top.y]=0;
                    }
                    if(bottom_exist(fixed,matrix,width,height)== true){
                        
                        dot bottom;
                        bottom.x = fixed.x + 1;
                        bottom.y = fixed.y;
                        cout<<"bottom:"<<bottom.x<<","<<bottom.y<<endl;//test delete me
                        obj_koord.push_back(bottom);
                        matrix[bottom.x][bottom.y] = 0;
                    }
                    if(left_exist(fixed,matrix,width,height)){
                        dot left;
                        left.x = fixed.x;
                        left.y = fixed.y - 1;
                        obj_koord.push_back(left);
                        cout<<"left: "<<left.x<<","<<left.y<<endl;//test delete me
                        matrix[left.x][left.y] = 0;
                    }
                    if(right_exist(fixed,matrix,width,height)){
                        
                        dot right;
                        right.x = fixed.x;
                        right.y = fixed.y + 1;
                        cout<<"right: "<<right.x<<","<<right.y<<endl;//test delete me
                        obj_koord.push_back(right);
                      
                        matrix[right.x][right.y] = 0;

                    }
                    //test delete me
                    cout<<"vector: ";
                    for(int i = 0; i< obj_koord.size();i++){
                        cout<<"("<<obj_koord[i].x<<","<<obj_koord[i].y<<")"<<" ";
                    }
                    cout<<endl;
                    //---------------
                    
                }  
                if(s > 0){
                    obj_s.push_back(s);
                    s = 0;
                }
            }
          
            
        }
    }

    
    for(int i = 0; i <obj_s.size(); i ++){//красиво обрабатываем массив площадей
        cout<<"объект["<<i+1<<"] это - ";
        if(obj_s[i] < 3) cout<<"ШУМ ";
        else if(obj_s[i]<=5) cout<<"ЦЕЛЬ ";
        else cout<<"ЗЕМЛЯ ";
        cout<<"площадью "<<obj_s[i]<<" усл. ед."<<endl;
    }
    for (int i = 0; i < height; i++){// чистим динамическую память
        delete[] matrix[i];
    }
    return 0;
}/*
0 0 1 0 0
0 0 1 1 0
0 0 0 0 1
0 0 0 0 0
0 0 0 0 0
*/