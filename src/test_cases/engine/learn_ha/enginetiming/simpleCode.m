% Define some data points
x = [1.0, 2.0, 3.0, 4.0, 5.0];
y = [1.0, 1.5; 2.0, 2.5; 3.0, 3.5; 4.0, 4.5; 5.0, 5.5];

c = [];
% Use the spline function to create a spline fit
for i = 1:size(y,2)   % size(y,col=2) and row=1
    y_col = y(:, i);
    spline_fit = spline(x, y_col);
    
    % Evaluate the spline at new points
    x_new = linspace(1.0, 5.0, 101);
    y_new = ppval(spline_fit, x_new);
    
    c = vertcat(c, y_new);
    
    figure(i+5)
    % Plot the original data and the spline fit
    plot(x, y(:,i), 'o', x_new, y_new, '*');
%     plot(x_new, y_new, '*');
%     hold on;
%     plot(x, y(:,2), 'o', x_new, y_new(:,2), '-');
end

        

% hold off;
legend('y1 Data', 'y1 Spline Fit', 'y2 Data', 'y2 Spline Fit');
