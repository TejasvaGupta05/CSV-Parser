✅ Schema inference
    Auto-detect delimiter
    Missing value strategies – built-in ways to fill, drop, or flag rows with empty fields.

🔍 Areas for Improvement
Here’s what you could add/fix to make it even better:
1️⃣ Robust quoted fields support
Currently, "Alice, Bob" inside a field will break parsing — add logic to handle quoted values with embedded delimiters.

2️⃣ Escape handling
CSVs often have escaped quotes ("He said ""Hello"""). Right now, this will fail or parse incorrectly.

3️⃣ Streaming support
Your createDataFrame still reads the whole file into a vector in memory. If a CSV has millions of rows, it could cause RAM issues. You can make your parser yield rows one by one.

4️⃣ Delimiter detection or config
You give a warning if only one field is identified, but adding automatic delimiter detection (e.g., guessing ,, ;, \t) would make it user-friendly.

5️⃣ Column type consistency checks
Currently, type inference happens on one line. You could analyze multiple rows to infer more reliably.

6️⃣ Error reporting
A syntax error or unexpected data should produce clear messages with line/column info.

7️⃣ Unit tests
Even a few tests in a test.cpp (or Google Test) would make your library production-ready.

8️⃣ Modularity
Consider splitting into header/source files, or making a reusable class CsvParser.

9️⃣ C++ best practices

Avoid global variables like fieldcount or TrueFields — encapsulate them in a class.

Use const where possible.

Replace raw loops with STL algorithms for clarity.