%% Script file for generating Programmatically Simulink Model!
bdclose all; 
sfnew bball0; 
rt = sfroot; 
ch = find(rt,'-isa','Stateflow.Chart'); 
set_param(bdroot, 'SolverType','Variable-step', 'StopTime', 'timeFinal', 'SolverName', 'ode45', 'MaxStep', 'timeStepMax'); 
ch.ActionLanguage = 'C'; 
ch.ChartUpdate = 'CONTINUOUS'; 
ch.EnableZeroCrossings = 0; 
ch.ExecuteAtInitialization = true; 
 
 
 %% Adding Locations or States with ODE 
loc1 = Stateflow.State(ch); 
loc1.Position = [30 30 90 60]; 
str = ['loc1', 10, ... 
 'du: ', 10, ... 
 '    x1_dot = -0.1094319 * x0 + 0.0006456 * x1 + 1.0065907 * x2 + -1.0208247 * 1;', 10, ...  
 '    x2_dot = 1.0766513 * x0 + -0.0004207 * x1 + -0.0043214 * x2 + 0.7165015 * 1;', 10, ...  
 'exit: ', 10, ... 
 '    x1_out = x1;', 10, ...  
 '    x2_out = x2;', 10, ...  
 ]; 
loc1.LabelString = str; 

 
 
 
 %% Adding Transition for each Locations or States 

 %%Transitions for Location loc1 
%% Transition to represent Invariants: Current fix is using Junction Connection to avoid inner Transitions 

 
%% Adding Loop Transition to represent Invariant Condition 
c1_0 = Stateflow.Junction(ch); 
c1_0.Position.Center = [20 0]; 
c1_0.Position.Radius = 10; 

ca1_0 = Stateflow.Transition(ch); 
ca1_0.Source = loc1; 
ca1_0.Destination = c1_0; 

cb1_0 = Stateflow.Transition(ch); 
cb1_0.Source = c1_0; 
cb1_0.Destination = loc1; 
cb1_0.LabelPosition = [20 10 31 26]; 
cb1_0.LabelString = '[1.0 * x0 + 0.06218485951721926 * x1 + 0.10545608685620408 * x2 + 10.652319707757878 * 1 <= 0.000000 + 0]{x1 = 0.0000000 * x0 + 1.0000000 * x1 + 0.0000000 * x2 + 0.000; x2 = -0.0008693 * x0 + -0.0097194 * x1 + -0.0055686 * x2 + 10.659; }'; 

 
%% Adding Loop Transition to represent Invariant Condition 
c1_1 = Stateflow.Junction(ch); 
c1_1.Position.Center = [10 0]; 
c1_1.Position.Radius = 10; 

ca1_1 = Stateflow.Transition(ch); 
ca1_1.Source = loc1; 
ca1_1.Destination = c1_1; 

cb1_1 = Stateflow.Transition(ch); 
cb1_1.Source = c1_1; 
cb1_1.Destination = loc1; 
cb1_1.LabelPosition = [10 10 31 16]; 
cb1_1.LabelString = '{x1 = x1; x2 = x2; }'; 

 
%% Default or Initial Transition 
init1 = Stateflow.Transition(ch); 
init1.Destination = loc1; 
init1.LabelString = '{x1 = a1; x2 = a2; }'; 
init1.DestinationOClock = 0; 
init1.SourceEndpoint = init1.DestinationEndpoint - [0 30]; 
init1.Midpoint = init1.DestinationEndpoint - [0 15]; 


 %% *** Variable Declaration Block **** 

 %% *** Input Variable Declaration **** 
x0_in  = Stateflow.Data(ch); 
x0_in.Name = 'x0'; 
x0_in.Scope = 'Input'; 
x0_in.Port = 1; 
x0_in.Props.Type.Method = 'Inherit'; 
x0_in.DataType = 'Inherit: Same as Simulink'; 
x0_in.UpdateMethod = 'Discrete'; 


 %% *** Output Variable Declaration **** 
