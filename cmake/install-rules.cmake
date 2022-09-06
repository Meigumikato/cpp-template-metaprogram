install(
    TARGETS cpp-template-metaprogram_exe
    RUNTIME COMPONENT cpp-template-metaprogram_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
