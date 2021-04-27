

%read csv file
Table_info = readtable('info.csv');
Table_info.fest_name(:,1);

% table2struct(Table_info) struct array
% table2struct(Table_info,'ToScalar',true) struct  contains array