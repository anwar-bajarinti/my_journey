% Clear workspace and figures
clc; clear; close all;

% ----------------------------
% --- analog filter specs ---
% ----------------------------
analog_passband_omega = 0.2*pi;    % (original wp) passband edge (rad/s)
analog_stopband_omega  = 0.6*pi;   % (original ws) stopband edge (rad/s)

passband_ripple_db = 4.898;        % (original rp) passband ripple in dB
stopband_atten_db  = 0.74;         % (original rs) stopband attenuation in dB

% ----------------------------
% --- sampling / time ----
% ----------------------------
Ts = 1;    % (original t) sampling interval [s] — kept for clarity (not used elsewhere)
Fs = 1;    % (original fs) sampling frequency [Hz] — used by impinvar

% --------------------------------------------------------------------
% Get minimum analog Butterworth order and the critical analog freq
% NOTE: I preserved your original buttord argument order:
%       buttord(ws, wp, rs, rp, 's')
% so the first argument is the stopband omega and second is the passband omega.
% --------------------------------------------------------------------
[filterOrder, cutoff_analog_omega] = buttord( ...
    analog_stopband_omega, ...   % was ws in your code (passed first)
    analog_passband_omega, ...   % was wp in your code (passed second)
    stopband_atten_db, ...       % was rs in your code (third)
    passband_ripple_db, ...      % was rp in your code (fourth)
    's' ...
);

disp('filterOrder ='); disp(filterOrder);
disp('cutoff_analog_omega (rad/s) ='); disp(cutoff_analog_omega);

% ----------------------------------------------------------
% Design analog lowpass prototype with cutoff = 1 rad/s
% (butter returns prototype coefficients for cutoff = 1)
% ----------------------------------------------------------
[b_proto, a_proto] = butter(filterOrder, 1, 'low', 's');
disp('b_proto ='); disp(b_proto);
disp('a_proto ='); disp(a_proto);

% ----------------------------------------------------------
% Scale prototype lowpass (cutoff = 1) to desired analog cutoff
% using lp2lp (lowpass-to-lowpass frequency scaling)
% ----------------------------------------------------------
[b_analog, a_analog] = lp2lp(b_proto, a_proto, cutoff_analog_omega);
disp('b_analog (scaled) ='); disp(b_analog);
disp('a_analog (scaled) ='); disp(a_analog);

% ----------------------------------------------------------
% Convert analog (s-domain) filter to discrete-time (z-domain)
% using impulse invariance (impinvar). Fs is the sampling freq.
% ----------------------------------------------------------
[numd, dend] = impinvar(b_analog, a_analog, Fs);
disp('numd (digital numerator) ='); disp(numd);
disp('dend (digital denominator) ='); disp(dend);

% ----------------------------------------------------------
% Plot digital frequency response (freq in rad/sample)
% freq_vec is 0:0.01:pi (same as your original W = 0:0.01:pi)
% ----------------------------------------------------------
freq_vec = 0:0.01:pi;
figure(1);
freqz(numd, dend, freq_vec);
title(sprintf('Digital freq response (impulse invariance), Fs = %g', Fs));
