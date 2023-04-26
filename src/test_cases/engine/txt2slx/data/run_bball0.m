%% ******** Simulate Learned Model ******** 
% Run the simulation and generate a txt file containing a result of the simulation. 
% run this file with the following variables in the workspace 
%       time_horizon:  Simulation Stop time or the simulation Time-Horizon 
%       time_step:   Maximum simulation time-step 
%       x0_0:       First variable initial value 
%       x1_0:       Second variable initial value 

 
 
timeFinal = 10; %Simulation Stop time or the simulation Time-Horizon 
timeStepMax = 0.01; %Maximum simulation time-step 

 % initial values for Simulation 
a1 = 10.2559;  % user modifies this initial (state) values to the desired values
a2 = 15;  % user modifies this initial (state) values to the desired values

 %% Putting the Warning Off 

warning('off','all'); 

 %% Load the model 
mdl ='bball0'; 
load_system(mdl); 
format shortG; 
%%%%% Non-deterministic inputs %%%%%%% These values are obtained from 
%%%%% our Tool using random bounded by initial input values or from CE 
% Make SimulationData.Dataset to feed to the Simulink model 
ds = Simulink.SimulationData.Dataset; 
%% 
x0_input = [-9.768462 -9.664819 -9.710553 -9.559442]; 
x0_time = [0.000000 3.333333 6.666667 10.000000]; 
timeseries_x0_input = timeseries(x0_input, x0_time); 
ds = ds.addElement(timeseries_x0_input, 'x0In'); 
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
result_matrix = [t, y( : ,1), y( : ,2), y( : ,3)]; 
result_filename = 'result.txt'; 
writematrix(result_matrix, result_filename, 'Delimiter', 'tab'); 
