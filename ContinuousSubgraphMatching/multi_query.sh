# Test Workflow
# This file was intended to run lsbench_x25, but it was too big for vtune.


# Testing Algo
# sj-tree, graphflow, turboflux, symbi, iedyn, parrallel_symbi
ALGORITHM=parrallel_symbi 

# Time
TIME_LIMIT=3600

  
# Graph
DATA_GRAPH=/data/sicheng/high_freq/data_graph/data.graph
INSERT_GRAPH=/data/sicheng/high_freq/data_graph/insertion.graph
QUERY_GRAPH_DIR=/data/sicheng/high_freq/query_graph/sparse_6

# write a test_dir array
test_dir=(/data/sicheng/high_freq/query_graph/sparse_6/Q_0)

# Get the file names from QUERY_GRAPH_DIR and set them to QUERY_GRAPH
for file in $QUERY_GRAPH_DIR/*
# for file in ${test_dir[@]}
do
    QUERY_GRAPH=$file
    # Extract just the last part of the path (Q_0)
    QUERY_GRAPH_NAME=$(basename $QUERY_GRAPH)
    
    echo $QUERY_GRAPH_NAME
    # Run
    sudo touch ./log/high_freq_${QUERY_GRAPH_NAME}.log
    sudo chmod 777 ./log/high_freq_${QUERY_GRAPH_NAME}.log
    sudo ./build/csm -a ${ALGORITHM} -d ${DATA_GRAPH} -u ${INSERT_GRAPH} -q ${QUERY_GRAPH} --time-limit ${TIME_LIMIT} > ./log/high_freq_${QUERY_GRAPH_NAME}.log
done

