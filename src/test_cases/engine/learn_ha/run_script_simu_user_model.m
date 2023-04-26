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
mdl ='bball'; 
load_system(mdl); 
format shortG; 
%%%%% Non-deterministic inputs %%%%%%% These values are obtained from 
%%%%% our Tool using random bounded by initial input values or from CE 
% Make SimulationData.Dataset to feed to the Simulink model 
ds = Simulink.SimulationData.Dataset; 
%% 
timeseries_u_input = timeseries(u_input, u_time); 
ds = ds.addElement(timeseries_u_input, 'uIn'); 
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
end 
%Write the simulation result to the txt file 
result_matrix = [t, y( : , 3), y( : , 1), y( : , 2)]; 
result_filename = 'result_simu_data.txt'; 
writematrix(result_matrix, result_filename, 'Delimiter', 'tab'); 
