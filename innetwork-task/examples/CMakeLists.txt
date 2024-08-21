build_lib_example(
  NAME innetwork-test
  SOURCE_FILES innetwork-test.cc
  LIBRARIES_TO_LINK
    ${libcore}
    ${libquic}
    ${libinternet}
    ${libinnetwork-task}
    ${libapplications}
    ${libflow-monitor}
    ${libpoint-to-point}
)