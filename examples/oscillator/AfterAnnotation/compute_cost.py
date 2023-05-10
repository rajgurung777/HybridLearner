import numpy as np
import pandas as pd
import sys
from sklearn.metrics import mean_squared_error

from scipy.spatial.distance import euclidean
from fastdtw import fastdtw     #https://pypi.org/project/fastdtw/



def compute_correlation(path, signal1, signal2):
    '''
    Now works on only a single output variable
    :param path:
    :param signal1: is an array of one dimensional
    :param signal2: is an array of one dimensional
    :return: Returns the correlation and maximum deviation on the signal value
    '''

    path1 = np.array(path)
    # print("type=", type(path1))
    # print("len of path=", len(path), "    len of path1=", len(path1))
    M1 = []
    for id in path1[:, 0]:
        M1.append(signal1[id])
    M2 = []
    for id in path1[:, 1]:
        M2.append(signal2[id])
    M1 = np.array(M1)
    M2 = np.array(M2)
    # print("len of M1 = ", len(M1))
    # print("len of M2 = ", len(M2))
    # print("M1 = ", M1)
    # print("M2 = ", M2)

    # ********* Compute maximum distance for measuring deviation *****
    difference_array = abs(M1 - M2)
    maximum_deviation = max(difference_array)
    # print('difference_array =', difference_array)
    # print('maximum_deviation = ', maximum_deviation)
    # ********* Compute maximum distance for measuring deviation *****


    # ******** We use numpy correlation coefficient function ******
    corel_value = np.corrcoef(M1, M2, rowvar=False) # rowvar=False will consider column as variables and
                                                    # rows as observations for those variables. See document
    # offset = M1.shape[1]  # shape[1] gives the dimension of the signal
    offset = 1  # Now signal1 and signal2 is a 1-D array
    correl_per_variable_wise = np.diagonal(corel_value, offset)
    # print("correl_per_variable_wise=", correl_per_variable_wise)

    return correl_per_variable_wise, maximum_deviation


def compute_dtw_cost(file1, file2, inputVar_size, outputVar_size):

    total_column_size = 1 + inputVar_size + outputVar_size   # 1 for time column
    data1 = np.loadtxt(file1, dtype=float)
    data2 = np.loadtxt(file2, dtype=float)

    assert data1.shape[1] == data2.shape[1]     #dimension of the two files or data should be same.
    assert data1.shape[1] == total_column_size
    startFrom = 1 + inputVar_size   # time-column and inputVar_column to be excluded

    dist1=0
    dist2=0
    max_dev1=0
    max_dev2 = 0
    corr1=0
    corr2=0

    for i in range(startFrom, total_column_size):  # For each output variable compute DTW distance, maximum deviation and correlation
        # print("variable i=", i)
        signal1 = data1[:, i]
        signal2 = data2[:, i]
        dataSize = 5
        distance, path = fastdtw(signal1, signal2, radius=dataSize, dist=euclidean)
        correlValue, maximum_deviation = compute_correlation(path, signal1, signal2)
        if i == startFrom:      # First output variable: position
            dist1 = distance
            max_dev1 = maximum_deviation
            corr1 = correlValue

        if i == (startFrom+1):     # Second output variable: velocity
            dist2 = distance
            max_dev2 = maximum_deviation
            corr2 = correlValue

        # print("variable i=", i, " ,    Maximum Deviation =", maximum_deviation, " ,   DTW Distance = ", distance, "   and   correlation(output variables) = ", correlValue)

    return max_dev1, dist1, corr1, max_dev2, dist2, corr2

    # signal1 = data1[:, startFrom:total_column_size]
    # signal2 = data2[:, startFrom:total_column_size]
    # # dataSize = data1.shape[0]   # total number of rows or records
    # dataSize = 5
    # distance, path = fastdtw(signal1, signal2, radius=dataSize, dist=euclidean)
    #
    # correlValue = compute_correlation(path, signal1, signal2)
    # print("DTW Distance = ", distance, "   and   correlation(output variables) = ", correlValue)
    #
    # f = open("cost_computed.txt", "w")
    #
    # f.write(str(distance) + "\t")   # writing the DTW distance
    # for varID in range(0, len(correlValue)):    # writing correlation or diagonality for each output variable which is the signal-data used in fastdtw()
    #     f.write(str(correlValue[varID]) + "\t")
    # f.close()


