clc;
clear variables;
close all;

a = magic(4);

% Sequence decimation and interpolation 
x = a(:);
disp('Original sequence');

x1 = x(1:2:end);
x2 = x1(1:5:end);
disp('Decimated by 2:');
disp(x1);
disp('Decimated by 5:');
disp(x2);

x3 = upsample(x1,3);
x4 = upsample(x1,7);
disp('Interpolated by 3:');
disp(x3);
disp('Interpolated by 7:');
disp(x4);

% Signal decimation and interpolation 
fs = 1000;
t = 0:1/fs:0.1;
f = 50;
s = sin(2*pi*f*t);

s1 = decimate(s,3);
s2 = decimate(s,7);
s3 = interp(s,5);
s4 = interp(s,10);


subplot(2,3,1);
stem(s);
title('Original Signal');
xlabel('Time (s)');
ylabel('Amplitude');

subplot(2,3,2);

stem(s1);
title('Decimated Signal (Factor 3)');
xlabel('Time (s)');
ylabel('Amplitude');

subplot(2,3,3);

 stem(s2);
title('Decimated Signal (Factor 7)');
xlabel('Time (s)');
ylabel('Amplitude');

subplot(2,3,4);

stem(s3);
title('Interpolated Signal (Factor 5)');
xlabel('Time (s)');
ylabel('Amplitude');

subplot(2,3,5);

stem(s4);
title('Interpolated Signal (Factor 10)');
xlabel('Time (s)');
ylabel('Amplitude');
figure;
% image decimation and interpolation 
i=imread("unnamed.png");
g=rgb2gray(i);
d1=g(1:2:end,1:2:end);
d2=g(1:6:end,1:6:end);
i1=imresize(g,[size(g,1)*2,size(g,1)*3],"bicubic");
i2=imresize(g,[size(g,1)*5,size(g,1)*9],"bicubic");
near_inter=imresize(g,2,"nearest");
bilinear_inter=imresize(g,2,"bilinear");
subplot(4,2,1);
imshow(g);
subplot(4,2,2);
imshow(d1);
title('Decimated Image (Factor 2)');
subplot(4,2,3);
imshow(d2);
title('decimated by 6');
subplot(4,2,4);
imshow(i1);
title('Interpolated Image (2x3)');
subplot(4,2,5);
imshow(i2);
title('inter 9*3');
% Display the interpolated images
subplot(4,2,6);
imshow(near_inter);
title('Nearest Neighbor Interpolation');
% Display the bilinear interpolated image
subplot(4,2,7);
imshow(bilinear_inter);
title('Bilinear Interpolation');

