clc;
close all;
clear all;

% -----------------------------
% Filter specifications
% -----------------------------
passband_ripple_linear = 4.898;   % given Rp (linear scale)
stopband_ripple_linear = 0.75;    % given Rs (linear scale)
Ts = 1;                           % sampling time
Fs = 1;                           % sampling frequency

% Analog passband and stopband edge frequencies (rad/s)
omega_p = 0.64 / Ts;              % passband edge
omega_s = 2.75 / Ts;              % stopband edge

% Convert ripple specifications from linear to dB
Rp_db = abs(20*log10(passband_ripple_linear)); % passband ripple (dB)
Rs_db = abs(20*log10(stopband_ripple_linear)); % stopband attenuation (dB)

% Desired analog cutoff frequency (rad/s) for scaling
omega_c = 0.75;

% -----------------------------
% Step 1: Find minimum order N
% -----------------------------
[filter_order, butter_cutoff] = buttord(omega_s, omega_p, Rs_db, Rp_db, 's');
disp('Filter order (N) ='); disp(filter_order);
disp('Butterworth cutoff (rad/s) ='); disp(butter_cutoff);

% -----------------------------
% Step 2: Analog prototype filter
% -----------------------------
[b_proto, a_proto] = butter(filter_order, 1, 'low', 's'); % normalized cutoff = 1 rad/s
disp('Prototype numerator (b_proto) ='); disp(b_proto);
disp('Prototype denominator (a_proto) ='); disp(a_proto);

% -----------------------------
% Step 3: Scale prototype to desired cutoff (ωc)
% -----------------------------
[num_analog, den_analog] = lp2lp(b_proto, a_proto, omega_c);
disp('Analog numerator after scaling ='); disp(num_analog);
disp('Analog denominator after scaling ='); disp(den_analog);

% -----------------------------
% Step 4: Convert analog → digital using bilinear transform
% -----------------------------
[num_digital, den_digital] = bilinear(num_analog, den_analog, Fs);
disp('Digital numerator ='); disp(num_digital);
disp('Digital denominator ='); disp(den_digital);

% -----------------------------
% Step 5: Frequency response
% -----------------------------
omega_vec = 0:0.01:pi;   % digital frequency range
figure(1);
freqz(num_digital, den_digital, omega_vec);
title('Digital Butterworth Filter Response (Bilinear Transform)');
