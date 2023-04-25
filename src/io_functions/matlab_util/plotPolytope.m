% A = load('Dirs_A_printing.txt');
% b = load('polytope_b_printing.txt');

A = [-1.000000 0.000000 0.000000 0.000000 ; 
    1.000000 0.000000 0.000000 0.000000 ; 
    0.000000 -1.000000 0.000000 0.000000 ; 
    0.000000 1.000000 0.000000 0.000000 ; 
    0.000000 0.000000 -1.000000 0.000000 ; 
    0.000000 0.000000 1.000000 0.000000 ; 
    0.000000 0.000000 0.000000 -1.000000 ; 
    0.000000 0.000000 0.000000 1.000000 ];
b = [-0.200000 0.700000 -0.200000 0.700000 -0.800000 0.800000 -0.000000 0.000000 ]';
%Amit: did not work for this 

output = con2vert(A,b);
X = output(:,1);      %Select the x variable, where 1st column represent x
Y = output(:,2);      %Select the y variable, where 2nd column represent y

% *********** This part from Bruno Luong's code  ***********
xmean = mean(X);
ymean = mean(Y);
[~,j] = sort(atan2(Y-ymean, X-xmean));
X = X(j);
Y = Y(j);
% *******************************
% Repeating the first vertex to close the polytope when plotted using
% GNUPlot Util
l = length(X);  
X(l+1) = X(1);
Y(l+1) = Y(1);

points = [X, Y];
result_filename = 'vertices.txt';
writematrix(points, result_filename, 'Delimiter', 'tab');
