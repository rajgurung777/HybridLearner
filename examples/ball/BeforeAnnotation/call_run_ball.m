%% Generate output trajectories using the learned model
format long
warning('off','all'); 
total_test_trace = 32;
learnedModel = 64;      % just modify this with the model learned using number of training traces

% Get the current directory
current_dir = pwd();
% Construct the full path to the file
% filename = fullfile(current_dir, 'xyz', 'abc.txt');

copyfile("../../../results/bball/BeforeAnnotation/bball_64.slx", current_dir);

outputTrace_path =  "../../../results/bball/BeforeAnnotation/testData_Output";
benchmarkName = "bball_";
    
model = benchmarkName + num2str(learnedModel);  % Learned model

for test_id = 1 : total_test_trace
    fileName = benchmarkName + num2str(test_id) + ".csv"; % testing trace file
    inputFileName = fullfile(current_dir, '../TestSet', fileName);
%   inputFileName = "testdata/" + benchmarkName + num2str(test_id) + ".csv"; % testing trace file
    input_data = load(inputFileName);
    %%%%% 
    x0_input = input_data(:,2);  % time series input
    x0_time = input_data(:,1);   % values for the time series

    a1 = input_data(1,3);   % initial state of the output variable-1
    a2 = input_data(1,4);   % initial state of the output variable-2

    timeFinal = 13; % Simulation Stop time or the simulation Time-Horizon 
    timeStepMax = 0.001; % Maximum simulation time-step 

    % Make SimulationData.Dataset to feed to the Simulink model 
    ds = Simulink.SimulationData.Dataset; 
    %% 
    timeseries_x0_input = timeseries(x0_input, x0_time); 
    ds = ds.addElement(timeseries_x0_input, 'x0In'); 

    %%
    outFileName = model + "_Trace_" + num2str(test_id) + ".txt"; % output from Leanred model for test traces
    outfile = fullfile(current_dir, outputTrace_path, outFileName); 

%     run_bball(modelFile_withPath, outfile, timeFinal, timeStepMax);
    
    
     %% Load the model 
%     learnedModel_path = "/home/amit/eclipse-workspace/HybridLearner/results/bball/BeforeAnnotation"
%     addpath(learnedModel_path)
%      mdl = "/home/amit/eclipse-workspace/HybridLearner/results/bball/BeforeAnnotation/bball_64"
     mdl = model;
    
    load_system(mdl); 
    format long
    %format shortG; 

    set_param(mdl, 'LoadExternalInput', 'on');  
    set_param(mdl, 'ExternalInput', 'ds'); % Set the initial input values in the model. 
    simOut = sim(mdl, 'SaveOutput', 'on', 'OutputSaveName', 'yOut', 'SaveTime', 'on','TimeSaveName','tOut', 'LimitDataPoints', 'off', 'SaveFormat', 'Array'); 
    %% Plot the result 
    y = simOut.get('yOut'); 
    t = simOut.get('tOut'); 
    [rsize, csize] = size(y); 
%     Comment this for--loop to disable plots
    for i=1:csize 
        figure(i); 
        plot(t, y( : , i)); 
        title('Learned Model','FontSize',26, 'FontWeight', 'bold'); 
        xlabel('time', 'FontSize',26, 'FontWeight', 'bold'); 
        grid on; 
        grid minor; 
    end 
    
            
    %Write the simulation result to the txt file 
    result_matrix = [t, y( : , 3), y( : , 1), y( : , 2)]; 
    %result_filename = 'learned_prune_j.txt'; 
    result_filename = outfile;  
    writematrix(result_matrix, result_filename, 'Delimiter', 'tab'); 

end

% Close the Simulink model without saving
close_system('bball_64', 0);