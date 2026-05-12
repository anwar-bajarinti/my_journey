clc;
clear;
close all;

N=input("Enter the order: ");
wc=(pi)/4;
a=(N-1)/2;
esp=0.0001;
n=0:N-1;
hd=sin(wc*(n-a+esp))./(pi*(n-a+esp));
k=0:1:N-1;
%rectangular window
wr=1;
hn_r=hd*wr;
figure(1);freqz(hn_r,k)
figure(2);zplane(hn_r) 

%hamming window
wr=0.54-0.46*cos((2*pi*n)./(N-1));
hn_hamm=hd.*wr;
figure(3);freqz(hn_hamm,k)
figure(4);zplane(hn_hamm)

%Hanning window
wr=0.5-0.5*cos((2*pi*n)./(N-1));
hn_hann=hd.*wr;
figure(5);freqz(hn_hann,k)
figure(6);zplane(hn_hann)

%blackamann window
wr=0.5-0.5*cos((2*pi*n)./(N-1))+0.08*cos((4*pi*n)./(N-1));
hn_bla=hd.*wr;
figure(7);freqz(hn_bla,k)
figure(8);zplane(hn_bla)
disp("  rect codefisnrtbs");
disp(hn_r)
disp("  hanning codefisnrtbs");
disp(hn_hann)
disp("  hamming codefisnrtbs");
disp(hn_hamm)
disp("  blackman codefisnrtbs");
disp(hn_bla)