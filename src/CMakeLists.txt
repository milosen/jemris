list (APPEND CORE_SRC AnalyticCoil.cpp AnalyticCoil.h
  AnalyticGradPulse.cpp AnalyticGradPulse.h AnalyticPulseShape.cpp
  AnalyticPulseShape.h AnalyticRFPulse.cpp AnalyticRFPulse.h
  AtomicSequence.cpp AtomicSequence.h Attribute.cpp Attribute.h
  BinaryContext.cpp BinaryContext.h BinaryIO.h BinaryIO.cpp
  BiotSavartLoop.cpp BiotSavartLoop.h Bloch_McConnell_CV_Model.cpp
  Bloch_McConnell_CV_Model.h Bloch_CV_Model.cpp Bloch_CV_Model.h
  Coil.cpp Coil.h CoilArray.cpp CoilArray.h CoilPrototypeFactory.cpp
  CoilPrototypeFactory.h ConcatSequence.cpp ConcatSequence.h
  ConstantGradPulse.cpp ConstantGradPulse.h Container.cpp Container.h 
  ContainerSequence.cpp ContainerSequence.h DOMTreeErrorReporter.cpp
  DOMTreeErrorReporter.h Debug.h Declarations.h DelayAtomicSequence.cpp
  DelayAtomicSequence.h DynamicVariables.cpp DynamicVariables.h
  EddyPulse.cpp EddyPulse.h EmptyPulse.cpp EmptyPulse.h ExternalCoil.cpp
  ExternalCoil.h ExternalGradPulse.cpp ExternalGradPulse.h
  ExternalRFPulse.cpp ExternalRFPulse.h ExternalPulseData Event.h GaussianRFPulse.cpp
  GaussianRFPulse.h GradPulse.cpp GradPulse.h HardRFPulse.cpp
  HardRFPulse.h HDF5IO.cpp HDF5IO.h IdealCoil.cpp IdealCoil.h KSpace.h
  Microstructure.cpp Microstructure.h MicrostructureBoxes.cpp
  MicrostructureBoxes.h MicrostructureCrossingFiber.cpp
  MicrostructureCrossingFiber.h MicrostructureKissingFiber.cpp
  MicrostructureKissingFiber.h MicrostructureSingleFiber.cpp
  MicrostructureSingleFiber.h Module.cpp Module.h
  ModulePrototypeFactory.cpp ModulePrototypeFactory.h NDData.h
  OutputSequenceData.h OutputSequenceData.cpp Parameters.cpp Parameters.h 
  Prototype.cpp Prototype.h
  PrototypeFactory.cpp PrototypeFactory.h Pulse.cpp Pulse.h RFPulse.cpp
  RFPulse.h RepIter.cpp RepIter.h MultiPoolSample.cpp MultiPoolSample.h
  Sample.cpp Sample.h SampleReorderShuffle.cpp SampleReorderShuffle.h
  SampleReorderStrategyInterface.h SechRFPulse.cpp SechRFPulse.h
  Sequence.cpp Sequence.h SequenceTree.cpp SequenceTree.h Signal.cpp
  Signal.h SimpleIO.h SimpleIO.cpp Simulator.cpp Simulator.h
  SincRFPulse.cpp SincRFPulse.h SpiralGradPulse.cpp SpiralGradPulse.h
  StrX.cpp StrX.h TPOI.cpp TPOI.h Trajectory.cpp Trajectory.h
  Trajectory1D.cpp Trajectory1D.h TrajectoryDiffusion.cpp
  TrajectoryDiffusion.h TrajectoryEmpty.h TrajectoryInterface.cpp
  TrajectoryInterface.h TrajectoryMotion.cpp TrajectoryMotion.h
  TrajectoryFlow.cpp TrajectoryFlow.h
  TrajectoryT2s.cpp TrajectoryT2s.h TrapGradPulse.cpp TrapGradPulse.h
  TriangleGradPulse.cpp TriangleGradPulse.h TxRxPhase.cpp TxRxPhase.h
  World.cpp World.h XMLIO.cpp XMLIO.h config.h ginac_functions.h list.h
  list_c.h rng.cpp rng.h) 

# Those directories do not exist, right?
#include_directories (${PROJECT_SOURCE_DIR}/src/core
#  ${PROJECT_SOURCE_DIR}/src/matrix/io) 

if (LINUX)
  list (APPEND COMMON_LIBS dl)
endif()

list (APPEND COMMON_LIBS ${HDF5_CXX_LIBRARIES} ${Xerces_LIBRARY} ${GINAC_LIBRARIES} ${SUNDIALS_LIBRARIES})

add_library (core ${CORE_SRC})

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  target_link_libraries (core ${COMMON_LIBS} )
endif()
add_executable (jemris Model.h Model.cpp jemris.cpp)
target_link_libraries (jemris ${COMMON_LIBS} core) 

# Install the binary to bin
install (TARGETS jemris DESTINATION "bin")

add_executable (sanityck Model.h Model.cpp sanityck.cpp)
target_link_libraries (sanityck ${COMMON_LIBS} core) 

if (MPI_C_FOUND)
  add_executable (pjemris Mpi2Evolution.h
    Mpi2Evolution.cpp mpi_Model.h Model.h Model.cpp pjemris.cpp)
  target_link_libraries (pjemris core ${COMMON_LIBS}
	${MPI_C_LIBRARIES})  
  target_compile_definitions (pjemris PRIVATE PARALLEL)
  if (MPI_C_COMPILE_FLAGS)
    set_target_properties(pjemris PROPERTIES
      COMPILE_FLAGS "${MPI_COMPILE_FLAGS} -DHAVE_MPI_THREADS")
  else()
    set_target_properties(pjemris PROPERTIES
      COMPILE_FLAGS "-DHAVE_MPI_THREADS")
  endif()
  if(MPI_LINK_FLAGS)
    set_target_properties(pjemris PROPERTIES
      LINK_FLAGS "${MPI_LINK_FLAGS}")
  endif()
  install (TARGETS pjemris DESTINATION "bin")
endif()

# Install the examples and matlab GUIs
install (TARGETS jemris DESTINATION "bin")

add_test (
  NAME sequences
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/share/examples
  COMMAND sanityck . 1)
add_test (
  NAME signals 
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/share/examples
  COMMAND sanityck . 2)
add_test (
  NAME coils 
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/share/examples
  COMMAND sanityck . 3)
add_test (
  NAME pulseq_output 
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/share/examples
  COMMAND sanityck . 4)

if (MPI_FOUND)
   add_test(
     NAME mpi 
     WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/share
     COMMAND ${MPIEXEC} -np 3 ${PROJECT_BINARY_DIR}/src/pjemris examples/approved/mpi_simu.xml)
endif()
