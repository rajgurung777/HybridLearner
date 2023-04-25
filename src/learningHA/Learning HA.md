# Running BBC4CPS's learn-ha Engine
About the learn-ha Engine
-----------------------------------------------------
    The engine takes input a simulation trace(s) file (time serise data having 
    format {time_i, Var_input, Var_output}) obtained by simulation of the 
    model under learning. The tool learns a model of a hybrid automaton (HA).
    A sample of the command is show below:

**Example command:**

    ./BBC4CPS --engine learn-ha --simu-trace-file simu_Tank.txt --modes 10 --degree 1 --boundary-degree 1 --cluster-error-tol 0.1  --output-file twotanks2.txt  --variable-types 'x0=t1,x1=t1,x2=t1'
    
Mandatory Tool's arguments for learn-ha Engine
---------------------------------------------
The simulation trace file is supplied by using the option --simu-trace-file.
A higher approximate value as a desired number of modes is selected by the user using the option --modes, however our algorithm returns optimal number of modes or select the size supplied by the user (when the number of modes learned is higher then the desired modes, in this case modes having less data are dropped).

The option --degree is use to select the degree of the polynomial ODE and --boundary-degree is the degree of the polynomial guard equation.
The options --cluster-error-tol is a special parameters that takes in an epsilon value which is used in the algorithm control on the segmentation and clustering error tolerance. 
The options --output-file is use to print the learned HA model as a text file.
Finally, to help the learning algorithm in learning the jump reset equations, extra information (manual annotation) can be supplied that describes the behaviour of the variables. (Note: Here each column of the input time serise data indicate a variables, where x0 is the 2nd column, x1 the 3rd column, and so on. The 1st column being the time component of the user-supplied time serise data.). An example of the behaviour is:
        
        --variable-types 'x0=t1,x1=t1,x2=t1'
where all the variables x0, x1 and x2 have same behaviour indicated by the value 't1'.
The meaning and the value that can be assigned for each variable based on the jump behaviour are shown below:

| Type     |             Behaviour                    | 
| -------- | ---------------------------------------- |
| t1       | continuous and constant throughout       | 
| t2       | takes a possible value from {c1,...,cn}  | 
| t3       | random, Eg., piecewise constant          | 
| t4       | any arbitrary constant value             | 
| t5       | linear expression                        | 

