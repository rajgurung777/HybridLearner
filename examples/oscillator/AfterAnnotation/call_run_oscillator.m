%% Generate output trajectories using the learned model

format long
total_test_trace = 32;
learnedModel = 64;      % just modify this with the model learned using number of training traces


% Get the current directory
current_dir = pwd();
copyfile("../../../results/oscillator/AfterAnnotation/oscillator_64_Type.slx", current_dir);

outputTrace_path =  "../../../results/oscillator/AfterAnnotation/testData_Output";

benchmarkName = "oscillator_";
    
% model = benchmarkName + num2str(learnedModel);  % Learned model

for test_id = 1 : total_test_trace
    fileName = benchmarkName + num2str(test_id) + ".csv"; % testing trace file
    inputFileName = fullfile(current_dir, '../TestSet', fileName);      
%     inputFileName = "testdata/" + benchmarkName + num2str(test_id) + ".csv"; % testing trace file
    input_data = load(inputFileName);
   
    a0 = input_data(1,2);   % initial state of the output variable-1
    a1 = input_data(1,3);   % initial state of the output variable-2

    timeFinal = 10; % Simulation Stop time or the simulation Time-Horizon 
    timeStepMax = 0.01; % Maximum simulation time-step 

%     outfile = "testData_Output/" + model + "_Trace_" + num2str(test_id) + ".txt"; % output from Leanred model for test traces
%     run_oscillator(model, outfile, timeFinal, timeStepMax);

    outFileName = benchmarkName + num2str(learnedModel) + "_Trace_" + num2str(test_id) + ".txt"; % output from Leanred model for test traces
    outfile = fullfile(current_dir, outputTrace_path, outFileName); 
    
    
    %% Load the model 
    mdl = "oscillator_64_Type";    
    load_system(mdl); 
    
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
    
    result_matrix = [t, y( : , 1), y( : , 2)]; 
    result_filename = outfile; 
    writematrix(result_matrix, result_filename, 'Delimiter', 'tab');
        
end

% Close the Simulink model without saving
close_system('oscillator_64_Type', 0);

