%% Simulate Navigation Model (Nav04 model in the Author's Webpage)
% Run the simulation and generate a tsv file containing a result of the simulation.
% run this file with the following variables in the workspace
%       time_horizon:  Simulation Stop time or the simulation Time-Horizon
%       time_step:   Maximum simulation time-step
%       x1_0:       First variable initial value (displacement in x-axis)
%       x2_0:       Second variable initial value (displacement in y-axis)
%       v1_0:       Third variable initial value (velocity in x-axis)
%       v2_0:       Fourth variable initial value (velocity in y-axis)
%
%  For this Nav instance initial loc==1, x1 \in [0,1] and x2 \in [0,1]

% Run the simulation using the model described similar to the
% Fig. 7 in [http://xspeed.nitmeghalaya.in/Benchmarks.pdf], with appropriate loc-labelling
% and initial location.
% Set the model-parameters in the .slx file
timeFinal = time_horizon;  %  time_horizon=5;
timeStepMax = time_step; %  time_step=0.1; 

% initial values for Simulation
a0 = x1_0;   %  x1_0=0.5;
a1 = x2_0;   %  x2_0=0.5;
b0 = v1_0;   %  v1_0=0.8;
b1 = v2_0;   %  v2_0=0;

%% Run the simulation
result = sim('Nav_inst1');
%% Set the result
tout = result.tout;
%x1 = result.yout.signals(1).values;
%x2 = result.yout.signals(2).values;
figure(2);
%Read from user the variable name for plotting and replace here accordingly
x1 = result.yout.getElement('x1Out').Values.Data;
x2 = result.yout.getElement('x2Out').Values.Data;
v1 = result.yout.getElement('v1Out').Values.Data;
v2 = result.yout.getElement('v2Out').Values.Data;


plot(x1,x2);


%Write the simulation result to the tsv file
result_matrix = [tout, x1, x2, v1, v2];
result_filename = 'result.txt';  %changed to .txt from .tsv
writematrix(result_matrix, result_filename, 'FileType', 'text', 'Delimiter', 'tab');
