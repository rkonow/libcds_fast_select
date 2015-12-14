cmake_minimum_required(VERSION 2.8)
project(libcds)
set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories(src/utils/)
include_directories(src/static/sequence/)
include_directories(src/static/permutation/)
include_directories(src/static/bitsequence/)
include_directories(src/static/mapper/)
include_directories(src/static/coders/)

set (SOURCES
"src/static/bitsequence/BitSequence.cpp"
"src/static/bitsequence/BitSequenceBuilderDArray.cpp"
"src/static/bitsequence/BitSequenceBuilderRG.cpp"
"src/static/bitsequence/BitSequenceBuilderRRR.cpp"
"src/static/bitsequence/BitSequenceBuilderSDArray.cpp"
"src/static/bitsequence/BitSequenceDArray.cpp"
"src/static/bitsequence/BitSequenceRG.cpp"
"src/static/bitsequence/BitSequenceRGK.cpp"
"src/static/bitsequence/BitSequenceRRR.cpp"
"src/static/bitsequence/BitSequenceSDArray.cpp"
"src/static/bitsequence/sdarraySadakane.cpp"
"src/static/bitsequence/TableOffsetRRR.cpp"
"src/static/coders/huff.cpp"
"src/static/coders/HuffmanCoder.cpp"
"src/static/mapper/Mapper.cpp"
"src/static/mapper/MapperCont.cpp"
"src/static/mapper/MapperNone.cpp"
"src/static/mapper/MapperRev.cpp"
"src/static/permutation/perm.cpp"
"src/static/permutation/Permutation.cpp"
"src/static/permutation/PermutationBuilderMRRR.cpp"
"src/static/permutation/PermutationBuilderWT.cpp"
"src/static/permutation/PermutationMRRR.cpp"
"src/static/permutation/PermutationWT.cpp"
"src/static/sequence/BitmapsSequence.cpp"
"src/static/sequence/Sequence.cpp"
"src/static/sequence/SequenceAlphPart.cpp"
"src/static/sequence/SequenceBuilderAlphPart.cpp"
"src/static/sequence/SequenceBuilderGMR.cpp"
"src/static/sequence/SequenceBuilderGMRChunk.cpp"
"src/static/sequence/SequenceBuilderStr.cpp"
"src/static/sequence/SequenceBuilderWaveletMatrix.cpp"
"src/static/sequence/SequenceBuilderWaveletTree.cpp"
"src/static/sequence/SequenceBuilderWaveletTreeNoptrs.cpp"
"src/static/sequence/SequenceBuilderWaveletTreeNoptrsS.cpp"
"src/static/sequence/SequenceGMR.cpp"
"src/static/sequence/SequenceGMRChunk.cpp"
"src/static/sequence/WaveletMatrix.cpp"
"src/static/sequence/WaveletTree.cpp"
"src/static/sequence/WaveletTreeNoptrs.cpp"
"src/static/sequence/WaveletTreeNoptrsS.cpp"
"src/static/sequence/wt_coder.cpp"
"src/static/sequence/wt_coder_binary.cpp"
"src/static/sequence/wt_coder_huff.cpp"
"src/static/sequence/wt_node.cpp"
"src/static/sequence/wt_node_internal.cpp"
"src/static/sequence/wt_node_leaf.cpp"
"src/utils/Array.cpp"
"src/utils/cppUtils.cpp"
"src/utils/cppUtils.h"
"src/utils/libcdsBitString.cpp"
"src/utils/timing.cpp"

)


add_library(cds STATIC ${SOURCES})
target_include_directories (cds PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
install(TARGETS cds DESTINATION lib)