x1_out  = Stateflow.Data(ch); 
x1_out.Name = 'x1_out'; 
x1_out.Scope = 'Output'; 
x1_out.Port = 1; 
x1_out.Props.Type.Method = 'Inherit'; 
x1_out.DataType = 'Inherit: Same as Simulink'; 
x1_out.UpdateMethod = 'Discrete'; 

x2_out  = Stateflow.Data(ch); 
x2_out.Name = 'x2_out'; 
x2_out.Scope = 'Output'; 
x2_out.Port = 2; 
x2_out.Props.Type.Method = 'Inherit'; 
x2_out.DataType = 'Inherit: Same as Simulink'; 
x2_out.UpdateMethod = 'Discrete'; 



 %% *** Local Variable Declaration **** 
x1 = Stateflow.Data(ch); 
x1.Name = 'x1'; 
x1.Scope = 'Local'; 
x1.UpdateMethod = 'Continuous'; 

x2 = Stateflow.Data(ch); 
x2.Name = 'x2'; 
x2.Scope = 'Local'; 
x2.UpdateMethod = 'Continuous'; 



 %% *** Parameter Variable Declaration **** 
a1 = Stateflow.Data(ch); 
a1.Name = 'a1'; 
a1.Scope = 'Parameter'; 
a1.Tunable = true; 
a1.Props.Type.Method = 'Inherit'; 
a1.DataType = 'Inherit: Same as Simulink'; 

a2 = Stateflow.Data(ch); 
a2.Name = 'a2'; 
a2.Scope = 'Parameter'; 
a2.Tunable = true; 
a2.Props.Type.Method = 'Inherit'; 
a2.DataType = 'Inherit: Same as Simulink'; 



chartOutSignal = get_param('bball0/Chart', 'PortHandles'); 



 %% *** Adding Input  components **** 
add_block('simulink/Sources/In1', 'bball0/x0In'); 
x0Input = get_param('bball0/x0In', 'PortHandles'); 
set_param('bball0/x0In', 'Port', '1'); 
set_param('bball0/x0In', 'SignalType', 'auto'); 
set_param('bball0/x0In', 'position', [-40, 18, 0, 33]); 

 
add_line('bball0', x0Input.Outport(1), chartOutSignal.Inport(1)); 

 



 %% *** Adding Output components **** 
add_block('simulink/Sinks/Out1', 'bball0/x1Out'); 
x1Output = get_param('bball0/x1Out', 'PortHandles'); 
set_param('bball0/x1Out', 'SignalName', 'x1Out'); 
set_param('bball0/x1Out', 'Port', '1'); 
set_param('bball0/x1Out', 'SignalType', 'auto'); 
set_param('bball0/x1Out', 'position', [140, 18, 180, 33]); 

 
add_line('bball0', chartOutSignal.Outport(1), x1Output.Inport(1)); 

 

add_block('simulink/Sinks/Out1', 'bball0/x2Out'); 
x2Output = get_param('bball0/x2Out', 'PortHandles'); 
set_param('bball0/x2Out', 'SignalName', 'x2Out'); 
set_param('bball0/x2Out', 'Port', '2'); 
set_param('bball0/x2Out', 'SignalType', 'auto'); 
set_param('bball0/x2Out', 'position', [140, 58, 180, 73]); 

 
add_line('bball0', chartOutSignal.Outport(2), x2Output.Inport(1)); 

 

add_block('simulink/Sinks/Out1', 'bball0/x0Out'); 
x0Output = get_param('bball0/x0Out', 'PortHandles'); 
set_param('bball0/x0Out', 'SignalName', 'x0Out'); 
set_param('bball0/x0Out', 'Port', '3'); 
set_param('bball0/x0Out', 'SignalType', 'auto'); 
set_param('bball0/x0Out', 'position', [140, 98, 180, 113]); 
add_line('bball0', x0Input.Outport(1), x0Output.Inport(1)); 

 



Simulink.BlockDiagram.arrangeSystem('bball0'); 
Simulink.BlockDiagram.arrangeSystem('bball0/Chart'); 


sfsave; 
sfclose; 
close_system; 
bdclose all; 
