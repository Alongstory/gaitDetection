For the cpp file you can't use it directly:
1.You need to add the dlib-19.2 library into your includes first

2.Then change the "j" and "k" values(I have pointed them out in the file) 
and create more loop structure for each time period "you think" is the heel strike,
which is like a prior verification.
I will tell the reason why I didn't choose j and k myself in the solution.

3.You need to choose a score value which would be the threshold.

4.after you did this, the chosen data point in scoreRank will get "1" in the "status" column, those point are heel strike one.