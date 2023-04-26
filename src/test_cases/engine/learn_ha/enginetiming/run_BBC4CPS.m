% For our tool we take all traces data in a single file, traces are appended.
% TODO: vary Kp and Ki to generate traces and use this data to learn model
timeFinal = 10; %Simulation Stop time or in the model it is set 10
timeStepMax = 0.01 % fixed-step 0.00008; %In this model it is set auto

%% Load the model
mdl ='sldemo_enginewc';
load_system(mdl);
format shortG;

%%
times = 64 % 64;  % Decide the number of traces to Generate
%%

Kp = 0.01;  %0.1 to 0.01 should be varied for stable signal; (>0.2 increases nonlinearity)
Ki = 0.03;  %0.03 to 0.07 should be varied (below 3k);
Kp_mnval = 0.01;
Kp_mxval = 0.1;

Ki_mnval = 0.03;
Ki_mxval = 0.07;

rng(100,'twister');     %  sets the seed to 100 for TRAINING Set and the generator to Mersenne Twister.
% rng(200,'twister');   %  sets the seed to 200 For TEST Set. We use the
% run_POSEHAD.m file to generate the TEST SET even for BBC4CPS

for count = 1 : times
    %%   parameters
    %     Kp = Kp + 0.015;  %0.1 to 0.01 shoule be varied for stable signal; (>0.2 increases nonlinearity)
    %     Ki = Ki + 0.005;  %0.03 to 0.07 should be varied (for speed below 3k);
    Kp = Kp_mnval + rand * (Kp_mxval - Kp_mnval);
    Ki = Ki_mnval + rand * (Ki_mxval - Ki_mnval);

    %%
    simOut = sim(mdl, 'SaveOutput', 'on', 'OutputSaveName', 'yOut', 'SaveTime', 'on','TimeSaveName','tOut', 'LimitDataPoints', 'off', 'SaveFormat', 'Array');
    %%

    %%  Plotting
    y = simOut.get('yOut');
    t = simOut.get('tOut');
    [rsize, csize] = size(y);
    for i=1:csize
        figure(i);
        scatter(t, y( : , i));
        title('Original Model','FontSize',16, 'FontWeight', 'bold');
        xlabel('time', 'FontSize',16, 'FontWeight', 'bold');
        grid on;
        grid minor;
    end

    data_filter = 1;    % For this model fixed-step does not give proper
    % output range for enginespeed. So must be variable
    new_timeStep = timeStepMax; % 0.2; % to make processing fast extract less data
    %% Data Filtering to get fixed timestep
    if (data_filter == 1)
        [t, y] = simple_filter(t, y, timeFinal, new_timeStep);
        
%        [t, y] = linear_interpolate(t, y, timeFinal, new_timeStep);        
        
    end

    %%
    % Write the simulation result to the txt file
    result_matrix = [t, y( : , 2), y( : , 3), y( : , 1)];

    %result_filename = "data/engine_" + int2str(count) + ".csv";  % for tool POSEHAD (Passive Online Strategy for Extracting Hybrid Automaton based on DTW technique)

    result_filename = "dataBBC/engine_" + int2str(times) + ".txt";  % for our tool .txt or .tsv writing on the same file

    %     writematrix(result_matrix, result_filename, 'Delimiter', 'tab');

    if count == 1
        writematrix(result_matrix, result_filename, 'Delimiter', 'tab');
    else
        writematrix(result_matrix, result_filename, 'Delimiter', 'tab','WriteMode','append');
    end

end

% Output file contain: [time, throttleAngle, loadTorque, engineSpeed]
% The format is [time-value, input-variable-1, input-variable-2, output-variable]
