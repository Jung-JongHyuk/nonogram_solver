# Description
nonogram_solver is fast nonogram puzzle solver. Several algorithms like heuristic algorithm, proof by contradiction, brute force search are adopted.
  
# Environment
nonogram_solver is implemented with c++14, so it can be compiled by both g++, clang compiler and run on several OS such as linux, mac, window.
  
# Prerequsite
No external library was used in this project except STL. So there is no prerequsite in this project

# Usage
1. clone this project
2. compile code via IDE(tested in Xcode)
3. make nonogram puzzle data to solve as txt file  
   puzzle data must be following format
    ~~~
    puzzle description
    rowSize colSize
    (number of hint in row: hints)...
    (number of hint in col: hints)...
    ~~~
4. run program
5. program will solves puzzle and show result to console
    ![running](https://user-images.githubusercontent.com/66899806/135102274-509833c1-341b-45fc-be5d-4a5410640e71.gif)

# Reference
heuristic nonogram solving algorithms in this project are implemented by referencing below paper  
  
[1] An efficient algorithm for solving nonograms (Chiung-Hsueh Yu et al, Springer  Science+Business Media, LLC 2009) [[pdf]](https://link.springer.com/content/pdf/10.1007/s10489-009-0200-0.pdf)

