clc; clear; close all;

% ---------- Input ----------
x = input('Enter input sequence: ');
N = length(x);               % Number of points

% ---------- Check power of 2 ----------
if log2(N) ~= floor(log2(N))
    error('N must be power of 2');
end

% ---------- Bit reversal ----------
x = bitrevorder(x);          % Reorder samples for in-place FFT
S = log2(N);                 % Total number of stages

% ---------- FFT Computation ----------
for s = 1:S
    M = 2^s;                 % Group size (2,4,8,...)
    H = M/2;                 % Half group (butterfly size)
    W = exp(-1i*2*pi/M);     % Twiddle base for this stage
    
    for k = 1:M:N             % Process each group
        for j = 0:H-1         % Each butterfly pair
            t = W^j * x(k+j+H);  % Twiddle * lower value
            u = x(k+j);          % Upper value
            x(k+j) = u + t;      % Upper output
            x(k+j+H) = u - t;    % Lower output
        end
    end
end

% ---------- Display FFT Output ----------
disp('FFT Output:');
disp(x);

% ---------- Plot Magnitude & Phase ----------
subplot(2,2,1);
stem(abs(x));                 % Magnitude plot
title('Magnitude Spectrum');
xlabel('Index (k)');
ylabel('|X(k)|');

subplot(2,2,2);
stem(angle(x));               % Phase plot
title('Phase Spectrum');
xlabel('Index (k)');
ylabel('∠X(k) [radians]');
stem(real(x));
subplot(2,2,3);
stem(real(x));               % Real part plot
title('Real Part of FFT Output');
xlabel('Index (k)');
ylabel('Re{X(k)}');