clc;
clear variables;
close all;
x=[1,2,3,4,5];
y=[6,7,8];
l=conv(x,y);
display(l);
c=cconv(x,y,5);
display(c);