#include "include/csvparser.hpp"

int main(){
    DataFrame df;
    DataFrame new_df;
    df.read_csv("data.csv", ',');
    df.copy(new_df, std::vector<std::string>{"Age","Score"});  //Avoid using same DataFrame object for both reading and making a new DataFrame
    df.print();
    new_df.print();
    new_df.print_info();
}
