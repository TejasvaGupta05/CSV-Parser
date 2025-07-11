# Documentation
A light weight CSV parser library for C++

### 🚀 Features
- **Schema Inference :**
Automatically determines the data type of each column (e.g., int, float, string).

- **Auto-Detect Delimiter :**
Detects common delimiters such as commas, semicolons, tabs, or pipes without manual configuration.

- **Configurable or Detected Delimiters :**
Supports both automatic detection and manual setting of delimiters.

- **Missing Value Strategies :**
Identifies and flags rows with missing or empty fields, helping in data cleaning and validation.

> Flags can be printed through:<pre>`df.print_info(); //df is the object of DataFrame class`</pre>

- **Robust Quoted Field Handling :** 
Properly parses fields enclosed in quotes, including those with embedded delimiters or newlines.

- **Escape Character Support :** 
Handles escaped characters like \", \\, and \, to ensure accurate parsing.

- **Header File Support :** 
Can be included in your code with few steps

## 📁 Installation