def compute_cost_result(learned_model_with_traces, tot_traces):
    '''
    1) Read trajectories from the folder TestSet containing test trajectories, and
    2) Read trajectories from the folder testData_Output containing trajectories obtained by simulating the learned
    model using inputs same as for the trajectories in TestSet.
    3) Compute DTW distance between (1) and (2) above

    Note this python script is called from HyrbidLearner/build folder
    :return:
    '''

    # learned_model_with_traces = int(sys.argv[1])    # total number of training traces used to learn the model
    # tot_traces = int(sys.argv[2])    # total number of traces to test

    learnedModel_path = "../results/oscillator/AfterAnnotation/testData_Output/"  # running from build folder
    testFolder_path = "../examples/oscillator/TestSet/"
    csv_output_path = "../results/oscillator/AfterAnnotation/"

    # ****** writing results to a .csv file  ******
    outFile = csv_output_path + "oscillator" + "_traces_" + str(learned_model_with_traces) + ".csv"
    # if os.path.exists(outFile):
    #     os.remove(outFile)
    outputFile = open(outFile, "a")
    tableHeader = "Traces" + "\t" + "DTW_distance_x" + "\t" + "DTW_distance_y" + "\n"
    outputFile.write(tableHeader)

    benchmark_max_output1 = float('-inf')
    benchmark_min_output1 = float('inf')
    benchmark_max_output2 = float('-inf')
    benchmark_min_output2 = float('inf')
    total_output1 = 0.0
    total_output2 = 0.0
    values_output1 = []
    values_output2 = []

    for i in range(0, tot_traces):  # Testing traces

        file1 = testFolder_path + "oscillator_" + str(i+1) + ".csv" # Read the testdata folder containing test traces obtained by simulating the original model
        file2 = learnedModel_path + "oscillator_" + str(learned_model_with_traces) + "_Trace_" + str(i+1) + ".txt"  # Read the testData_Output folder containing the traces obtained by simulating the learned model

        # print("file1 = ", file1, "    and   file2 =", file2)

        # The format of the file1 and file2 is as follows: 1st column: time-value; 2nd column onwards: InputVariable's values followed by columns for OutputVariables's values
        # in the case of oscillator there is no input variables.
        inputVar_size = 0 # size of input variable   # int(sys.argv[3])
        outputVar_size = 2 # size of output variable  # int(sys.argv[4])
        # ************************************

        max_dev1, dist1, corr1, max_dev2, dist2, corr2 = compute_dtw_cost(file1, file2, inputVar_size, outputVar_size)

        values_output1.append(dist1)
        values_output2.append(dist2)
        total_output1 += dist1
        total_output2 += dist2

        if dist1 < benchmark_min_output1:
            benchmark_min_output1 = dist1
        if dist1 > benchmark_max_output1:
            benchmark_max_output1 = dist1

        if dist2 < benchmark_min_output2:
            benchmark_min_output2 = dist2
        if dist2 > benchmark_max_output2:
            benchmark_max_output2 = dist2

        tableData = str(i + 1) + "\t" + str(dist1) + "\t" + str(dist2) + "\n"
        outputFile.write(tableData)


    outputFile.close()
    benchmark_avg_output1 = total_output1 / tot_traces
    benchmark_avg_output2 = total_output2 / tot_traces
    benchmark_std_output1 = (sum([(x - benchmark_avg_output1)**2 for x in values_output1]) / (tot_traces - 1) )**0.5  # (tot_traces -1) is the formula used in LibreOffice's =STDEV
    benchmark_std_output2 = (sum([(x - benchmark_avg_output2)**2 for x in values_output2]) / (tot_traces - 1) )**0.5  # (tot_traces -1) is the formula used in LibreOffice's =STDEV

    return benchmark_min_output1, benchmark_max_output1, benchmark_avg_output1, benchmark_std_output1, benchmark_min_output2, benchmark_max_output2, benchmark_avg_output2, benchmark_std_output2



if __name__ == '__main__':
    learned_model_with_traces = int(sys.argv[1])  # total number of training traces used to learn the model
    tot_traces = int(sys.argv[2])  # total number of traces to test

    compute_cost_result(learned_model_with_traces, tot_traces)  # This function is executed
