clc;
clear;
close all;

fs = 1000;
t = 0:1/fs:0.1;
f = 50;
x = sin(2*pi*f*t);

% ==== Signal interpolation ====
p1 = interp(x, 2);
p2 = interp(x, 3);
p3 = interp(x, 4);

figure(1); % Figure for signals
subplot(2,2,1);
stem(x, 'filled');
title("Original sine wave");

subplot(2,2,2);
stem(p1, 'filled');
title("Interpolated (×2)");

subplot(2,2,3);
stem(p2, 'filled');
title("Interpolated (×3)");

subplot(2,2,4);
stem(p3, 'filled');
title("Interpolated (×4)");

% ==== Image interpolation ====
i = imread('deer.png');
j = rgb2gray(i);

k1 = imresize(j, [size(j,1)*2, size(j,2)*3], 'bicubic');
k2 = imresize(j, [size(j,1)*2, size(j,2)*3], 'nearest');
k3 = imresize(j, [size(j,1)*3, size(j,2)*2], 'bicubic');
k4 = imresize(j, 2, 'nearest');
k5 = imresize(j, 2, 'bilinear');

figure(2); % Figure for images
subplot(2,3,1);
imshow(i);
title("Original RGB Image");

subplot(2,3,2);
imshow(j);
title("Grayscale Image");

subplot(2,3,3);
imshow(k1);
title("Resized (2×3) Bicubic");

subplot(2,3,4);
imshow(k2);
title("Resized (2×3) Nearest");

subplot(2,3,5);
imshow(k3);
title("Resized (3×2) Bicubic");

subplot(2,3,6); 
imshow(k4);
title("Resized (×2) Nearest");
