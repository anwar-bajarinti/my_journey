clc;
clear;
close all;
% Input sequence
signal = input("Enter the input sequence (length must be power of 2): ");
N = length(signal);   % Length of the input sequence
% Check if length is a power of 2
if log2(N) ~= floor(log2(N))
    error('Length of input must be a power of 2');
end 
% Reorder the input sequence in bit-reversed order
signal = bitrevorder(signal);
numStages = log2(N);  % Number of FFT stages

% FFT computation (Cooley-Tukey algorithm)
for stage = 1:numStages
    sectionSize = 2^stage;        % Size of each section (butterfly group)
    halfSection = sectionSize/2;  % Half of section size (for butterfly pair)
    twiddleBase = exp(-2i*pi/sectionSize); % Base twiddle factor
    
    for sectionStart = 1:sectionSize:N
        for butterfly = 0:halfSection-1
            % Compute twiddle factor for current butterfly
            twiddle = (twiddleBase^butterfly);
            
            % Fetch upper and lower elements for butterfly
            top = signal(sectionStart + butterfly);
            bottom = signal(sectionStart + butterfly + halfSection);
            
            % Perform butterfly operation
            temp = twiddle * bottom;
            signal(sectionStart + butterfly) = top + temp;
            signal(sectionStart + butterfly + halfSection) = top - temp;
        end
    end
end

% Display FFT result
disp('FFT Output:');
disp(signal);

% Plot results
subplot(3,1,1);
stem(abs(signal));
title('Magnitude Response');

subplot(3,1,2);
stem(angle(signal));
title('Phase Response');

subplot(3,1,3);
stem(real(signal));
title('Real Part of FFT Output');
