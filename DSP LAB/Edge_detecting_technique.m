% Identify edges of a given image using sobel ,robort,prewitt,and
% canny,edge operates using all these
clc;
clear;
close all;

% Load a high-contrast built-in image
a = imread('E:\all files\5th sem\DSP\DSP LAB/OIP.jpeg');   % You can also try 'coins.png' or 'cameraman.tif'
b = rgb2gray(a);

c = edge(b, 'sobel', 'horizontal');  % Sobel Horizontal
d = edge(b, 'sobel', 'vertical');    % Sobel Vertical

e = edge(b, 'prewitt', 'horizontal');  % Prewitt Horizontal
f = edge(b, 'prewitt', 'vertical');    % Prewitt Vertical

g = edge(b, 'roberts', 'horizontal');  % Roberts Horizontal
h = edge(b, 'roberts', 'vertical');    % Roberts Vertical

i = edge(b, 'canny');  % Canny (default is combined)

% Plot
subplot(5,2,1); imshow(a); title('Original Image');
subplot(5,2,2); imshow(b); title('Grayscale');

subplot(5,2,3); imshow(c); title('Sobel - Horizontal');
subplot(5,2,4); imshow(d); title('Sobel - Vertical');

subplot(5,2,5); imshow(e); title('Prewitt - Horizontal');
subplot(5,2,6); imshow(f); title('Prewitt - Vertical');

subplot(5,2,7); imshow(g); title('Roberts - Horizontal');
subplot(5,2,8); imshow(h); title('Roberts - Vertical');

subplot(5,2,9); imshow(i); title('Canny Edge (Combined)');

j = edge(b, 'sobel');  % Combined Sobel
subplot(5,2,10); imshow(j); title('Sobel Edge (Combined)');
