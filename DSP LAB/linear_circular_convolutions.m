clc;
clear;
close all;

% ==== Input Sequences ====
x1 = [1, 0, 2, 3];
y1 = [1, 2, 3];

x2 = [1, 2, 3, 4];
y2 = [1, 1];

x3 = [4, 5, 9, 13];
y3 = [2, 3, 1];

% ==== Convolutions ====
l1 = conv(x1, y1);
c1 = cconv(x1, y1, 4);

l2 = conv(x2, y2);
c2 = cconv(x2, y2, 4);

l3 = conv(x3, y3);
c3 = cconv(x3, y3, 4);

% ==== Display in Command Window ====
disp('--- X inputs ---');
disp(x1); disp(x2); disp(x3);

disp('--- Y inputs ---');
disp(y1); disp(y2); disp(y3);

disp('--- Linear Convolution Results ---');
disp(l1); disp(l2); disp(l3);

disp('--- Circular Convolution Results ---');
disp(c1); disp(c2); disp(c3);

% ==== Plot Results ====
figure;

% For x1 & y1
subplot(3,2,1);
stem(l1, 'filled');
title('Linear Conv (x1,y1)');

subplot(3,2,2);
stem(c1, 'filled');
title('Circular Conv (x1,y1)');

% For x2 & y2
subplot(3,2,3);
stem(l2, 'filled');
title('Linear Conv (x2,y2)');

subplot(3,2,4);
stem(c2, 'filled');
title('Circular Conv (x2,y2)');

% For x3 & y3
subplot(3,2,5);
stem(l3, 'filled');
title('Linear Conv (x3,y3)');

subplot(3,2,6);
stem(c3, 'filled');
title('Circular Conv (x3,y3)');
