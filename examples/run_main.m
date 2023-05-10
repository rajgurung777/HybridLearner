%% This script file should be executed from HybridLearner/build folder

build_path = pwd();
path = build_path + "/" + "../examples/ball/BeforeAnnotation";
cd(path); 
call_run_ball;  %executing the script inside ball/BeforeAnnotation

path = build_path + "/" + "../examples/ball/AfterAnnotation";
cd(path); 
call_run_ball;  %executing the script inside ball/AfterAnnotation


path = build_path + "/" + "../examples/cell/BeforeAnnotation";
cd(path); 
call_run_cell;  %executing the script inside cell/BeforeAnnotation


path = build_path + "/" + "../examples/cell/AfterAnnotation";
cd(path); 
call_run_cell;  %executing the script inside cell/AfterAnnotation


path = build_path + "/" + "../examples/oscillator/BeforeAnnotation";
cd(path); 
call_run_oscillator;  %executing the script inside oscillator/BeforeAnnotation


path = build_path + "/" + "../examples/oscillator/AfterAnnotation";
cd(path); 
call_run_oscillator;  %executing the script inside oscillator/AfterAnnotation


path = build_path + "/" + "../examples/twoTanks/BeforeAnnotation";
cd(path); 
call_run_twoTanks;  %executing the script inside twoTanks/BeforeAnnotation


path = build_path + "/" + "../examples/twoTanks/AfterAnnotation";
cd(path); 
call_run_twoTanks;  %executing the script inside twoTanks/AfterAnnotation


path = build_path + "/" + "../examples/engine/BeforeAnnotation";
cd(path); 
call_run_engine;  %executing the script inside engine/BeforeAnnotation


path = build_path + "/" + "../examples/engine/AfterAnnotation";
cd(path); 
call_run_engine;  %executing the script inside engine/AfterAnnotation


