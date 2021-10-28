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
make run
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
B|Set bubblesort as selected algorithm
M|Set mergesort as selected algorithm
Q|Set quicksort as selected algorithm
R|Set radixsort as selected algorithm

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

###### TODO
###### Add more sorting algorithms