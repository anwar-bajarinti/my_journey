clc;
clear;
close all;

fs = 1000;          
t = 0:1/fs:0.1;     
f = 50;             

x = sin(2*pi*f*t);

% Decimation for signals
p1 = decimate(x, 3);
p2 = decimate(x, 5);
p3 = decimate(x, 10);

figure;

% ==== Signal plots (top row) ====
subplot(2,3,1);
stem(x, 'filled');
title("Original signal");

subplot(2,3,2);
stem(p1, 'filled');
title("Decimated by factor 3");

subplot(2,3,3);
stem(p2, 'filled');
title("Decimated by factor 5");

% ==== Image plots (bottom row, larger) ====
i = imread("deer.png");
j = rgb2gray(i);

subplot(2,3,4);
imshow(j);
title("Gray image");

img_d10 = j(1:10:end, 1:10:end);
subplot(2,3,5);
imshow(img_d10);
title("Image decimation x10");

img_d15 = j(1:15:end, 1:15:end);
subplot(2,3,6);
imshow(img_d15);
title("Image decimation x15");

% If you also want factor 20, replace any image above
% img_d20 = j(1:20:end, 1:20:end);
% imshow(img_d20);
% title("Image decimation x20");
