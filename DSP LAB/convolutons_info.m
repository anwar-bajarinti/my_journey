clc; clear; close all;

x = [1, 0, 2, 3];
h = [1, 2, 3];

%% ---------- LINEAR CONVOLUTION ----------
Lx = length(x);
Lh = length(h);
Ny = Lx + Lh - 1;
y_linear = zeros(1, Ny);

disp('--- Linear Convolution Steps ---')
for n = 1:Ny
    fprintf('y_linear(%d) = ', n);
    for k = 1:Lx
        if (n-k+1 > 0) && (n-k+1 <= Lh)
            val = x(k) * h(n-k+1);
            y_linear(n) = y_linear(n) + val;
            fprintf('[x(%d)=%d * h(%d)=%d] + ', k, x(k), n-k+1, h(n-k+1));
        end
    end
    fprintf('= %d\n', y_linear(n));
end

%% ---------- CIRCULAR CONVOLUTION ----------
N = max(Lx, Lh);
x_pad = [x, zeros(1, N-Lx)];
h_pad = [h, zeros(1, N-Lh)];
y_circular = zeros(1, N);

disp(' ')
disp('--- Circular Convolution Steps ---')
for n = 1:N
    fprintf('y_circular(%d) = ', n);
    for k = 1:N
        idx = mod(n-k, N); % wrap-around index
        val = x_pad(k) * h_pad(idx+1);
        y_circular(n) = y_circular(n) + val;
        fprintf('[x(%d)=%d * h(%d)=%d] + ', k, x_pad(k), idx+1, h_pad(idx+1));
    end
    fprintf('= %d\n', y_circular(n));
end

%% ---------- Compare with MATLAB ----------
disp(' ')
disp('Our Linear Conv:'); disp(y_linear);
disp('MATLAB Linear Conv:'); disp(conv(x, h));

disp('Our Circular Conv:'); disp(y_circular);
disp('MATLAB Circular Conv:'); disp(cconv(x, h, N));
