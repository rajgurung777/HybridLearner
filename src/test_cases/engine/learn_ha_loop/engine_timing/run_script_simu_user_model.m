%% ******** Simulate User Supplied Model ******** 
% Run the simulation and generate a txt file containing a result of the simulation. 
% run this file with the following variables in the workspace 
%    timeFinal:  is the simulation Stop time or the simulation Time-Horizon. Note, .slx must have it set in the Model Settings->Solver menu. 
%    timeStepMax: is the Maximum simulation time-step or 'Max step size'. Note, .slx must set it in the Model Settings->Solver menu. 
%    a0, a1, and so on...: the initial values for state/output variables should also be loaded in the workspace. 
%    x0_input:       control point for the first input variable 
%    x0_time:       time series for the first input variable 
%    x1_input:       control point for the second input variable 
%    x1_time:       time series for the second input variable ..... and so on. 
%     
% Note: If the .slx model has input variable, then the inport must be labelled as 
%   x0In for the first input variable, x1In for the second input variable ..... and so on. 

 
 
timeFinal = 10; %Simulation Stop time or the simulation Time-Horizon 
timeStepMax = 0.001; %Maximum simulation time-step 

 % initial values for Simulation 

 %% Putting the Warning Off 

warning('off','all'); 

 %% Load the model 
mdl ='sldemo_engine'; 
load_system(mdl); 
format shortG; 
%%%%% Non-deterministic inputs %%%%%%% These values are obtained from 
%%%%% our Tool using random bounded by initial input values or from CE 
% Make SimulationData.Dataset to feed to the Simulink model 
ds = Simulink.SimulationData.Dataset; 
%% 
timeseries_throttle_input = timeseries(throttle_input, throttle_time); 
ds = ds.addElement(timeseries_throttle_input, 'throttleIn'); 
 %% 
timeseries_torque_input = timeseries(torque_input, torque_time); 
ds = ds.addElement(timeseries_torque_input, 'torqueIn'); 
 %% 
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
% Write the simulation result to the txt file 
result_matrix = [t, y( : , 2), y( : , 3), y( : , 1)]; 
result_filename = 'result_simu_data.txt'; 
writematrix(result_matrix, result_filename, 'Delimiter', 'tab'); 
