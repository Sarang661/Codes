#include<iostream>
#include<omp.h>
#include<vector>
using namespace std;

void bubble(vector<int>&v){

    for(int i = 0; i < v.size(); i++){

        int first = i%2;

        #pragma omp parallel for shared(v, first)
        for(int j = first; j < v.size()-1; j += 2){

            if(v[j] > v[j+1]){
                swap(v[j], v[j+1]);
            }
        }
    }

    for(int i = 0; i< v.size(); i++){
        cout<<v[i]<<" ";
    }
}


void merge(vector<int>&v, int i, int m , int j){

    int n1 = m-i+1;
    int n2 = j-m;

    vector<int>v1(n1);
    vector<int>v2(n2);

    for(int s = 0; s < n1; s++){
        v1[s] = v[i+s];
    }
    for(int s = 0; s < n2; s++){
        v2[s] = v[s+m+1];
    }

    int k = i;
    int s1 = 0;
    int s2= 0;

    while(s1 < n1 && s2 < n2){

        if(v1[s1] <= v2[s2]){
            v[k] = v1[s1];
            s1++;
            k++;
        }
        else{
             v[k] = v2[s2];
            s2++;
            k++;
    }
    }
    
    while(s1 < n1){
        v[k] = v1[s1];
        k++;
        s1++;
    }

     while(s2 < n2){
        v[k] = v2[s2];
        k++;
        s2++;
    }

}
void mergeSort(vector<int>&v, int s, int e){


    if(s < e){

        int m = s + (e-s)/2;

    #pragma omp parallel sections
    {

        #pragma omp section
        mergeSort(v, s, m);

        #pragma omp section
        mergeSort(v, m+1, e);

    }

    merge(v, s, m, e);

    }

}
int main(){

    vector<int>v;

    for(int i = 0; i< 100; i++){

        v.push_back(rand()%500);
    }
    v.push_back(9);
    v.push_back(1);
    v.push_back(8);

    mergeSort(v, 0, v.size()-1);

       for(int i = 0; i< v.size(); i++){
        cout<<v[i]<<" ";
    }

}