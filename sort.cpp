#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <bits/stdc++.h>
#include <vector>
#include <sys/stat.h> 


using namespace std;
int arr[100000000];
int initial_split(FILE * file_in, int block_size, int* count_pages){
    //load to output temp file and sort
    int data;
    int num_data = 0;
    //int arr[block_size]; since global can do 10^8 size
    bool check = true;
    int cc = 0;
    int i ;
    int special_count;
    FILE *file_out;
    while(check){
        //scan the input file in to block
        for(i = 0; i < block_size; i++){
            fscanf(file_in, "%d" , &arr[i]);
            if(feof(file_in) != 0){
                special_count = i;
                i++;
                check = false;
                break;
            }
        }
        

        sort(arr, arr+i);

        cout << "out_temp_" << (*count_pages)+1 << ".txt has been sorted. " << endl;
        (*count_pages) ++ ;
        //store in out_temp file
        string title = "out_temp_" + to_string(*count_pages) + ".txt";
        file_out = fopen(title.c_str(), "w+");
        if(file_out == NULL){
            cout << "out_temp_" + to_string(*count_pages) + ".txt" << " can not open" << endl;
        }
        else {
            for(int j = 0; j < i; j++){
                fprintf(file_out,"%d\n" ,arr[j]);
                //if(j != i-1)fprintf(file_out, "\n");
                cc++;
            }
            //cout << "# of fpirntf " << cc << endl; 
            if(check==false)break;
            //fclose((*pages)[(*count_pages)-1]);
            fclose(file_out);
        }
    }
    fclose(file_in);
    //turn read mode to write mode
    // for(int i = 0; i < (*count_pages); i++)
    //     rewind((*pages)[i]);    

    cout << "finish initial split" << endl;
    return special_count;
}
void merge_file(FILE *file_out, int block_size, int sum_pages, int special_count){
    //priority_queue <int, vector<int>, greater<int> > pq(block_size); 
    bool check = true;
    int count_pages = 0; // count the null pages
    //int arr[sum_pages];
    int standard = 0; //standard to record the min key value
    int standard_pages; // record the min key index
    bool check_file[sum_pages];// check the file is empty or not
    int seek[sum_pages];
    int limit_seek[sum_pages];
    int count_seek[sum_pages];
    memset(count_seek, 0, sizeof(count_seek));
    memset(seek, 0, sizeof(seek));
    FILE *file_in;
    memset(check_file, 0, sizeof(check_file));
    //initialize block 
    for(int i = 0; i < sum_pages; i++){
        int tmp;
        string title = "out_temp_" + to_string(i+1) + ".txt";
        file_in = fopen(title.c_str(), "rb");
        if(file_in == NULL){
            cout << title << " not found" << endl;
        }
        else {
            fscanf(file_in, "%d", &tmp);
            arr[i] = tmp;
            seek[i] = ftell(file_in);
            //cout << seek[i] << endl;
            count_seek[i]++;
            fclose(file_in);
        }
    }

    //do selection sort
    while(count_pages != sum_pages){

        //cout << count_pages << endl;
        standard = arr[0];
        standard_pages = 0;
        //find the min key
        for(int i = 0; i < sum_pages; i++){ 
            if(standard > arr[i]){
                standard = arr[i];
                standard_pages = i;
            }
        }
        //input the min key index value
        int tmp;
        string title = "out_temp_" + to_string(standard_pages+1) + ".txt";
        file_in = fopen(title.c_str(), "rb");
        if(file_in == NULL){
            cout << title << " not found" << endl;
        }
        else {
    
            //cout << title << endl;
            fseek(file_in, seek[standard_pages], SEEK_SET);
            //cout << "before scan " << seek[standard_pages] << endl;
            fscanf(file_in, "%d", &tmp);
            arr[standard_pages] = tmp;
            seek[standard_pages] = ftell(file_in);
            count_seek[standard_pages]++;

            //cout << seek[standard_pages] << endl;
            if((count_seek[standard_pages] >= block_size || (standard_pages+1 == sum_pages && count_seek[standard_pages] >=  special_count)) && check_file[standard_pages] == 0){ //the file is empty and count the # of empty file
                //cout << "out_temp_" << standard_pages << ".txt has been empty." << endl;
                check_file[standard_pages] = 1;
                fprintf(file_out, "%d\n", standard);
            }
            else if((count_seek[standard_pages] >= block_size || (standard_pages == sum_pages-1 && count_seek[standard_pages] >=  special_count))  && check_file[standard_pages] == 1){
                fprintf(file_out, "%d\n", standard);
                arr[standard_pages] = INT_MAX;
                count_pages++;
            }
            else {
                fprintf(file_out, "%d\n", standard); //write file
            }
            fclose(file_in);
        }
    }

    // for(int i = 0; i < sum_pages; i++){
    //     string title = "out_temp_" + to_string(i+1) + ".txt";
    //     if (remove(title.c_str()) != 0)
    //         cout<<"Remove operation failed"<<endl;
    //     else
    //         //cout<< "out_temp_" << to_string(i) <<".txt has been removed."<<endl;
    //         ;
    // }
    // for(int i = 0; i < sum_pages; i++){
    //     fclose(file_in);
    // }
    fclose(file_out);
    cout << "finish merge" << endl;
}
int main(){
    cout.unsetf(ios::scientific);
    FILE *file_in;
    FILE *file_out;
    clock_t start, end;
    file_in = fopen("input.txt", "r");
    file_out = fopen("output.txt", "w");
    int block_size;
    cout << "input the # of data in a block size" << endl;
    cin >> block_size;
    int count_pages = 0;
    start = clock();
    if(file_in){
        int special_count =  initial_split(file_in, block_size, &count_pages);
        merge_file(file_out , block_size, count_pages, special_count);
    }
    else{
        cout << "file can not open" << endl;
    }
    cout << "total execution time " << ((double) (end - start)) / CLOCKS_PER_SEC  << " secs" << endl;

    fclose(file_in);
    fclose(file_out);   
    return 0;
}