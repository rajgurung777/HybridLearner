function [t, y] = simple_filter(t, y, timeFinal, new_timeStep)
    tstep=0;
    seq_index=1;
    totalSamples = timeFinal / new_timeStep + 1;
    [rsize, csize] = size(y);
    t_temp1 = zeros(totalSamples, 1);
    y_temp1 = zeros(totalSamples, csize);
    firstFound = 1;
    for i = 1:rsize     %rsize is the total rows of y or y_temp
        diffVal = t(i) - tstep;     %initially time-step will be >= 0
        if (diffVal >= 0)
            firstFound = 1;
        end

        if (diffVal >= 0 && firstFound == 1)  %1st value that matches, i.e., positive value
            t_temp1(seq_index) = t(i);
            for j = 1:csize     %csize is the total columns of y or y_temp, i.e., for each variables
                y_temp1(seq_index, j) = y(i, j);
            end
            seq_index = seq_index + 1;
            tstep = tstep + new_timeStep;
            firstFound = 0;
        end
    end
    t = t_temp1;
    y = y_temp1;
end
