clc;
close all;
clear all;

% -----------------------------
% Filter specifications
% -----------------------------
wp = 0.2*pi;    % Analog passband edge (rad/s)
ws = 0.6*pi;    % Analog stopband edge (rad/s)

Rp_linear = 0.8;   % Given passband ripple (linear scale)
Rs_linear = 0.2;   % Given stopband ripple (linear scale)

Ts = 1;            % Sampling interval
Fs = 1/Ts;         % Sampling frequency

% Convert ripple values to dB
Rp_dB = abs(20*log10(Rp_linear));   % Passband ripple (dB)
Rs_dB = abs(20*log10(Rs_linear));   % Stopband attenuation (dB)

% -----------------------------
% Step 1: Find minimum order
% -----------------------------
[filter_order, wn_cheb] = cheb1ord(wp, ws, Rp_dB, Rs_dB, 's');
disp('Chebyshev filter order (N) ='); disp(filter_order);
disp('Cutoff frequency wn (rad/s) ='); disp(wn_cheb);

% -----------------------------
% Step 2: Analog prototype Chebyshev-I filter
% (cutoff = 1 rad/s for now)
% -----------------------------
[b_proto, a_proto] = cheby1(filter_order, Rp_dB, 1, 'low', 's');
disp('Prototype numerator (b_proto) ='); disp(b_proto);
disp('Prototype denominator (a_proto) ='); disp(a_proto);

% -----------------------------
% Step 3: Scale prototype cutoff (1 rad/s → wn_cheb)
% -----------------------------
[num_analog, den_analog] = lp2lp(b_proto, a_proto, wn_cheb);
disp('Scaled analog numerator ='); disp(num_analog);
disp('Scaled analog denominator ='); disp(den_analog);

% -----------------------------
% Step 4: Convert analog → digital (impulse invariance)
% -----------------------------
[num_digital, den_digital] = impinvar(num_analog, den_analog, Fs);
disp('Digital numerator ='); disp(num_digital);
disp('Digital denominator ='); disp(den_digital);

% -----------------------------
% Step 5: Frequency and Pole-Zero Plots
% -----------------------------
w = 0:0.01:pi;

figure(1);
freqz(num_digital, den_digital, w);
title('Digital Chebyshev-I Filter (Impulse Invariance)');

figure(2);
zplane(num_digital, den_digital);
title('Pole-Zero Plot of Digital Chebyshev-I Filter');
