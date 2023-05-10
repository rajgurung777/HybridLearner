%% Generate output trajectories using the learned model
format long
learnedModel = 64;      % just modify this with the model learned using number of training traces
total_test_trace = 32;

% Get the current directory
current_dir = pwd();
copyfile("../../../results/engine/BeforeAnnotation/engineTiming_64.slx", current_dir);

outputTrace_path =  "../../../results/engine/BeforeAnnotation/testData_Output";

benchmarkName = "engine_";
    
% model = benchmarkName + num2str(learnedModel);  % Learned model

for test_id = 1 : total_test_trace
    
    fileName = benchmarkName + num2str(test_id) + ".csv"; % testing trace file
    inputFileName = fullfile(current_dir, '../TestSet', fileName);   
    input_data = load(inputFileName);
    
%   inputFileName = "testdata/engine_" + num2str(test_id) + ".csv"; % testing trace file
%   input_data = load(inputFileName);
    
    %%%%% 
    ds = Simulink.SimulationData.Dataset; 

    x0_input = input_data(:,2); % 1st input variable
    x0_time = input_data(:,1); 
    timeseries_x0_input = timeseries(x0_input, x0_time); 
    ds = ds.addElement(timeseries_x0_input, 'x0In'); 
     %% 
    x1_input = input_data(:,3);   % 2nd input variable
    x1_time = input_data(:,1); 
    timeseries_x1_input = timeseries(x1_input, x1_time); 
    ds = ds.addElement(timeseries_x1_input, 'x1In'); 
    %% 

    a2 = input_data(1,4);   % initial state of the output variable


    timeFinal = 10; % Simulation Stop time or the simulation Time-Horizon 
    timeStepMax = 0.01; % Maximum simulation time-step 


    %%

%     outfile = "testData_Output/engine_" + num2str(learnedModel) + "_Trace_" + num2str(test_id) + ".txt"; % output from Leanred model for test traces
    
    outFileName = benchmarkName + num2str(learnedModel) + "_Trace_" + num2str(test_id) + ".txt"; % output from Leanred model for test traces
    outfile = fullfile(current_dir, outputTrace_path, outFileName); 
  
    warning('off','all'); 
    %% Load the model     
    mdl = "engineTiming_64";
    load_system(mdl);  
    
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
        title('Learned Model','FontSize',26, 'FontWeight', 'bold'); 
        xlabel('time', 'FontSize',26, 'FontWeight', 'bold'); 
        grid on; 
        grid minor; 
    end
    
     %%    
    data_filter = 1;    %
    %% Data Filtering to get approximately fixed timestep
    if (data_filter == 1)
         [t, y] = simple_filter(t, y, timeFinal, timeStepMax);        
%        [t, y] = linear_interpolate(t, y, timeFinal, timeStepMax);        
    end

    %% 

    %Write the simulation result to the txt file 
    result_matrix = [t, y( : ,2), y( : ,3), y( : ,1)]; % keeping same format [time, inputVar-1, inputVar-2, outputVar]
    result_filename = outfile;
    writematrix(result_matrix, result_filename, 'Delimiter', 'tab'); 
    
end

% Close the Simulink model without saving
close_system('engineTiming_64', 0);


