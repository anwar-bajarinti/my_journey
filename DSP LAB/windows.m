clc; close all; clear all;
N = 7;
n = 0:N-1;
a = (N-1)/2;
wc = pi/4;

% Ideal impulse response (sinc function)
hd = sin(wc*(n - a)) ./ (pi * (n - a));
%hd(a+1) = wc / pi;  % Handle division by zero at center

% Rectangular window
w_rect = ones(1, N);

% Triangular window
w_tri = 1 - (2 * abs(n - a)) / (N - 1);

% Hanning window
w_hann = 0.5 - 0.5 * cos(2 * pi * n / (N - 1));

% Hamming window
w_hamm = 0.54 - 0.46 * cos(2 * pi * n / (N - 1));

% Apply windows
h_rect = hd .* w_rect;
h_tri  = hd .* w_tri;
h_hann = hd .* w_hann;
h_hamm = hd .* w_hamm;

% Display coefficients
disp('FIR coefficients with Rectangular Window:');
disp(h_rect);
disp('FIR coefficients with Triangular Window:');
disp(h_tri);
disp('FIR coefficients with Hanning Window:');
disp(h_hann);
disp('FIR coefficients with Hamming Window:');
disp(h_hamm);

% Plot all windows
figure;
subplot(2,2,1);
stem(n, h_rect, 'filled');
title('Rectangular Window');
xlabel('n'); ylabel('h(n)');

subplot(2,2,2);
stem(n, h_tri, 'filled');
title('Triangular Window');
xlabel('n'); ylabel('h(n)');

subplot(2,2,3);
stem(n, h_hann, 'filled');
title('Hanning Window');
xlabel('n'); ylabel('h(n)');

subplot(2,2,4);
stem(n, h_hamm, 'filled');
title('Hamming Window');
xlabel('n'); ylabel('h(n)');