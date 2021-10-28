# Sort Visualizer

Visualization and Audibilization of different sorting algorithms.

## Building

1. Clone the repository
```bash
git clone --recursive https://github.com/BijanRegmi/Sort-Visualizer.git
```
2. Install dependencies

[SFML](https://www.sfml-dev.org/download.php)

3. Compile and run

```bash
mkdir bin && make run
```

## KeyBindings
### **Window**
KEY | ACTION
----|-----------
Escape|Close the window


### **Modes**
KEY | ACTION
----|-----------
C|Switch to check mode
S|Switch to shuffle mode
B|Set Bubble Sort as selected algorithm
M|Set Merge Sort as selected algorithm
Q|Set Quick Sort as selected algorithm
R|Set Radix Sort as selected algorithm
I|Set Insertion Sort as selected algorithm
Shift S|Set selection Sort as selected algorithm

### **Delay**
KEY | ACTION
----|-----------
+|Increase reading delay by 10μs
-|Decrease reading delay by 10μs
Ctrl +|Increase reading delay by 100μs
Ctrl -|Decrease reading delay by 100μs
Shift +|Increase writing delay by 10μs
Shift -|Decrease writing delay by 10μs
Ctrl Shift +|Increase writing delay by 100μs
Ctrl Shift -|Decrease writing delay by 100μs
0|Set delay to 0μs

### **Misc**
KEY | ACTION
----|-----------
Space|Start the currently selected algorithm
Up_Arrow|Cycle through modes in forward direction
Down_Arrow|Cycle through modes in reverse direction

## Algorithms included
- Bubblesort
- Mergesort
- Quicksort
- Radixsort
- InsertionSort
- SelectionSort

###### TODO
###### Add more sorting algorithms