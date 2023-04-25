%% Amit 
% Due to the below error 
%      Derivative of state '1' in block 'AbstractFuelControl/Air Fuel Control Model 1/Wall wetting/Integrator' at time 0.76 is not finite. The
%      simulation will be stopped. There may be a singularity in the solution.  
%       If not, try reducing the step size (either by reducing the fixed step
%      size or by tightening the error tolerances)
% caused due to the Integrator block. This model can not be solved using
% "Type=Fixed-sized" which was the standard approach in our tool for all
% models/benchmarks so that Trace(s) comparison can be done for uniform time-step
% but now this model require "Solver Options: Type: Variable-step Solver: ode15s (stiff/NDF)
% as suggested in https://in.mathworks.com/matlabcentral/answers/99084-why-am-i-receiving-error-messages-about-singularities-in-my-simulink-model
% So, we need to filter the final result before we output to our tool.
%%

%% Load the AFC model
mdl = 'AbstractFuelControl';
load_system(mdl);

format shortG   % Discards trailing zeros, which cause error in floating comparison

%% initial parameter as it is in Breach Tool
fuel_inj_tol = 1.0;  %fule injection actuator error factor, c25
MAF_sensor_tol = 1.0; %MAF sensor error factor, c23
AF_sensor_tol = 1.0;  %A/F sensor error factor, c24
pump_tol = 1.;
kappa_tol=1;   
tau_ww_tol=1;
fault_time=60;  % 60 in STalario, 50 in Breach. Time to introduce sensor failure (sec)
kp = 0.04;
ki = 0.14;
%%


%% initial Input values (x0_0, x1_0) for Simulation taken from Workspace
timeFinal = time_horizon;  % 50; Simulation Stop time or the simulation Time-Horizon
timeStepMax = time_step;  % 0.001;   %Maximum simulation time-step

%%%%% Non-deterministic inputs %%%%%%% These 4 values are obtained from
%%%%% our Tool using random bounded by initial input values or from CE
Pedal_Angle = timeseries(cp_pedal_angle, timeVector_pedal_angle);
Engine_Speed = timeseries(cp_engine_speed, timeVector_engine_speed);

%%%%%% Deterministic single input value %%%%%%
% padelAngle_input = x0_0;   % 35,50-problem-time-step, 56 check; In Breach use SetParamRanges({'Pedal_Angle_pulse_period', 'Pedal_Angle_pulse_amp'}, [10 20; 10 60])
% engineSpeed_input = x1_0; % 56 and 1067.5 ncheck  x1_0;   % 900
% Pedal_Angle = timeseries(padelAngle_input, 0);  
% Engine_Speed = timeseries(engineSpeed_input, 0);

% Make SimulationData.Dataset to feed to the Simulink model
ds = Simulink.SimulationData.Dataset;
ds = ds.addElement(Pedal_Angle,'Pedal Angle');
ds = ds.addElement(Engine_Speed,'Engine Speed');
%%

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
% 
% figure(1);
% plot(t,y);


%% Output Data Filterring required
% (1) Model-Checker is added lt and gt to take care of time constriants, Eg
% gt >= 10 & gt <=TH
% (2) data should be refined to include only fixed time-step values using
% Interpolation, otherwise data-size will be very high for Learning Algo.
% Moreover, traces comparison during equivalence test will require it.

tstep = 0;
seq_index = 1;
%totalSamples = int16(timeFinal / timeStepMax) + 1;  % Should be an
%integer. Why did I took one sample extra ?
totalSamples = int16(timeFinal / timeStepMax);  % Should be an integer

% total_discardSamples = 10 / timeStepMax + 1;
% totalSamples = totalSamples - total_discardSamples;

t_out = zeros(totalSamples, 1);
AF_ref =  zeros(totalSamples, 1);
AF =  zeros(totalSamples, 1);
controller_mode = zeros(totalSamples, 1);
padel_angle_out =  zeros(totalSamples, 1);
engine_speed_out =  zeros(totalSamples, 1);

for i= 1:r         
    if (abs(t(i) - tstep) < 1e-10)    % equal or close by 1e-10 to the user-decided time-steps
        t_out(seq_index) = t(i);
        AF_ref(seq_index) = y(i, 1);
        AF(seq_index) = y(i, 2);
        controller_mode(seq_index) = y(i, 3);
        padel_angle_out(seq_index) = y(i, 4);
        engine_speed_out(seq_index) = y(i, 5);

        seq_index = seq_index +1;       
        tstep = tstep + timeStepMax;    
    end
end


% AF_ref = y(:, 1);     % AF reference values
% AF = y(:, 2);     % computed AF values
% controller_mode = y(:, 3);     % Controller Modes: StartUp, Normal, Power and Fault
% padel_angle_out = y(:, 4);     % computed Padel Angle
% engine_speed_out = y(:, 5);     % computed Engine Speed values

% 
%% Plotting Section may be disable
% 
% 

figure(1);
plot (t_out, padel_angle_out)
title('Padel Angle');

figure(2);
plot (t_out, engine_speed_out)
title('Engine Speed'); 

figure(3);
plot (t_out, AF_ref)
title('AF ref')

figure(4);
plot (t_out, AF);
title('AF');


figure(5);
plot (t_out, controller_mode)
title('Controller Mode');
% 

%% Write the simulation result to the file
%result_matrix = [t_out, padel_angle_out, engine_speed_out, AF_ref, AF, controller_mode];
result_matrix = [t_out, padel_angle_out, engine_speed_out, AF_ref, AF, controller_mode];
result_filename = 'result.txt';
writematrix(result_matrix, result_filename, 'FileType', 'text', 'Delimiter', 'tab');


%% References
% * [Jin et al., HSCC'14]: *Powertrain Control Verification
% Benchmark*, HSCC 2014, X. Jin, J. V. Deshmukh, J.Kapinski,
% K. Ueda, and K. Butts
