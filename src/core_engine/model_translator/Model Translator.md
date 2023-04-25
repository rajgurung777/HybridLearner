# Running BBC4CPS's txt2slx Engine
About the txt2slx Engine
-----------------------------------------------------
    The engine takes input a Text file (.txt) describing a hybrid automaton (whose format
    is described below) and creates a Simulink Model file (.slx) that represnts 
    the model described in the .txt file.
    In addition, the engine also creates a script file (.m) that can be directly 
    excuted in MatLab based on the parameters supplied along with the .txt file.
    The parameters are time-horizon for simulation, initial input bounds (and the initial
    state of the system/output variables) and information about the input variables.
    Input signals can be any one of the following types fixed-step/linear/spline or
    a full cycle sine-wave signal with a fixed amplitude and zero_offset values.

***** Text File Format *****
-------------------------------
    Line-1: #modes #number_of_Variables_in_ODE_section #transitions
    Line-2: Initial-mode #mode-id
    Line-3: mode #mode-id
    Line-4: inv:
    Line-5: invariant constraints 
    Line-6: ODE:
    Line-7: ODE on the first variable
    Line-8: ODE on the second variable etc (assume here only 2 variable)
    Line-9: Transition-ID #id-value
    Line-10: specific word Trans-Src-Dest followed by #src_mode-id => #dest_mode-id
             where #src_mode-id is the source mode ID and #dest_mode-id is the 
             destination mode ID.
    Line-11: guard:          
    Line-12: contain the guard constraints
    Line-13: reset:
    Line-14-15: the reset equations on the two variables.
    
    Note: the #number_of_Variables_in_ODE_section is the first line is the number of lines or variables in the ODE: section and we expect the reset equation to be of the same size.
    However, the declaration of the input and output variables is supplied to the tool using the tool's various arguments.
    
    
**Example 1: bball.txt**
    
	1 2 1
    Initial-mode 1
    mode 1
    inv:
    x >= 0.0 & u >= 2 & u <= 5
    ODE: 
    x' = v
    v' = -9.81 + 0.5 * u
    Transition-ID 0
    Trans-Src-Dest 1 => 1
    guard:
    x <= 0 && v <= 0
    reset:
    x' = x
    v' = -0.75 * v


**Example 2: twotanks.txt**
    
    3 3 3
