clc;
clear variables;
close all;
i=imread("pcb.jpg");
j=rgb2gray(i);
figure;
sv=edge(j,"sobel","vertical");
sh=edge(j,"sobel","horizontal");
s=edge(j,"sobel","both");
% Display the edge-detected images
subplot(1, 3, 1), imshow(sv), title('Vertical Edges');
subplot(1, 3, 2), imshow(sh), title('Horizontal Edges');
subplot(1, 3, 3), imshow(s), title('Both Edges');
figure;
rv=edge(j,"roberts","vertical");
rh=edge(j,"roberts","horizontal");
r=edge(j,"roberts","both");
% Display the edge-detected images using Roberts method
subplot(1, 3, 1), imshow(rv), title('Vertical Edges (Roberts)');
subplot(1, 3, 2), imshow(rh), title('Horizontal Edges (Roberts)');
subplot(1, 3, 3), imshow(r), title('Both Edges (Roberts)');
figure;
pv=edge(j,"prewitt","vertical");
ph=edge(j,"prewitt","horizontal");
p=edge(j,"prewitt","both");
% Display the edge-detected images using Prewitt method
subplot(1, 3, 1), imshow(pv), title('Vertical Edges (Prewitt)');
subplot(1, 3, 2), imshow(ph), title('Horizontal Edges (Prewitt)');
subplot(1, 3, 3), imshow(p), title('Both Edges (Prewitt)');
figure;
c=edge(j,"canny");
imshow(c);
