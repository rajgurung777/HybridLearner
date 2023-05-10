%% Generate output trajectories using the learned model
format long
learnedModel = 64;      % just modify this with the model learned using number of training traces
total_test_trace = 32;

% Get the current directory
current_dir = pwd();
copyfile("../../../results/cell/BeforeAnnotation/cellModel_64.slx", current_dir);

outputTrace_path =  "../../../results/cell/BeforeAnnotation/testData_Output";

benchmarkName = "cellModel_";

model = benchmarkName + num2str(learnedModel);  % Learned model

for test_id = 1 : total_test_trace
    
    fileName = "excitableCells_" + num2str(test_id) + ".csv"; % testing trace file
    inputFileName = fullfile(current_dir, '../TestSet', fileName);    
%   inputFileName = "testdata/excitableCells_" + num2str(test_id) + ".csv"; % testing trace file
    input_data = load(inputFileName);
   
    a0 = input_data(1,2);   % initial state of the output variable-1

    timeFinal = 500; % Simulation Stop time or the simulation Time-Horizon 
    timeStepMax = 0.01; % Maximum simulation time-step 

%     outfile = "testData_Output/excitableCells_" + num2str(learnedModel) + "_Trace_" + num2str(test_id) + ".txt"; % output from Leanred model for test traces
    outFileName = "excitableCells_" + num2str(learnedModel) + "_Trace_" + num2str(test_id) + ".txt"; % output from Leanred model for test traces
    outfile = fullfile(current_dir, outputTrace_path, outFileName); 
    
    %% Putting the Warning Off 
    warning('off','all'); 

    %% Load the model  
    mdl = model;
    load_system(mdl); 
    
    format shortG; 
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
    
    %Write the simulation result to the txt file 
    result_matrix = [t, y( : , 1)]; 
    result_filename = outfile;
    writematrix(result_matrix, result_filename, 'Delimiter', 'tab');     
    
end

% Close the Simulink model without saving
close_system('cellModel_64', 0);