Initial-mode 3
mode 1
inv:
x0 >= -0.0702790314869594 & x0 <= 0.0281109671949784 & x1 >= -0.991055212583803 & x1 <= 2.0882602943821 & x2 >= -0.47881749024704 & x2 <= 1.00193967245843
ODE: 
x0' = -0.0596536 * x0 + 0.0004300 * x1 + -0.0009066 * x2 + -0.0061878 * 1
x1' = 1.0 * x0 + -1.0 * x1 + -0.0 * x2 + 3.0 * 1
x2' = 1.0 * x0 + 1.0 * x1 + -0.0 * x2 + -0.0 * 1
mode 2
inv:
x0 >= -0.0685280466396983 & x0 <= 0.0331065933483445 & x1 >= -0.989982818320354 & x1 <= 1.16589037304741 & x2 >= -0.320147135671873 & x2 <= 0.258522818877488
ODE: 
x0' = -0.0559064 * x0 + 0.0002609 * x1 + -0.0023654 * x2 + -0.0054710 * 1
x1' = 1.0 * x0 + -1.0 * x1 + 0.0 * x2 + -2.0 * 1
x2' = 1.0 * x0 + 1.0 * x1 + -0.0 * x2 + 0.0 * 1
mode 3
inv:
x0 >= -0.0686577832324096 & x0 <= 0.0342052165273005 & x1 >= 0.600282996468782 & x1 <= 2.08410705563579 & x2 >= 0.0105478633896886 & x2 <= 1.0
ODE: 
x0' = -0.0637954 * x0 + -0.0023943 * x1 + 0.0020951 * x2 + -0.0034098 * 1
x1' = 1.0 * x0 + -1.0 * x1 + 0.0 * x2 + -2.0 * 1
x2' = 1.0 * x0 + 1.0 * x1 + -1.0 * x2 + -5.0 * 1
Transition-ID 0
Trans-Src-Dest 2 => 1
guard:
1.0000 * x0  + 258.6006 * x1  + 251.0599 * x2  + 410.2655 * 1 = 0
reset:
x0' = 1.0 * x0 + 0.0 * x1 + 0.0 * x2 + 0.0
x1' = 0.0 * x0 + 1.0 * x1 + 0.0 * x2 + 0.0
x2' = 0.0 * x0 + 0.0 * x1 + 1.0 * x2 + 0.0
Transition-ID 1
Trans-Src-Dest 1 => 3
guard:
1.0000 * x0  + -234.2342 * x1  + -491.3723 * x2  + 1281.3711 * 1 = 0
reset:
x0' = 1.0 * x0 + 0.0 * x1 + 0.0 * x2 + 0.0
x1' = 0.0 * x0 + 1.0 * x1 + 0.0 * x2 + 0.0
x2' = 0.0 * x0 + 0.0 * x1 + 1.0 * x2 + 0.0
Transition-ID 2
Trans-Src-Dest 3 => 2
guard:
1.0000 * x0  + 755.1168 * x1  + 995.0134 * x2  + -944.5154 * 1 = 0
reset:
x0' = 1.0 * x0 + 0.0 * x1 + 0.0 * x2 + 0.0
x1' = 0.0 * x0 + 1.0 * x1 + 0.0 * x2 + 0.0
x2' = 0.0 * x0 + 0.0 * x1 + 1.0 * x2 + 0.0

**Example command:**

    ./BBC4CPS --model-file twotanks.txt --variable-category "x0:input, x1:output, x2:output" --engine txt2slx --guard 1  --time-horizon 10 --sampling-time 0.001 --invariant 2 --initial-value "x0>=-0.1 & x0<=0.1 & x1>=1.2 & x1<=1.2 & x2>=1 & x2<=1" --precision-guard-range 0.5 --input-signal-type "x0=linear" --numberOf-control-points "x0=1"
    
Mandatory Tool's arguments for txt2slx Engine
---------------------------------------------
Currently, we ask the user to decide on the types of the variable as input and output. This can be done using the command line options --variable-category arg, where arg has the syntax: 
            
            "x0:input, x1:input, x2:output".

Other options used for generating a running script file for testing a simulation of the generated model are described with an example command below:
        
        ./BBC4CPS --model-file bball2.txt --variable-category "u:input, x:output, v:output" --engine txt2slx --guard 1 --time-horizon 10 --sampling-time 0.1 --invariant 1 --input-signal-type "u=sine-wave" --numberOf-control-points "u=3" --initial-value "u>=1 & u<=10 & x>=10.2 & x<=10.2 & v>=0 & v<=1" --precision-guard-range 0.1 --sine-wave-parameter "u={5,5}"
        
        
The option --guard takes the value either 0 meaning no change in the guard, or a 1  (default) meaning, equality modified into inequality (+/- epsilon). Epsilon value is supplied by the option --precision-guard-range.
The option --time-horizon is the total time for the simulation, --sampling-time is time-step of each sample of the simulation. 
The option --invariant is use to either include or exclude the invariants in the simulink model. Available values are:
0 (default): include input and output variables in the invariant
1: include only output variables in the invariant
2: remove the invariant.
The initial value for the simulation can be provided using the option --initial-value . At the moment the values are supplied using closed bounded constraints, however, the operator "=" can also be used.
The options --input-signal-type, --numberOf-control-points and --sine-wave-parameter are special parameters to describe the input variables further. 
Available options for --input-signal-type are "fixed-step or linear or spline or sine-wave". 
For input signal of type sine-wave the argument --sine-wave-parameter provides the amplitude and zero_offset of the signal and the number of control points for the rest of the signal types are specified by --numberOf-control-points.
