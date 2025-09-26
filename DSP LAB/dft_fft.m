clc;
clear;

x = input("Enter a input sequence: ");
n = length(x);

% Check if length is power of 2
if log2(n) ~= floor(log2(n))
    error('Input sequence length must be a power of 2.');
end

stages = log2(n);

% DIF FFT algorithm
for s = stages:-1:1
    m = 2^s;           % size of each group
    half = m/2;        
    w = exp(-2j*pi/m); % twiddle base
    for k = 1:m:n
        for j = 0:half-1
            u = x(k+j);
            v = x(k+j+half);
            x(k+j)       = u + v;
            x(k+j+half)  = (u - v) * (w^j);  % FIXED
        end
    end
end

% Bit reversal
x = bitrevorder(x);

disp("DIF FFT Output:");
disp(x);

% Plot responses
subplot(3,1,1);
stem(abs(x));
title("Magnitude Response");

subplot(3,1,2);
stem(angle(x));
title("Phase Response");

subplot(3,1,3);
stem(real(x));
title("Real Part of FFT Output");
