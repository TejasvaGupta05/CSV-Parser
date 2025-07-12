#include "include/csvparser.hpp"

int main(){
    DataFrame df;
    std::vector<float> Scores;
    df.read_csv("data.csv", ',');
    df.sort(2);
    df.print();
    df.change_value("Age",3,100);
    df.get_column(Scores,4);
    for(auto score : Scores) {
        std::cout << score << " ";
    }
    df.save("output.csv");
    df.reset();
}