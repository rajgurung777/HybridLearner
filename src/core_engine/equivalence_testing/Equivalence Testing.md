# Running BBC4CPS's equi-test Engine
About the equi-test Engine
-----------------------------------------------------
    The engine takes input two simulink model file (.slx or .mdl) describing a 
    hybrid automaton (whose format is described below) along with various parameters. 
    The tool display the two simulink model is either "Equivalent" OR "NOT Equivalent"
    based on comparing the simulation traces obtained out of the two models.
        
    Our tool, do not ask users any script file for running the .slx/.mdl file.
    The tool itself generates a script file to simulate the .slx/.mdl model with the 
    information provided about the input signals as described below.
    
    The information provided are time-horizon for simulation, initial input bounds
    (and the initial state of the system/output variables) and information about the 
    input variables.
    Input signals can be any one of the following types fixed-step/linear/spline or
    a full cycle sine-wave signal with a fixed amplitude and zero_offset values.

***** .Slx Format *****
-------------------------------
   In the .slx model, when it has input signal, the name of the inport should be assigned as "uIn" where 'u' is the input variable name and 'In' is a naming convension we set for all inport label.
Also, the total Outport is the number of output/Outport followed by the number of input/Inport (for each Inport an Outport is created and directly connected) in order.
Note: Although, in the .slx model we require Outport to be in the order as output variables followed by input variables but the result of simulation is always generated as a time serise data having format {time_i, Var_input, Var_output}.
A sample of the command to perform equivalent testing on two models twoTank.slx and twoTanks2.slx is show below:

**Example command:**

    ./BBC4CPS --engine equi-test --simulink-model-file "twoTank.slx twoTanks2.slx" --variable-category "u:input, x1:output, x2:output" --numberOf-control-points "u=2" --input-signal-type "u=linear"  --initial-value "u>=-0.1 & u<=0.1 & x1>=1.2 & x1<=1.5 & x2>=1 & x2<=1" --simu-init-size 1 --max-traces 1 --time-horizon 10 --sampling-time 0.001 --precision-equivalence 1.5
    
Mandatory Tool's arguments for equi-test Engine
---------------------------------------------
Currently, we ask the user to decide on the types of the variable as input and output. This can be done using the command line options --variable-category arg, where arg has the syntax: 
            
            "x0:input, x1:input, x2:output".

The option --time-horizon is the total time for the simulation, --sampling-time is time-step of each sample of the simulation. 
The initial value for the simulation can be provided using the option --initial-value . At the moment the values are supplied using closed bounded constraints, however, the operator "=" can also be used.
The options --input-signal-type, --numberOf-control-points and --sine-wave-parameter are special parameters to describe the input variables further. 
Available options for --input-signal-type are "fixed-step or linear or spline or sine-wave". 
For input signal of type sine-wave the argument --sine-wave-parameter provides the amplitude and zero_offset of the signal and the number of control points for the rest of the signal types are specified by --numberOf-control-points.
The total number of simulation traces to be generated for comparison is provided by the option --simu-init-size and/or --max-traces (which ever is higher) and the precision of comparison is given by the option --precision-equivalence.

