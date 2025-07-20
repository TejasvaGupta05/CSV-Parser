# Documentation  
A lightweight and header-only **CSV parser library for C++**.



## 🚀 Features

- **Schema Inference :** Automatically determines the data type of each column (`int`, `float`, or `std::string`).

- **Auto-Detect Delimiter :** Detects common delimiters like `,`, `;`, `\t`, `|` without any manual input.

- **Configurable or Auto Delimiter Detection :** Supports both automatic delimiter detection and manual setting via constructor.

- **Missing Value Strategies :** Flags rows with missing or empty fields to help in data validation and cleaning.

- **Robust Quoted Field Handling :** Accurately parses fields enclosed in quotes — even if they contain newlines or delimiters inside them.

- **Escape Character Support :** Handles escaped characters like `\\`, `\"`, `\,` for precise parsing.

- **Header-Only Design :** Just include the `.hpp` file — no build step, no dependencies.

---

## 📁 Installation

### Requirements
- A C++17 compatible compiler (e.g., **g++**, **clang++**)
- No external libraries required



### Installation Steps

#### 📌 Method 1: Project-local use

1. Clone the repository or copy the `include/` folder into your project directory:
   ```bash
   git clone https://github.com/TejasvaGupta05/CSV-Parser.git
   ```
2. Include the header file in your *.cpp* file:
   ```cpp
   #include "include/csvparser.hpp"
   ```
#### 📌 Method 2: Global installation
1. Copy the `csvparser.hpp` file into your global compiler include path
    (e.g., `/usr/include/` or your `MinGW/VS include/` folder).

2. Then you can simply write:
   ```cpp
   #include "csvparser.hpp"
   ```
---
## 🏗️ Getting Started
Use either form based on where the file is located:
```cpp
#include "csvparser.hpp"
// or
#include "include/csvparser.hpp"
```
### Initializing DataFrame:
Since `csvparser.hpp` is a class based header, we need to initialize it with object creation of the class `DataFrame`.
```cpp
#include "csvparser.hpp" //or "include/csvparser.hpp"

int main(){
    DataFrame df;  // df is the object of the DataFrame class
}
```
This is the basic structure of your program.

### Reading CSV file
Let's take `df` as our reference object.
Make sure you have the `.csv` file in the same directory, or in the directory you will mention in `read_csv()` function.
```cpp
df.read_csv("data.csv");
```
```cpp
df.read_csv("\path\to\data.csv");
```
This will fetch all the information from your `.csv` file and store it inside the **df DataFrame**.

### 🖨️ Printing the DataFrame
YES, it has a option to print the fetched `DataFrame` in form of `table`.
```cpp
df.print();   //will print the fetched contents of csv file in the terminal (as a table)
```

Output:
```bash
+----+---------+-----+-----------+-----------+
| ID | Name    | Age | Country   | Score     |
+----+---------+-----+-----------+-----------+
| 1  | Alice   | 29  | France    | 83.5      |
| 2  | Bob     | 35  | Canada    | 77        |
| 3  | Charlie | 42  | UK        | 91.199997 |
| 4  | Diana   | 23  | Australia | 68.900002 |
| 5  | Ethan   | 31  | India     | 74.300003 |
| 6  | Fatima  | 27  | UAE       | 88.400002 |
| 7  | George  | 39  | Germany   | 81        |
| 8  | Hiro    | 34  | Japan     | 79.699997 |
| 9  | Ivy     | 26  | China     | 85.099998 |
| 10 | Jack    | 30  | Brazil    | 90        |
+----+---------+-----+-----------+-----------+
```

### Getting information about different fields

```cpp
df.print_info();   //will print the information about different fields of the data
```

Output:
```bash
DataFrame Information:
Number of Fields: 5
Number of Rows: 10

Field Information:
Field 1: ID (Type: INTEGER, Missing Data: No)
Field 2: Name (Type: STRING, Missing Data: No)
Field 3: Age (Type: INTEGER, Missing Data: No)
Field 4: Country (Type: STRING, Missing Data: No)
Field 5: Score (Type: FLOAT, Missing Data: No)
```

### 🔃 Sorting 
To sort the `DataFrame` df in 
- **Ascending**
```cpp
df.sort(2,true);     //this will sort the data according to the column of index 2 in ascending order
```
this will sort the data according to the column of **index 2** in ascending order
- **Descending**
```cpp
df.sort(2,false);     //this will sort the data according to the column of index 2 in descending order
```
If we _sort_ our dataset in ascending order in context of **index 2 i.e. Age**, and then print it using `df.print();` 
```bash
+----+---------+-----+-----------+-----------+
| ID | Name    | Age | Country   | Score     |
+----+---------+-----+-----------+-----------+
| 4  | Diana   | 23  | Australia | 68.900002 |
| 9  | Ivy     | 26  | China     | 85.099998 |
| 6  | Fatima  | 27  | UAE       | 88.400002 |
| 1  | Alice   | 29  | France    | 83.5      |
| 10 | Jack    | 30  | Brazil    | 90        |
| 5  | Ethan   | 31  | India     | 74.300003 |
| 8  | Hiro    | 34  | Japan     | 79.699997 |
| 2  | Bob     | 35  | Canada    | 77        |
| 7  | George  | 39  | Germany   | 81        |
| 3  | Charlie | 42  | UK        | 91.199997 |
+----+---------+-----+-----------+-----------+
```

### 📑 Copying The DataFrame
Specific contents of a DataFrame can be copied to other using `copy` function.
For that you should have a new dataframe object :
```cpp
DataFrame new_df; //New DataFrame Object Declaration
```
1. Using index numbers
   ```cpp
   df.copy(new_df,std::vector<int>{1,4});    //Copying specific fields from df to new_df
   new_df.print();    //Printing the new DataFrame
   ```
2. Using Field Names
   ```cpp
   df.copy(new_df,std::vector<std::string>{"Name","Score"});    //Copying specific fields from df to new_df
   new_df.print();    //Printing the new DataFrame
   ```
**OUTPUT**
```bash
+---------+-----------+
| Name    | Score     |
+---------+-----------+
| Alice   | 83.5      |
| Bob     | 77        |
| Charlie | 91.199997 |
| Diana   | 68.900002 |
| Ethan   | 74.300003 |
| Fatima  | 88.400002 |
| George  | 81        |
| Hiro    | 79.699997 |
| Ivy     | 85.099998 |
| Jack    | 90        |
+---------+-----------+
```
### Changing a Specific Value
Any value in the database can be changed using:
```cpp
df.change_value("Age",3,100);   //This will change the 3rd index value of *Age* Field to = 100 
```
This will change the 3rd index value of *Age* Field to = **100**
```bash
| 1  | Alice   | 100  | France    | 83.5      |      //Since in Sorted dataset 3rd index is this
```

### Store any field -> vector
1. Create a vector of your desired field datatype
   e.g. I want to Store `Score` in a `vector` i.e. a `float` datatype
   ```cpp
   std::vector<float> Scores;     //Create a float vector Scores to store score
   ```
2. Use `get_column()` function to fetch the column data into `Scores`
   ```cpp
   df.get_column(Scores,4);      //Stores 4th index column in Scores vector
   ```

### 💾 Saving the DataFrame
To save the DataFrame df into your working directory use:
```cpp
df.save("output.csv");         //Saves the DataFrame as output.csv
```

### ♻️ Resetting
To Reset the DataFrame `df`
```cpp
df.reset();                   //Empties the DataFrame and is ready to read another csv again
```

---
## Author
Made with ❤️ by [Tejasva Gupta](https://github.com/TejasvaGupta05/)
