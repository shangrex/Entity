#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <bits/stdc++.h>
#include <vector>
using namespace std;
vector initial_split(FILE * file_in, int block_size, int* count_pages){
    // //open output temp file
    // FILE *page[pages];
    // for(int i = 0; i < pages; i++){
    //     string y = ("out_temp_" + to_string(i) + ".txt");
    //     page[i] = fopen(y.c_str(), "w");
    // }
    //load to output temp file and sort
    int data;
    int num_data = 0;
    int arr[block_size];
    bool check = true;
    vector<FILE*> pages(1);
    while(check){
        int i;
        for(i = 0; i < block_size; i++){
            fscanf(file_in, "%d" , &arr[i]);
            if(feof(file_in) != 0){
                check = false;
                break;
            }
        }
        sort(arr, arr+i);
        *count_pages ++ ;
        string title = "out_temp_" + to_string(*count_pages) + ".txt";
        pages.resize(*count_pages);
        pages[*count_pages-1] = fopen(title.c_str(), "w");
        for(int j  = 0; j < i; j++){
            fprintf(pages[*count_pages-1],"%d" ,arr[j]);
            if(j != i-1)fprintf(pages[*count_pages-1], "\n");
        }
    }
    return pages;
}
void merge_file(FILE *file_out, int block_size, int sum_pages, vector<FILE*>pages){
    priority_queue <int, vector<int>, greater<int> > pq; 
    bool check = true;
    int arr[block_size];
    int count_pages = 0;
    while(check){
        for(int i = 0; i < block_size; i++){
            fscanf(pages[count_pages], "%d", &arr[i]);
        }
    }
}
int main(){
    FILE *file_in;
    FILE *file_out;
    clock_t start, end;
    file_in = fopen("input.txt", "r");
    file_out = fopen("output.txt", "w");
    int block_size;
    // int pages, block_size;
    // cout << "input the # of pages" << endl;
    // cin >> pages;
    //block size * pages = total size
    cout << "input the # of data in a block size" << endl;
    cin >> block_size;
    int count_pages;
    start = clock();
    vector<FILE*>pages;
    if(file_in){
        pages = initial_split(file_in, block_size, &count_pages);
        merge_file(file_out , block_size, count_pages, pages);
    }
    else{
        cout << "file can not open" << endl;
    }
    cout << "total execution time " << ((double) (end - start)) / CLOCKS_PER_SEC  << " secs" << endl;

    fclose(file_in);
    fclose(file_out);   
    return 0;
}