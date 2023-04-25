import numpy as np
import pandas as pd
import sys
from sklearn.metrics import mean_squared_error

from scipy.spatial.distance import euclidean
from fastdtw import fastdtw     #https://pypi.org/project/fastdtw/


# This function takes two time series files and does the following:
# 1) All data in every column are first normalized to [0,1]
# 2) Next for each column/variable's values in the corresponding files, it computes
#	a) RMSE, b) Absolute Difference and c) Average Absolute Difference
# 3) 	Finally, it writes only the (c) Average Absolute Difference in a output file named "cost_computed.txt"
# The formula for (c) Average Absolute Difference is given by Equation (4) in paper "A Passive Online Technique for Learning Hybrid Automata from Input/Output Traces" by Iman Saberi, Fathiyeh Faghih and Farzad Sobhi Bavil. arXiv, Jan 2021 

def compute_cost():
    n = len(sys.argv)

    # print("Total arguments passed:", n)
    # print("\nName of Python script: ", sys.argv[0])
    # print("Input Data Filename: ", sys.argv[1])
    # print("Output Data Filename: ", sys.argv[2])
    # print("Variable ID: ", sys.argv[3])
    # print("\n")
    file1 = sys.argv[1]
    file2 = sys.argv[2]
    # varID = 3  # int(sys.argv[3])

    data1 = np.loadtxt(file1, dtype=float)
    data2 = np.loadtxt(file2, dtype=float)

    # for i in range(0, data1.shape[1]):
    # 	min_val = np.min(data1[:, i])
    # 	max_val = np.max(data1[:, i])
    # 	zeroVal = max_val - min_val
    # 	print("zeroVal=", zeroVal)
    # 	if zeroVal == 0.0:		#this will result in divide by zero
    # 		data1[:, i] = 0	# this is normalized to zero can also be all 1
    # 	else:
    # 		data1[:, i] = (data1[:, i] - np.min(data1[:, i])) / (np.max(data1[:, i]) - np.min(data1[:, i]))
    #
    # print(data2)
    # for i in range(0, data2.shape[1]):
    # 	min_val = np.min(data2[:, i])
    # 	max_val = np.max(data2[:, i])
    # 	zeroVal = max_val - min_val
    # 	print("zeroVal=", zeroVal)
    # 	if zeroVal == 0.0:		#this will result in divide by zero
    # 		data2[:, i] = 0	# this is normalized to zero can also be all 1
    # 	else:
    # 		data2[:, i] = (data2[:, i] - np.min(data2[:, i])) / (np.max(data2[:, i]) - np.min(data2[:, i]))
    # print("data2 after Normalization")
    # print(data2)
    f = open("cost_computed.txt", "w")
    diff_value = [None] * data1.shape[1]
    data1_length = data1.shape[0]
    data2_length = data2.shape[0]
    min_length = data1_length
    if data2_length < data1_length:
        min_length = data2_length
    for varID in range(0, data1.shape[1]):
        min_val = np.min(data1[0:min_length, varID])
        max_val = np.max(data1[0:min_length, varID])
        zeroVal = max_val - min_val
        # print("zeroVal=", zeroVal)
        if zeroVal == 0.0:  # this will result in divide by zero
            data1[0:min_length, varID] = 0  # this is normalized to zero can also be all 1
        else:
            data1[0:min_length, varID] = (data1[0:min_length, varID] - np.min(data1[0:min_length, varID])) / (
                        np.max(data1[0:min_length, varID]) - np.min(data1[0:min_length, varID]))
        # print("data1 after Normalization")
        # print(data1)

        min_val = np.min(data2[0:min_length, varID])
        max_val = np.max(data2[0:min_length, varID])
        zeroVal = max_val - min_val
        # print("zeroVal=", zeroVal)
        if zeroVal == 0.0:  # this will result in divide by zero
            data2[0:min_length, varID] = 0  # this is normalized to zero can also be all 1
        else:
            data2[0:min_length, varID] = (data2[0:min_length, varID] - np.min(data2[0:min_length, varID])) / (
                        np.max(data2[0:min_length, varID]) - np.min(data2[0:min_length, varID]))
        # print("data2 after Normalization")
        # print(data2)


        rmse = np.sqrt(mean_squared_error(data1[0:min_length, varID], data2[0:min_length, varID]))
        # print("rmse is ", rmse)

        absolute_difference = np.sum(data1[0:min_length, varID] - data2[0:min_length, varID])
        # print("absolute_difference is ", absolute_difference)

        denominator = np.sum(data2[0:min_length, varID])
        if denominator == 0.0:
            diff_value[varID] = 0.0
        else:
            diff_value[varID] = np.sum(data1[0:min_length, varID] - data2[0:min_length, varID]) / np.sum(data2[0:min_length, varID])

        # print("Average of the absolute distance =", diff_value[varID])
        f.write(str(diff_value[varID]) + "\t")

    f.close()


