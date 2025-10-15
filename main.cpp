#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <math.h>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>
#include <ctime>
#include <utility> 
#include <map>

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

class FibDigits{
    std::map<int, int> fib_digits = {{0, 0}, {1, 1}, {2, 1}};
    private: 
    int eval_next_digit(int new_ind){
        int to_return;
        if (new_ind < fib_digits.size()){
            return fib_digits[new_ind];
        }else{
            to_return = fib_digits[new_ind - 1] + fib_digits[new_ind - 2];
            if (fib_digits.count(new_ind) ==0){
                fib_digits[new_ind] = to_return;
            }
            return to_return;
         }
    }
    public:
    int get_val(int ind){
        if (fib_digits.count(ind) ==0){
            return eval_next_digit(ind);
        }else{
            return fib_digits[ind];
        }
        return -1;
    }
};

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

    int search_ind_to_insert(Record data[], Record elem, int _len){
        Record prev;
        Record next;
        if (_len == 0){
            return 0;
        }else if (_len ==1){
            if (elem.cost >= data[0].cost){
                return 0;
            }else{
                return 1;
            }
        }else{
            prev = data[0];
            next = data[1];
            for (int i = 1; i < _len; i++){
                if (elem.cost < prev.cost){
                    return i-1;
                }else if (elem.cost >= next.cost){
                    return i+1;
                }else if (elem.cost>= prev.cost && elem.cost < next.cost){
                    return i;
                }else{
                    prev = next;
                    next = data[i+1];
                }
            }
        }
        return -1;
    }

    Record* insert_elem(Record data[], Record elem, int _len, int ind){
        if (ind >= _len){
            data[ind] = elem;
        }else{
            auto to_move = data[ind];
            data[ind] = elem;
            for (int i = ind+1; i<=_len; i++){
                auto new_to_move = data[i];
                data[i] = to_move;
                to_move = new_to_move;
            }
        }
        return data;
    }

    int linear_search_arr(Record data[], int search_cost, int _len){
        int ind = -1;
        for (int i = 0; i < _len; i++){
            if (data[i].cost == search_cost){
                ind = i;
                break;
            }
        }
        return ind;
    }

    int fib_search_arr(Record data[],int search_cost, int _len, FibDigits fib_digits, int fib_ind){
        int offset = -1;
        while (fib_digits.get_val(fib_ind) > 1){
            int i = std::min(offset+fib_digits.get_val(fib_ind-2), _len -1);
            if (data[i].cost < search_cost){
                fib_ind --;
                offset = i;
            }else if(data[i].cost > search_cost){
                fib_ind -=2;

            }else{
                return i;
            }
        }
        if (fib_digits.get_val(fib_ind-1) && data[offset + 1].cost == search_cost){
            offset + 1;
        }
        std::cout<<fib_ind<<std::endl;
        return -1;
    }  

    //working wrong !!
    int new_fib_search_arr(Record data[],int search_cost, int _len, FibDigits fib_digits, int fib_ind){
        int fib_1 = fib_digits.get_val(fib_ind);
        int fib_2 = fib_digits.get_val(fib_ind - 1);
        int fib_3 = fib_digits.get_val(fib_ind- 2);
        int offset = -1;
        while (fib_1 != 1){
            auto ind = std::min(offset+ fib_3, _len -1);
            if (data[ind].cost > search_cost){
                fib_1 = fib_2;
                fib_2 = fib_3;
                fib_3 = fib_1 - fib_2;
                offset = ind;
            }else if(data[fib_1].cost < search_cost){
                fib_1 = fib_3;
                fib_2 -= fib_3;
                fib_3 = fib_1 - fib_2;
            }else{
                return ind;
            }
        }
        if (fib_2 && data[offset + 1].cost == search_cost){
            return offset + 1;
        }
        return -1;
    }

    int bad_fib_search(Record data[], int search_cost, int _len){
        int a = 0, b=1, c=1;
        int offset = -1;
        while (c > 1) {
            int i = std::min(offset + a, _len - 1);
            if (data[i].cost < search_cost) {
                c = b;
                b = a;
                a = c - b;
                offset = i;
            }
            else if (data[i].cost > search_cost) {
                c = a;
                b = b - a;
                a = c - b;
            }
            else
                return i;
        }
        if (b && data[offset + 1].cost == search_cost){
            return offset + 1;
        }
        return -1;
    }

    int linear_search_vec(std::vector<Record> data, int search_cost, int _len){
        int ind = -1;
        for (int i = 0; i < _len; i++){
            if (data[i].cost == search_cost){
                ind = i;
                break;
            }
        }
        return ind;
    }

    int test_search_algs(Record raw_data[], Record sorted_data[], std::vector<Record> data_vector, int _len){
        int cost = 0;
        int ind = -1;
        std::cout<<"Enter cost of flight ticket :"<<std::endl;
        std::cin>>cost;
        auto start_time  = clock();
        ind = linear_search_arr(raw_data, cost, _len);
        auto end_time = clock();
        std::cout<<"Linear search on row array: "<< end_time - start_time<< std::endl;
        std::cout<<"Index: "<<ind<<std::endl;
        start_time = clock();
        ind = -1;
        ind = linear_search_vec(data_vector, cost, _len);
        end_time = clock();
        std::cout<<"Linear search on vector: "<< end_time - start_time<< std::endl;
        std::cout<<"Index: "<<ind<<std::endl;
        start_time = clock();
        ind = -1;
        ind = linear_search_arr(sorted_data, cost, _len);
        end_time = clock();
        std::cout<<"Linear search on sorted arr: "<< end_time - start_time<< std::endl;
        std::cout<<"Index: "<<ind<<std::endl;
        std::cout<<sorted_data[ind].cost<<std::endl;
        FibDigits fib_digits;
        int fib_ind = 0;
        while(fib_digits.get_val(fib_ind) < _len){
            fib_ind ++;
        }
        start_time = clock();
        // ind = -1;
        // ind = fib_search_arr(raw_data, cost, _len, fib_digits, fib_ind);
        // std::cout<<fib_ind<<std::endl;
        // end_time = clock();
        // std::cout<<"Fibonachi search on raw arr: "<< end_time - start_time<< std::endl;
        // std::cout<<"Index: "<<ind<<std::endl;
        // start_time = clock();
        // ind = -1;
        // ind = fib_search_vec(data_vector, cost, _len, fib_digits, fib_ind);
        // end_time = clock();
        // std::cout<<"Fibonachi search on vector: "<< end_time - start_time<< std::endl;
        // std::cout<<"Index: "<<ind<<std::endl;start_time = clock();
        ind = -1;
        // ind = new_fib_search_arr(sorted_data, cost, _len, fib_digits, fib_ind);
        ind = bad_fib_search(sorted_data, cost, _len);
        end_time = clock();
        std::cout<<"Fibonachi search on sorted arr: "<< end_time - start_time<< std::endl;
        std::cout<<"Index: "<<ind<<std::endl;
        std::cout<< fib_digits.get_val(fib_ind)<<std::endl;
        return 0;
    }
    public:
    int big_test(std::string root_to_input_file){
        std::string line_n;
        MadeReader reader = make_reader(root_to_input_file);
        Record* raw_arr = new Record[reader._len];
        std::string line ="";
        int ind=0;
        auto start_time = clock();
        while (std::getline(reader.reader, line)){
            Record to_add = make_record(line);
            raw_arr[ind] = to_add;
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
        reader = make_reader(root_to_input_file);
        Record* sorted_arr = new Record[reader._len];
        start_time = clock();
        ind =0;
        while (std::getline(reader.reader, line)){
            Record to_add = make_record(line);
            auto  new_ind = search_ind_to_insert(sorted_arr, to_add, ind);
            sorted_arr = insert_elem(sorted_arr, to_add, ind, new_ind);
            ind ++;
        }
        end_time = clock();
        std::cout<<"Time of add to sorted array: "<<end_time - start_time<<std::endl;
        std::cout<<"Start testing search algorithms"<<std::endl;
        test_search_algs(raw_arr, sorted_arr, data, reader._len);
        return 0;
    }
};

int main(){
    std::string root_to_input_file;
    std::cout<<"Enter file name(start from disk)"<<std::endl;
    //C:\Users\Alexandr\C++Projects\Algotihms\lab_work_2\output.txt
    std::cin>>root_to_input_file;
    Tester test;
    test.big_test(root_to_input_file);
    std::cout<<"Done"<<std::endl;
}
