Basically, first is a normal std::vector, and second is a memory mapped vector. We first push into both the same amount of data, then change every element of both, then read every data. 

The current approach is syncing with file constantly. will try less sync approaches in the future   

Current output  

size of vector:: 10000  
push first(micros): 10009 1864  
push second(micros): 10000 255  
write first(micros): 10009 295  
write second(micros): 10000 38  
acceess first(nanos): 10009 309547  
access second(nanos): 10000 35799  


size of vector: 2087151  
push first(micros): 2087160 372011  
push second(micros): 2087151 49565  
write first(micros): 2087160 62337  
write second(micros): 2087151 7890  
acceess first(nanos): 2087160 62191865  
access second(nanos): 2087151 7770746  