def compute_correlation(path, signal1, signal2):
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

    # ******** We use numpy correlation coefficient function ******
    corel_value = np.corrcoef(M1, M2, rowvar=False) # rowvar=False will consider column as variables and
                                                    # rows as observations for those variables. See document
    offset = M1.shape[1]  # shape[1] gives the dimension of the signal
    correl_per_variable_wise = np.diagonal(corel_value, offset)
    # print("correl_per_variable_wise=", correl_per_variable_wise)

    return correl_per_variable_wise
    # correlation_value = min(correl_per_variable_wise)
    # # print("min correlation value =", correlation_value)
    # # *************************************************************
    # return correlation_value

def compute_dtw_cost():
    n = len(sys.argv)

    # print("Total arguments passed:", n)
    # print("\nName of Python script: ", sys.argv[0])
    # print("Input Data Filename: ", sys.argv[1])
    # print("Output Data Filename: ", sys.argv[2])
    # print("Variable ID: ", sys.argv[3])
    # print("\n")

    # ************************************
    file1 = sys.argv[1]
    file2 = sys.argv[2]
    # file1 = "original_t1.txt"
    # file2 = "learned_t1.txt"
    # The format of the file1 and file2 is as follows: 1st column: time-value; 2nd column onwards: InputVariable's values followed by columns for OutputVariables's values
    inputVar_size = int(sys.argv[3])   # 1 #
    outputVar_size = int(sys.argv[4])  #  2 #
    # ************************************


    total_column_size = 1 + inputVar_size + outputVar_size   # 1 for time column
    data1 = np.loadtxt(file1, dtype=float)
    data2 = np.loadtxt(file2, dtype=float)

    assert data1.shape[1] == data2.shape[1]     #dimension of the two files or data should be same.
    assert data1.shape[1] == total_column_size
    startFrom = 1 + inputVar_size   # time-column and inputVar_column to be excluded
    signal1 = data1[:, startFrom:total_column_size]
    signal2 = data2[:, startFrom:total_column_size]
    # print("signal1 ", signal1)
    # print("signal2 ", signal2)

    # dataSize = data1.shape[0]   # total number of rows or records
    dataSize = 5   #small dataSize is expected to increase speed
    distance, path = fastdtw(signal1, signal2, radius=dataSize, dist=euclidean)

    correlValue = compute_correlation(path, signal1, signal2)
    # print("distance between Signal1 and signal2 = ", distance, "   and   correlation(in order of output variables) = ", correlValue)

    f = open("cost_computed.txt", "w")

    f.write(str(distance) + "\t")   # writing the DTW distance
    for varID in range(0, len(correlValue)):    # writing correlation or diagonality for each output variable which is the signal-data used in fastdtw()
        f.write(str(correlValue[varID]) + "\t")
    f.close()


# compute_cost()
compute_dtw_cost()      # This function is executed
