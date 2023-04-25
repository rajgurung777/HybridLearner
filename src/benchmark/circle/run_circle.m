%% Simulate Circle Model: an object moving in a circular motion 
% Run the simulation and generate a tsv file containing a result of the simulation.
% run this file with the following variables in the workspace
%       time_horizon:  Simulation Stop time or the simulation Time-Horizon
%       time_step:   Maximum simulation time-step
%       x0_0:       First variable initial value
%       x1_0:       Second variable initial value


% Run the simulation using the model described in Fig. 3 of [http://xspeed.nitmeghalaya.in/Benchmarks.pdf].
% Set the model-parameters in the .slx file
timeFinal = time_horizon;  %Simulation Stop time or the simulation Time-Horizon
timeStepMax = time_step; %0.1;  %Maximum simulation time-step

% initial values for Simulation
a = x0_0;   %
b = x1_0;   %



%simResult = sim('circle.slx');
%% Set the internal variables for the initial values
% Note: x0 and y0 inside the chart the variables are "parameters"
%open_system('circle')
%workspace = get_param('circle', 'ModelWorkspace');
%assignin(workspace,'x0', x0);
%assignin(workspace,'y0', y0);

%% Run the simulation
result = sim('circle');
%% Set the result
tout = result.tout;
%x1 = result.yout.signals(1).values;
%x2 = result.yout.signals(2).values;

figure(1);

x1 = result.yout.getElement('xOut').Values.Data;
x2 = result.yout.getElement('yOut').Values.Data;
plot(x1,x2);


%Write the simulation result to the tsv file
result_matrix = [tout, x1, x2];
result_filename = 'result.txt';  %changed to .txt from .tsv
%writematrix(result_matrix, result_filename, 'FileType', 'text', 'Delimiter', 'tab');

%Docs:  writematrix(M,'M_tab.txt','Delimiter','tab')
writematrix(result_matrix, result_filename, 'Delimiter', 'tab');

