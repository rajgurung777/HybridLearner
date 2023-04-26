function [new_t_list, y_new] = linear_interpolate(t, y, timeFinal, new_timeStep)

    dt =new_timeStep;

    % Calculate the number of steps required
    n_steps = round(timeFinal / dt);

    % Initialize the list with zeros
    new_t_list = zeros(n_steps+1, 1);

    % Populate the list with values
    for i = 1:n_steps+1
        new_t_list(i) = (i-1) * dt;
    end

    c = zeros(length(new_t_list), size(y,2));
    
    for i = 1: size(y,2)
        
        y_col = y(:, i);    % for each dimension
        
        
        %% Perform linear interpolation
        y_new_out = interp1(t, y_col, new_t_list);

        %%
        % Perform spline interpolation to estimate the values of y at the given new_t_list.
        % Use MATLAB's spline function to perform spline interpolation         
%         spline_fit = spline(t, y_col);
%         % Evaluate the spline at new points
%         y_new_out = ppval(spline_fit, new_t_list);    % Not good for some input variables
        

        c(:,i) = y_new_out; % c = vertcat(c, y_new_out);
        
    end
    
    y_new = c;
    
end
