AFC model need to separately execute the initial setup to load values in the workspace


%% initial parameter as it is in Breach Tool
fuel_inj_tol = 1.0;  %fule injection actuator error factor, c25
MAF_sensor_tol = 1.0; %MAF sensor error factor, c23
AF_sensor_tol = 1.0;  %A/F sensor error factor, c24
pump_tol = 1.;
kappa_tol=1;   
tau_ww_tol=1;
fault_time=60;  % 60 in STalario, 50 in Breach. Time to introduce sensor failure (sec)
kp = 0.04;
ki = 0.14;