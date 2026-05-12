clc; clear; close all;

x = input('Enter input sequence: ');
N = length(x);
S = log2(N);

% check length = power of 2
if log2(N) ~= floor(log2(N))
    error('Length of input must be power of 2');
end

% --- DIF FFT computation ---
for s = 1:S
    M = 2^(S - s + 1);   % group size (decreasing)
    H = M / 2;           % half of group
    W = exp(-1i * 2 * pi / M);  % twiddle base
    for k = 1:M:N        % group loop
        for j = 0:H-1    % butterfly loop
            u = x(k + j);             % upper input
            t = x(k + j + H);         % lower input
            x(k + j) = u + t;         % upper output (sum)
            x(k + j + H) = (u - t) * W^j; % lower output (diff × twiddle)
        end
    end
end

% --- Bit reversal at the end for DIF ---
x = bitrevorder(x);

disp('DIF FFT Output:');
disp(x);

% --- Plot magnitude response ---
subplot(2,1,1);
stem(abs(x));
title('Magnitude Response');
xlabel('Index'); ylabel('|X(k)|');

subplot(2,1,2);
stem(angle(x));
title('Phase Response');
xlabel('Index'); ylabel('∠X(k)');
