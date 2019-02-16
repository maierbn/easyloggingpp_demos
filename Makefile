# Makefile for demos of easylogging++
# https://github.com/zuhd-org/easyloggingpp
#
CXXFLAGS=-std=c++17

easylogging.o:
	$(CXX) easylogging++.cc -c $(CXXFLAGS)

demo0: easylogging++.o
	$(CXX) demo0.cpp easylogging++.o $(CXXFLAGS) -o $@ 

demo1: easylogging++.o
	$(CXX) demo1.cpp $^ $(CXXFLAGS) -o $@ 

demo2: easylogging++.o
	$(CXX) demo2.cpp $^ $(CXXFLAGS) -o $@ 

demo3: easylogging++.o
	mpic++ initialize_logging.cpp demo3.cpp $^ $(CXXFLAGS) -o $@ 
	mpic++ initialize_logging.cpp demo3.cpp $^ $(CXXFLAGS) \
  -DNDEBUG -DELPP_DISABLE_DEBUG_LOGS -DELPP_DISABLE_VERBOSE_LOGS -DELPP_DISABLE_TRACE_LOGS -o $@_release 

demo4: easylogging++.o
	mpic++ initialize_logging.cpp demo4.cpp $^ $(CXXFLAGS) -o $@ 
	mpic++ initialize_logging.cpp demo4.cpp $^ $(CXXFLAGS) \
  -DNDEBUG -DELPP_DISABLE_DEBUG_LOGS -DELPP_DISABLE_VERBOSE_LOGS -DELPP_DISABLE_TRACE_LOGS -o $@_release 

demo5: easylogging++.o
	mpic++ initialize_logging.cpp demo5.cpp $^ $(CXXFLAGS) -o $@ 

demo6:
	mpic++ initialize_logging.cpp demo6.cpp easylogging++.cc -DELPP_FEATURE_PERFORMANCE_TRACKING $^ $(CXXFLAGS) -o $@ 
	mpic++ initialize_logging.cpp demo6.cpp easylogging++.cc $(CXXFLAGS) \
  -DNDEBUG -DELPP_DISABLE_DEBUG_LOGS -DELPP_DISABLE_VERBOSE_LOGS -DELPP_DISABLE_TRACE_LOGS -DELPP_FEATURE_PERFORMANCE_TRACKING -o $@_release 

demo7: easylogging++.o
	mpic++ initialize_logging.cpp demo7.cpp $^ $(CXXFLAGS) -o $@ 

demox:
	mpic++ demox.cpp easylogging++.cc $(CXXFLAGS) -o $@ 


clean:
	rm -f demo0 demo1 demo2 demo3 demo3_release demo4 demo4_release demo5 demo6 demo6_release demo7 demox *.log
