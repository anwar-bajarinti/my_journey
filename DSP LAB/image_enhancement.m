% Enhance the image quality using smoothing filters
% mean and median filters
clc;
clear;
close all;

% Load & convert image
i = imread('E:\all files\5th sem\DSP\DSP LAB\deer.png');
k = rgb2gray(i);
j = imnoise(k, "salt & pepper", 0.06);

% Median filter outputs
f  = medfilt2(j, [3,3]);
f1 = medfilt2(j, [5,5]);
f2 = medfilt2(j, [10,10]);

% Mean (average) filter outputs
g1 = fspecial("average", [3,3]);
b1 = imfilter(j, g1);

g2 = fspecial("average", [10,10]);
b2 = imfilter(j, g2);

% Histogram Equalization
ke = histeq(k);

% ------ All in One Figure ------
figure('Name','All Results in One Figure');

subplot(4,3,1); imshow(i);        title('Original RGB Image');
subplot(4,3,2); imshow(k);        title('Grayscale Image');
subplot(4,3,3); imshow(j);        title('Noisy Image (Salt & Pepper)');

subplot(4,3,4); imshow(f);        title('Median Filter 3x3');
subplot(4,3,5); imshow(f1);       title('Median Filter 5x5');
subplot(4,3,6); imshow(f2);       title('Median Filter 10x10');

subplot(4,3,7); imshow(b1);       title('Mean Filter 3x3');
subplot(4,3,8); imshow(b2);       title('Mean Filter 10x10');

subplot(4,3,9); imhist(k);        title('Histogram of Grayscale');

subplot(4,3,10); imhist(ke);      title('Histogram After Equalization');
subplot(4,3,11); imshow(k);       title('Grayscale Before HistEq');
subplot(4,3,12); imshow(ke);      title('After Histogram Equalization');
