# include <iostream>
# include <string>
#include <vector>
#include <cmath>
#include <math.h>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>
#include <ctime>
#include <utility> 

struct MadeReader{
    std::ifstream reader;
    int _len;
};


struct FlightNumber{
    std::string airport;
    int id;
};

struct DepartureTime
{
    int hh;
    int mm;
};

struct Record{
    FlightNumber flight_number;
    DepartureTime time;
    int cost;
    std::vector<std::string> departure_days;
};

template< typename T >
std::vector<T> reversed(std::vector<T> data){
    std::vector<T> to_return(data);
    std::reverse(to_return.begin(), to_return.end());
    return to_return;
} 

template< typename T>
void print(std::vector<T> data, bool reversed = false){
    if (reversed == false){
        for (T elem: data){
            std::cout<< elem;
        }   
    }else{
        std::reverse(data.begin(), data.end());
        for (T elem: data){
            std::cout<< elem ; //<< std::endl;
        }   
    }
    std::cout<< std::endl;
}

template<typename T>
std::vector<T> slice(std::vector<T> data, int first_ind, int second_ind){
    if (second_ind > lenght(data)){
        std::cout<<"Second ind error";
        return data;
    }
    if (first_ind < 0){
        std::cout<<"First ind error";
    }
    std::vector<T> new_data;
    for(int ind= first_ind; ind<second_ind; ind++){
        new_data.push_back(data[ind]);
    }
    return new_data;
}

std::string slice(std::string data, int first_ind, int second_ind){
    std::string result="";
    if (second_ind > data.size()){
        std::cout<<"Second ind error";
        return data;
    }
    if (first_ind < 0){
        std::cout<<"First ind error";
    }
    for (int ind = first_ind; first_ind < second_ind; first_ind ++){
        result += data[ind];
    }
    return result;
}

std::vector<std::string> split(std::string line, char delim){
    std::vector<std::string> to_return;
    std::stringstream ss(line);
    std::string part_line;
    while (std::getline(ss, part_line, delim)){
        to_return.push_back(part_line);
    }
    return to_return;
}

class Tester{
    private:
    Record make_record(std::string line){
        Record to_return;
        auto to_rec = split(line, ',');
        FlightNumber now_FN;
        DepartureTime now_DP;
        now_FN.airport = slice(to_rec[0], 0, 2);
        now_FN.id = std::stoi(slice(to_rec[0], 2, 5));
        auto to_DP = split(to_rec[1], ':');
        now_DP.hh = std::stoi(to_DP[0]);
        now_DP.mm = std::stoi(to_DP[1]);
        to_return.flight_number = now_FN;
        to_return.time = now_DP;
        to_return.cost = std::stoi(to_rec[2]);
        if (to_rec.size() == 4){
            to_return.departure_days  = split(to_rec[3], ' ');
        }else{
            to_return.departure_days = {};
        }
        return to_return;
    }

    MadeReader make_reader(std::string root_to_input_file){
        MadeReader to_return;
        std::ifstream reader(root_to_input_file);
        std::string line_n;
        int n=0;
        if (std::getline(reader, line_n)){
            n = std::stoi(line_n);
        }else{
            throw std::invalid_argument( "Wrong file!🤘" );
        }
        to_return.reader = std::move(reader);
        to_return._len = n;
        return to_return;
    }

    public:
    int big_test(std::string root_to_input_file){
        std::cout<<"Here 1"<<std::endl;
        std::string line_n;
        MadeReader reader = make_reader(root_to_input_file);
        Record* first_arr = new Record[reader._len];
        std::cout<<"Here 2"<<std::endl;
        std::string line ="";
        int ind=0;
        auto start_time = clock();
        while (std::getline(reader.reader, line)){
            Record to_add = make_record(line);
            first_arr[ind] = to_add;
            ind++;
        }
        auto end_time = clock();
        std::cout<<"Time of add to dinamyc arr: "<<end_time - start_time<<std::endl;
        std::vector<Record> data;
        reader = make_reader(root_to_input_file);
        start_time = clock();
        while (std::getline(reader.reader, line)){
            Record to_add = make_record(line);
            data.push_back(to_add);
        }
        end_time = clock();
        std::cout<<"Time of add to vector: "<<end_time - start_time<<std::endl;
        //add entering in sorted array 
        return 0;
    }
};

int main(){
    std::string root_to_input_file;
    std::cout<<"Enter file name(start from disk)"<<std::endl;
    std::cin>>root_to_input_file;
    Tester test;
    test.big_test(root_to_input_file);
    std::cout<<"Done"<<std::endl;
}
