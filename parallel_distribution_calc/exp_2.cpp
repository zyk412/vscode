#include <mpi.h>
#include <iostream>  // C++ 推荐的标准输入输出库
#include <cstdlib>

#define N 500

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // --- 第一步：计算分配方案 ---
    // 修改点 1：C++ 中推荐使用 new 来分配动态数组，安全且无需强制类型转换
    int *sendcounts = new int[size];
    int *displs = new int[size];
    int *y_counts = new int[size];
    int *y_displs = new int[size];

    int sum = 0;
    for (int i = 0; i < size; i++) {
        // 计算每个进程分多少行：基本行数 + 余数处理
        int rows = (N / size) + (i < (N % size) ? 1 : 0);
        
        y_counts[i] = rows;            // 结果向量 y 的元素个数
        y_displs[i] = sum;             // y 的偏移量
        
        sendcounts[i] = rows * N;      // 矩阵 A 的元素个数 (行数 * N)
        displs[i] = sum * N;           // A 的偏移量
        
        sum += rows;
    }

    int local_rows = y_counts[rank];
    double *A_local = new double[local_rows * N];
    double *x = new double[N];
    double *y_local = new double[local_rows];

    // 修改点 2：C++ 推荐使用 nullptr 代替 NULL
    double *A_full = nullptr;
    double *y_full = nullptr;

    if (rank == 0) {
        A_full = new double[N * N];
        y_full = new double[N];
        // 初始化数据
        for (int i = 0; i < N * N; i++) A_full[i] = 1.0;
        for (int i = 0; i < N; i++) x[i] = 1.0;
    }

    // --- 第二步：通信 ---
    // 1. 广播向量 x (所有人都要完整的 x)
    MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // 2. 散播矩阵 A (使用 Scatterv 处理不均匀情况)
    MPI_Scatterv(A_full, sendcounts, displs, MPI_DOUBLE, 
                 A_local, local_rows * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // --- 第三步：计算 ---
    // 修改点 3：增加 MPI_Barrier！保证所有进程都在这里等齐了，再一起开始计时，这样时间才准确！
    MPI_Barrier(MPI_COMM_WORLD); 
    double start_time = MPI_Wtime();
    
    for (int i = 0; i < local_rows; i++) {
        y_local[i] = 0.0;
        for (int j = 0; j < N; j++) {
            y_local[i] += A_local[i * N + j] * x[j];
        }
    }
    
    // 同理，计算完也等大家一下（可选，但推荐）
    MPI_Barrier(MPI_COMM_WORLD); 
    double end_time = MPI_Wtime();

    // --- 第四步：收集结果 ---
    // 使用 Gatherv 处理不均匀收集
    MPI_Gatherv(y_local, local_rows, MPI_DOUBLE, 
                y_full, y_counts, y_displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // --- 第五步：输出结果 ---
    if (rank == 0) {
        // 输出时用 N-1 代替写死的 499，以后就算把 N 改成 1000 也不用改这里的代码了
        printf("Size: %d, Time: %f s, y[0]=%f, y[%d]=%f\n", 
               size, end_time - start_time, y_full[0], N-1, y_full[N-1]);
               
        // 修改点 4：C++ 释放 new 分配的数组必须用 delete[]
        delete[] A_full; 
        delete[] y_full;
    }

    delete[] A_local; delete[] x; delete[] y_local;
    delete[] sendcounts; delete[] displs; delete[] y_counts; delete[] y_displs;
    
    MPI_Finalize();
    return 0;
}


/*
广播：由进程发送，所有进程（包含自身）均接受同样的消息
散播：由进程发送，所有进程（包含自身）均接受不同的消息
收集：所有进程（包含自身）发送不同的消息，汇总到一个进程
*/


/*
对于本次实验，相当于除线程 0 之外的每个进程分得矩阵的 m 行，并接收完整的矩阵
每个进程计算各自的向量乘积，由线程 0 收集结果，拼接后输出

矩阵行数为 2 的幂次，只是不需要写那个计算分配方案的循环，但 MPI_Scatter 这个搬运函数本身绝对不能省
*/




/*
终端操作：

# 1. 编译
mpicc main.c -o main

# 2. 运行并记录数据（记得加 oversubscribe 应对 2核限制）
mpirun --allow-run-as-root --oversubscribe -np 1 ./exp_2
mpirun --allow-run-as-root --oversubscribe -np 2 ./exp_2
mpirun --allow-run-as-root --oversubscribe -np 4 ./exp_2
mpirun --allow-run-as-root --oversubscribe -np 8 ./exp_2
mpirun --allow-run-as-root --oversubscribe -np 16 ./exp_2          
*/ 