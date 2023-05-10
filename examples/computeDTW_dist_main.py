#  This script file should be executed from HybridLearner/build folder

import csv
import os

from ball.BeforeAnnotation.compute_cost import compute_cost_result as compute_distance_ball
from ball.AfterAnnotation.compute_cost import compute_cost_result as compute_distance_ball_type
from cell.BeforeAnnotation.compute_cost import compute_cost_result as compute_distance_cell
from cell.AfterAnnotation.compute_cost import compute_cost_result as compute_distance_cell_type
from engine.BeforeAnnotation.compute_cost import compute_cost_result as compute_distance_engine
from engine.AfterAnnotation.compute_cost import compute_cost_result as compute_distance_engine_type
from oscillator.BeforeAnnotation.compute_cost import compute_cost_result as compute_distance_oscillator
from oscillator.AfterAnnotation.compute_cost import compute_cost_result as compute_distance_oscillator_type
from twoTanks.BeforeAnnotation.compute_cost import compute_cost_result as compute_distance_twoTanks
from twoTanks.AfterAnnotation.compute_cost import compute_cost_result as compute_distance_twoTanks_type


# define the filename for the output CSV file
filename = '../results/summary_results.csv'

total_training_traces = 64
total_test_traces = 32
try:
    # open the output CSV file and write the results
    with open(filename, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['Benchmark', 'Measure', 'W/o-Type:Output-1', 'W/o-Type:Output-2', 'Type:Output-1', 'Type:Output-2'])

        min_output1, max_output1, avg_output1, std_output1, min_output2, max_output2, avg_output2, std_output2 = compute_distance_ball(total_training_traces, total_test_traces)
        min_output1_type, max_output1_type, avg_output1_type, std_output1_type, min_output2_type, max_output2_type, avg_output2_type, std_output2_type = compute_distance_ball_type(total_training_traces, total_test_traces)

        writer.writerow(['Ball','Minimum',min_output1,min_output2,min_output1_type,min_output2_type])
        writer.writerow(['Ball','Maximum',max_output1,max_output2,max_output1_type,max_output2_type])
        writer.writerow(['Ball','Average',avg_output1,avg_output2,avg_output1_type,avg_output2_type])
        writer.writerow(['Ball','Std',std_output1,std_output2,std_output1_type,std_output2_type])

        min_output1, max_output1, avg_output1, std_output1, min_output2, max_output2, avg_output2, std_output2 = compute_distance_twoTanks(total_training_traces, total_test_traces)
        min_output1_type, max_output1_type, avg_output1_type, std_output1_type, min_output2_type, max_output2_type, avg_output2_type, std_output2_type = compute_distance_twoTanks_type(total_training_traces, total_test_traces)

        writer.writerow(['Two-Tanks','Minimum',min_output1,min_output2,min_output1_type,min_output2_type])
        writer.writerow(['Two-Tanks','Maximum',max_output1,max_output2,max_output1_type,max_output2_type])
        writer.writerow(['Two-Tanks','Average',avg_output1,avg_output2,avg_output1_type,avg_output2_type])
        writer.writerow(['Two-Tanks','Std',std_output1,std_output2,std_output1_type,std_output2_type])

        min_output1, max_output1, avg_output1, std_output1, min_output2, max_output2, avg_output2, std_output2 = compute_distance_oscillator(total_training_traces, total_test_traces)
        min_output1_type, max_output1_type, avg_output1_type, std_output1_type, min_output2_type, max_output2_type, avg_output2_type, std_output2_type = compute_distance_oscillator_type(total_training_traces, total_test_traces)

        writer.writerow(['Oscillator','Minimum',min_output1,min_output2,min_output1_type,min_output2_type])
        writer.writerow(['Oscillator','Maximum',max_output1,max_output2,max_output1_type,max_output2_type])
        writer.writerow(['Oscillator','Average',avg_output1,avg_output2,avg_output1_type,avg_output2_type])
        writer.writerow(['Oscillator','Std',std_output1,std_output2,std_output1_type,std_output2_type])

        min_output1, max_output1, avg_output1, std_output1 = compute_distance_cell(total_training_traces, total_test_traces)
        min_output1_type, max_output1_type, avg_output1_type, std_output1_type = compute_distance_cell_type(total_training_traces, total_test_traces)

        writer.writerow(['Cells', 'Minimum', min_output1, "--", min_output1_type, "--"])
        writer.writerow(['Cells', 'Maximum', max_output1, "--", max_output1_type, "--"])
        writer.writerow(['Cells', 'Average', avg_output1, "--", avg_output1_type, "--"])
        writer.writerow(['Cells', 'Std', std_output1, "--", std_output1_type, "--"])

        min_output1, max_output1, avg_output1, std_output1 = compute_distance_engine(total_training_traces, total_test_traces)
        min_output1_type, max_output1_type, avg_output1_type, std_output1_type = compute_distance_engine_type(total_training_traces, total_test_traces)

        writer.writerow(['Engine', 'Minimum', min_output1, "--", min_output1_type, "--"])
        writer.writerow(['Engine', 'Maximum', max_output1, "--", max_output1_type, "--"])
        writer.writerow(['Engine', 'Average', avg_output1, "--", avg_output1_type, "--"])
        writer.writerow(['Engine', 'Std', std_output1, "--", std_output1_type, "--"])

finally:
    # close the file
    csvfile.close()


