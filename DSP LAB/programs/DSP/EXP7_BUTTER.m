clc; clear; close all;

% ----- Specs -----
wp = 0.2*pi;    % passband edge (rad/s)
ws = 0.6*pi;    % stopband edge (rad/s)
rp = 4.898;     % passband ripple (dB)
rs = 0.74;      % stopband attenuation (dB)
Fs = 1;         % sampling freq (Hz)

% ----- Find filter order -----
[n, wc] = buttord(ws, wp, rs, rp, 's');
disp(['Order = ', num2str(n)]);
disp(['wc = ', num2str(wc)]);

% ----- Analog Butterworth prototype -----
[bp, ap] = butter(n, 1, 'low', 's');      % cutoff = 1 rad/s
[ba, aa] = lp2lp(bp, ap, wc);             % scale to wc

% ----- (1) Impulse Invariance -----
[numI, denI] = impinvar(ba, aa, Fs);
figure;
freqz(numI, denI, 0:0.01:pi);
title('Digital LPF – Impulse Invariance');
xlabel('Freq (rad/sample)'); ylabel('Magnitude (dB)');

% ----- (2) Bilinear Transformation -----
[numB, denB] = bilinear(ba, aa, Fs);
figure;
freqz(numB, denB, 0:0.01:pi);
title('Digital LPF – Bilinear Transform');
xlabel('Freq (rad/sample)'); ylabel('Magnitude (dB)');
