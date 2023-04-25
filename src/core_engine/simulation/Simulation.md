# Running BBC4CPS's simu Engine
About the simu Engine
-----------------------------------------------------
    The engine takes input a simulink model file (.slx or .mdl) describing a 
    hybrid automaton (whose format is described below) along with various 
    parameters. The result of simulation is dumped into an output file specified
    by the argument using the option --output-file.
    
    Our simu engine, do not ask users any script file for running the .slx/.mdl file.
    The tool itself generates a script file to simulate the .slx/.mdl model with the 
    information provided about the input signals as described below.
    
    The information provided are time-horizon for simulation, initial input bounds (and the initial
    state of the system/output variables) and information about the input variables.
    Input signals can be any one of the following types fixed-step/linear/spline or
    a full cycle sine-wave signal with a fixed amplitude and zero_offset values.

***** .Slx Format *****
-------------------------------
   In the .slx model, when it has input signal, the name of the inport should be assigned as "uIn" where 'u' is the input variable name and 'In' is a naming convension we set for all inport label.
Also, the total Outport is the number of output/Outport followed by the number of input/Inport (for each Inport an Outport is created and directly connected) in order.
Note: Although, in the .slx model we require Outport to be in the order as output variables followed by input variables but the result of simulation is always generated as a time serise data having format {time_i, Var_input, Var_output}.
A sample of the command to perform simulation on the model twoTank.slx is show below:

**Example command:**

    ./BBC4CPS --engine simu --simulink-model-file twoTank.slx --simu-init-size 3 --variable-category "u:input, x1:output, x2:output" --numberOf-control-points "u=2" --input-signal-type "u=linear"  --initial-value "u>=-0.1 & u<=0.1 & x1>=1.2 & x1<=1.5 & x2>=1 & x2<=1" --time-horizon 10 --sampling-time 0.001 --output-file Tank.txt
    
Mandatory Tool's arguments for simu Engine
---------------------------------------------
Currently, we ask the user to decide on the types of the variable as input and output. This can be done using the command line options --variable-category arg, where arg has the syntax: 
            
            "x0:input, x1:input, x2:output".

The option --time-horizon is the total time for the simulation, --sampling-time is time-step of each sample of the simulation. 
The initial value for the simulation can be provided using the option --initial-value . At the moment the values are supplied using closed bounded constraints, however, the operator "=" can also be used.
The options --input-signal-type, --numberOf-control-points and --sine-wave-parameter are special parameters to describe the input variables further. 
Available options for --input-signal-type are "fixed-step or linear or spline or sine-wave". 
For input signal of type sine-wave the argument --sine-wave-parameter provides the amplitude and zero_offset of the signal and the number of control points for the rest of the signal types are specified by --numberOf-control-points.
The total number of simulation traces to be generated is provided by the option --simu-init-size. Finally, the option (--output-file abc.txt) is used to generate the trace file (time serise data) having the name simu_abc.txt, where simu_ is prefix with the output-file argument (a copy of this file can also be obtained by the name tmp_simu_abc.txt).
