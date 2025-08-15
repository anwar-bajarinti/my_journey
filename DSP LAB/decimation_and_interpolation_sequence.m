clc;
clear;
close all;

% Original data
x = [1, 2, 33, 15, 6, 99, 4, 35, 12];
disp('Original vector:'); disp(x);

% Convert to column vector
x1 = x(:);
disp('Column vector:'); disp(x1);

% Decimation
x2 = x1(1:2:end);
x3 = x1(1:3:end);
x4 = x1(1:4:end);

% Interpolation (upsampling)
p1 = upsample(x, 3);
p2 = upsample(x, 5);
p3 = upsample(x, 10);

% Plotting in a compact arrangement
figure;

% ==== Decimation row ====
subplot(2,4,1);
stem(x1, 'filled');
title("Original");

subplot(2,4,2);
stem(x2, 'filled');
title("Decimation ×2");

subplot(2,4,3);
stem(x3, 'filled');
title("Decimation ×3");

subplot(2,4,4);
stem(x4, 'filled');
title("Decimation ×4");

% ==== Interpolation row ====
subplot(2,4,5);
stem(p1, 'filled');
title("Interpolation ×3");

subplot(2,4,6);
stem(p2, 'filled');
title("Interpolation ×5");

subplot(2,4,7);
stem(p3, 'filled');
title("Interpolation ×10");

% Fill last subplot with empty placeholder for symmetry
subplot(2,4,8);
axis off;
text(0.5, 0.5, 'End of Plots', 'HorizontalAlignment', 'center');
