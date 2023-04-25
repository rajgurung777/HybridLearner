%% Amit 
% Input (throttle[0 to 100] and BrakeTorque [0 to 325]

%%

%% Load the AFC model
mdl = 'AutomaticTransmission';
load_system(mdl);

format shortG   % Discards trailing zeros, which cause error in floating comparison

%% initial parameter as it is in Breach Tool

%%


%% initial Input values (x0_0, x1_0) for Simulation taken from Workspace
timeFinal = time_horizon;  % 50; Simulation Stop time or the simulation Time-Horizon
timeStepMax = time_step;  % 0.001;   %Maximum simulation time-step

%% %%% Non-deterministic inputs %%%%%%% These 4 values are obtained from
%%%%% our Tool using random bounded by initial input values or from CE
Throttle = timeseries(throttle_input, timeVector_throttle);
Brake = timeseries(BrakeTorque_input, timeVector_brake);

%% %%%% Deterministic single input value %%%%%%
% throttle_input = 50;   % x0_0;
% BrakeTorque_input = 0; % x1_0; 
% Throttle = timeseries(throttle_input, 0);  
% Brake = timeseries(BrakeTorque_input, 0);

%% Make SimulationData.Dataset to feed to the Simulink model
ds = Simulink.SimulationData.Dataset;
ds = ds.addElement(Throttle,'Throttle');
ds = ds.addElement(Brake,'BrakeTorque');


%% Run simulation
set_param(mdl, 'LoadExternalInput', 'on'); 
set_param(mdl, 'ExternalInput', 'ds'); % Set the initial input values in the model.

simOut = sim(mdl, 'SaveOutput', 'on', 'OutputSaveName', 'yOut', ...
    'SaveTime', 'on','TimeSaveName','tOut', ...
    'LimitDataPoints', 'off', 'SaveFormat', 'Array');

%% Plot the result
y = simOut.get('yOut');
t = simOut.get('tOut');    % time values
[r,c] = size(t);

%% Output Data Filterring required

t_out = t(:);
gear_out = y(:, 1); %y.signals(1).values;
Engine_rpm_out= y(:, 2); % y.signals(2).values;
vehicle_speed_out = y(:, 3); % y.signals(3).values;
throttle_out = y(:, 4); %  y.signals(4).values;
brake_out = y(:, 5); % y.signals(5).values;
% 

% 
%% Plotting Section may be disable

figure(1);
plot (t_out, throttle_out)
title('Throttle');

figure(2);
plot (t_out, brake_out)
title('Brake'); 

figure(3);
plot (t_out, gear_out)
title('Gear')

figure(4);
plot (t_out, Engine_rpm_out);
title('Engine RPM');

figure(5);
plot (t_out, vehicle_speed_out)
title('Vehicle Speed');



%% Write the simulation result to the file
result_matrix = [t_out, throttle_out, brake_out, gear_out, Engine_rpm_out, vehicle_speed_out];
result_filename = 'result.txt';
writematrix(result_matrix, result_filename, 'FileType', 'text', 'Delimiter', 'tab');


%% References
% [1] Bardh Hoxha, Houssam Abbas, and Georgios Fainekos. Benchmarks for Temporal Logic Requirements for Automotive Systems. In ARCH15
% Model taken and modified from Breach repo with the file name
% breach-master/Ext/Models/Autotrans_w_signal_builder.slx