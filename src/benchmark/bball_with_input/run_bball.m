%% ******** Simulate Bouncing Ball Model ******** 
% Run the simulation and generate a txt file containing a result of the simulation. 
% Note: This .slx model has input variable u (the force of gravity), the
% inport is labelled as uIn


%% Load the model
mdl = 'bball';
load_system(mdl);

format shortG   % Discards trailing zeros, which cause error in floating comparison

%% initial values for Simulation taken from Workspace
timeFinal = time_horizon;  % 50; Simulation Stop time or the simulation Time-Horizon
timeStepMax = time_step;  % 0.001;   %Maximum simulation time-step

% a1 = value1;   %initial value for ball-position.
                 % Values of a1 and a2 are populated from our tool BBC4CPS
% a2 = value2;   %initial value for ball-velocity

 %% Putting the Warning Off 
warning('off','all'); 

 
%% %%% Non-deterministic inputs %%%%%%% These 2 values are obtained from
%%%%% our Tool using random bounded by initial input values or from CE
timeseries_u_input = timeseries(u_input, u_time); 

%% Make SimulationData.Dataset to feed to the Simulink model
ds = Simulink.SimulationData.Dataset;
ds = ds.addElement(timeseries_u_input, 'uIn'); 

 %%  Run simulation
set_param(mdl, 'LoadExternalInput', 'on');  
set_param(mdl, 'ExternalInput', 'ds'); % Set the initial input values in the model.

simOut = sim(mdl, 'SaveOutput', 'on', 'OutputSaveName', 'yOut', 'SaveTime', 'on','TimeSaveName','tOut', 'LimitDataPoints', 'off', 'SaveFormat', 'Array'); 

%% Plot the result 
y = simOut.get('yOut'); 
t = simOut.get('tOut'); 
[rsize, csize] = size(y); 
for i=1:csize 
	figure(i); 
	plot(t, y( : , i)); 
	title('Original Model','FontSize',26, 'FontWeight', 'bold'); 
	xlabel('time', 'FontSize',26, 'FontWeight', 'bold'); 
	grid on; 
	grid minor; 
end 

 data_filter = 0;    % For this model fixed-step solver works
%% Data Filtering to get fixed timestep 
if (data_filter == 1)

    tstep = 0;  
    seq_index = 1;  
    totalSamples = timeFinal / timeStepMax + 1;  
    t_temp1 = zeros(totalSamples, 1);  
    y_temp1 = zeros(totalSamples, csize);  
    firstFound = 1; 
    for i = 1:rsize     %rsize is the total rows of y or y_temp  
      diffVal = t(i) - tstep;     %initially time-step will be >= 0  
        if (diffVal >= 0)    
            firstFound = 1;    
        end 

        if (diffVal >= 0 && firstFound == 1)  %1st value that matches, i.e., positive value    
            t_temp1(seq_index) = t(i);   
          for j = 1:csize     %csize is the total columns of y or y_temp, i.e., for each variables  
              y_temp1(seq_index, j) = y(i, j);   
          end   
            seq_index = seq_index + 1;    
            tstep = tstep + timeStepMax;  
            firstFound = 0;    
        end    
    end   
    last_row = y_temp1(totalSamples, :);   
    if last_row == 0   
        secondlast_row = y_temp1(totalSamples - 1, :);   
        y_temp1(totalSamples, :) = secondlast_row;   
        secondlast_row_time = t_temp1(totalSamples - 1);   
        t_temp1(totalSamples) = secondlast_row_time;   
    end   
    t = t_temp1; 
    y = y_temp1; 
end

%%   
% Write the simulation result to the txt file 
result_matrix = [t, y( : , 3), y( : , 1), y( : , 2)]; 
result_filename = 'result.txt'; 
writematrix(result_matrix, result_filename, 'Delimiter', 'tab'); 
