%% Simulate Shared Gas Burner
% Run the simulation and generate a tsv file containing a result of the simulation.
% All the configurations are hardcoded to the Simulink model
% Run the simulation using the shared gas burner model in Fig. 1 of [Doyen+, FORMATS'05].

% run this file with the following variables in the workspace
%       time_horizon:  Simulation Stop time or the simulation Time-Horizon
%       time_step:   Maximum simulation time-step
%       x0_0:       First variable initial value
%       x1_0:       Second variable initial value

% Set the model-parameters in the .slx file

timeFinal = time_horizon;  %Simulation Stop time or the simulation Time-Horizon
timeStepMax = time_step; %0.1;  %Maximum simulation time-step

% initial values for Simulation
a_init = x0_0;
b_init = x1_0;

%% Set the internal variables for the initial values
%assignin(workspace,'initX1', initX1);
%assignin(workspace,'initX2', initX2);

%% Run the simulation
result = sim('shared_gas_burner');
%% Set the result
tout = result.tout;
x1 = result.yout.signals(1).values;
x2 = result.yout.signals(2).values;

figure(1);

% x1 = result.yout.getElement('xOut').Values.Data;
% x2 = result.yout.getElement('yOut').Values.Data;
plot(x1,x2);

%Write the simulation result to the tsv file
result_matrix = [tout, x1, x2];
result_filename = 'result.txt';  %changed to .txt from .tsv
writematrix(result_matrix, result_filename, 'FileType', 'text', 'Delimiter', 'tab');
