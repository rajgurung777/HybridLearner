#!/bin/bash
# This file must be executed from the folder HybridLearner/build but before executing please perform the TODO below.

# TODO:
#  (1) Open a Terminal and start a MATLAB instance using the command:
#  matlab &
# (2) Then in the Command Window of MATLAB just started, type the command
#  matlab.engine.shareEngine
# This will save the time for starting MATLAB and Simulink for every experiment.


# Execute the shell script for learning the benchmark models
./run_results_main_learn_models.sh  # This took approximately 2 hours on Intel i9 CPU 2.4 GHz with 32 GB RAM
echo "Done Learning Models"

# Before executing this, we assume the script run_results_main_learn_models is already executed and models are learned and copied in the respective folders.
matlab -nodisplay -nosplash -r "cd('../examples'); run('run_main.m'); exit;"
echo "Done generating output Trajectories"

# Before executing this, we assume the scripts (1) run_results_main_learn_models and (2) run_main.m
# have already been excuted and models are learned and output trajectories are generated and copied in the respective folders.
python3 ../examples/computeDTW_dist_main.py
echo "Done creating summary_results.csv; DTW distances between learned and Test Trajectories"
