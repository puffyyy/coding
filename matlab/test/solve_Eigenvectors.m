A = [3, -1, -2; 2, 0, -2; 2, -1, -1];
[X, B] = eig(A);
printmat(B);
printmat(X);
%求矩阵A的特征值和特征向量
%其中B的对角线元素是特征值,
%X的列是相应的特征向量

% g=sprintf('%d ',vec);
% fprintf('Eigenvalue: %s\n', g)
