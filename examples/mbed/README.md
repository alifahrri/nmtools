## nmtools mbed examples

- [manip](manip/) demonstrate array manipulation using nmtools on stm32 mbed.

- [ufuncs](ufuncs/) demonstrate nmtools ufuncs (universal functions) on stm32 mbed.

### Requirements
- [platformio](https://platformio.org/install)

### Running the examples

Go to [manip](manip/) or [ufuncs](ufuncs/), then:
```
platformio run --target upload
```
```
platformio device monitor
```

### Example output
- ufuncs:
```
===================
a+b: 
[[[     17      14],
[       15      16],
[       17      18]],

[[      19      20],
[       21      22],
[       23      24]]]
a*b: 
[[[     52      13],
[       26      39],
[       52      65]],

[[      78      91],
[       104     117],
[       130     143]]]
mean(a): 
5.833333
sum(a): 
70
sum(a,0): 
[[      10      8],
[       10      12],
[       14      16]]
===================
```

- manip:
```
========================
flattened:  
shape: (12) 
[       4       1       2       3       4       5       6       7       8       9       10      15]
transposed: 
shape: [        2       3       2] 
[[[     4       6],
[       2       8],
[       4       10]],

[[      1       7],
[       3       9],
[       5       15]]]
reshaped:   
shape: [        2       6] 
[[      4       1       2       3       4       5],
[       6       7       8       9       10      15]]
padded:     
shape: [        3       3       3] 
[[[     0       4       1],
[       0       2       3],
[       0       4       5]],

[[      0       6       7],
[       0       8       9],
[       0       10      15]],

[[      0       0       0],
[       0       0       0],
[       0       0       0]]]
flipped:    
shape: [        2       3       2] 
[[[     15      10],
[       9       8],
[       7       6]],

[[      5       4],
[       3       2],
[       1       4]]]
concat:     
shape: [        2       3       3] 
[[[     4       1       13],
[       2       3       13],
[       4       5       13]],

[[      6       7       13],
[       8       9       13],
[       10      15      13]]]
========================
```